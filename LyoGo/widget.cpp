#include "widget.h"
#include "ui_widget.h"
#include <QTextEdit>
#include <QDockWidget>
#include <QUdpSocket>
#include <QHostInfo>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QNetworkInterface>
#include <QProcess>
#include <QFileDialog>
#include <QColorDialog>
#include <windows.h>
#include "messageform.cpp"

Widget::Widget(QWidget *parent,QString usrname) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/chess02.ico"));
    setFixedSize(1200,800);
    createLayout();
}

void Widget::paintEvent(QPaintEvent *event)
{
    //中间布局（棋盘区域）
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);// 反走样
    painter.drawPixmap(200,0,800,800, QPixmap(":/images/go03.jpg"));// 绘制图标
    //    painter.drawPixmap(300,100,50,50,QPixmap(":/images/black.png"));//背景不透明
    painter.setPen(QPen(QColor(0, 0, 0), 1));// 设置画笔黑线条、宽度1
    painter.setBrush(QColor(255, 255, 255));// 设置画刷颜色白
    //    painter.drawEllipse(QPointF(287, 87), 15, 15);//绘制圆长半径18宽半径18，位置300,100（0,0）

    //    painter.setBrush(QColor(0, 0, 0));// 设置画刷颜色黑
    painter.drawEllipse(QPointF(mousex, mousey), 15, 15);//（1,0）
}

void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    mousex=e->x();
    mousey=e->y();
    this->repaint();
}

void Widget::createLayout()
{
    //左方布局
    left=new QWidget(this);
    left->setGeometry(0,0,200,800);//对于父控件的绝对定位
    MessageForm *frm=new MessageForm(left);//聊天控件
    frm->resize(200, 800);
    frm->ui->layoutWidget->setGeometry(QRect(0, 0, 200, 800));
    //中间布局
    //    mid=new QWidget(this);
    //    mid->setGeometry(200,0,800,800);
    //    ui->label->setParent(mid);
    //    if(pix.load(":/images/go03.jpg"))
    //    {
    //        //        int width = ui->label->width();
    //        //        int height = ui->label->height();
    //        QPixmap fitpixmap=pix.scaled(800, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //        ui->label->setPixmap(fitpixmap);
    //    }
    //    QPainter painter(this);
    //    painter.setRenderHint(QPainter::Antialiasing, true);// 反走样
    //    painter.drawPixmap(200,0,800,800, QPixmap(":/images/go03.jpg"));// 绘制图标

    //右方布局
    right=new QWidget(this);
    right->setGeometry(1000,0,200,800);
    //1、对方tab页面
    tabWidgetOppo = new QTabWidget(right);
    tabWidgetOppo->addTab(new OppoListTab("对方一览"), tr("对方一览"));
    tabWidgetOppo->addTab(new OppoInfoTab("对方详情"), tr("对方详情"));
    tabWidgetOppo->setGeometry(0,0,200,300);
    //2、我方tab页面
    tabWidgetSelf = new QTabWidget(right);
    tabWidgetSelf->addTab(new SelfListTab("我方一览"), tr("我方一览"));
    tabWidgetSelf->addTab(new SelfInfoTab("我方详情"), tr("我方详情"));
    tabWidgetSelf->setGeometry(0,300,200,300);
    //3、功能区
    func=new QWidget(right);
    func->setGeometry(0,600,200,200);
    QPushButton *btnCount=new QPushButton(func);
    btnCount->setText(tr("点目"));
    QPushButton *btnLoss=new QPushButton(func);
    btnLoss->setText(tr("认输"));
    QPushButton *btnRun=new QPushButton(func);
    btnRun->setText(tr("逃跑"));
    QVBoxLayout *funclayout = new QVBoxLayout(func);
    funclayout->addWidget(btnCount);
    funclayout->addWidget(btnLoss);
    funclayout->addWidget(btnRun);
    setLayout(funclayout);
    //    //布局控制
    //    QHBoxLayout *pHLayout = new QHBoxLayout(this);
    //    pHLayout->addWidget(left);
    //    pHLayout->addWidget(mid);
    //    pHLayout->addWidget(right);
    //    setLayout(pHLayout);


    //    QPainter painter(this);
    //    painter.setPen(QPen(QColor(0, 0, 0), 1));// 设置画笔黑线条、宽度1
    //    painter.setBrush(QColor(255, 255, 255));// 设置画刷颜色白
    //    painter.drawEllipse(QPointF(300, 100), 18, 18);// 绘制圆长半径18宽半径18，位置300,100
    //    this->repaint();
    //    this->update();
}

//在棋盘指定位置绘制棋子
void Widget::pastechess(float x,float y)
{
    QPainter painter(mid);

    QPixmap pixmap(":/images/white.png");
    painter.drawPixmap(x, y, 50, 50, pixmap);

    QBitmap bitmap(":/images/black.png");
    painter.drawPixmap(x+100, y+100, 50, 50, bitmap);
}

Widget::~Widget()
{
    delete ui;
}

//对方一览
OppoListTab::OppoListTab(const QString &info, QWidget *parent)
    : QWidget(parent)
{
    QLabel *pic=new QLabel(this);
    QPixmap pm;
    if(pm.load(":/images/Cherry.png"))
    {
        QPixmap fitpixmap=pm.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        pic->setPixmap(fitpixmap);
    }
    QLabel *name=new QLabel(this);
    name->setText(tr("灬归海一刀灬"));
    QLabel *chess=new QLabel(this);
    if(pm.load(":/images/black.png"))
    {
        QPixmap fitpixmap=pm.scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        chess->setPixmap(fitpixmap);
    }
    //布局控制
    QVBoxLayout *Layout = new QVBoxLayout(this);
    Layout->addWidget(pic);
    Layout->addWidget(name);
    Layout->addWidget(chess);
    Layout->setAlignment(Qt::AlignHCenter);        //布局中各窗体的显示位置
    setLayout(Layout);
}

//对方详情
OppoInfoTab::OppoInfoTab(const QString &info, QWidget *parent)
    : QWidget(parent)
{

}

//我方一览
SelfListTab::SelfListTab(const QString &info, QWidget *parent)
    : QWidget(parent)
{
    QLabel *pic=new QLabel(this);
    QPixmap pm;
    if(pm.load(":/images/qq.png"))
    {
        QPixmap fitpixmap=pm.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        pic->setPixmap(fitpixmap);
    }
    QLabel *name=new QLabel(this);
    name->setText(tr("黄龙士"));
    QLabel *chess=new QLabel(this);
    if(pm.load(":/images/white.png"))
    {
        QPixmap fitpixmap=pm.scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        chess->setPixmap(fitpixmap);
    }
    //布局控制
    QVBoxLayout *Layout = new QVBoxLayout();
    Layout->addWidget(pic);
    Layout->addWidget(name);
    Layout->addWidget(chess);
    Layout->setAlignment(Qt::AlignHCenter);        //布局中各窗体的显示位置
    setLayout(Layout);
}

//我方详情
SelfInfoTab::SelfInfoTab(const QString &info, QWidget *parent)
    : QWidget(parent)
{

}
