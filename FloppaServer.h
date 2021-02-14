#pragma once

#include <QObject>
#include <QList>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QTcpServer>
#include "LobbyController.h"
#include "ServerData.h"

class FloppaServer : public QObject {
    Q_OBJECT

public:
    FloppaServer(LobbyController* lobbyController, PlayerController* playerController, QObject* parent = nullptr);
    ~FloppaServer();
    ServerData::ServerContext serverContext(const QJsonObject obj) const;

signals:
    void closed();

private slots:
    void onNewConnection();
    void onReadyRead();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);


private:

    void handleLobbyContext(QTcpSocket* client, const QJsonObject data);
    void handleRoomsList(QTcpSocket* client);
    void handleLobbyJoin(QTcpSocket* client, const QJsonObject data);
    void handleLobbyLeave(QTcpSocket* client, const QJsonObject data);

    uint getPlayerId(QTcpSocket* client) const;

    LobbyController* const m_lobbyController;
    PlayerController* const m_playerController;
    QTcpServer* const m_tcpServer;
    const QHostAddress m_address = QHostAddress("192.168.1.104");
    const quint16 m_port = 60420;
    QMap<QTcpSocket*, const Player*> m_clients;


};
