#include "admin.h"
#include <QFile>
#include <QDebug>
#include <QDataStream>

Equipment::Equipment()    //初始化
{
    device_name = "";
//    device_type = "";
    device_number = "";
    model_number = "";
    device_spec = "";
    device_price = "";
    device_quantity = "";
//    buy_date= new QDate(2016,1,1);
    device_producer = "";
    device_purchaser = "";
    device_lot = "";
    nextEqu = nullptr;
}

Equipment::Equipment(const Equipment &other)
{
    device_name = other.device_name;
//    device_type = "";
    device_number = other.device_number;
    model_number = other.model_number;
    device_spec = other.device_spec;
    device_price = other.device_price;
    device_quantity = other.device_quantity;
    buy_date = other.buy_date;
    device_producer =other.device_producer;
    device_purchaser =other.device_purchaser;
    device_lot = other.device_lot;
    nextEqu = nullptr;
}

Equipment::Equipment(const Equipment *other)
{
    device_name = other->device_name;
//    device_type = "";
    device_number = other->device_number;
    model_number = other->model_number;
    device_spec = other->device_spec;
    device_price = other->device_price;
    device_quantity = other->device_quantity;
    buy_date = other->buy_date;
    device_producer =other->device_producer;
    device_purchaser =other->device_purchaser;
    device_lot = other->device_lot;
    nextEqu = nullptr;
}

void Equipment::output()
{
    qDebug()<<device_name;
    qDebug()<<device_number;
    qDebug()<<model_number;
    qDebug()<<device_spec;
    qDebug()<<device_price;
    qDebug()<<device_quantity;
    qDebug()<<buy_date;
    qDebug()<<device_producer;
    qDebug()<<device_purchaser;
    qDebug()<<device_lot;
/*    device_number
    model_number
    device_spec
    device_price
    device_quantity
    buy_date
    device_producer
    device_purchaser
    device_lot*/
}


Admin::Admin(QWidget *parent) : QWidget(parent)    //如有本地有相关设备信息，则读入
{

}

Admin::Admin(int kin)
{
    int a;
    a = kin;
    eHead = new Equipment();    //存储正常设备的信息
    equNumber = 0;
    sHead = new ScrapList();    //存储报废设备信息
    scrapNumber = 0;
    rHead = new RepairList();   //存储被维修设备的信息
    repairNumber = 0;
    this->Read();
}

Admin::Admin(const Admin &other)
{
    eHead =other.eHead ;    //存储正常设备的信息
    equNumber = other.equNumber;
    sHead = other.sHead;    //存储报废设备信息
    scrapNumber = other.scrapNumber;
    rHead =other.rHead ;   //存储被维修设备的信息
    repairNumber = other.repairNumber;
}

Admin::~Admin()
{
    qDebug()<<tr("nonthing");
}

void Admin::Read()//读文件
{
    this->readEqument();
    this->readSrcapList();
    this->readRepairList();
}

void Admin::Write()//读文件
{
    this->writeEqument();
    this->writeScrapList();
    this->writeRepairList();
}

void Admin::qdebug(Equipment *cur)    //用于验证读写结果是否正确
{
   qDebug()<<QString("device_name:")<<cur->device_name << QString("device_number:")<< cur->device_number <<QString("model_number:")<<cur->model_number
          <<QString("device_spec:")<<cur->device_spec <<QString("device_price")<< cur->device_price <<QString("device_quantity:")<<cur->device_quantity
          <<QString("buy_date:")<<cur->buy_date<<QString("device_producer:")<<cur->device_producer <<QString("device_purchaser")<<cur->device_purchaser
         <<QString("device_lot:")<<cur->device_lot;
}

void Admin::qdebug(RepairList *cur)
{
    qDebug()<<QString("rDevice_name:")<< cur->rDevice_name<<QString("rCost:") <<cur->rCost <<QString("iden:")<<cur->iden
           <<QString("rMan:")<<cur->rMan<<QString("rVender:")<<cur->rVender<<QString("rDevice_number:") << cur->rDevice_number;
}

