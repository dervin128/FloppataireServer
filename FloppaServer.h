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

    const QHostAddress m_address = QHostAddress("127.0.0.1");
    const quint16 m_port = 15000;
    QUdpSocket m_sender;
    QUdpSocket m_reveiver;
    QSet<QHostAddress> m_clients;
};
