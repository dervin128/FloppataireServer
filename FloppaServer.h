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
    void onNewConnection();
    void readPendingDatagrams();
    void clientDisconnected();


private:
    void processData(QNetworkDatagram datagram);

    const QHostAddress m_address = QHostAddress("192.168.1.104");
    const quint16 m_port = 60420;
    QUdpSocket m_sender;
    QUdpSocket m_reveiver;
    QSet<QHostAddress> m_clients;
};
