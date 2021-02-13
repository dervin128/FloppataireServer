#pragma once

#include <QObject>
#include "Player.h"
#include "SerializableJson.h"

class Room : public QObject, public SerializableJson {
    Q_OBJECT

public:

    explicit Room(const uint id, const QString& roomName, QObject* parent = nullptr);
    bool operator==(const Room& room) const;

    int getPlayerCount() const;
    QString getRoomName() const;
    uint getId() const;

    bool addPlayer(const Player* player);
    bool removePlayer(const Player* player);
    bool containsPlayer(const Player* player);

    QJsonObject toJson() const;


private:
    const uint m_id;
    const QString m_roomName;
    QMap<uint, const Player*> m_players;

};