void Admin::qdebug(ScrapList *cur)
{
    qDebug()<<QString("sDevice_name:")<<cur->sDevice_name <<QString("sDevice_number:")<< cur->sDevice_number <<QString("sDevice_lot:")<< cur->sDevice_lot
            <<QString("sDate:")<< cur->sDate <<QString("sRemark:")<< cur->sRemark;
}
//----------------------文件读写--------------------------------
void Admin::readEqument(){ //将本地的设备（无异常）的信息读入
    int n;
    QFile file("Equipment.text");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QDataStream in(&file);
       n = 1;
       Equipment *input;   //不带表头的链接结构
       in >> equNumber;
       qDebug()<<QStringLiteral("--------------------------读文件--------------------------");
       qDebug()<<QStringLiteral("equNumber:")<<equNumber;
       while(n <= equNumber){
           Equipment *cur =new Equipment();
           in >> cur->device_name >> cur->device_number >>cur->model_number
                   >>cur->device_spec >> cur->device_price >>cur->device_quantity >>cur->buy_date
                   >>cur->device_producer >>cur->device_purchaser >>cur->device_lot;
           if(n == 1){
               eHead = new Equipment(cur);
               input =eHead;
           }
           else if(n > 1){
               input ->nextEqu =new Equipment(cur);
               input = input->nextEqu;
           }
           qDebug()<<QStringLiteral("序号:")<<n;
           qdebug(cur);
           n++;
       }
       file.close();
    }

}

bool Admin::writeEqument()    //将设备信息写入本地
{
    int n;
    n = equNumber;
    if(n <= 0 ){ return true;}
    QFile file("Equipment.text");
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QDataStream out(&file);
        Equipment *cur = eHead;
        out <<equNumber;
        qDebug()<<QStringLiteral("--------------------------写文件--------------------------");
        qDebug()<<QStringLiteral("equNumber:")<<equNumber;
        n = 1;
        while(cur != nullptr){
            qDebug()<<QStringLiteral("序号:")<<n;
            qdebug(cur);
            out<<cur->device_name << cur->device_number <<cur->model_number
              <<cur->device_spec << cur->device_price <<cur->device_quantity <<cur->buy_date
              <<cur->device_producer <<cur->device_purchaser <<cur->device_lot;
            cur = cur->nextEqu;
            n++;
        }
        file.close();
        return true;
    }
    else return false;
}

void Admin::readSrcapList(){    //读取报废信息
    int n;
    QFile file_2("ScrapList.text");
    if(file_2.open(QIODevice::ReadOnly|QIODevice::Text)){
        QDataStream in_2(&file_2);
        n =1;
        ScrapList *input;
        in_2 >>scrapNumber;
        qDebug()<<QStringLiteral("--------------------------读文件--------------------------");
        qDebug()<<QStringLiteral("scrapNumber:")<<scrapNumber;
        while(n <= scrapNumber){
            ScrapList cur;
            in_2 >> cur.sDevice_name >> cur.sDevice_number >> cur.sDevice_lot
                    >> cur.sDate >> cur.sRemark;
            if(n == 1){
                sHead =new ScrapList(cur);
                input =sHead;
            }
            else{
                input ->nextScrap = new ScrapList(cur);
                input =input->nextScrap;
            }
            n++;
        }
        file_2.close();
    }
}

bool Admin::writeScrapList()
{
    int n;
    n = scrapNumber;
    if(n <= 0) return true;
    QFile  file("ScrapList.text");
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QDataStream out(&file);
        out<<scrapNumber;
        ScrapList *cur = sHead;
        qDebug()<<QStringLiteral("--------------------------写文件--------------------------");
        qDebug()<<QStringLiteral("scrapNumber:")<<scrapNumber;
        while(n > 0){
            qdebug(cur);
            out << cur->sDevice_name << cur->sDevice_number << cur->sDevice_lot
                    << cur->sDate << cur->sRemark;
            cur = cur->nextScrap;
            n--;
        }
        file.close();
        return true;
    }
    else return false;
}

void Admin::readRepairList()   //读取维修信息
{
    int n;
    QFile file_1("RepairList.text");     //将本地中维修信息读入
    if(file_1.open(QIODevice::ReadOnly|QIODevice::Text)){
        QDataStream in_1(&file_1);
        n =1;
        RepairList *input;
        in_1 >> repairNumber;
        qDebug()<<QStringLiteral("--------------------------读文件--------------------------");
        qDebug()<<QStringLiteral("repairNumber:")<<repairNumber;
        while(n <= repairNumber){
            RepairList cur;
            in_1 >> cur.rDevice_name >>cur.rCost >>cur.iden >>cur.rMan
                    >>cur.rVender >>cur.rDevice_number >>cur.equ.device_name >> cur.equ.device_number >>cur.equ.model_number
                    >>cur.equ.device_spec >> cur.equ.device_price >>cur.equ.device_quantity >>cur.equ.buy_date
                    >>cur.equ.device_producer >>cur.equ.device_purchaser >>cur.equ.device_lot;
            if(n == 1){
                rHead = new RepairList(cur);
                input = rHead;
            }
            else{
                input->nextRep = new RepairList(cur);
                input =input->nextRep;
            }
            n++;
        }
        file_1.close();
    }
}

