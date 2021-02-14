#include <QCoreApplication>
#include "FloppaServer.h"
#include "LobbyController.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PlayerController* playerController = new PlayerController();
    LobbyController* lobbyController = new LobbyController(playerController);
    FloppaServer* server = new FloppaServer(lobbyController, playerController);
    Q_UNUSED(server)

    return a.exec();
}
