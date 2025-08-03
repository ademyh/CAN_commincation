#ifndef CANRECEIVER_H
#define CANRECEIVER_H

#include <QObject>

class canreceiver : public QObject
{

    Q_OBJECT ;
public:

    explicit canreceiver(const QString &ligne="",QObject *parent = nullptr);

signals :
    void ChunkRecived(QString chunk);
    void fullmessage(QString full_message);
    void error_(QString error);
    void id_received(QString id);
    void read_message();
    void data_lc(QString dlc);
public slots :
    void listen();
    void setRunning(bool value=true);
    void stopRunning();

private :
    bool running = true ;
    bool connect_chunk = false ;
    bool read__ = false;
    QString chunk;
    QString vcan_name;





};

#endif // CANRECEIVER_H
