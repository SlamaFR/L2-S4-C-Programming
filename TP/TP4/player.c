#include "player.h"

Player adversary(Player player) {
    return player == PLAYER_1 ? PLAYER_2 : PLAYER_1;
}
