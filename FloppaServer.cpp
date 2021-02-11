#include "FloppaServer.h"
#include <QNetworkDatagram>
#include <QJsonObject>
#include <QJsonDocument>

FloppaServer::FloppaServer(QObject* parent) :
    QObject(parent),
    m_tcpServer(new QTcpServer()),
    m_UdpSocket(new QUdpSocket()){

    //connect(&m_socket, &QUdpSocket::readyRead, this, &FloppaServer::readPendingDatagrams);
    //m_socket.bind(m_address, m_port);
    m_tcpServer->listen(m_address, m_port);

    connect(m_tcpServer, &QTcpServer::newConnection, this, &FloppaServer::onNewConnection);

    qDebug() << "Server running on" << m_address << ":" << m_port;
}

FloppaServer::~FloppaServer(){
    m_tcpServer->disconnect();
}

void FloppaServer::onNewConnection(){
    QTcpSocket *clientSocket = m_tcpServer->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &FloppaServer::onReadyRead);
    connect(clientSocket, &QTcpSocket::stateChanged, this, &FloppaServer::onSocketStateChanged);
    m_clients.push_back(clientSocket);

    qDebug() << "New connection from:" << clientSocket->localAddress() << clientSocket->localPort();
}

void FloppaServer::onReadyRead(){

}

void FloppaServer::onSocketStateChanged(QAbstractSocket::SocketState socketState){
    if (socketState == QAbstractSocket::UnconnectedState) {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        m_clients.removeOne(sender);
    }
}

void FloppaServer::readPendingDatagrams()
{
    qDebug() << "Message received";
    while (m_UdpSocket->hasPendingDatagrams()) {
            QNetworkDatagram datagram = m_UdpSocket->receiveDatagram();

            QHostAddress address = datagram.senderAddress();
                /*
            if(!m_clients.contains(address)){
                qDebug() << "New client: " << datagram.senderAddress() << ":" << datagram.senderPort();
                m_clients << address;
            }
                */

            processData(datagram);
    }
}

void FloppaServer::processData(QNetworkDatagram datagram){
    qDebug() << datagram.data();


    QJsonObject data_object;
    data_object["action_type"] = 2;
    QJsonDocument doc(data_object);
    /*
    for(const QHostAddress& address : m_clients){
        qDebug() << "sending to:" << address << ":" << m_port;
        m_UdpSocket->writeDatagram(doc.toJson(), address, m_port);
    }
    */
}
