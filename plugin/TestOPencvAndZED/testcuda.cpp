#include "testcuda.h"
#include "GL_3D/GL3Dcommon.h"
TestCuda::TestCuda()
{
    flag=2;
    //初始化摄像机：
    // Create a ZED camera object
    if(flag==0)
    {

        zed=new sl::Camera ;

        // Open the camera
        sl::ERROR_CODE returned_state = zed->open();
        if (returned_state != sl::ERROR_CODE::SUCCESS) {
            std::cout << "Error " << returned_state << ", exit program.\n";
            return ;
        }

        // Get camera information (ZED serial number)
        auto camera_config = zed->getCameraInformation().camera_configuration;
        float image_aspect_ratio = camera_config.resolution.width / (1.f * camera_config.resolution.height);
        int requested_low_res_w = std::min(720, (int)camera_config.resolution.width);
        sl::Resolution ress(requested_low_res_w, requested_low_res_w / image_aspect_ratio);
        res=ress;
        //获取分辨率，为后面的空间开辟提供最小尺寸
        qDebug()<<"camera connected";
        //初始化图像存储容器，在GPU上开辟空间：

        strm = zed->getCUDAStream();//strm是摄像机GPU内存拷贝的操作流
        //    sl::Mat point_clouds(res, sl::MAT_TYPE::F32_C4, sl::MEM::GPU);
        //    point_cloud=point_clouds;
    }
}

void TestCuda::draw()
{
    if(flag==0)
    {


        //冷静，图片是能够显示的,if也是能够进去的
        //我们需要更小的子问题
        sl::RuntimeParameters runParameters;
        // Setting the depth confidence parameters
        runParameters.confidence_threshold = 50;
        runParameters.texture_confidence_threshold = 100;
        if (matGPU_.isInit()) {
            //        //retrieve之前要先grab！！
            if (zed->grab(runParameters) == sl::ERROR_CODE::SUCCESS)
            {
//从这个摄像机到实际世界的xyz还有一个沿着z轴的旋转变化要做大概是沿着z轴做180度的旋转
                sl::Mat point_cloud(res, sl::MAT_TYPE::F32_C4, sl::MEM::GPU);
                //下面获取一帧图像到matGPU_中,但是好像不能够直接放matGPU_，得先放point_cloud里面
                //                sl::uchar1 op;
                sl::ERROR_CODE err= zed->retrieveMeasure(point_cloud, sl::MEASURE::XYZRGBA, sl::MEM::GPU, res);

                //                sl::ERROR_CODE err= zed->retrieveMeasure(point_cloud, sl::MEASURE::XYZRGBA, sl::MEM::GPU, res);
                matGPU_.setFrom(point_cloud, sl::COPY_TYPE::GPU_GPU,strm);
                //和initialization说的一样，将数据拷贝到xyzrgbaMappedBuf_里面，strm是摄像机的操作流

                //下面这一步有问题，sl::float4并不是一个float4指针，它是一个带有成员的类
                //因此内存空间不可能是连续的,核心在下面的拷贝函数，我不觉得这是正确的方法
                //问题在ZED不在cuda.这已经是一个难度极大的下降了的版本了
                //但是我们可能得不到任何能够帮助我们解决问题的资源了....

                checkError(cudaMemcpyAsync(xyzrgbaMappedBuf_, matGPU_.getPtr<sl::float4>(sl::MEM::GPU), numBytes_, cudaMemcpyDeviceToDevice, strm));
                //                checkError(cudaMemcpyAsync(cubebuffer_vec4_test, xyzrgbaMappedBuf_, numBytes_, cudaMemcpyDeviceToDevice, strm));

                //看了一下cudaMemcpy出来的东西，鉴定cubebuffer_vec4_test里面确实全部都是nan,或者大部分是nan
                //通过下面打印出来的结果，也是几乎都是nan
                //一个float数组从-XXX（初始值）变为nan，说明值确实被复制进去了
                //也就是说cuda确实有按照正确的顺序将pointcloud复制进去，sl::float4类型转化是没有问题的
                //接下来的可能问题有两个
                //一是openGL接收到NAN就死机（我们可以在flag=1里面试一下）,不是，NAN会跳过去
                //而是摄像机视觉范围不对，因为我们打印的值普遍在1000以上，所以应该重设视觉远端平面
                //同时视野里面大部分点是黑色的，我们应该设置背景为白色
                //成了！！！果然就是摄像机设置的不对，场景在背面呢！！
                //如何check sl::mat里面的东东呢
                //float4是vector!!
                //这里唯一多了的变量就是matGPU了
                //我们不确定它是不是在cuda上面
                //                sl::float4 point3D;//它并不等效于float!!
                //                int height=point_cloud.getHeight();
                //                int width=point_cloud.getWidth();
                //                for(int i=0;i<width;i++)
                //                {
                //                    for(int j=0;j<height;j++)
                //                    {
                //                        point_cloud.getValue(i,j,&point3D,sl::MEM::GPU);
                //                        float x = point3D.x;
                //                        float y = point3D.y;
                //                        float z = point3D.z;
                //                        float color = point3D.w;
                //                        if(x!=NAN || y!=NAN || z!=NAN || color!=NAN)
                //                        {
                //                            qDebug()<<"; x : "<<x<<"; y : "<<y<<"; z : "<<z<<"; color : "<<color;
                //                        }
                //                    }
                //                }

                //不用怀疑,matGPU_里面就是好多nan值
                //临时创建的pointcloud也是好多nan值
                //但是绝对是有正常数据的！并且不少，可以认为就是能用
                m_animator->GLDrawArrays(GL_POINTS, 0, matGPU_.getResolution().area());
                //不要被干扰,unbind其实不影响啥
            }
        }
    }
    if(flag==1)
    {
        cudaMemcpy(xyzrgbaMappedBuf_, cubebuffer_vec4, 12*4*3 * sizeof(float), cudaMemcpyHostToDevice);
        //        cudaMemcpy(cubebuffer_vec4_test, xyzrgbaMappedBuf_, 12*4*3 * sizeof(float), cudaMemcpyDeviceToHost);
        //  通过上面这一步，我们能够确认数据确实被拷贝到GPU里面了，cubebuffer_vec4_test一直是对的
        //因为能够拷贝回来
        //剩下的问题就是，为什么没有被openGL读取到了
        // Render from buffer object
        m_animator->GLDrawArrays(GL_POINTS, 0, 6);
        //这里的1是指送1批数据进去
        //在下面vertexattrib里面定义了一批数据是4个
        //所以这里写1就应该是送数组里面的四个数进去！！而不是一个数！
    }
    if(flag==2)
    {
        m_animator->GLDrawArrays(GL_POINTS, 0, 12*3*4);
    }
}

