
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QNetworkInterface>

#include <QHostInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString protocolName(QAbstractSocket::NetworkLayerProtocol protocol)
    {
        switch(protocol)
        {
        case QAbstractSocket::IPv4Protocol:
            return "IPv4";
        case QAbstractSocket::IPv6Protocol:
            return "IPv6";
        case QAbstractSocket::AnyIPProtocol:
            return "Any Internet protocol";
        default:
            return "Unknown Network Layer protocol";
        }
    }
    void do_lookedupHostInfo(const QHostInfo &host)
    {
        QList<QHostAddress>addrList=host.addresses();
        if(addrList.isEmpty())
        {
            return;
        }
        foreach(QHostAddress host,addrList)
        {
            //只显示IPv4
            bool show=ui->chkBox_OnlyIPv4->isChecked();
            show=show?(host.protocol()==QAbstractSocket::IPv4Protocol):true;
            if(show)
            {
                ui->textEdit->appendPlainText(("协议:"+protocolName(host.AnyIPProtocol)));
                ui->textEdit->appendPlainText(host.toString());
                ui->textEdit->appendPlainText(QString("isGlobal()=%1\n").arg(host.isGlobal()));

            }
        }
    }
    QString interfaceTyoe(QNetworkInterface::InterfaceType type)
    {
        switch (type) {
        case QNetworkInterface::Unknown:
            return "Unkown";

        case QNetworkInterface::Loopback:
            return "Loopback";
        case QNetworkInterface::Ethernet:
            return "Ethernet";
            case QNetworkInterface::Wifi:
            return "Wifi";

        default:
            return "onter type";

        }
    }


private slots:
    void on_pushButton_clicked();

    void on_btnGetHostInfo_clicked();

    void on_lookupHostInfo_clicked();

    void on_pushButton_2_clicked();

    void on_btn_Add_clicked();

    void on_btn_Inter_clicked();

    void on_btn__clicked();

private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
