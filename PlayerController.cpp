#include "PlayerController.h"
#include <QJsonArray>

uint PlayerController::m_idGenerator = 1;

PlayerController::PlayerController(QObject* parent) : QObject(parent) {}

const Player* PlayerController::getPlayer(uint id){
    return m_players[id];
}
