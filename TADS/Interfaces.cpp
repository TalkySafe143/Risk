//
// Created by talkysafe143 on 1/10/23.
//

#include "Interfaces.h"

const Risk &Interfaces::getGame() const {
    return game;
}

void Interfaces::setGame(const Risk &game) {
    Interfaces::game = game;
}
