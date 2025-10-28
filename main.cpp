#include <iostream>
#include <raylib.h>
#include <vector>
#include "include/interaction.h"
#include "include/BoardRender.h"
#include "include/Game.h"
#include "include/External.h"
#include "src/interaction.cpp"
#include "src/BoardRender.cpp"
#include "src/External.cpp"
using namespace std;


int main () {

    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 800;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Go Game");
    SetTargetFPS(60);
    InitAudioDevice();
    State game;
    // 0 -> stay    [1 -> Build board    2 -> Play game] (Option)
    // 0 -> No      1-> 2 players       2-> AI (Mode)
    int time=0,used=0;
    int x=rand()%(1200-500),y=rand()%(800-300);
    while (WindowShouldClose() == false){
        BeginDrawing();
        if (game.option==0)
        {
            DrawExternal(game);
            InputExternal(game);
            
        } else
        if (game.option==1)
        {
            if (game.mode==0)
            {
                DrawInvalidOption(game,x,y);
                if (used==0)
                {
                    time=GetTime();
                    used=1;
                } 
                if (GetTime()-time>=2){
                    time=0;
                    used=0;
                    game.option=0;
                    x=rand()%(1200-500),y=rand()%(800-300);
                }
            } else game.option=2;
            
        } else
        if (game.option==2)
        {
            int invalid=0;
            InputStone(game,invalid);
            DrawBoard(game);
            if (invalid)
            {
                time=GetTime();
                used=1;
            }
            if (used==1){
                if (GetTime()-time>=1)
                {
                    time=0;
                    used=0;
                } else DrawText("Invalid!",500,300,50,GREEN),DrawText("Invalid!",500,302,50,BLACK);
            }
            
        } else
        if (game.option==3)
        {
            
            Draw2Options(game);
            InputOptions(game);

            
        }
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();
}