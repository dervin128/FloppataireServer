#pragma once

#include <QJsonObject>

class ServerData : public QJsonObject {
public:
    enum ServerContext{
        LOBBY = 0,
        GAME,
        CONNECTION
    };

    ServerData();

    QByteArray toJson() const;
    void setContext(const ServerContext context);
    void setData(const QJsonObject data);

private:
    QJsonValue operator[](const QString& key);

};
