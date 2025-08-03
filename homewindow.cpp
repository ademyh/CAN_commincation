#include "homewindow.h"
#include "ui_homewindow.h"

homewindow::homewindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::homewindow)
{
    ui->setupUi(this);
// Add custom buttons to the message box
    ui->label_3->setPixmap(QPixmap("/adem/download.png"));
    msgBox.addButton(QMessageBox::Ok);
    connect(ui->pushButton,&QPushButton::clicked,this,&homewindow::on_pushButton_clicked);


}

homewindow::~homewindow()
{
    delete ui;
}

void homewindow::on_pushButton_clicked()
{
    /*string ligne = ui->lineEdit->text().toStdString();
    string lign_ = "ip link add dev "+ligne+" type vcan";
    string lign__ = "ip link set up "+ligne;
    const char* ligne_c = lign_.c_str();
    const char* ligne_cc = lign__.c_str();*/
    QString ligne = ui->lineEdit->text();
    //const char* name_vcan = ligne.toUtf8().constData();
    // 🟢 Create windows here
    S = new SenderWindow(ligne);
    R = new ReceiverWindow(ligne);
    c= new canreceiver(ligne);

    QString cmd = QString("ip link show %1").arg(ligne);
    QProcess Qpros;
    Qpros.start("sh",QStringList() << "-c" <<cmd);
    Qpros.waitForFinished();
    if(Qpros.exitCode()==0){

        if(!show_connect){
        this->hide();     // Better than close() to keep app running
        S->show();
        R->show();
        msgBox.setText("VCAN already existed ");
        showMessage_();
        show_connect = true;
        }
    }
    else{
    QString fullCommand = QString("modprobe vcan && ip link add dev %1 type vcan && ip link set up %1").arg(ligne);
    int exitCode ;
    if(!connected){


    exitCode = QProcess::execute("pkexec", QStringList() << "sh" << "-c" << fullCommand);
    connected = true ;
    }

    if (exitCode != 0) {
        qDebug() << "Erreur d’exécution avec pkexec";
    }


/*
    QStringList commands = {
        "modprobe vcan",
        ligne_c,
        ligne_cc
    };


    for (const QString &cmd : commands) {
        int exitCode = QProcess::execute("pkexec", QStringList() << "sh" << "-c" << cmd);
        if (exitCode != 0) {


        }
    }



    msgBox.setText("Please enter data to send.");
    // Create the message box

    // Set the icon type (Information, Warning, Critical, etc.)
    msgBox.setIcon(QMessageBox::Information);

    // Set the title of the message box
    msgBox.setWindowTitle("Information");



    // Set a detailed message (optional)
    msgBox.setInformativeText("This is some additional detailed information.");


    // Show the message box and wait for the user's response
    msgBox.exec();  // It blocks until the user responds
*/
    Qpros.start("sh",QStringList() << "-c" <<cmd);
    Qpros.waitForFinished();
    if(Qpros.exitCode()==0){

        if(!show_connect){
        this->hide();     // Better than close() to keep app running
        S->show();
        R->show();
        msgBox.setText(QString("%1 is now active  ").arg(ligne));
        showMessage_();
       //emit name_interface(ligne);
        show_connect = true;
        }

    }



}
}
void homewindow::showMessage_()
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



