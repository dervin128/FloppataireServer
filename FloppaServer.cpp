#include "FloppaServer.h"
#include <QNetworkDatagram>
#include <QJsonObject>
#include <QJsonDocument>

FloppaServer::FloppaServer(QObject* parent) : QObject(parent){

    connect(&m_reveiver, &QUdpSocket::readyRead, this, &FloppaServer::readPendingDatagrams);

    m_reveiver.bind(m_address, m_port);
    m_sender.bind(m_address, 53739);

    qDebug() << "Server running on" << m_address << ":" << m_port;
}

FloppaServer::~FloppaServer(){
    m_reveiver.close();
    m_sender.close();
}

void FloppaServer::readPendingDatagrams()
{
    qDebug() << "Message received";
    while (m_reveiver.hasPendingDatagrams()) {
            QNetworkDatagram datagram = m_reveiver.receiveDatagram();

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
    qDebug() << "sending to: " << datagram.senderAddress() << ":" << datagram.senderPort();
    m_sender.writeDatagram(doc.toJson(), datagram.senderAddress(), datagram.senderPort());
}

void FloppaServer::onNewConnection(){}

void FloppaServer::clientDisconnected(){
    qDebug() << "socketDisconnected";
}
