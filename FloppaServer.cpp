#include "FloppaServer.h"
#include <QNetworkDatagram>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

FloppaServer::FloppaServer(LobbyController* lobbyController, QObject* parent) :
    QObject(parent),
    m_lobbyController(lobbyController),
    m_tcpServer(new QTcpServer()){

    m_tcpServer->listen(m_address, m_port);

    connect(m_tcpServer, &QTcpServer::newConnection, this, &FloppaServer::onNewConnection);

    qDebug() << "Server running on" << m_address << ":" << m_port;
}

FloppaServer::~FloppaServer(){
    m_tcpServer->disconnect();
}

ServerData::ServerContext FloppaServer::serverContext(const QJsonObject obj) const{
    return static_cast<ServerData::ServerContext>(obj["context"].toInt());
}

void FloppaServer::onNewConnection(){
    QTcpSocket *clientSocket = m_tcpServer->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &FloppaServer::onReadyRead);
    connect(clientSocket, &QTcpSocket::stateChanged, this, &FloppaServer::onSocketStateChanged);
    m_clients.push_back(clientSocket);

    qDebug() << "New connection from:" << clientSocket->localAddress() << clientSocket->localPort();
}

void FloppaServer::onReadyRead(){
    QTcpSocket* client = static_cast<QTcpSocket*>(QObject::sender());

    QJsonDocument document = QJsonDocument::fromJson(client->readAll());
    const QJsonObject data = document.object();


     ServerData::ServerContext context = serverContext(data);
     switch(context){
     case ServerData::LOBBY:
         handleLobbyContext(client, data);
         return;
     default:
         qDebug() << "Unhandled context";
         return;
     }
}

void FloppaServer::onSocketStateChanged(QAbstractSocket::SocketState socketState){
    if (socketState == QAbstractSocket::UnconnectedState) {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        m_clients.removeOne(sender);
        qDebug() << "Connection lost:" << sender->localAddress() << sender->localPort();
    }
}

void FloppaServer::handleLobbyContext(QTcpSocket* client, const QJsonObject data){
    auto request = m_lobbyController->lobbyRequest(data);
    switch(request){
    case LobbyController::ROOMS_LIST:
        handleRoomsList(client);
        return;
    case LobbyController::JOIN:
        handleLobbyJoin(client, data);
        return;
    case LobbyController::LEAVE:
        handleLobbyLeave(client, data);
        return;
    default:
        qDebug() << "unhandled lobby request";
        return;
    }
}

void FloppaServer::handleRoomsList(QTcpSocket* client){
    ServerData data_object;
    data_object.setContext(ServerData::LOBBY);
    data_object.setData(m_lobbyController->getRoomsData());
    QByteArray data = data_object.toJson();
    client->write(data);
}

void FloppaServer::handleLobbyJoin(QTcpSocket* client, const QJsonObject data){
    ServerData data_object;
    data_object.setContext(ServerData::LOBBY);

    QJsonObject success;
    uint roomId = data["room_id"].toInt();
    uint playerId = data["player_id"].toInt();
    success["success"] = m_lobbyController->addPlayerToRoom(roomId, playerId);

    data_object.setData(success);
    QByteArray out_data = data_object.toJson();
    client->write(out_data);
}
void FloppaServer::handleLobbyLeave(QTcpSocket* client, const QJsonObject data){
    ServerData data_object;
    data_object.setContext(ServerData::LOBBY);

    QJsonObject success;
    uint roomId = data["room_id"].toInt();
    uint playerId = data["player_id"].toInt();
    success["success"] = m_lobbyController->removePlayerFromRoom(roomId, playerId);

    data_object.setData(success);
    QByteArray out_data = data_object.toJson();
    client->write(out_data);
}









