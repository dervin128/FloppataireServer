#pragma once

#include <QObject>
#include "Room.h"

class PlayerController : public QObject {
    Q_OBJECT
public:
    PlayerController(QObject* parent = nullptr);

    const Player* getPlayer(uint id);
    const Player* createNewPlayer();

signals:

private slots:

private:
    static uint m_idGenerator;
    QMap<uint, Player*> m_players;
};
