#include "FloppaServer.h"

FloppaServer::FloppaServer(QObject* parent) : QObject(parent){
    m_webSocketServer = new QWebSocketServer("Floppa Server", QWebSocketServer::NonSecureMode, this);

}

FloppaServer::~FloppaServer(){
    m_webSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());

    if (m_webSocketServer->listen(QHostAddress::Any, port)) {
            qDebug() << "Echoserver listening on port" << port;
            connect(m_webSocketServer, &QWebSocketServer::newConnection,
                    this, &FloppaServer::onNewConnection);
            connect(m_webSocketServer, &QWebSocketServer::closed, this, &FloppaServer::closed);
        }
}

void FloppaServer::onNewConnection(){

    QWebSocket *socket = m_webSocketServer->nextPendingConnection();

    connect(socket, &QWebSocket::textMessageReceived, this, &FloppaServer::processTextMessage);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &FloppaServer::processBinaryMessage);
    connect(socket, &QWebSocket::disconnected, this, &FloppaServer::socketDisconnected);

    m_clients << socket;
}

void FloppaServer::processTextMessage(QString message){
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    qDebug() << "Message received:" << message;
    if (pClient) {
        pClient->sendTextMessage(message);
    }
}
void FloppaServer::processBinaryMessage(QByteArray message){
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    qDebug() << "Binary Message received:" << message;
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}
void FloppaServer::socketDisconnected(){
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