bool Admin::writeRepairList()
{
    int n;
    n = repairNumber;
    if(n <= 0) return true;
    QFile file("RepairList.text");
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QDataStream out(&file);
        RepairList *cur =rHead;
        out<<repairNumber;
        qDebug()<<QStringLiteral("--------------------------写文件--------------------------");
        qDebug()<<QStringLiteral("repairNumber:")<<repairNumber;
        while(n > 0){
            qdebug(cur);
            out<< cur->rDevice_name <<cur->rCost <<cur->iden <<cur->rMan
               <<cur->rVender << cur->rDevice_number<< cur->equ.device_name << cur->equ.device_number <<cur->equ.model_number
               <<cur->equ.device_spec << cur->equ.device_price <<cur->equ.device_quantity <<cur->equ.buy_date
               <<cur->equ.device_producer <<cur->equ.device_purchaser <<cur->equ.device_lot;
            cur = cur->nextRep;
            n--;
       }
        file.close();
        return true;
    }
    else return false;
}

//---------------------文件读写--------------------------------

Equipment *Admin::search(QString name, QString lot)    //查找设备名和批次匹配的节点，并返回该节点的上一节点的指针
{
//    qDebug()<<QStringLiteral("search参数：")<<name<<lot;
    int n;
    n = 0;
    Equipment *cur,*before;
    cur = eHead;
    before = eHead;
    while(cur != nullptr){
//        qDebug()<<QStringLiteral("search中第")<<++n<<QStringLiteral("次循环")<<QStringLiteral("name:")<<cur->device_name;
        if(cur ->device_name.compare(name) == 0 && cur->device_lot.compare(lot) == 0){
//            qDebug()<<QStringLiteral("目标结果")<<cur->device_name;
            return before;
        }
        else {
            before = cur;
            cur = cur->nextEqu;
        }
    }
    return nullptr;
}

void Admin::deleEqu(Equipment *before,QString name,QString lot)    //删除相关设备信息
{
//    qDebug()<<QStringLiteral("deleEqu");
    Equipment *cur ,*del;
    if(equNumber == 1){
        equNumber = 0;
        delete  eHead;
        return;
    }
    if(before->device_name.compare(name) == 0 && before->device_lot.compare(lot) == 0){
        cur = eHead ->nextEqu;
        delete  eHead;
        eHead = cur;
        equNumber--;
        return;
    }
    cur = before;
    del = before->nextEqu;
    equNumber--;
    cur->nextEqu = del->nextEqu;
    delete del;
}

void Admin::modifyEqu(Equipment *before,QString n,QString name,QString lot)    //修改设备数量或进一步调用删除函数删除相关设备信息（节点）
{
//    qDebug()<<QStringLiteral("modifyEqu");
    Equipment *cur;
    int qua,scra;
    if(before ->device_name.compare(name) != 0 || before->device_lot.compare(lot) != 0)
        cur = before->nextEqu;
    else {
        cur = before;
    }
    qua = cur->device_quantity.toInt();
    scra = n.toInt();
    if(qua == scra){//默认报废数量合法
        deleEqu(before,name,lot);
    }
    else{
           qua = qua - scra;
           cur->device_quantity = QString::number(qua); //更新设备数量
    }

}

RepairList *Admin::searchRepair(QString iden)     //以维修编号查找相关维修信息
{
    RepairList *last, *cur ;
    cur= rHead;
    last =rHead;
    while(cur != nullptr){
        if(cur ->iden.compare(iden) == 0){
            last->nextRep =cur->nextRep;
            repairNumber--;
            return cur;
        }
        else {
            last = cur;
            cur = cur->nextRep;
        }
    }
    return nullptr;
}

