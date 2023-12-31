
#include "server.h"

Server::Server()
{
    if(this->listen(QHostAddress::Any, 2323)) //запуск сервера
    {
        qDebug()<<"start";
    }
    else
    {
        qDebug()<<"error";
    }
    nextBlockSize = 0; //обнуляем, чтобы данные приходили правильно
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    Sockets.push_back(socket);
    qDebug()<<"client connected"<<socketDescriptor; //для каждого нового создаём новый сокет
}

void Server::slotReadyRead()
{
    socket = (QTcpSocket*)sender();
    QDataStream in(socket); //работа с данными в сокете
    in.setVersion(QDataStream::Qt_6_4);
    if(in.status()==QDataStream::Ok)
    {
        qDebug()<<"read";
        /*QString str;
        in>>str;
        qDebug() << str;
        SendToClient(str);*/
        for(;;)
        {
            if(nextBlockSize == 0)
            {
                qDebug()<<"nextBlockSize = 0";
                if(socket->bytesAvailable()<2)
                {
                    qDebug() <<"Data < 2, break";
                    break;
                }
                in>>nextBlockSize;
                qDebug() << "nextBlockSize = " << nextBlockSize;
            }
            if(socket->bytesAvailable()<nextBlockSize)
            {
                qDebug() << "Data not full, break";
                break;
            }
            QString str;
            QTime time;
            in>>time>>str;
            nextBlockSize = 0;
            SendToClient(str);
            break;
        }
    }
    else
    {
        qDebug()<<"DataStream error";
    }
}

void Server::SendToClient(QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    out<< quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(Data.size()-sizeof(quint16));
    //socket->write(Data);
    for(int i = 0; i < Sockets.size(); i++)
    {
        Sockets[i]->write(Data);
    } // отправка всем клиентам
}

