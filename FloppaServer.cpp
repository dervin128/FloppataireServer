#include "FloppaServer.h"
#include <QNetworkDatagram>
#include <QJsonObject>
#include <QJsonDocument>

FloppaServer::FloppaServer(QObject* parent) : QObject(parent){

    connect(&m_socket, &QUdpSocket::readyRead, this, &FloppaServer::readPendingDatagrams);

    m_socket.bind(m_address, m_port);

    qDebug() << "Server running on" << m_address << ":" << m_port;
}

FloppaServer::~FloppaServer(){}

void FloppaServer::readPendingDatagrams()
{
    qDebug() << "Message received";
    while (m_socket.hasPendingDatagrams()) {
            QNetworkDatagram datagram = m_socket.receiveDatagram();

            QHostAddress address = datagram.senderAddress();
            if(!m_clients.contains(address)){
                qDebug() << "New client: " << datagram.senderAddress() << ":" << datagram.senderPort();
                m_clients << address;
            }

            processData(datagram);
    }
}

void FloppaServer::processData(QNetworkDatagram datagram){
    qDebug() << datagram.data();


    QJsonObject data_object;
    data_object["action_type"] = 2;
    QJsonDocument doc(data_object);
    for(const QHostAddress& address : m_clients){
        qDebug() << "sending to:" << address << ":" << 60420;
        m_socket.writeDatagram(doc.toJson(), address, 60420);
    }
}
