#pragma once

#include <QObject>
#include <QList>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QTcpServer>

class FloppaServer : public QObject {
    Q_OBJECT

public:

    FloppaServer(QObject* parent = nullptr);
    ~FloppaServer();

signals:
    void closed();

private slots:
    void readPendingDatagrams();
    void onNewConnection();
    void onReadyRead();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);


private:
    void processData(QNetworkDatagram datagram);

    QTcpServer* const m_tcpServer;
    QUdpSocket* const m_UdpSocket;
    const QHostAddress m_address = QHostAddress("192.168.1.104");
    const quint16 m_port = 60420;
    //QSet<QHostAddress> m_clients;
    QList<QTcpSocket*> m_clients;


};
