#pragma once
#include "include/Game.h"
#include "include/GameLogic.h"
#include "src/GameLogic.cpp"
#include <raylib.h>

void InputStone(State &game, int &invalid);
void MakeSound(State &game);
void MakeSoundGetScore(State &game);
