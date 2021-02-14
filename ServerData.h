#pragma once

#include <QJsonObject>

class ServerData : public QJsonObject {
public:
    enum ServerContext{
        ERROR,
        LOBBY,
        GAME,
        CONNECTION
    };

    ServerData();

    QByteArray toJson() const;
    void setContext(const ServerContext context);
    void setData(const QJsonObject data);

private:
    QJsonValueRef operator[](const QString& key);

};
