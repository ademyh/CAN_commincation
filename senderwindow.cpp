#include "senderwindow.h"
#include "ui_senderwindow.h"

#include<iostream>
#include<cstring>
#include<sys/types.h>
#include<sys/socket.h>
#include<linux/can.h>
#include<linux/can/raw.h>
#include<unistd.h>
#include <net/if.h>        // for struct ifreq and SIOCGIFINDEX
#include <sys/ioctl.h>     // for ioctl()
#include <cstring>         // for std::strcpy
#include <vector>
#include "canmessage.h"

using namespace std;

SenderWindow::SenderWindow(const QString &ligne,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SenderWindow)
{
    ui->setupUi(this);
    vcan_name=ligne;



    // Add custom buttons to the message box
    msgBox.addButton(QMessageBox::Ok);

    // Connect the button's click signal to the slot
    connect(ui->pushButton, &QPushButton::clicked,this,&SenderWindow::send_clicked);


}

SenderWindow::~SenderWindow()
{
    delete ui;
}


void SenderWindow::send_clicked(){




    // stup CAN socket
    int sock = socket(PF_CAN,SOCK_RAW,CAN_RAW);
    if (sock<0) {
        perror("socket");  //Shows both your custom message and the system error
        // Set the message text
        msgBox.setText("erreur.");
        showMessage();
        // return;
    }
    //first step get the message from the TEXT_EDIT

    QString inputText = ui->lineEdit->text();  // Get the text entered by the user
    // Get the message from QLineEdit
    if (inputText.isEmpty()) {
        msgBox.setText("Please enter data to send.");
        showMessage();
        ::close(sock);
        return;
    }

    // Convert QString to QByteArray (UTF-8 encoded)
    QByteArray byteArray = inputText.toUtf8();
    vector<uint8_t> bytes(byteArray.begin(), byteArray.end()) ;// make it byte by bytes

    struct ifreq ifr {};
    const char* vcan_ = vcan_name.toUtf8().constData();
    strcpy(ifr.ifr_name,vcan_);
    ioctl(sock,SIOCGIFINDEX,&ifr);   // SIOCGIFINDEX (mapping the interface )= A macro that tells ioctl: "Get the index of the network interface"
    //ioctl fills ifr.ifr_name = "vcan0" in ifr.ifr_ifindex.

    struct sockaddr_can addr {};
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Bind");
        msgBox.setText("erreur.");
        showMessage();
        // return ;
    }
    // Get the text from QLineEdit
    QString inputText_id = ui->text_id->text();
    QString value ="0x" + inputText_id;

    bool ok;
    uint16_t base_id = value.toUShort(&ok, 16);  // base 16 = hexadecimal



    // Convert the text to uint16_t
    if (!ok) {
        msgBox.setText("Invalid ID entered.");
        showMessage();
        ::close(sock);
        return;
    }


    //last step split and send

    const size_t chunkSize=8;
    //uint16_t base_id = 0x123 ;
    for (size_t i = 0 ;i < bytes.size();i+=chunkSize){// size_t is for the Sizes, indexes, loops

        array<uint8_t,8> chunk={0};
        size_t len = min(chunkSize , bytes.size()-i);

        for (size_t j=0 ; j<len;j++){
            chunk[j] = bytes[i+j];

        }

        canmessage msg(base_id + i, len, chunk);
        struct can_frame frame =msg.toframe();
        write(sock,&frame,sizeof(frame));

        cout<<msg.tostring() <<endl;
        usleep(10000);// small delay (10ms) for clarity in candump
        perror("Bind");
        msgBox.setText("erreur.");





    }
    ::close(sock);
    msgBox.setText("The message has been sent successfully.");
    showMessage();
    ui->label->setText("The message has been sent successfully.");



}



void SenderWindow::showMessage()
{
    // Create the message box

    // Set the icon type (Information, Warning, Critical, etc.)
    msgBox.setIcon(QMessageBox::Information);

    // Set the title of the message box
    msgBox.setWindowTitle("Information");



    // Set a detailed message (optional)
    msgBox.setInformativeText("This is some additional detailed information.");


    // Show the message box and wait for the user's response
    msgBox.exec();  // It blocks until the user responds
}
