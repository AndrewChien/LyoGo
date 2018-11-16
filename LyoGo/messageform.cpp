#include "messageform.h"
#include "ui_messageform.h"

MessageForm::MessageForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageForm)
{
    ui->setupUi(this);
//    ui->layoutWidget->setGeometry(QRect(0, 0, 200, 800));
}

MessageForm::~MessageForm()
{
    delete ui;
}
