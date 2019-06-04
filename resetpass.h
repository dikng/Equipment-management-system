#ifndef RESETPASS_H
#define RESETPASS_H

#include <QWidget>

namespace Ui {
class resetPass;
}

class resetPass : public QWidget
{
    Q_OBJECT

public:
    explicit resetPass(QWidget *parent = nullptr);
    ~resetPass();

private:
    Ui::resetPass *ui;
};

#endif // RESETPASS_H
