#ifndef ADMIN_H
#define ADMIN_H

#include "loginwindow.h"
#include <QWidget>
#include <QDate>
#include <QString>
#include <QMetaType>
#include <QVariant>

typedef struct Equipment{   //存储正常设备的信息
    Equipment();    //初始化设备信息
    Equipment(const Equipment &other);
    Equipment(const Equipment *other);
    void output();
    QString device_name;     //设置为public是为了方便增删改
//    QString device_type;      //
    QString device_number;    //设备号
    QString model_number;     //型号
    QString device_spec;      //规格
    QString device_price;     //单格
    QString device_quantity;   //数量
    QString buy_date;
    QString device_producer;
    QString device_purchaser;
    QString device_lot;     //当相同品牌、批次设备入库时设置该变量，否则默认为1
    Equipment *nextEqu;

} Equipment;

Q_DECLARE_METATYPE(Equipment);

typedef struct ScrapList{    //存储报废的设备信息
    QString sDevice_name;
    QString sDevice_number;
    QString sDevice_lot;
    QString sDate;
    QString sRemark;   //记录报废备注
    ScrapList *nextScrap;
    ScrapList();
    ScrapList(const ScrapList &other);
} ScrapList;


Q_DECLARE_METATYPE(ScrapList);

typedef struct RepairList{    //存储设备的维修信息
    QString rDevice_name;
    QString rCost;
    QString iden;   //编号
    QString rMan;
    QString rVender;
    QString rDevice_number;
    RepairList *nextRep;
    Equipment equ;   //保存被维修的设备的信息，方便恢复
    RepairList();
    RepairList(const RepairList &other);
} RepairList;

Q_DECLARE_METATYPE(RepairList);

class Admin : public QWidget
{
    Q_OBJECT
public:
    explicit Admin(QWidget *parent = nullptr);
    Admin(int kin);//用于软件启动时将本地文件读入内存，完成4
    Admin(const Admin &other);
     ~Admin();
    void Read();    //读文件
    void Write();   //写文件
    void qdebug(Equipment *cur);   //用于验证读写是否正确
    void qdebug(RepairList *cur);
    void qdebug(ScrapList *cur);
    //以下函数读写Equipment
    void readEqument();   //*完成1
    bool writeEqument();  //*完成5

    //以下函数读写ScrapList
    void readSrcapList();  //*完成 2
    bool writeScrapList(); //*完成6

    //以下函数读写RepairList
    void readRepairList(); //*完成3
    bool writeRepairList(); //*完成7
    int getEquNumber(){ return equNumber;}
    int getScrapNumber(){return scrapNumber;}
    int getRepairNumber(){return repairNumber;}
    Equipment *getEHead(){return eHead;}
    RepairList *getRHead(){return rHead;}
    ScrapList *getSHead(){return sHead;}

    Equipment *search(QString name,QString lot);    //根据批次还有设备名查找相关设备
    void deleEqu(Equipment *before,QString name,QString lot);    //before为待删除结点的上一节点
    void modifyEqu(Equipment *before,QString n,QString name,QString lot); //before为待修改结点的上一节点,n为报废或维修的设备数量

    RepairList *searchRepair(QString iden);   //查找相关维修信息
private:
    Equipment *eHead;    //存储正常设备的信息
    int equNumber;
    ScrapList *sHead;    //存储报废设备信息
    int scrapNumber;
    RepairList *rHead;   //存储被维修设备的信息
    int repairNumber;
signals:
    void ScrapErro();
    void RepairErro();
    void returnEquErro();
public slots:
    //以下函数实现tab（设备入库）相关功能
    bool addNewEqu(Equipment newEqu);   //增加新设备   *完成8

    //以下函数对应tab_2（运行状况管理）中的的相关查询函数


    //以下函数实现tab_3（报修管理）中相关功能
    void repairEqu(RepairList newRepair, QString lot);   //维修设备
    void afterRepair(RepairList after);  //维修完成

    //以下函数实现tab_4（报废管理）相关功能
    void scrapEqu( ScrapList newScrap);    //报废设备
};
Q_DECLARE_METATYPE(Admin);
#endif // ADMIN_H
