#ifndef LYOGO_H
#define LYOGO_H

#include <QMainWindow>
#include <QPrintDialog>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include "widget.h"

namespace Ui {
class lyogo;
}

class lyogo : public QMainWindow
{
    Q_OBJECT

public:
    explicit lyogo(QWidget *parent = 0);
    ~lyogo();

private slots:
    void fileNewQipu();
    void fileOpenQipu();
    void fileSaveQipu();
    void fileSaveAsQipu();
    void filePrintQipu();
    void filePrintPreviewQipu();
    void fileNewDuiju();
    void fileOpenDuiju();
    void fileSaveDuiju();
    void fileSaveAsDuiju();
    void filePrintDuiju();
    void filePrintPreviewDuiju();
    void about();
    void aboutAuthor();
    void ShowMatch(QString data);

private:
    Ui::lyogo *ui;
    void createToolBars();
    void createStatusBar();
    void createLayout();
    void loadMessageArea();
    void loadActions();

    //菜单
    QMenu *fileMenu;
    QMenu *toolMenu;
    QMenu *settingMenu;
    QMenu *helpMenu;
    //工具栏
    QToolBar *qipuToolBar;
    QToolBar *duijuToolBar;
    QToolBar *logoutToolBar;
    //动作(Action)
    QAction *qipunewAct;
    QAction *qipuopenAct;
    QAction *qipusaveAct;
    QAction *qipusaveAsAct;
    QAction *qipuprintAct;
    QAction *qipuprintPreviewAct;
    QAction *duijunewAct;
    QAction *duijuopenAct;
    QAction *duijusaveAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutAuthorAct;
    QAction *enterMatchAct;

    Widget *chatWidget;
};

#endif // LYOGO_H
