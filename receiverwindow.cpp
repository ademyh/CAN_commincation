#include "receiverwindow.h"
#include "ui_receiverwindow.h"
#include <QThread>
//#include "homewindow.h"



using namespace std ;
ReceiverWindow::ReceiverWindow(const QString &ligne,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ReceiverWindow)
{
    ui->setupUi(this);
    ui->textBrowser->clear();
    ui->textBrowser->setText("⏳ Écoute de vcan...");
    vcan_name=ligne;

//    homewindow *home = new homewindow();
 /*   connect(home, &homewindow::name_interface, this, [=](QString vcan_name){
        ui->textBrowser->append(vcan_name);

    });*/
    // Connexion du signal de `homewindow` à un slot dans `ReceiverWindow`
 //       connect(home, &homewindow::name_interface, this, &ReceiverWindow::onNameInterfaceReceived);

   // receiver->setRunning(true);


    // Add custom buttons to the message box
    msgBox.addButton(QMessageBox::Ok);


    // Exemple : définir un texte au démarrage

    ui->textBrowser->setText("click to  start ......");
    ui->textBrowser->setText(ligne);

    connect(ui->start_button,&QPushButton::clicked,this,&ReceiverWindow::on_start_button_clicked);
    connect(ui->stop_button,&QPushButton::clicked,this,&ReceiverWindow::on_stop_button_clicked);


}




ReceiverWindow::~ReceiverWindow()
{
    delete ui;
}




void ReceiverWindow::on_start_button_clicked()
{

    ui->textBrowser->clear();

    ui->textBrowser->setText(QString("Listening on %1... (waiting for CAN frames)").arg(vcan_name));


   if (receiver != nullptr) return;
   // Créer un thread
   QThread *thread = new QThread;
   canreceiver *receiver = new canreceiver;

   // Initialiser running = true avant de démarrer
   receiver->setRunning(true);

   connect(thread,&QThread::started,receiver,&canreceiver::listen);
   if(!connected_chunk){
   connect(receiver, &canreceiver::ChunkRecived, this, [=](QString chunk){
       ui->textBrowser->append("🔹 Chunk: " + chunk);
       });
       connected_chunk = true ;
   }
   if(!connected_read){
       connect(receiver, &canreceiver::read_message, this, [=](){
           clear_textBrowse();
       });
       connected_read = true ;
   }
   if (!connected){

       connect(receiver, &canreceiver::id_received, this, [=](QString id){
           ui->textBrowser->append("🔹 id: " + id);
       });
       connected = true;
   }
   if (!connected_fullmessage){
       connect(receiver, &canreceiver::fullmessage, this, [=](QString full){
           ui->textBrowser->append("✅ Message complet: " + full);
       });
       connected_fullmessage = true ;
   }
   connect(receiver, &canreceiver::error_, this, [=](QString err){
       ui->textBrowser->append("❌ Erreur: " + err);
   });

   // Nettoyage
   connect(receiver, &canreceiver::error_, thread, &QThread::quit);
   connect(thread, &QThread::finished, receiver, &QObject::deleteLater);
   connect(thread, &QThread::finished, thread, &QObject::deleteLater);

   thread->start();
   receiver->moveToThread(thread);
   // Connect the sender's signal to a slot or lambda in ReceiverWindow

   //connect(thread,&QThread::started,sender,&SenderWindow::send_clicked);
   //connect(sender, &SenderWindow::clicked, this, [=](){ ui->textEdit->clear();});





}



void ReceiverWindow::showmessage(){



    // Set the icon type (Information, Warning, Critical, etc.)
    msgBox.setIcon(QMessageBox::Information);

    // Set the title of the message box
    msgBox.setWindowTitle("Information");



    // Set a detailed message (optional)
    msgBox.setInformativeText("This is some additional detailed information.");


    // Show the message box and wait for the user's response
    msgBox.exec();  // It blocks until the user responds

}



void ReceiverWindow::update_string(string chunk_,QString qstr){

    ui->textBrowser->setText(qstr);
    QString chunk__= QString::fromStdString(chunk_); // conver to Qstring
    ui->textBrowser->setText(chunk__);


}
void ReceiverWindow::append_text(string chunk_,QString qstr){

    ui->textBrowser->append(qstr);
    QString chunk__= QString::fromStdString(chunk_); // conver to Qstring
    ui->textBrowser->setText(chunk__);
}


void ReceiverWindow::clear_textBrowse(){
    ui->textBrowser->clear();

}



void ReceiverWindow::on_stop_button_clicked()
{

    ui->textBrowser->clear();

    if (receiver) {
        QMetaObject::invokeMethod(receiver, "stop", Qt::QueuedConnection); // arrête la boucle
    }
    if (receiverThread) {
        receiverThread->quit(); // quitte la boucle Qt
        receiverThread->wait(); // attend la fin
    }

    receiver = nullptr;
    receiverThread = nullptr;

    ui->textBrowser->append("🛑 Réception arrêtée.");
    receiver->stopRunning();

}
//void ReceiverWindow::onNameInterfaceReceived(const QString &vcan_name) {
    // Mets à jour l'interface, ou fais quelque chose avec le nom de l'interface vcan
  //  ui->textBrowser->append("VCAN interface updated: " + vcan_name);  // Affiche le nom dans un QTextBrowser
//}
