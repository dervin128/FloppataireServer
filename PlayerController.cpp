#include "PlayerController.h"
#include <QJsonArray>

uint PlayerController::m_idGenerator = 1;

PlayerController::PlayerController(QObject* parent) : QObject(parent) {}

const Player* PlayerController::getPlayer(uint id){
    return m_players[id];
}

const Player* PlayerController::createNewPlayer(){
    Player* player = new Player(m_idGenerator++);
    m_players[player->getId()] = player;
    return player;
}
