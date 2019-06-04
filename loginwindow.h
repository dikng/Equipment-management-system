#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QMouseEvent>
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint mousePoint;            //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;            //鼠标是否按下


private slots:
    void on_Exit_clicked();

    void on_Login_clicked();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
