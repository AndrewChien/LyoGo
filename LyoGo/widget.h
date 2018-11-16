#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent,QString usrname);
    ~Widget();

private:
    Ui::Widget *ui;
    QPixmap pix;
    QWidget *left;
    QWidget *mid;
    QWidget *right;
    QTabWidget *tabWidgetOppo;//对方tab页面
    QTabWidget *tabWidgetSelf;//我方tab页面
    QWidget *func;//功能区
    QGraphicsScene *scene;
    QGraphicsView *view;
    void createLayout();
    void pastechess(float x,float y);
    float mousex=0;
    float mousey=0;

protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *e);
};

//对手总览tab页
class OppoListTab : public QWidget
{
    Q_OBJECT

public:
    explicit OppoListTab(const QString &info, QWidget *parent = 0);
};

//对手详情tab页
class OppoInfoTab : public QWidget
{
    Q_OBJECT

public:
    explicit OppoInfoTab(const QString &info, QWidget *parent = 0);
};

//己方总览tab页
class SelfListTab : public QWidget
{
    Q_OBJECT

public:
    explicit SelfListTab(const QString &info, QWidget *parent = 0);
};

//己方详情tab页
class SelfInfoTab : public QWidget
{
    Q_OBJECT

public:
    explicit SelfInfoTab(const QString &info, QWidget *parent = 0);
};

#endif // WIDGET_H
