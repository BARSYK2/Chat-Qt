#include "chatwindow.h"
#include "ui_chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &ChatWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    nextBlockSize = 0;
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::on_pushButton_clicked()
{
    socket->connectToHost("127.0.0.1", 2323);

}

void ChatWindow::SendToServer(QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    out<< quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(Data.size()-sizeof(quint16));
    socket->write(Data);
    ui->lineEdit->clear(); //отправка данных на сервер
}

void ChatWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_4);
    if(in.status()==QDataStream::Ok)
    {
        /*QString str;
        in>>str;
        ui->textBrowser->append(str);*/
        for(;;)
        {
            if(nextBlockSize == 0)
            {
                if(socket->bytesAvailable()<2)
                {
                    break;
                }
                in>>nextBlockSize;
            }
            if(socket->bytesAvailable()<nextBlockSize)
            {
                break;
            }
            QString str;
            QTime time;
            in >> time >> str;
            nextBlockSize = 0;
            ui->textBrowser->append(time.toString() + " " + str);
        }
    }

    else
    {
        ui->textBrowser->append("read error");
    }
}


void ChatWindow::on_pushButton_2_clicked()
{
    SendToServer(ui->lineEdit->text());
}


void ChatWindow::on_lineEdit_returnPressed()
{
    SendToServer(ui->lineEdit->text());
}
