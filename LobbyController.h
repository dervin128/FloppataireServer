#pragma once

#include <QObject>
#include <QMap>
#include "Room.h"
#include "PlayerController.h"

class LobbyController : public QObject {
    Q_OBJECT
public:
    enum LobbyRequest {
        ROOMS_LIST,
        JOIN,
        LEAVE
    };
    Q_ENUM(LobbyRequest);


    enum LobbyData {
        ROOMS
    };
    Q_ENUM(LobbyData);

    LobbyController(PlayerController* playerController, QObject* parent = nullptr);
    LobbyRequest lobbyRequest(const QJsonObject obj) const;
    LobbyData lobbyData(const QJsonObject obj) const;

    uint createNewRoom(const QString& roomName, uint hostId);
    bool addPlayerToRoom(uint roomId, uint playerId);
    bool removePlayerFromRoom(uint roomId, uint playerId);

    QJsonObject getRoomsData() const;


signals:

private slots:

private:
    static uint m_idGenerator;

    PlayerController* const m_playerController;
    QMap<uint, Room*> m_rooms;

};
