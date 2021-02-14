#include "Room.h"
#include <QJsonArray>

Room::Room(const uint id, const QString& roomName, QObject* parent) :
    QObject(parent),
    m_id(id),
    m_roomName(roomName){

}

bool Room::operator==(const Room& room) const{
    return m_id == room.m_id;
}

bool Room::addPlayer(const Player* player){
    if(m_players.size() < 3 && !m_players.contains(player->getId())){
        m_players[player->getId()] = player;
        return true;
    }
    return false;
}

bool Room::removePlayer(const Player* player){
    return m_players.remove(player->getId()) == 1;
}

bool Room::containsPlayer(const Player* player){
    return m_players.contains(player->getId());
}

int Room::getPlayerCount() const{
    return m_players.size();
}

QString Room::getRoomName() const{
    return m_roomName;
}

uint Room::getId() const{
    return m_id;
}

QJsonObject Room::toJson() const{
    QJsonObject json;
    json["id"] = (int) m_id;
    json["roomName"] = m_roomName;
    QJsonArray players;
    foreach(const Player* player, m_players){
        players.append(player->toJson());
    }
    return json;
}
