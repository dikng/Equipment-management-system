#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "admin.h"
#include "resetpass.h"
#include "loginwindow.h"
#include <QString>
#include <QDesktopWidget>
#include <QHeaderView>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    admin = new Admin(1);
    this->initTab_2();
    this->initTab_3();
    this->initTab_4();
    this->conn();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTab_2()
{
    this->initTable_1();
    this->initTable_2();
}

void MainWindow::initTable_1()
{
    ui->tableWidget_1->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格不可编辑
//    ui->tableWidget_1->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置表格整行选中
    ui->lineEdit_s_dn->hide();
    ui->dateEdit->show();
    //设置表头
    int width = ui->tableWidget_1->width();
    ui->tableWidget_1->setColumnCount(11);      //设置列数
    ui->tableWidget_1->setColumnWidth(0, static_cast<int>(round(width * 0.06)));
    ui->tableWidget_1->setColumnWidth(1, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_1->setColumnWidth(2, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_1->setColumnWidth(3, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_1->setColumnWidth(4, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_1->setColumnWidth(5, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_1->setColumnWidth(6, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_1->setColumnWidth(7, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_1->setColumnWidth(8, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_1->setColumnWidth(9, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_1->setColumnWidth(10, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_1->setColumnWidth(11, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_1->verticalHeader()->setDefaultSectionSize(25);

    QStringList headText;
//    headText<<"1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9";
//    headText << "名称" << "设备号" << "型号" << "规格" << "单价" << "数量" << "购置日期" << "生产商家" << "购买人" ;
    headText << QStringLiteral("序号") << QStringLiteral("名称") << QStringLiteral("设备号")<< QStringLiteral("型号")
             << QStringLiteral("规格") << QStringLiteral("单价") << QStringLiteral("数量") << QStringLiteral("购置日期")
              << QStringLiteral("生产商家") << QStringLiteral("购买人")<< QStringLiteral("批次") <<QStringLiteral("所在机房");
    ui->tableWidget_1->setHorizontalHeaderLabels(headText);
    ui->tableWidget_1->horizontalHeader()->setStyleSheet("QHeaderView::section{background:whitesmoke;}");
    ui->tableWidget_1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_1->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_1->setAlternatingRowColors(true);
    ui->tableWidget_1->verticalHeader()->setVisible(false);
    ui->tableWidget_1->horizontalHeader()->setStretchLastSection(true);

    //设置行高
    ui->tableWidget_1->setRowCount(0);    //设置行数
}

void MainWindow::initTable_2()   //暂时忽略掉所在机房这一列
{
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格不可编辑
//    ui->tableWidget_1->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置表格整行选中

    int width = ui->tableWidget_2->width();
    ui->tableWidget_2->setColumnCount(11);      //设置列数
    ui->tableWidget_2->setColumnWidth(0, static_cast<int>(round(width * 0.06)));
    ui->tableWidget_2->setColumnWidth(1, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_2->setColumnWidth(2, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_2->setColumnWidth(3, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_2->setColumnWidth(4, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_2->setColumnWidth(5, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_2->setColumnWidth(6, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_2->setColumnWidth(7, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_2->setColumnWidth(8, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_2->setColumnWidth(9, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_2->setColumnWidth(10, static_cast<int>(round(width * 0.15)));
//    ui->tableWidget_2->setColumnWidth(11, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_2->verticalHeader()->setDefaultSectionSize(25);

    QStringList headText;

    headText << QStringLiteral("序号") << QStringLiteral("名称") << QStringLiteral("设备号")<< QStringLiteral("型号")
             << QStringLiteral("规格") << QStringLiteral("单价") << QStringLiteral("数量") << QStringLiteral("购置日期")
              << QStringLiteral("生产商家") << QStringLiteral("购买人")<< QStringLiteral("批次") <<QStringLiteral("所在机房");
    ui->tableWidget_2->setHorizontalHeaderLabels(headText);
    ui->tableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:whitesmoke;}");
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_2->setAlternatingRowColors(true);
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);

    //设置行高
    ui->tableWidget_2->setRowCount(0);    //设置行数
}

void MainWindow::initTab_3()
{
    this->initTable_3();
}

void MainWindow::initTable_3()   //初始化维修情况
{
    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格不可编辑
    int width = ui->tableWidget_3->width();
    ui->tableWidget_3->setColumnCount(7);      //设置列数
    ui->tableWidget_3->setColumnWidth(0, static_cast<int>(round(width * 0.1)));
    ui->tableWidget_3->setColumnWidth(1, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_3->setColumnWidth(2, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_3->setColumnWidth(3, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_3->setColumnWidth(4, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_3->setColumnWidth(5, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_3->setColumnWidth(5, static_cast<int>(round(width * 0.15)));
    ui->tableWidget_3->verticalHeader()->setDefaultSectionSize(25);

    QStringList headText;

    headText << QStringLiteral("序号") << QStringLiteral("设备名") << QStringLiteral("维修费") << QStringLiteral("维修编号")
             << QStringLiteral("责任人")<< QStringLiteral("修理厂家") << QStringLiteral("数量");
    ui->tableWidget_3->setHorizontalHeaderLabels(headText);
    ui->tableWidget_3->horizontalHeader()->setStyleSheet("QHeaderView::section{background:whitesmoke;}");
    ui->tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_3->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_3->setAlternatingRowColors(true);
    ui->tableWidget_3->verticalHeader()->setVisible(false);
    ui->tableWidget_3->horizontalHeader()->setStretchLastSection(true);

    //设置行高
    ui->tableWidget_3->setRowCount(0);    //设置行数
}

void MainWindow::initTab_4()    //初始化报废信息的表格
{
    ui->tableWidget_scrap->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格不可编辑
//    ui->tableWidget_scrap->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置表格整行选中
    //设置表头
    int width = ui->tableWidget_scrap->width();
    ui->tableWidget_scrap->setColumnCount(6);      //设置列数
    ui->tableWidget_scrap->setColumnWidth(0, static_cast<int>(round(width * 0.06)));
    ui->tableWidget_scrap->setColumnWidth(1, static_cast<int>(round(width * 0.188)));
    ui->tableWidget_scrap->setColumnWidth(2, static_cast<int>(round(width * 0.188)));
    ui->tableWidget_scrap->setColumnWidth(3, static_cast<int>(round(width * 0.188)));
    ui->tableWidget_scrap->setColumnWidth(4, static_cast<int>(round(width * 0.188)));
    ui->tableWidget_scrap->setColumnWidth(5, static_cast<int>(round(width * 0.188)));

    ui->tableWidget_scrap->verticalHeader()->setDefaultSectionSize(25);

    QStringList headText;
    headText << QStringLiteral("序号") << QStringLiteral("设备名称") << QStringLiteral("数量")<< QStringLiteral("批次")
             << QStringLiteral("报废日期") << QStringLiteral("备注") ;
    ui->tableWidget_scrap->setHorizontalHeaderLabels(headText);
    ui->tableWidget_scrap->horizontalHeader()->setStyleSheet("QHeaderView::section{background:whitesmoke;}");
    ui->tableWidget_scrap->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_scrap->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_scrap->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_scrap->setAlternatingRowColors(true);
    ui->tableWidget_scrap->verticalHeader()->setVisible(false);
    ui->tableWidget_scrap->horizontalHeader()->setStretchLastSection(true);

}

void MainWindow::conn()   //初始化信号与槽
{
    connect(this,SIGNAL(addEqu(Equipment)),admin,SLOT(addNewEqu(Equipment)));
    connect(this,SIGNAL(scrapEqu(ScrapList)),admin,SLOT(scrapEqu(ScrapList)));
    connect(admin,SIGNAL(ScrapErro()),this,SLOT(scrapErro()));
    connect(admin,SIGNAL(RepairErro()),this,SLOT(RepairErro()));
    connect(this,SIGNAL(repairEqu(RepairList, QString)),admin,SLOT(repairEqu(RepairList,QString)));
    connect(this,SIGNAL(afterRepair(RepairList)),admin,SLOT(afterRepair(RepairList)));
    connect(admin,SIGNAL(returnEquErro()),this,SLOT(returnEquErro()));
}

void MainWindow::outputOneEqu_1(Equipment *cur,int n)
{
//    qDebug()<<QString("output:") <<cur->device_name;
    QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(n+1));   //序号
    QTableWidgetItem *itemDevice_name =new QTableWidgetItem(cur->device_name);
    QTableWidgetItem *itemDevice_number = new QTableWidgetItem(cur->device_number);
    QTableWidgetItem *itemModel_number = new QTableWidgetItem(cur->model_number);
    QTableWidgetItem *itemDevice_spec = new QTableWidgetItem(cur->device_spec);
    QTableWidgetItem *itemDevice_price = new QTableWidgetItem(cur->device_price);
    QTableWidgetItem *itemDevice_quantity = new QTableWidgetItem(cur->device_quantity);
    QTableWidgetItem *itemBuy_date = new QTableWidgetItem(cur->buy_date );
    QTableWidgetItem *itemDevice_producer = new QTableWidgetItem(cur->device_producer);
    QTableWidgetItem *itemDevice_purchaser = new QTableWidgetItem(cur->device_purchaser);
    QTableWidgetItem *itemDevice_lot = new QTableWidgetItem(cur->device_lot);


    ui->tableWidget_1->setItem(n,0,itemDeviceID);
    ui->tableWidget_1->setItem(n,1,itemDevice_name);
    ui->tableWidget_1->setItem(n,2,itemDevice_number);
    ui->tableWidget_1->setItem(n,3,itemModel_number);
    ui->tableWidget_1->setItem(n,4,itemDevice_spec);
    ui->tableWidget_1->setItem(n,5,itemDevice_price);
    ui->tableWidget_1->setItem(n,6,itemDevice_quantity);
    ui->tableWidget_1->setItem(n,7,itemBuy_date);
    ui->tableWidget_1->setItem(n,8,itemDevice_producer);
    ui->tableWidget_1->setItem(n,9,itemDevice_purchaser);
    ui->tableWidget_1->setItem(n,10,itemDevice_lot);
}

void MainWindow::outputOneEqu_2(Equipment *cur, int n)
{
    QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(n+1));   //序号
    QTableWidgetItem *itemDevice_name =new QTableWidgetItem(cur->device_name);
    QTableWidgetItem *itemDevice_number = new QTableWidgetItem(cur->device_number);
    QTableWidgetItem *itemModel_number = new QTableWidgetItem(cur->model_number);
    QTableWidgetItem *itemDevice_spec = new QTableWidgetItem(cur->device_spec);
    QTableWidgetItem *itemDevice_price = new QTableWidgetItem(cur->device_price);
    QTableWidgetItem *itemDevice_quantity = new QTableWidgetItem(cur->device_quantity);
    QTableWidgetItem *itemBuy_date = new QTableWidgetItem(cur->buy_date);
    QTableWidgetItem *itemDevice_producer = new QTableWidgetItem(cur->device_producer);
    QTableWidgetItem *itemDevice_purchaser = new QTableWidgetItem(cur->device_purchaser);
    QTableWidgetItem *itemDevice_lot = new QTableWidgetItem(cur->device_lot);


   ui->tableWidget_2->setItem(n,0,itemDeviceID);
   ui->tableWidget_2->setItem(n,1,itemDevice_name);
   ui->tableWidget_2->setItem(n,2,itemDevice_number);
   ui->tableWidget_2->setItem(n,3,itemModel_number);
   ui->tableWidget_2->setItem(n,4,itemDevice_spec);
   ui->tableWidget_2->setItem(n,5,itemDevice_price);
   ui->tableWidget_2->setItem(n,6,itemDevice_quantity);
   ui->tableWidget_2->setItem(n,7,itemBuy_date);
   ui->tableWidget_2->setItem(n,8,itemDevice_producer);
   ui->tableWidget_2->setItem(n,9,itemDevice_purchaser);
   ui->tableWidget_2->setItem(n,10,itemDevice_lot);
}

void MainWindow::outputOneEqu_3(RepairList *cur, int n)    //打印全部维修信息
{
    QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(n+1));   //序号
    QTableWidgetItem *itemDevice_name =new QTableWidgetItem(cur->rDevice_name);
    QTableWidgetItem *itemCost = new QTableWidgetItem(cur->rCost);
    QTableWidgetItem *itemDevice_number = new QTableWidgetItem(cur->rDevice_number);
    QTableWidgetItem *itemMan = new QTableWidgetItem(cur->rMan);
    QTableWidgetItem *itemIden = new QTableWidgetItem(cur->iden);
    QTableWidgetItem *itemVender = new QTableWidgetItem(cur->rVender);


   ui->tableWidget_3->setItem(n,0,itemDeviceID);
   ui->tableWidget_3->setItem(n,1,itemDevice_name);
   ui->tableWidget_3->setItem(n,2,itemCost);
   ui->tableWidget_3->setItem(n,3,itemIden);
   ui->tableWidget_3->setItem(n,4,itemMan);
   ui->tableWidget_3->setItem(n,5,itemVender);
   ui->tableWidget_3->setItem(n,6,itemDevice_number);
}

void MainWindow::outputOneEqu_scrap(ScrapList *cur, int n)   //打印报废信息
{
    QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(n+1));   //序号
    QTableWidgetItem *itemDevice_name =new QTableWidgetItem(cur->sDevice_name);
    QTableWidgetItem *itemDevice_number = new QTableWidgetItem(cur->sDevice_number);
    QTableWidgetItem *itemRemark = new QTableWidgetItem(cur->sRemark);
    QTableWidgetItem *itemscrapDate = new QTableWidgetItem(cur->sDate);
    QTableWidgetItem *itemDevice_lot = new QTableWidgetItem(cur->sDevice_lot);


   ui->tableWidget_scrap->setItem(n,0,itemDeviceID);
   ui->tableWidget_scrap->setItem(n,1,itemDevice_name);
   ui->tableWidget_scrap->setItem(n,2,itemDevice_number);
   ui->tableWidget_scrap->setItem(n,3,itemDevice_lot);
   ui->tableWidget_scrap->setItem(n,4,itemscrapDate);
   ui->tableWidget_scrap->setItem(n,5,itemRemark);
}


void MainWindow::outputAllEqu()
{
    int i,total;
    Equipment *cur = admin->getEHead();
    total = admin->getEquNumber();
    this->initTable_2();
    ui->tableWidget_2->setRowCount(total);
    for(i = 0;i<total;i++){
        this->outputOneEqu_2(cur,i);
        cur = cur->nextEqu;
    }

}

void MainWindow::outputByDevice_name(QString find)   //以设备名称查询正常设备的信息
{
    int n;
    n =0;
    Equipment *res_head,*res_cur,*cur;
    cur = admin->getEHead();
    while( cur != nullptr){
        if(find.compare(cur->device_name) == 0){
            if(n == 0){
                res_head = new Equipment(cur);
//                qDebug()<<QString("res_head->device_name:")<< res_head ->device_name;
                res_cur = res_head;
            }
            else if(n > 0){
                res_cur ->nextEqu= new Equipment(cur);
//                qDebug()<<QString("res_cur ->device_name:")<<res_cur->device_name;
                res_cur = res_cur->nextEqu;
            }
            n++;
        }
        cur = cur->nextEqu;
    }
//    qDebug()<<QString("n:")<<n;
    if(n == 0){
        QMessageBox::warning(this,tr("warning"),QStringLiteral("查询结果为空！"),QMessageBox::Yes);
        return;
    }
    this->initTable_1();
    ui->tableWidget_1->setRowCount(n);
    res_cur = res_head;
    for(int i =0;res_cur != nullptr ;i++){
 //       qDebug()<<QStringLiteral("i:")<<i;
        this->outputOneEqu_1(res_cur,i);
        res_cur = res_cur->nextEqu;
    }
}

void MainWindow::outputScrapEqu()
{
    int i,total;
    ScrapList *cur = admin->getSHead();
    total = admin->getScrapNumber();
    this->initTab_4();
    ui->tableWidget_scrap->setRowCount(total);
    for(i = 0;i < total; i++){
        this->outputOneEqu_scrap(cur, i);
        cur =cur->nextScrap;
    }
}

void MainWindow::outputAllRepair()  //打印所有设备维修信息
{
    int i,total;
    RepairList *cur = admin->getRHead();
    total =admin->getRepairNumber();
//    qDebug()<<QStringLiteral("repairNumber:")<<total;
    this->initTab_3();
    ui->tableWidget_3->setRowCount(total);
    for(i = 0;i < total;i++){
        this->outputOneEqu_3(cur,i);
        cur = cur->nextRep;
    }
}

void MainWindow::on_pushButton_clicked()
{
    QDate date(2016,1,1);
    ui->LineEdit->clear();
    ui->LineEdit_2->clear();
    ui->LineEdit_3->clear();
    ui->LineEdit_4->clear();
    ui->LineEdit_5->clear();
    ui->LineEdit_6->clear();
    ui->LineEdit_7->setText(tr("yyyy/mm/dd"));
    ui->LineEdit_8->clear();
    ui->LineEdit_9->clear();
}

void MainWindow::on_comboBox_s_currentIndexChanged(const QString &arg1)
{

    QString tmpStr = "购置日期";
    if(QString::compare(tmpStr,arg1)== 29392){
//        qDebug()<<arg1;
        ui->lineEdit_s_dn->hide();
        ui->dateEdit->show();
    }
    else{

        ui->dateEdit->hide();
        ui->lineEdit_s_dn->show();
    }
 //   qDebug()<<QString::compare(tmpStr,arg1);
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)   //此槽无用，删除会提示错误，所以暂时不处理
{
    QString tmp = arg1;
}

void MainWindow::on_action_logout_triggered()       //注销，回到登录界面
{
    this->hide();
    LoginWindow login;
    login.show();
    if(login.exec() == QDialog::Accepted){
        this->show();
    }

}

void MainWindow::on_action_resetpass_triggered()     //用于修改密码，未实现
{
    QMessageBox::warning(this,tr("warning"),QStringLiteral("功能暂未实现!"),QMessageBox::Yes);
/*    this->hide();
    resetPass *tmp = new resetPass();
    tmp->show();*/
}

void MainWindow::on_comboBox_repair_currentIndexChanged(const QString &arg1)    //选择搜索条件
{
    QString unused = arg1;
    unused.append(".");
/*    QString tmpStr = "送修日期";
    if(QString::compare(tmpStr,arg1)!= 28668){
        ui->lineEdit_repair_find->show();
    }
    else{
        ui->lineEdit_repair_find->hide();
    }*/
}

void MainWindow::on_pushButton_2_clicked()     //提交设备入库信息按钮
{
    QString tmp;
    Equipment newEqu;
    newEqu.device_name = ui->LineEdit->text();
    newEqu.device_number = ui->LineEdit_2->text();
    newEqu.model_number = ui->LineEdit_3->text();
    newEqu.device_spec = ui->LineEdit_4->text();
    newEqu.device_price = ui->LineEdit_5->text();
    newEqu.device_quantity= ui->LineEdit_6->text();
    newEqu.buy_date= ui->LineEdit_7->text();
//    qDebug()<<tmp<<newEqu.buy_date;
    newEqu.device_producer = ui->LineEdit_8->text();
    newEqu.device_purchaser = ui->LineEdit_9->text();
    newEqu.device_lot = ui->LineEdit_lot->text();
//    qDebug()<<tr("start");
    emit addEqu(newEqu);
//    qDebug()<<tr("end");

}

void MainWindow::on_pushButton_3_clicked()    //打印全部正常的设备的信息
{
    int n;
    n = admin->getEquNumber();
    if(n>0)
        this->outputAllEqu();
    else {
        QMessageBox::warning(this,tr("warning"),QStringLiteral("无设备信息！"),QMessageBox::Yes);
    }
}

void MainWindow::on_pushButton_s_clicked()
{
    if(admin->getEquNumber() == 0){
        QMessageBox::warning(this,tr("warning"),QStringLiteral("无设备信息！"),QMessageBox::Yes);
        return;
    }
    QString find;
    int acc,s_1,s_2,s_3;
    s_1 = 0;    //日期
    s_2 = 1;    //设备名称
    s_3 = 2;    //机房名称
    acc = ui->comboBox_s->currentIndex();
    qDebug()<<acc;
    if(acc == s_2){
//        qDebug()<<QStringLiteral("开始根据设备名称查询");

        find = ui->lineEdit_s_dn->text();
//        qDebug()<<QStringLiteral("设备名称")<<find;
        if(find.compare("")== 0){
            QMessageBox::warning(this,tr("warning"),QStringLiteral("设备名不能为空！"),QMessageBox::Yes);
            return;
        }
        this->outputByDevice_name(find);
    }
    else if(acc == s_1){   //日期
        QMessageBox::warning(this,tr("warning"),QStringLiteral("功能未加入！请通过设备名查找"),QMessageBox::Yes);
    }
    else if(acc == s_3){   //机房名称
        QMessageBox::warning(this,tr("warning"),QStringLiteral("功能未加入！请通过设备名查找"),QMessageBox::Yes);
    }
    this->on_comboBox_s_currentIndexChanged(ui->comboBox_s->currentText());
}

void MainWindow::on_pushButton_10_clicked()    //将已经输入的报废信息清空
{
    ui->LineEdit_scrap_dn->clear();
    ui->LineEdit_scrap_num->clear();
    ui->LineEdit_scrap_lot->clear();
    ui->LineEdit_scrap_mess->clear();
    ui->lineEdit_scrap_date->setText("yyyy/mm/dd");

}

void MainWindow::on_pushButton_9_clicked()    //提交报废信息
{
    if(admin->getEquNumber() == 0){
        QMessageBox::warning(this,tr("warning"),QStringLiteral("无设备信息！"),QMessageBox::Yes);
        return;
    }
    ScrapList newScrap;
    newScrap.sDevice_name = ui->LineEdit_scrap_dn->text();
    newScrap.sDevice_number = ui->LineEdit_scrap_num->text();
    newScrap.sDevice_lot = ui->LineEdit_scrap_lot->text();
    newScrap.sRemark = ui->LineEdit_scrap_mess->text();
    newScrap.sDate = ui->lineEdit_scrap_date->text();
    emit scrapEqu(newScrap);
    on_pushButton_10_clicked();
}

void MainWindow::on_pushButton_11_clicked()    //打印报废信息
{
    if(admin->getScrapNumber() == 0){
        QMessageBox::warning(this,tr("warning"),QStringLiteral("无设备已报废！"),QMessageBox::Yes);
        return;
    }
    this->outputScrapEqu();  //打印所有已报废的设备的信息
}

void MainWindow::scrapErro()
{
    QMessageBox::warning(this,tr("warning"),QStringLiteral("无相关设备信息！请验证后重新填写报废信息"),QMessageBox::Yes);
}

void MainWindow::RepairErro()
{
    QMessageBox::warning(this,tr("warning"),QStringLiteral("无相关设备信息！请验证后重新填写维修信息"),QMessageBox::Yes);
}

void MainWindow::returnEquErro()
{
    QMessageBox::warning(this,tr("warning"),QStringLiteral("无相关设备信息！请验证后重新填写"),QMessageBox::Yes);
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->LineEdit_r_num_2->clear();
    ui->LineEdit_r_peo_2->clear();
    ui->LineEdit_r_pro_2->clear();
    ui->LineEdit_r_iden_2->setText(QStringLiteral("由日期加上维修请求的序号，如2016102910  为2016/10/29 的第10次请求"));
    ui->LineEdit_r_name_2->clear();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->LineEdit_r_num_1->clear();
    ui->LineEdit_r_peo_1->clear();
    ui->LineEdit_r_pro_1->clear();
    ui->LineEdit_r_iden_1->setText(QStringLiteral("由日期加上维修请求的序号，如2016102910  为2016/10/29 的第10次请求"));
    ui->LineEdit_r_name_1->clear();
    ui->LineEdit_r_lot->clear();
}

void MainWindow::on_pushButton_5_clicked()    //提交维修信息
{
    if(admin->getEquNumber() == 0){
        QMessageBox::warning(this,tr("warning"),QStringLiteral("无设备信息！"),QMessageBox::Yes);
    }
    RepairList newRepair;
    QString lot;
    newRepair.rDevice_name = ui->LineEdit_r_name_1->text();
    newRepair.rCost = ui->LineEdit_r_money_1->text();
    newRepair.rMan = ui->LineEdit_r_peo_1->text();
    newRepair.rVender = ui->LineEdit_r_pro_1->text();
    newRepair.rDevice_number = ui->LineEdit_r_num_1->text();
    newRepair.iden = ui->LineEdit_r_iden_1->text();
    lot = ui->LineEdit_r_lot->text();
    emit repairEqu(newRepair,lot);
    on_pushButton_4_clicked();
}

void MainWindow::on_pushButton_8_clicked()
{
    if(admin->getRepairNumber() == 0){
        QMessageBox::warning(this,tr("warning"),QStringLiteral("无维修记录"),QMessageBox::Yes);
        return;
    }
    this->outputAllRepair();
}

void MainWindow::on_pushButton_6_clicked()    //设备维修结束，将设备信息添加回去正常设备的行列
{
    RepairList after;
    if(admin->getEquNumber() == 0){
        QMessageBox::warning(this,tr("warning"),QStringLiteral("无设备信息！"),QMessageBox::Yes);
    }
    after.rDevice_name =ui->LineEdit_r_name_2->text();
    after.rMan = ui->LineEdit_r_peo_2->text();
    after.rVender = ui->LineEdit_r_pro_2->text();
    after.rDevice_number = ui->LineEdit_r_num_2->text();
    after.iden = ui->LineEdit_r_iden_2->text();
    emit afterRepair(after);
    on_pushButton_7_clicked();
    this->initTable_3();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
        button=QMessageBox::question(this,QStringLiteral("退出程序"),QStringLiteral("确认退出程序"),QMessageBox::Yes|QMessageBox::No);
        if(button==QMessageBox::No)
        {
            event->ignore(); // 忽略退出信号，程序继续进行
        }
        else if(button==QMessageBox::Yes)
        {
            admin->Write();
            event->accept(); // 接受退出信号，程序退出
        }
}
