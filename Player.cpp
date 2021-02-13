#include "Player.h"

Player::Player(uint id, QObject* parent) :
    QObject(parent),
    m_id(id){

}

bool Player::operator==(const Player& player) const{
    return m_id == player.m_id;
}

QJsonObject Player::toJson() const{
    QJsonObject json{};
    json["id"] = (int) m_id;
    return json;
}

uint Player::getId() const{
    return m_id;
}
