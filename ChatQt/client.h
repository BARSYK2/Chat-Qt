
#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include "chatwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow

{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void on_go_clicked();

private:
    Ui::Client *ui;
    ChatWindow *window;
};

#endif // CLIENT_H