bool Admin::addNewEqu(Equipment newEqu)    //将新入库的设备信息添加到链表中去
{
//    qDebug()<<tr("equNumber:")<<equNumber+1;
    if(equNumber == 0){
        eHead = new Equipment(newEqu);
        equNumber++;
        return true;
    }
    else{
       Equipment *cur = eHead;
        while(cur->nextEqu != nullptr ){
            cur = cur->nextEqu;
        }
        cur->nextEqu =new Equipment(newEqu);
        equNumber++;
        return true;
    }

}

void Admin::repairEqu(RepairList newRepair,QString lot)    //添加维修信息
{
//    qDebug()<<QStringLiteral("进入repairEqu")<<newRepair.rDevice_name;
    RepairList *cur = &newRepair;
    Equipment *res,*reser;
    res = search(cur->rDevice_name,lot);
    if(res == nullptr){
        emit RepairErro();
        return;
    }
    if(res->device_name.compare(cur->rDevice_name) == 0 && res->device_lot.compare(lot) == 0){
        reser = new Equipment(res);
    }
    else {
        reser = new Equipment(res->nextEqu);
    }

    modifyEqu(res,cur->rDevice_number,cur->rDevice_name,lot);
//     qDebug()<<QStringLiteral("添加维修信息后equNumber:")<<equNumber;
    if(repairNumber == 0){
        rHead = new RepairList(newRepair);
        rHead->equ = Equipment(reser);
//         qDebug()<<QStringLiteral("测试rHead->equ:")<<rHead->equ.device_name;
        repairNumber++;
        return;
    }
    else{

        RepairList *tmp = rHead;
        while(tmp->nextRep != nullptr){
            tmp = tmp->nextRep;
        }
        tmp ->nextRep = new  RepairList(newRepair);
        tmp->nextRep->equ = Equipment(reser);
//        qDebug()<<QStringLiteral("测试rHead->equ:")<<rHead->equ.device_name;
        repairNumber++;
        return;
    }
}

void Admin::afterRepair(RepairList after)   //将维修结束的设备放回实验室
{
    RepairList *res,*cur;
    cur = &after;
    res = searchRepair(after.iden);
    if(res == nullptr){
        emit returnEquErro();
        return;
    }
    addNewEqu(res->equ);
    delete  res;
}

void Admin::scrapEqu(ScrapList newScrap)    //报废设备
{
    ScrapList *cur = &newScrap;
    Equipment *res;
    res = search(cur->sDevice_name,cur->sDevice_lot);
    if(res == nullptr){
        emit ScrapErro();
        return;
    }
/*    if(equNumber >= 2)
        qDebug()<<QStringLiteral("搜索完毕:")<<res->nextEqu->device_name;
    else {
        qDebug()<<QStringLiteral("搜索完毕:")<<res->device_name;
    }*/
    modifyEqu(res,cur->sDevice_number,cur->sDevice_name,cur->sDevice_lot);
//    qDebug()<<QStringLiteral("修改节点成功");
    if(scrapNumber == 0){
        sHead = new ScrapList(newScrap);
        scrapNumber ++;
        return;
    }
    else {
        ScrapList *tmp = sHead;
//        int n = 0;
//        qDebug()<<QStringLiteral("开始查找对应尾指针");
        while(tmp->nextScrap != nullptr){
//            qDebug()<<++n;
            tmp = tmp->nextScrap;
        }
//        qDebug()<<QStringLiteral("成功找到对应尾指针");
        tmp ->nextScrap = new ScrapList(newScrap); // 添加新的报废信息
        scrapNumber++;
        return;
    }

}


ScrapList::ScrapList()
{
    nextScrap =nullptr;
}

ScrapList::ScrapList(const ScrapList &other)
{
    sDevice_name = other.sDevice_name;
    sDevice_number = other.sDevice_number;
    sDevice_lot = other.sDevice_lot;
    sDate = other.sDate;
    sRemark = other.sRemark;   //记录报废备注
    nextScrap = other.nextScrap;
}

RepairList::RepairList()
{
    nextRep = nullptr;
}

RepairList::RepairList(const RepairList &other)   //复制构造函数
{
    rDevice_name = other.rDevice_name;
    rCost = other.rCost;
    iden = other.iden;   //编号
    rMan = other.rMan;
    rVender = other.rVender;
    rDevice_number = other.rDevice_number;
    nextRep = other.nextRep;
    equ = other.equ;
}
