#pragma once

#include <QObject>
#include <QList>
#include <QWebSocket>
#include <QWebSocketServer>

class FloppaServer : public QObject {
    Q_OBJECT

public:

    FloppaServer(QObject* parent = nullptr);
    ~FloppaServer();

signals:
    void closed();

private slots:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();


private:
    const quint16 port = 15000;
    QWebSocketServer* m_webSocketServer;
    QList<QWebSocket*> m_clients;
};
