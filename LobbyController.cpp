#include <QJsonArray>
#include "LobbyController.h"

uint LobbyController::m_idGenerator = 1;

LobbyController::LobbyController(PlayerController* playerController,
                                 QObject* parent) :
    QObject(parent),
    m_playerController(playerController) {}

LobbyController::LobbyRequest LobbyController::lobbyRequest(const QJsonObject obj) const{
    return static_cast<LobbyRequest>(obj["request"].toInt());
}

LobbyController::LobbyData LobbyController::lobbyData(const QJsonObject obj) const{
    return static_cast<LobbyData>(obj["data"].toInt());
}


Room* LobbyController::createNewRoom(const QString& roomName, uint hostId){
    const Player* player = m_playerController->getPlayer(hostId);
    if(player == nullptr) return 0;
    Room* newRoom = new Room(m_idGenerator++, roomName);
    newRoom->addPlayer(player);
    m_rooms[newRoom->getId()] = newRoom;
    return newRoom;
}

bool LobbyController::addPlayerToRoom(uint roomId, uint playerId){
    if(!m_rooms.contains(roomId)) return false;
    const Player* player = m_playerController->getPlayer(playerId);
    if(player == nullptr) return false;

    return m_rooms[roomId]->addPlayer(player);
}

bool LobbyController::removePlayerFromRoom(uint roomId, uint playerId){
    if(m_rooms.contains(roomId)) return false;
    const Player* player = m_playerController->getPlayer(playerId);
    if(player == nullptr) return false;

    Room* room = m_rooms[roomId];
    room->removePlayer(player);

    if(room->getPlayerCount() <= 0){
        room->deleteLater();
        return true;
    }else{
        return !room->containsPlayer(player);
    }
}

QJsonObject LobbyController::getRoomsData() const{
    QJsonArray rooms;
    foreach(Room* room, m_rooms){
        rooms << room->toJson();
    }
    QJsonObject obj;
    obj.insert("rooms", rooms);
    return obj;
}
