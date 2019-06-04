#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "admin.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initTabWidget();    //初始化所有TabWidget
    void initTab_2();
    void initTable_1();
    void initTable_2();
    void initTab_3();
    void initTable_3();
    void initTab_4();
    void initTab_5();
    void conn();     //将对应的信号与槽连接起来
    void outputOneEqu_1(Equipment *cur,int n);
    void outputOneEqu_2(Equipment *cur,int n);
    void outputOneEqu_3(RepairList *cur,int n);
    void outputOneEqu_scrap(ScrapList *cur, int n);
    void outputAllRepair();   //打印所有设备维修信息
    void outputAllEqu();    //打印所有正常设备信息
    void outputByDevice_name(QString find);   //根据设备名称打印正常的设备的信息
    void outputScrapEqu();  //打印所有已报废信息


signals:
    //tab_1
    void addEqu(Equipment temp);    //作为添加设备的信号

    //tab_3
    void repairEqu(RepairList tmp,QString lot);    //提交维修信息
    void afterRepair(RepairList tmp);
/*    void outputRepairList();     //查找相关设备的信息
    void searchByDeviceName_3(QString deviceName);
    void searchByProductor(QString productor);
    void searchByRepairDate(QDate &tmp);*/

    //tab_4
    void scrapEqu(ScrapList tmp);
/*    void outputScrapList();
    void searchByDeviceName_4(QString deviceName);
    void searchByScrapDate(QDate &temp);*/

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_s_currentIndexChanged(const QString &arg1);

    void on_action_logout_triggered();

    void on_action_resetpass_triggered();

    void on_comboBox_repair_currentIndexChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_s_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void scrapErro();
    void RepairErro();
    void returnEquErro();
    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();
protected:
    void closeEvent(QCloseEvent *event);    //捕捉窗口关闭信号之后将文件写入本地
private:
    Ui::MainWindow *ui;
    Admin *admin;
};

#endif // MAINWINDOW_H
