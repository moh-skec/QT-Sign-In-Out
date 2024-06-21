#include "signup.h"
#include "ui_signup.h"
#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QFileDialog>
#include <QFile>
#include <QCryptographicHash>

using namespace std;

signup::signup(MainWindow *mainWindow, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::signup),
    mainWindow(mainWindow){
    ui->setupUi(this);
    ui->comboBox_gender->addItem("male");
    ui->comboBox_gender->addItem("female");
    file_name_sign_up = mainWindow->name;
}

signup::~signup(){
    delete ui;
}

void signup::on_pushButton_clicked(){
    if(ui->lineEdit_user_name->text().isEmpty())
    {
        QMessageBox::warning(this, "user name", "User name can't be empty");
        return;
    } else
    {
        for (auto a : ui->lineEdit_user_name->text())
        {
            if(!a.isLetterOrNumber() && a != '_')
            {
                QMessageBox::warning(this, "Error", "A username can only contain letters, numbers, and '_'!");
                return;
            }

        }

    }

    if(ui->lineEdit_password->text().isEmpty())
    {
        QMessageBox::warning(this, "password", "Password can't be empty!");
        return;
    } else
    {
        for (auto a : ui->lineEdit_password->text())
        {
            if(a == '|')
            {
                QMessageBox::warning(this, "Error", "A password can't contain '|'!");
                return;
            }

        }

    }

    if(ui->lineEdit_name->text().isEmpty())
    {
        QMessageBox::warning(this, "name", "Name can't be empty!");
        return;
    } else
    {
        for (auto a : ui->lineEdit_name->text())
        {
            if(!a.isLetterOrNumber())
            {
                QMessageBox::warning(this, "Error", "A name can only contain letters, numbers");
                return;
            }

        }

    }

    if(ui->lineEdit_email->text().isEmpty())
    {
        QMessageBox::warning(this, "email", "Email can't be empty!");
    } else
    {
        for (auto a : ui->lineEdit_email->text())
        {
            if(!a.isLetterOrNumber() && a != '@' && a != '.')
            {
                QMessageBox::warning(this, "Error", "Invalid email!");
                return;
            }

        }

    }

    if(ui->lineEdit_age->text().isEmpty())
    {
        QMessageBox::warning(this, "age", "Age can't be empty!");
        return;
    } else
    {
        for (auto a : ui->lineEdit_age->text())
        {
            if(!a.isNumber())
            {
                QMessageBox::warning(this, "Error", "An age can only contain numbers!");
                return;
            }

        }

    }

    QString user_name = ui->lineEdit_user_name->text();
    QString password = ui->lineEdit_password->text();
    QString name = ui->lineEdit_name->text();
    QString email = ui->lineEdit_email->text();
    QString age = ui->lineEdit_age->text();
    QString gender = ui->comboBox_gender->currentText();
    QFile my_file(file_name_sign_up);

    if (my_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&my_file);

        while (!in.atEnd())
        {
            QString line = in.readLine();

            QStringList fields = line.split('|');

            QString user_name_1 = fields[0];

            if(user_name_1 == user_name)
            {
                QMessageBox::warning(this, "title", "There is user with the same username!");
                return;
            }

            my_file.close();
        }

    }

    QFile my_file_1(file_name_sign_up);

    if (!my_file_1.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QMessageBox::warning(this, "title", "Could not open file!");

        return;
    } else
    {
        QCryptographicHash hash(QCryptographicHash::Sha256);
        hash.addData(password.toUtf8());
        QByteArray hashedResult = hash.result();
        QString hashedHex = hashedResult.toHex();
        QTextStream out(&my_file_1);
        out << user_name << '|' << hashedHex << '|' << name << '|' << email << '|' << age << '|' << gender << Qt::endl;

        my_file_1.flush();
        my_file_1.close();
        QMessageBox::information(this, "title", "Added sucesfully!");
    }

}




void signup::on_pushButton_pressed()
{

}

