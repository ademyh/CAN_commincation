#include "homewindow.h"
#include <QApplication>
#include "receiverwindow.h"
#include "senderwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    homewindow whome;
    SenderWindow *S = nullptr;
    ReceiverWindow *R = nullptr;

    whome.show();
    // 🟢 Create windows here
    S = new SenderWindow();
    R = new ReceiverWindow();
    //S->show();
    //R->show();




    return a.exec();

}
