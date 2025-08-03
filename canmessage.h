#ifndef canmessage_H
#define canmessage_H

using namespace std;

#include <linux/can.h>
#include <array>     //for struct can frame
#include <sstream> //C++ array for the data[n]
#include <iomanip> // for formatting output (hex display )


class canmessage{
public :
    canid_t id ;  // ID of message
    uint8_t dlc ; //data lenghth code
    array <uint8_t, 8> data ;// actual message data



    //constructeurs and fonctions
    canmessage();
    canmessage(canid_t id ,uint8_t dlc,const array<uint8_t,8>&data);


    struct can_frame toframe() const ;
    string tostring() const ;


};

#endif // CANMESSAGE_H
