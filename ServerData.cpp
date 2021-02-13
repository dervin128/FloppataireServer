#include "ServerData.h"
#include <QJsonDocument>

ServerData::ServerData() : QJsonObject() {};

QByteArray ServerData::toJson() const{
    return QJsonDocument(*this).toJson();
}

QJsonValue ServerData::operator[](const QString& key){
    return QJsonObject::operator[](key);
}

void ServerData::setContext(const ServerContext context){
    this->operator[]("context") = context;
}

void ServerData::setData(const QJsonObject data){
    this->operator[]("data") = data;
}
