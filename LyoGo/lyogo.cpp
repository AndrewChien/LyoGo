#include "lyogo.h"
#include "ui_lyogo.h"
#include <windows.h>
#include <QTextEdit>
#include <QDockWidget>
#include <QScrollArea>
#include <QToolButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QtWidgets>
#include "drawer.cpp"
#include "widget.cpp"

const QString rsrcPath = ":/images";

lyogo::lyogo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::lyogo)
{
    ui->setupUi(this);
    setWindowTitle(tr("LyoGo围棋-游戏大厅"));	//设置主窗口的标题栏文字
    setWindowIcon(QIcon(":/images/chess02.ico"));
    loadActions();
    createToolBars();
    createLayout();
    createStatusBar();

    Sleep(1000);//用于飞屏加载延迟
}

lyogo::~lyogo()
{
    delete ui;
}

void lyogo::loadActions()
{
    //1.必须先加载action，后面才能使用
    qipunewAct = new QAction(QIcon(rsrcPath + "/filenew.png"), tr("新建棋谱(&N)"), this);
    qipunewAct->setShortcuts(QKeySequence::New);
    qipunewAct->setToolTip("新建棋谱");                   //设置工具栏按钮的提示文本
    qipunewAct->setStatusTip(tr("创建一个新棋谱"));     //设置状态栏提示文本
    connect(qipunewAct, SIGNAL(triggered()), this, SLOT(fileNewQipu()));
    qipuopenAct = new QAction(QIcon(rsrcPath + "/fileopen.png"), tr("打开棋谱(&O)..."), this);
    qipuopenAct->setShortcuts(QKeySequence::Open);
    qipuopenAct->setToolTip("打开棋谱");
    qipuopenAct->setStatusTip(tr("打开已存在的棋谱"));
    connect(qipuopenAct, SIGNAL(triggered()), this, SLOT(fileOpenQipu()));
    qipusaveAct = new QAction(QIcon(rsrcPath + "/filesave.png"), tr("保存棋谱(&S)"), this);
    qipusaveAct->setShortcuts(QKeySequence::Save);
    qipusaveAct->setToolTip("保存棋谱");
    qipusaveAct->setStatusTip(tr("将当前棋谱存盘"));
    connect(qipusaveAct, SIGNAL(triggered()), this, SLOT(fileSaveQipu()));
    qipusaveAsAct = new QAction(QIcon(rsrcPath + "/filesaveas.png"), tr("棋谱另存为(&A)..."), this);
    qipusaveAsAct->setShortcuts(QKeySequence::SaveAs);
    qipusaveAct->setToolTip("棋谱另存为");
    qipusaveAsAct->setStatusTip(tr("以一个新名字保存棋谱"));
    connect(qipusaveAsAct, SIGNAL(triggered()), this, SLOT(fileSaveAsQipu()));
    qipuprintAct = new QAction(QIcon(rsrcPath + "/fileprint.png"), tr("打印棋谱(&P)..."), this);
    qipuprintAct->setShortcuts(QKeySequence::Print);
    qipuprintAct->setToolTip("打印棋谱");
    qipuprintAct->setStatusTip(tr("打印棋谱"));
    connect(qipuprintAct, SIGNAL(triggered()), this, SLOT(filePrintQipu()));
    qipuprintPreviewAct = new QAction(QIcon(rsrcPath + "/fileprintview.png"), tr("棋谱打印预览..."), this);
    qipuprintPreviewAct->setStatusTip(tr("预览棋谱打印效果"));
    connect(qipuprintPreviewAct, SIGNAL(triggered()), this, SLOT(filePrintPreviewQipu()));

    duijunewAct = new QAction(QIcon(rsrcPath + "/filenew.png"), tr("新建对局(&N)"), this);
    duijunewAct->setShortcuts(QKeySequence::New);
    duijunewAct->setToolTip("新建对局");                   //设置工具栏按钮的提示文本
    duijunewAct->setStatusTip(tr("创建一个新对局"));     //设置状态栏提示文本
    connect(duijunewAct, SIGNAL(triggered()), this, SLOT(fileNewDuiju()));
    duijuopenAct = new QAction(QIcon(rsrcPath + "/fileopen.png"), tr("进入对局(&O)..."), this);
    duijuopenAct->setShortcuts(QKeySequence::Open);
    duijuopenAct->setToolTip("进入对局");
    duijuopenAct->setStatusTip(tr("进入一个已存在的对局"));
    connect(duijuopenAct, SIGNAL(triggered()), this, SLOT(fileOpenDuiju()));
    duijusaveAct = new QAction(QIcon(rsrcPath + "/filesave.png"), tr("保存对局(&S)"), this);
    duijusaveAct->setShortcuts(QKeySequence::Save);
    duijusaveAct->setToolTip("保存对局");
    duijusaveAct->setStatusTip(tr("将当前对局存盘"));
    connect(duijusaveAct, SIGNAL(triggered()), this, SLOT(fileSaveDuiju()));

    exitAct = new QAction(QIcon(rsrcPath + "/logout.png"), tr("退出(&X)"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("退出应用程序"));
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));           //不用自己实现
    aboutAct = new QAction(QIcon(rsrcPath + "/help.png"), tr("关于(&A)"), this);
    aboutAct->setStatusTip(tr("关于 Myself Word"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    aboutAuthorAct = new QAction(QIcon(rsrcPath + "/help.png"), tr("关于作者(&Q)"), this);
    aboutAuthorAct->setStatusTip(tr("关于作者"));
    connect(aboutAuthorAct, SIGNAL(triggered()), this, SLOT(aboutAuthor()));
}

void lyogo::createToolBars()
{
    //2.以下加载菜单栏
    fileMenu = menuBar()->addMenu(tr("文件(&F)"));
    fileMenu->addAction(qipunewAct);
    fileMenu->addAction(qipuopenAct);
    fileMenu->addAction(qipusaveAct);
    fileMenu->addAction(qipusaveAsAct);
    fileMenu->addAction(qipuprintAct);
    fileMenu->addAction(qipuprintPreviewAct);
    fileMenu->addSeparator();   //分隔线
    fileMenu->addAction(duijunewAct);
    fileMenu->addAction(duijuopenAct);
    fileMenu->addAction(duijusaveAct);
    fileMenu->addSeparator();   //分隔线
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("帮助(&H)"));
    helpMenu->addAction(aboutAct);
    helpMenu->addSeparator();   //分隔线
    helpMenu->addAction(aboutAuthorAct);

    //3.以下加载工具栏
    qipuToolBar = addToolBar(tr("棋谱"));
    qipuToolBar->addAction(qipunewAct);
    qipuToolBar->addAction(qipuopenAct);
    qipuToolBar->addAction(qipusaveAct);
    qipuToolBar->addAction(qipusaveAsAct);
    qipuToolBar->addSeparator();        //分隔条
    qipuToolBar->addAction(qipuprintAct);
    qipuToolBar->addAction(qipuprintPreviewAct);

    duijuToolBar = addToolBar(tr("对局"));
    duijuToolBar->addAction(duijunewAct);
    duijuToolBar->addAction(duijuopenAct);
    duijuToolBar->addAction(duijusaveAct);

    logoutToolBar = addToolBar(tr("其他"));
    logoutToolBar->addAction(exitAct);
}

