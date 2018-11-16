#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QtSql>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/chess02.ico"));
    setFixedSize(520,370);
    setWindowTitle(tr("登录"));
    ui->pwdLineEdit->setFocus();
    ui->loginBtn->setDefault(true);
}

login::~login()
{
    delete ui;
}

void login::on_loginBtn_clicked()
{
    if(ui->pwdLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("请输入密码"),tr("请先输入密码再登录！"),QMessageBox::Ok);
        ui->pwdLineEdit->setFocus();
    }else{
        QSqlQuery query;
        query.exec("select pwd from password");
        query.next();
        if(query.value(0).toString() == ui->pwdLineEdit->text()){
            QDialog::accept();
        }else{
            QMessageBox::warning(this,tr("密码错误"),tr("请输入正确的密码再登录！"),QMessageBox::Ok);
            ui->pwdLineEdit->clear();
            ui->pwdLineEdit->setFocus();
        }
    }
}

void login::on_quitBtn_clicked()
{
    QDialog::reject();
}
