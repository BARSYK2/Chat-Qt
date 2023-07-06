#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include <QTcpSocket>
#include <QTime>

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QDialog
{
    Q_OBJECT

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_returnPressed();

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();

private:
    Ui::ChatWindow *ui;
    QTcpSocket *socket;
    QByteArray Data;
    void SendToServer(QString str);
    quint16 nextBlockSize;

public slots:
    void slotReadyRead();
};

#endif // CHATWINDOW_H
