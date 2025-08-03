#include "canmessage.h"



canmessage::canmessage() : id(0) ,dlc(0),data{0}{} // initialise empty message
canmessage::canmessage(canid_t id , uint8_t dlc,const array<uint8_t,8>&data):id(id),dlc(dlc),data(data){}




// preparing the message in the format Linux expects


struct can_frame canmessage::toframe() const{
    struct can_frame frame {};  // // Zero-initialize all fields


    frame.can_id= id;
    frame.can_dlc=dlc;
    for(int i=0;i<dlc;i++)
    {
        frame.data[i]=data[i];
    }
    return frame;

};

string canmessage::tostring() const{

    ostringstream oss;   //output string stream.
    oss << hex << uppercase << setfill('0');  //This sets formatting options for the stream:
    // uppercase >>	Use capital letters: A-F instead of a-f
    //setfill('0')	Fill empty digits with 0

    oss << "ID: 0x" << setw(3) << id << " DLC: "<< dec << (int)dlc ;
    oss<<"data: ";
    for(int i=0;i<dlc;i++){
        oss<<" "<<hex<<setw(2)<<(int)data[i];
    }
    return oss.str();


};
