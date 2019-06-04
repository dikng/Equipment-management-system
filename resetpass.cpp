#include "resetpass.h"
#include "ui_resetpass.h"

resetPass::resetPass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::resetPass)
{
    ui->setupUi(this);
}

resetPass::~resetPass()
{
    delete ui;
}
