#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMouseEvent>
#include <string.h>
#include <QMessageBox>
#include <QFileInfo>
#include <QStringList>
#include <QDateTime>
#include <QDebug>
#include <QFont>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
//  this->setAttribute(Qt::WA_TranslucentBackground);   //设置背景透明
    QFont font("Microsoft YaHei",20,QFont::Bold - 75);
    ui->label_4->setFont(font);
    ui->label_4->setStyleSheet("color:white;");


}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = event->pos();
    }
}

void LoginWindow::mouseReleaseEvent(QMouseEvent *) {
    mousePressed = false;
}

void LoginWindow::mouseMoveEvent(QMouseEvent *event) {
    if (mousePressed && (event->buttons() && Qt::LeftButton)) {
        this->move(event->globalPos() - mousePoint);
        event->accept();
    }
}

void LoginWindow::on_Exit_clicked()
{
    this->reject();
}

void LoginWindow::on_Login_clicked( )
{
    QString userName,Password;
    QFile file("admin.text");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<file.errorString();
        file.close();
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        file.write("kindol\n212799");
        file.close();
//        userName="kindol";
 //       Password="212799";
    }
    else{
        userName = file.readLine();
        Password = file.readLine();
        file.close();
    }


    if(ui->username->text() == tr("kindol") & ui->password->text() == tr("212799")){
        accept();
//        this->reject();
    }
    else{
        QMessageBox::warning(this,tr("warning"),tr("用户名或密码错误!"),QMessageBox::Yes);
              //如果还想清空用户名、密码框，并且光标自动跳转到用户名输入框，就继续下面
              ui->username->clear();
              ui->password->clear();
              ui->username->setFocus();//将光标移到用户名框内

    }
}
