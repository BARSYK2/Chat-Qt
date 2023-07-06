
#include "client.h"
#include "ui_client.h"


Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
}

Client::~Client()
{
    delete ui;
}

void Client::on_go_clicked()
{

    window = new ChatWindow(this);
    window->show();

}
