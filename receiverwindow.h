#ifndef RECEIVERWINDOW_H
#define RECEIVERWINDOW_H


#include <QMainWindow>
#include<qtextedit.h>
#include<qtextbrowser.h>
#include<qmessagebox.h>
#include "canreceiver.h"

using namespace std;

namespace Ui {
class ReceiverWindow;
}

class ReceiverWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReceiverWindow(const QString &ligne="",QWidget *parent = nullptr);
    ~ReceiverWindow();
    void clear_textBrowse();


private slots:
    void on_start_button_clicked();

    void on_stop_button_clicked();


private:
    Ui::ReceiverWindow *ui;
    QTextBrowser textBrowser;
    void showmessage();
    QMessageBox msgBox;    // Create the message box
    void update_string(string chunk_,QString qstr="");
    void append_text(string chunk_,QString qstr="");
    canreceiver *receiver = nullptr;
    QThread *receiverThread = nullptr;
    bool connected  = false;
    bool connected_chunk  = false;
    bool connected_fullmessage  = false;
    bool connected_read  = false;
    void onNameInterfaceReceived(const QString &vcan_name);  // Slot pour recevoir le nom de l'interface
    QString vcan_name;







};

#endif // RECEIVERWINDOW_H
