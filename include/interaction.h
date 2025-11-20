#pragma once
#include "include/Game.h"
#include "include/GameLogic.h"
#include <raylib.h>

class Player
{
    private:
    int score;
    public:
    Player():score(0){};
    void InputStone(State &game, int &invalid);
    
};

void MakeSound(State &game);
void MakeSoundGetScore(State &game);

