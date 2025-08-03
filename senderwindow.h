#ifndef SENDERWINDOW_H
#define SENDERWINDOW_H
#include <QMessageBox>
#include<qlineedit.h>


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class SenderWindow;
}
QT_END_NAMESPACE

class SenderWindow : public QMainWindow
{
    Q_OBJECT


public:
    SenderWindow(const QString &ligne="",QWidget *parent = nullptr);
    ~SenderWindow();


private:

    Ui::SenderWindow *ui;
    QLineEdit *lineEdit;    // QLineEdit to enter text
    QLineEdit *text_id;    // QLineEdit to enter text
    QLabel *label;          // QLabel to display result
    QMessageBox msgBox;    // Create the message box
    void showMessage();
    QString vcan_name;


private slots :
    void send_clicked();
};
#endif // SENDERWINDOW_H
