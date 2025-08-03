#include "canreceiver.h"
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstring>
#include<qstring.h>
#include <QThread>
#include <QDebug>
#include<iostream>
using namespace std;

canreceiver::canreceiver(const QString &ligne,QObject *parent) {
    vcan_name=ligne;

}
void canreceiver::listen(){
    // open can socket
    int sock = socket(PF_CAN,SOCK_RAW,CAN_RAW);
    if (sock <0){
        perror("socket:");
     emit error_("Erreur : socket");

    }



    //bind vcan0
    const char* vcan_ = vcan_name.toUtf8().constData();
    struct ifreq ifr{};
    strcpy(ifr.ifr_name,vcan_);
    if(ioctl(sock,SIOCGIFINDEX,&ifr)<0)
    {
        perror("ioctl : ");
        emit error_("Erreur : ioctl");


    }

    struct sockaddr_can addr{};
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if(bind(sock,(struct sockaddr*)&addr,sizeof(addr))<0){
        perror("bind");
        emit error_("Erreur : bind");

    }




    QString full_message ;
    while(running){
        struct can_frame frame{};
        int nbyte = read(sock,&frame,sizeof(frame));

        if(nbyte<0){
            perror("read");
            emit error_("Erreur : read");
            break;
        }
        if(!read__){

        emit read_message();
            read__ =true;
        }
        // convert data to readable texte

        QString msg = QString::fromUtf8((char*)frame.data, frame.can_dlc);

        emit id_received(QString("0x%1").arg(frame.can_id, 3, 16, QLatin1Char('0')).toUpper());


        //string chunk(reinterpret_cast<char*>(frame.data));//take the raw CAN data (which is in bytes like 0x68 to string
        chunk = QString::fromUtf8(reinterpret_cast<char*>(frame.data),frame.can_dlc);

            emit ChunkRecived(chunk);
            full_message +=chunk ;
            chunk.clear();




        if(frame.can_dlc<8){
            emit fullmessage(full_message);

            full_message.clear();
        }


    }
    ::close(sock);


}

void canreceiver::stopRunning(){
    running = false;
}


void canreceiver::setRunning(bool value){
    running = value;
}
// receiverwindow.cpp
