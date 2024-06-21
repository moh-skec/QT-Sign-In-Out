#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QString name;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_sign_up_clicked();
    void on_pushButton_login_clicked();

    void on_actionLog_in_triggered();

    void on_actionSign_Up_triggered();

private:
    Ui::MainWindow *ui;
    QString file_path;
};
#endif // MAINWINDOW_H
