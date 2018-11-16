#include "lyogo.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include "connection.h"
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!createConnection()||!createXml())return 0;
    login dlg;
    if(dlg.exec()==QDialog::Accepted){
        QPixmap pixmap(":/images/go.jpg");				//(a)
        QSplashScreen splash(pixmap);			//(b)
        splash.show();							//显示此启动图片
        a.processEvents();						//(c)
        lyogo w;
        w.show();
        splash.finish(&w);						//(e)
        return a.exec();
    }else{
        return 0;
    }
}