void lyogo::ShowMatch(QString data)
{
    chatWidget = new Widget(0,data);
    chatWidget->setWindowTitle(data);
    chatWidget->show();
}

void lyogo::loadMessageArea()
{

}

void lyogo::fileNewQipu()
{

}

void lyogo::fileOpenQipu()
{

}

void lyogo::fileSaveQipu()
{

}

void lyogo::fileSaveAsQipu()
{

}

void lyogo::filePrintQipu()
{

}

void lyogo::filePrintPreviewQipu()
{

}

void lyogo::fileNewDuiju()
{

}

void lyogo::fileOpenDuiju()
{

}

void lyogo::fileSaveDuiju()
{

}

void lyogo::fileSaveAsDuiju()
{

}

void lyogo::filePrintDuiju()
{

}

void lyogo::filePrintPreviewDuiju()
{

}

void lyogo::about()
{
    QMessageBox::about(this, tr("关于本软件"), tr("这是一个类似于QQ游戏大厅，提供围棋棋谱管理并能进行网络对局的程序。"));
}

void lyogo::aboutAuthor()
{
    QMessageBox::about(this, tr("关于作者"), tr("作者：Lyo 2018-4-12"));
}

void lyogo::createStatusBar()
{
    statusBar()->showMessage(tr("就绪"));
}

