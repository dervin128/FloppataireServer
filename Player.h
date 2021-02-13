#pragma once

#include <QObject>
#include "SerializableJson.h"

class Player : public QObject, public SerializableJson {
    Q_OBJECT

public:

    explicit Player(uint id, QObject* parent = nullptr);
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    bool operator==(const Player& player) const;

    QJsonObject toJson() const override;

    uint getId() const;

private:
    Player();
    const uint m_id;

};