void TestCuda::initialization()
{
    if(flag==0)
    {
        m_animator->setbackgroundColor(1,1,1,1);
        m_animator->setCameraParms(0.1,15000,3000);
        //这里开始写我们的cuda测试程序
        //下面这两行创建shader程序
        programID = m_animator->LoadShaders("ZEDvertex.shader", "ZEDfrag.shader");
        //这里我们使用不同的shader，不然无法处理zed的mat(我们无法在CPU中iterate然后整理为新的矩阵)
        m_animator->SetPainterID(programID);

        //我们在头文件中已经创建了指向cudabuffer的指针，接下来需要将cudabuffer与
        //openGL的buffer绑定，也就是共享一片GPU储存

        m_animator->GLGenBuffers(1, &vertexbuffer);
        //创建buffer，注意，即使没有cuda,opengl创建的buffer也是在GPU内存上的
        //我们耗费的时间仅仅是从CPU拷贝vertex到GPU的过程上。
        m_animator->GLBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        //下面要赋予空间的时候，设置第二项输入为开辟的最大空间
        //只要大于等于可能输入的数据的尺寸就行（不要求一定等于）
        //设置第三项输入为0，意味着此时先不分配CPU上的内存
        //第四项输入指明为GL_DYNAMIC_DRAW，也就是说GPU上的内容会动态修改
        m_animator->GLBufferData(GL_ARRAY_BUFFER, res.area() * 4 * sizeof(float), 0, GL_DYNAMIC_DRAW);

        //    接着，绑定openGL和cudabuffer:
        //     cudaGLSetGLDevice(0);
        cudaGraphicsGLRegisterBuffer(&bufferCudaID_, vertexbuffer, cudaGraphicsRegisterFlagsNone);
        //上面这个是绑定buffer,但是实际上没有执行任何内存操作，仅仅是添加了一个flag，允许cuda访问vertexbuffer指向的内存
        cudaGraphicsMapResources(1, &bufferCudaID_);
        //上面这个在GPU内存中给这个buffer开辟内存了
        //通过上面这两步骤，但是bufferCudaID_并不是指向GPU内存的指针，它更类似于一个flag
        //你可以简单的把bufferCudaID_理解为和VAO一样的东西：它必须要被创建，但是后面再也不会用到了
        //唯一会使用bufferCudaID_的地方就是cudaGraphicsMapResources和cudaGraphicsunMapResources
        //也就是只有程序开始和结束的时候会使用，所以，我们完全无视
        //我们需要通过下面这个函数获取指向GPU的指针：
        cudaGraphicsResourceGetMappedPointer((void**) &xyzrgbaMappedBuf_, &numBytes_, bufferCudaID_);
        //上面这个函数xyzrgbaMappedBuf_和numBytes_是返回值，它们分别是指向GPU内存的指针和内存区域的大小
        //通过上面的步骤，我们只要向xyzrgbaMappedBuf_填充数据就可以实现向vertexbuffer中填充数据了
        //填充数据的方法是如下的：
        //cudaMemcpyAsync(xyzrgbaMappedBuf_,
        // matGPU_.getPtr<sl::float4>(sl::MEM::GPU), numBytes_, cudaMemcpyDeviceToDevice, strm)
        //上面这一步的解释：cudaMemcpyDeviceToDevice的意思是从GPU上的内存拷贝（共享）到GPu上
        //strm是标识符，类似flag的东东，这里粗略解释一下啥是cuda stream
        //一个GPU内存上的东西可以被多个进程操作，每个进程都分配一个stream
        //cuda按照stream来并行化操作，比如说如果一个stream是从摄像机拷贝数据到CUDA
        //内存上，并且我们在这个流的下面附加的操作是cudaMemcpyAsync
        //那么cuda核心就可以优化两个过程，让上流转移数据到CUDA刚完成一格的时候，后脚
        //拷贝就在这一格完成
        //所以，任何cuda上的操作都需要说明自己是依附于哪个stream的
        //然后头两个输入就是指针了，形式和CPU上的指针是一模一样的，没有区别（都是char*）
        //然后为什么用Async，这是为了不发生阻塞，可以直接回到主程序中，拷贝由GPU完成
        //接下来做的倒是和之前差不多，使能向shader传递数据的通道

        m_animator->GLEnableVertexAttribArray(0);
        m_animator->GLVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,0, nullptr);
        //这里数据是4个一组送到shader里面
        matGPU_.alloc(res, sl::MAT_TYPE::F32_C4, sl::MEM::GPU);


    }
    if(flag==1)
    {
        programID = m_animator->LoadShaders("ZEDvertex.shader", "ZEDfrag.shader");
        m_animator->SetPainterID(programID);
        m_animator->GLGenBuffers(1, &vbo);
        m_animator->GLBindBuffer(GL_ARRAY_BUFFER, vbo);
        m_animator->GLBufferData(GL_ARRAY_BUFFER, 12*4*3 * sizeof(float), 0, GL_DYNAMIC_DRAW);
        //数据拷贝经过检查没有问题，我很确定问题在下面这三行
        cudaGraphicsGLRegisterBuffer(&resource, vbo, cudaGraphicsRegisterFlagsNone);
        cudaGraphicsMapResources(1, &resource);
        cudaGraphicsResourceGetMappedPointer((void**)&xyzrgbaMappedBuf_, &numBytes_, resource);
        //老是忘记下面两行，这两行和gl::mat model一个德行！！
        //现在可以了，确认能够从cuda里面使用数据了
        m_animator->GLEnableVertexAttribArray(0);
        m_animator->GLVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,0, nullptr);
        //没办法，只能先留在这里，这一句话经常忘记...
        //只能希望以后做高级封装的时候别忘了
    }
    if(flag==2)
    {
        programID = m_animator->LoadShaders("ZEDvertex.shader", "ZEDfrag.shader");
        m_animator->SetPainterID(programID);

        m_animator->GLGenBuffers(1, &vbo);
        m_animator->GLBindBuffer(GL_ARRAY_BUFFER, vbo);
        m_animator->GLBufferData(GL_ARRAY_BUFFER,sizeof(cubebuffer_vec4), cubebuffer_vec4, GL_STATIC_DRAW);

        m_animator->GLEnableVertexAttribArray(0);
        m_animator->GLVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,0, nullptr);
    }
}

void TestCuda::printpointcloud(int i, int j, sl::Mat pointcloud)
{
    //    float4 point3D;
    //    // Get the 3D point cloud values for pixel (i, j)
    //    point_cloud.
    //    float x = point3D.x;
    //    float y = point3D.y;
    //    float z = point3D.z;
    //    float color = point3D.w;
    //    qDebug()<<"x: "<<x<<" y "<<y<<" z "<<z<<" w "<<color;
}

void TestCuda::checkError(cudaError_t err)
{

    if(err != cudaSuccess)
        std::cerr << "Error: (" << err << "): " << cudaGetErrorString(err) << std::endl;

}
