#include "testcuda.h"
#include "GL_3D/GL3Dcommon.h"
TestCuda::TestCuda()
{
    //    //初始化摄像机：
    //    // Create a ZED camera object
    //    zed=new sl::Camera ;

    //    // Open the camera
    //    sl::ERROR_CODE returned_state = zed->open();
    //    if (returned_state != sl::ERROR_CODE::SUCCESS) {
    //        std::cout << "Error " << returned_state << ", exit program.\n";
    //        return ;
    //    }

    //    // Get camera information (ZED serial number)
    //    auto camera_config = zed->getCameraInformation().camera_configuration;
    //    float image_aspect_ratio = camera_config.resolution.width / (1.f * camera_config.resolution.height);
    //    int requested_low_res_w = std::min(720, (int)camera_config.resolution.width);
    //    sl::Resolution ress(requested_low_res_w, requested_low_res_w / image_aspect_ratio);
    //    res=ress;
    //    //获取分辨率，为后面的空间开辟提供最小尺寸
    //    qDebug()<<"camera connected";
    //    //初始化图像存储容器，在GPU上开辟空间：
    //    matGPU_.alloc(res, sl::MAT_TYPE::F32_C4, sl::MEM::GPU);
    //    strm = zed->getCUDAStream();//strm是摄像机GPU内存拷贝的操作流
    //    //    sl::Mat point_clouds(res, sl::MAT_TYPE::F32_C4, sl::MEM::GPU);
    //    //    point_cloud=point_clouds;
}

void TestCuda::draw()
{
    //冷静，图片是能够显示的,if也是能够进去的
    //我们需要更小的子问题

    //    sl::RuntimeParameters runParameters;
    //    // Setting the depth confidence parameters
    //    runParameters.confidence_threshold = 50;
    //    runParameters.texture_confidence_threshold = 100;
    //    if (matGPU_.isInit()) {
    //        //retrieve之前要先grab！！我真是傻瓜
    //        if (zed->grab(runParameters) == sl::ERROR_CODE::SUCCESS)
    //        {
    //    m_animator->GLUseProgram(programID);
    //    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    //    //            sl::Mat point_cloud(res, sl::MAT_TYPE::F32_C4, sl::MEM::GPU);
    //    m_animator->GLBufferData(GL_ARRAY_BUFFER, sizeof(cubebuffer), cubebuffer, GL_STATIC_DRAW);

    //            //下面获取一帧图像到matGPU_中,但是好像不能够直接放matGPU_，得先放point_cloud里面
    //            //            zed->retrieveMeasure(point_cloud, sl::MEASURE::XYZRGBA, sl::MEM::GPU, res);
    //            zed->retrieveMeasure(point_cloud, sl::MEASURE::XYZRGBA, sl::MEM::GPU, res);
    //            //            printpointcloud(10,10,point_cloud);
    //            //            printpointcloud(20,20,point_cloud);
    //            matGPU_.setFrom(point_cloud, sl::COPY_TYPE::GPU_GPU);
    //            cv::Mat image_ocv = slMat2cvMat(matGPU_);
    //            cv::imshow("Image", image_ocv);
    //和initialization说的一样，将数据拷贝到xyzrgbaMappedBuf_里面，strm是摄像机的操作流
    //            checkError(cudaMemcpyAsync(xyzrgbaMappedBuf_, matGPU_.getPtr<sl::float4>(sl::MEM::GPU), numBytes_, cudaMemcpyDeviceToDevice, strm));
    //            cudaMemcpy(xyzrgbaMappedBuf_, matGPU_.getPtr<sl::float4>(sl::MEM::GPU), numBytes_, cudaMemcpyDeviceToDevice);

    //            cudaMemcpy(xyzrgbaMappedBuf_, cubebuffer, 36 * sizeof(float), cudaMemcpyHostToDevice);
    // qDebug()<<err;//一直成功，这里没有问题的
    // qDebug()<<xyzrgbaMappedBuf_[0]<<xyzrgbaMappedBuf_[1]<<xyzrgbaMappedBuf_[2];
    //下面都没啥好说的，都是openGL的东西
    //前两步不能够合并，原因倒是好理解：没办法retrieveMeasure到float*的对象中，reincast也不行
    //            m_animator->GLUseProgram(programID);
    //            m_animator->GLBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    //这里和一般的OpenGL绘图一样，指定此时送入的数据（数据实际上没有发生拷贝，是shader去找数据）

    //    m_animator->GLVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //    m_animator->GLEnableVertexAttribArray(0);
    //    //这一步。传递数据，我不太理解，理论上不是第一次就行了吗....
    //    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    //    m_animator->GLBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    //    //            cudaMemcpy(colorMappedBuf_, g_color_buffer_data, 36 * sizeof(float), cudaMemcpyHostToDevice);
    //    m_animator->GLVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //    m_animator->GLEnableVertexAttribArray(1);
    //            qDebug()<<matGPU_.getResolution().area();
    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    //    m_animator->GLBufferData(GL_ARRAY_BUFFER, 600 * sizeof(float), 0, GL_DYNAMIC_DRAW);
    m_animator->GLBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    //    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, 0);//一定要这一步
    //    checkError(cudaGraphicsGLRegisterBuffer(&bufferCudacolorID_, colorbuffer, cudaGraphicsRegisterFlagsNone));
    //    checkError(cudaGraphicsMapResources(1, &bufferCudacolorID_, 0));
    //    checkError(cudaGraphicsResourceGetMappedPointer((void**) &colorMappedBuf_, &numcolorBytes_, bufferCudacolorID_));
    m_animator->GLEnableVertexAttribArray(1);
    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, colorbuffer);

    m_animator->GLVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,0, nullptr);
    m_animator->GLDrawArrays(GL_POINTS, 0, 36);//绘图，不解释
    //下面这两步的含义：解除对vertexbuffer的绑定，解除对programID的使用
    //            m_animator->GLBindBuffer(GL_ARRAY_BUFFER, 0);
    //            m_animator->GLUseProgram(0);
    //        }
    //    }
}

