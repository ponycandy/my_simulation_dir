#include "widframe.h"
#include "ui_widframe.h"
#include "WidFrameWorkActivator.h"
WidFrame::WidFrame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WidFrame)
{
//使用何种模式实现动态菜单？



    Menu_layout=new QVBoxLayout;
    over_all_layout=new QVBoxLayout;
    ui->setupUi(this);

    // 设置窗口名称
    setWindowTitle("Software");

    // 创建两个菜单栏
    QMenuBar *menuBar1 = new QMenuBar;

    // 添加第一行菜单
    QMenu *fileMenu = menuBar1->addMenu("File");
    QAction* exit_action=fileMenu->addAction("Exit");
    connect(exit_action,&QAction::triggered,this,&WidFrame::closeAll);
    QMenu *editMenu = menuBar1->addMenu("Edit");
    QMenu *viewMenu = menuBar1->addMenu("View");


    QWidget *Menuwidget = new QWidget;
    Menu_layout->addWidget(menuBar1);


    Menuwidget->setLayout(Menu_layout);
    Menuwidget->resize(800,50);

    over_all_layout->addWidget(Menuwidget);
    over_all_layout->addStretch();
    // 添加拉伸项占据剩余空间
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(over_all_layout);

    this->setCentralWidget(centralWidget);
    Add_Menu(menuBar1,"Top_menu_bar");

    QMenuBar *menuBar2 = new QMenuBar;

    // 添加第一行菜单
    menuBar2->addMenu("xxx");
    Add_Menu(menuBar2,"Top_bar_2");

    remove_Menu("Top_bar_2");
}

WidFrame::~WidFrame()
{
    delete ui;
}

void WidFrame::Add_Menu(QMenuBar *menu,QString menuname)
{
    remove_Menu(menuname);
    menuist.insert(menuname,menu);
    Menu_layout->addWidget(menu);
}

void WidFrame::remove_Menu(QString Menuname)
{
    if(menuist.contains(Menuname))
    {
        menuist.remove(Menuname);
        QMenuBar *wid=menuist.value(Menuname);
        wid->setParent(nullptr);
        Menu_layout->removeWidget(wid);
    }
    else
    {
    }

}

void WidFrame::closeAll()
{
    this->close();
    this->deleteLater();
}

