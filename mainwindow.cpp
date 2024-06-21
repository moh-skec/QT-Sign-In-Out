#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "signup.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QCryptographicHash>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    QString path = QFileDialog::getOpenFileName(this, "Choose a directory!", QDir::homePath());
    name = path;
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_sign_up_clicked(){
    signup *sign = new signup(this,this);
    sign->exec();
}

void MainWindow::on_pushButton_login_clicked(){
    QString input_username = ui->lineEdit_user_log->text();
    QString input_password = ui->lineEdit_pass_log->text();
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(input_password.toUtf8());
    QByteArray hashedResult = hash.result();
    QString hashedHex = hashedResult.toHex();

    QFile file(name);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString line = in.readLine();

            QStringList fields = line.split('|');


            if (fields.size() >= 2)
            {
                QString username = fields[0];
                QString password = fields[1];

                if (username == input_username && password == hashedHex)
                {
                    QMessageBox::information(this, "title", "Your in!");
                    file.close();
                    return;
                } else if (username == input_username && password != hashedHex)
                {
                    QMessageBox::warning(this, "title", "Wrong password!");
                    file.close();
                    return;
                }

            }

        }

        file.close();

        QMessageBox::warning(this, "title", "User not found!");
    }

}


void MainWindow::on_actionLog_in_triggered()
{
    on_pushButton_login_clicked();
}


void MainWindow::on_actionSign_Up_triggered()
{
    on_sign_up_clicked();
}