void TestCuda::initialization()
{
    //这里开始写我们的cuda测试程序
    //下面这两行创建shader程序
    programID = m_animator->LoadShaders("vertexview.shader", "Fragcolorset.shader");
    //    programID = m_animator->LoadShaders("ZEDvertex.shader", "ZEDfrag.shader");
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
    //    m_animator->GLBufferData(GL_ARRAY_BUFFER, 600 * 4 * sizeof(float), 0, GL_DYNAMIC_DRAW);
    m_animator->GLBufferData(GL_ARRAY_BUFFER, sizeof(cubebuffer), cubebuffer, GL_STATIC_DRAW);

    //    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, 0);//一定要这一步
    //接着，绑定两个buffer:
    //    checkError(cudaGraphicsGLRegisterBuffer(&bufferCudaID_, vertexbuffer, cudaGraphicsRegisterFlagsNone));
    //上面这个是绑定buffer,但是实际上没有执行任何内存操作，仅仅是添加了一个flag，允许cuda访问vertexbuffer指向的内存
    //    checkError(cudaGraphicsMapResources(1, &bufferCudaID_, 0));
    //上面这个在GPU内存中给这个buffer开辟内存了
    //通过上面这两步骤，但是bufferCudaID_并不是指向GPU内存的指针，它更类似于一个flag
    //你可以简单的把bufferCudaID_理解为和VAO一样的东西：它必须要被创建，但是后面再也不会用到了
    //唯一会使用bufferCudaID_的地方就是cudaGraphicsMapResources和cudaGraphicsunMapResources
    //也就是只有程序开始和结束的时候会使用，所以，我们完全无视
    //我们需要通过下面这个函数获取指向GPU的指针：
    //    checkError(cudaGraphicsResourceGetMappedPointer((void**) &xyzrgbaMappedBuf_, &numBytes_, bufferCudaID_));
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
    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);


    m_animator->GLVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0, nullptr);
    //这里数据是4个一组送到shader里面

    m_animator->GLGenBuffers(1, &colorbuffer);
    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    //    m_animator->GLBufferData(GL_ARRAY_BUFFER, 600 * sizeof(float), 0, GL_DYNAMIC_DRAW);
    m_animator->GLBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    //    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, 0);//一定要这一步
    //    checkError(cudaGraphicsGLRegisterBuffer(&bufferCudacolorID_, colorbuffer, cudaGraphicsRegisterFlagsNone));
    //    checkError(cudaGraphicsMapResources(1, &bufferCudacolorID_, 0));
    //    checkError(cudaGraphicsResourceGetMappedPointer((void**) &colorMappedBuf_, &numcolorBytes_, bufferCudacolorID_));
    m_animator->GLEnableVertexAttribArray(1);
    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, colorbuffer);

    m_animator->GLVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,0, nullptr);

    //初始化model矩阵
    //我们这里不会修改它
    m_animator->GLUseProgram(programID);
    glm::mat4 Model = glm::mat4(1.0f);
    GLuint MatrixID = m_animator->GLGetUniformLocation(programID, "Modelmat");
    m_animator->GLUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Model[0][0]);
    //默认不运动的矩阵,draw里面好像不能够重新bind和buffer了
    //不存在的，主程序依然可以这么干
    //我感觉核心的错误就是必须在GLUseProgram(programID)后面追加Model矩阵
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
