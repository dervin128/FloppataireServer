#pragma once

#include <QJsonObject>

class SerializableJson {
public:
    virtual ~SerializableJson() {}
    virtual QJsonObject toJson() const = 0;
};
