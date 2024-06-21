#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class signup;
}

class signup : public QDialog
{
    Q_OBJECT

public:
    signup(MainWindow *mainWindow, QWidget *parent);
    ~signup();
    QString file_name_sign_up;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_pressed();

private:
    Ui::signup *ui;
    MainWindow *mainWindow;

};

#endif // SIGNUP_H
