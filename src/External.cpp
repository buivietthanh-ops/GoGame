#include<iostream>
#include "include/External.h"

void InputExternal(State &game)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        MakeSound(game);
        Vector2 mousePos=GetMousePosition();
        // 222 80
        if (mousePos.x>=600-111 && mousePos.x<=600-111+222 && mousePos.y>=400-40 && mousePos.y<=400-40+80)
        {
            game.option=1;
        }
        
        if (mousePos.x>=600-120 && mousePos.x<=600-120+240 && mousePos.y>=400+150 && mousePos.y<=400+150+75)
        {
            game.option=3;
        }
    }
}

void DrawExternal(State &game)
{
    ClearBackground(RAYWHITE);
    DrawTexture(game.External,0,0,WHITE);
    Vector2 mousePos=GetMousePosition();
    // Start
    if (mousePos.x>=600-111 && mousePos.x<=600-111+222 && mousePos.y>=400-40 && mousePos.y<=400-40+80)
    {
        if (game.curStart==0) MakeSound(game),game.curStart=1;
        DrawTexture(game.ButtonStartFade,600-111,400-40,WHITE);
        
    } else game.curStart=0,DrawTexture(game.ButtonStart,600-111,400-40,WHITE);
    // Mode
    if (mousePos.x>=600-120 && mousePos.x<=600-120+240 && mousePos.y>=400+150 && mousePos.y<=400+150+75)
    {
        if (game.curMode==0) MakeSound(game),game.curMode=1;
        DrawTexture(game.GameModeFade,600-120,400+150,WHITE);
    } else game.curMode=0,DrawTexture(game.GameMode,600-120,400+150,WHITE);
    
}

void InputOptions(State &game)
{   // -> Draw2Options
    
     Vector2 mousePos=GetMousePosition();
    if (mousePos.x>=469 && mousePos.x<=785 && mousePos.y>=200 && mousePos.y<=325)
    {
        if (game.curPlayers==0) MakeSound(game),game.curPlayers=1;
        DrawTexture(game.TwoPlayers,469-30,200-30,WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            game.mode=1;
            game.option=0;
        }

    } else game.curPlayers=0;
    if (mousePos.x>=469 && mousePos.x<=785 && mousePos.y>=471 && mousePos.y<=600)
    {
        if (game.curComputer==0) MakeSound(game),game.curComputer=1;
        DrawTexture(game.Computer,469-30,471-30,WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            game.mode=2;
            game.option=0;
        }
    } else game.curComputer=0;

}

