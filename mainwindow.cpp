
#include "mainwindow.h"
#include "ui_mainwindow.h"
 #include <QHostInfo>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnGetHostInfo_clicked()
{
    ui->textEdit->clear();
    QString hostName=QHostInfo::localHostName();
    ui->textEdit->appendPlainText("本机主机名： "+hostName+"\n");
    QHostInfo hostInfo=QHostInfo::fromName(hostName);
    QList<QHostAddress>addrList=hostInfo.addresses();
    if(addrList.isEmpty())
        return;
    foreach (QHostAddress host, addrList) {
        bool show=ui->chkBox_OnlyIPv4->isChecked();
        show =show?(host.protocol()==QAbstractSocket::IPv4Protocol):true;
        if(show)
        {
            ui->textEdit->appendPlainText("协议："+protocolName(host.protocol()));
            ui->textEdit->appendPlainText("本机ip地址:"+host.toString());
            ui->textEdit->appendPlainText(QString("isGlobal()=%1\n").arg(host.isGlobal()));
        }

    }
}


void MainWindow::on_lookupHostInfo_clicked()
{
//
    ui->textEdit->clear();
    QString hostname=ui->comboBox->currentText();
    ui->textEdit->appendPlainText("正在查找主机信息"+hostname);
    QHostInfo::lookupHost(hostname,this,SLOT(do_lookedupHostInfo(QHostInfo)));
}








void MainWindow::on_btn_Inter_clicked()
{
    ui->textEdit->clear();
    QList<QNetworkInterface>list=QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface interface ,list)
    {
        if(!interface.isValid())
            continue;
        ui->textEdit->appendPlainText("设备名称："+interface.humanReadableName());
        ui->textEdit->appendPlainText("硬件地址："+interface.hardwareAddress());
        ui->textEdit->appendPlainText("接口类型"+interfaceTyoe(interface.type()));
        QList<QNetworkAddressEntry>entryList=interface.addressEntries();//地址列表
        foreach (QNetworkAddressEntry entry,entryList) {
            ui->textEdit->appendPlainText("IP地址 ："+entry.ip().toString());
            ui->textEdit->appendPlainText("子网掩码： "+entry.netmask().toString());
            ui->textEdit->appendPlainText("广播地址："+entry.broadcast().toString()+"\n");


        }

    }
}


void MainWindow::on_btn_Add_clicked()
{
    ui->textEdit->clear();
    QList<QHostAddress>addrList=QNetworkInterface::allAddresses();
    if(addrList.isEmpty())
     return;
    foreach(QHostAddress host,addrList)
    {
     bool show=ui->chkBox_OnlyIPv4->isChecked();// 只显示IPv4地址
     show=show?(host.protocol()==QAbstractSocket::IPv4Protocol):true;
     if(show)
     {
            ui->textEdit->appendPlainText("协议："+protocolName(host.protocol()));
            ui->textEdit->appendPlainText("IP地址"+host.toString());
             ui->textEdit->appendPlainText(QString(" isGlobal()=%1\n").arg(host.isGlobal()));
     }
    }
}

