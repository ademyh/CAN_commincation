#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include<qlineedit.h>
#include<QString>
#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include<qstringlist.h>
#include<QMessageBox>
#include "receiverwindow.h"
#include "senderwindow.h"
#include "canreceiver.h"



using namespace std ;
namespace Ui {
class homewindow;
}

class homewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit homewindow(QWidget *parent = nullptr);
    void showMessage_();


    ~homewindow();

signals :
    void name_interface(QString vcan_name);


private slots:
    void on_pushButton_clicked();


private:
    Ui::homewindow *ui;
    QLineEdit ligneEdite;
    QMessageBox msgBox;
    QLabel *label_3;
    SenderWindow *S = nullptr;
    ReceiverWindow *R = nullptr;
    canreceiver *c=nullptr;
    bool connected = false;
    bool show_connect = false ;
};

#endif // HOMEWINDOW_H
