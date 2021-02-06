#pragma once

#include <QObject>
#include <QList>
#include <QUdpSocket>

class FloppaServer : public QObject {
    Q_OBJECT

public:

    FloppaServer(QObject* parent = nullptr);
    ~FloppaServer();

signals:
    void closed();

private slots:
    void readPendingDatagrams();


private:
    void processData(QNetworkDatagram datagram);

    const QHostAddress m_address = QHostAddress("192.168.1.104");
    const quint16 m_port = 60420;
    QUdpSocket m_socket;
    QSet<QHostAddress> m_clients;
};