void lyogo::createLayout()
{
    //左方
    QDockWidget *dockleft=new QDockWidget(tr("通讯录"),this);
    dockleft->setFeatures(QDockWidget::AllDockWidgetFeatures);//设置属性
    addDockWidget(Qt::LeftDockWidgetArea,dockleft);//设置区域位置
    Drawer *drawer=new Drawer();
    dockleft->setWidget(drawer);//将对象设置为子控件


    //中央控件-滚动区域
    QScrollArea *s = new QScrollArea(this);
    s->setGeometry(0, 0, 300, 300);//设置大小
    s->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//垂直滚动条不可见，只能通过鼠标滑动
    setCentralWidget(s);//将对象设为主窗口的中央窗体
    //窗体1，其父窗体为滚动区域
    QWidget *w = new QWidget(s);
    s->setWidget(w);//设置滚动区域的窗体
    w->setGeometry(0, 0, 600, 3000);//设置大小

    QGroupBox *groupBox=new QGroupBox(w);
    QGridLayout *layout=new QGridLayout(groupBox);
    layout->setMargin(20);                         //布局中各窗体的显示间距
    layout->setAlignment(Qt::AlignHCenter);        //布局中各窗体的显示位置
    //加入抽屉内的各个按钮
    //向布局中加入需要布局的控件
    //设定两列分别占用空间的比例，本例设定为1:3，即使对话框大小改变了，两列之间的宽度比依然保存不变
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,1);

    QString str = "1号桌,2号桌,3号桌,4号桌,5号桌,6号桌,7号桌,8号桌,9号桌,10号桌,11号桌,12号桌,13号桌,14号桌,15号桌,16号桌,17号桌";
    QStringList strList = str.split(",");
    QSignalMapper *pMapper = new QSignalMapper();
    int rowc=0;
    int colc=0;
    for (int i = 0; i < strList.length(); ++i)
    {
        //创建房间
        QToolButton *pBtn = new QToolButton;
        pBtn->setText(strList.at(i));
        pBtn->setStatusTip("进入"+strList.at(i));
        pBtn->setIcon(QPixmap(":/images/desk.jpg"));
        pBtn->setIconSize(QSize(150, 150));
        pBtn->setFixedSize(190, 220);
        pBtn->setAutoRaise(true);
        pBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        connect(pBtn, SIGNAL(clicked()), pMapper, SLOT(map()));//将无参数的clicked信号映射到QSignalMapper中的map函数
        pMapper->setMapping(pBtn, pBtn->text());//将单元信号的参数映射到QSignalMapper

        if(i%3==0)
        {
            rowc++;
            colc=0;
        }
        layout->addWidget(pBtn, rowc, colc);//房间的排列方式
        colc++;
    }
    connect(pMapper, SIGNAL(mapped(QString)), this, SLOT(ShowMatch(QString)));//将QSignalMapper中信号绑定至带参数的ShowMatch方法

    //下方
    QDockWidget *dockdown=new QDockWidget(tr("大厅聊天"),this);
    dockdown->setFixedHeight(200);
    //可移动
    dockdown->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dockdown->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    MessageForm *frm=new MessageForm();//聊天控件
    frm->resize(1200, 200);
    frm->ui->layoutWidget->setGeometry(QRect(0, 0, 1200, 200));
    dockdown->setWidget(frm);
    addDockWidget(Qt::BottomDockWidgetArea,dockdown);//设置区域位置

    //右上方
    QDockWidget *dockright1=new QDockWidget(tr("我的属性"),this);
    dockright1->setFeatures(QDockWidget::AllDockWidgetFeatures);
    SelfListTab *self=new SelfListTab("",dockright1);
//    QTextEdit *te2 =new QTextEdit();
//    te2->setText(tr("右上方区域"));
    dockright1->setWidget(self);
    addDockWidget(Qt::RightDockWidgetArea,dockright1);//设置区域位置

    //右下方
    QDockWidget *dockright2=new QDockWidget(tr("动态区域"),this);
    dockright2->setFeatures(QDockWidget::AllDockWidgetFeatures);//全部特性
    QTextEdit *te3 =new QTextEdit();
    te3->setText(tr("右下方区域"));
    dockright2->setWidget(te3);
    addDockWidget(Qt::RightDockWidgetArea,dockright2);//设置区域位置
}
