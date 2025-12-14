#pragma once
#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<cmath>
#include "include/game.h"
#include "include/GameLogic.h"

using namespace std;

State gameCopy(State &game);
pair<int,int> AI(State game);
