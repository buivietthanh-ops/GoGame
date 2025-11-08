#include<iostream>
#include "include/External.h"

void InputExternal(State &game)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        MakeSound(game);
        Vector2 mousePos=GetMousePosition();
        if (mousePos.x>=600-250/2 && mousePos.x<=600+250/2 && mousePos.y>=400-85/2 && mousePos.y<=400+85/2)
        {
            game.option=1;
        }
        
        if (mousePos.x>=600-250/2 && mousePos.x<=600+250/2 && mousePos.y>=400-85/2+100 && mousePos.y<=400+85/2+100)
        {
            game.option=3;
        }
        if (mousePos.x>=600-250/2 && mousePos.x<=600+250/2 && mousePos.y>=400-85/2+200 && mousePos.y<=400+85/2+200)
        {
            game.option=4;
        }
    }
}

void DrawExternal(State &game)
{
    ClearBackground(RAYWHITE);
    DrawTexture(game.External,0,0,WHITE);
    Vector2 mousePos=GetMousePosition();
    // Start
    if (mousePos.x>=600-250/2 && mousePos.x<=600+250/2 && mousePos.y>=400-85/2 && mousePos.y<=400+85/2)
    {
        if (game.curStart==0) MakeSound(game),game.curStart=1;
        DrawTexture(game.ButtonStartFade,600-250/2,400-85/2,WHITE);
        DrawTextEx(game.Font,"Start",(Vector2){600-150/2+18,400-80/2+6},60,3,BLACK);
        
    } else 
    {
        game.curStart=0;
        DrawTexture(game.ButtonStart,600-250/2,400-85/2,WHITE);
        DrawTextEx(game.Font,"Start",(Vector2){600-150/2+18,400-80/2+6},60,3,{0,0,0,200});
    }
    // Mode
    if (mousePos.x>=600-250/2 && mousePos.x<=600+250/2 && mousePos.y>=400-85/2+100 && mousePos.y<=400+85/2+100)
    {
        if (game.curMode==0) MakeSound(game),game.curMode=1;
        DrawTexture(game.ButtonStartFade,600-250/2,400-85/2+100,WHITE);
        DrawTextEx(game.Font,"Mode",(Vector2){600-150/2+18,400-80/2+100+6},60,3,BLACK);
    } else 
    {
        game.curMode=0;
        DrawTexture(game.ButtonStart,600-250/2,400-85/2+100,WHITE);
        DrawTextEx(game.Font,"Mode",(Vector2){600-150/2+18,400-80/2+100+6},60,3,{0,0,0,200});
    }
    // Setting
    //DrawTexture(game.SettingButton,600-120,400+190,WHITE);
    if (mousePos.x>=600-250/2 && mousePos.x<=600+250/2 && mousePos.y>=400-85/2+200 && mousePos.y<=400+85/2+200)
    {
        if (game.curSetting==0) MakeSound(game),game.curSetting=1;
        DrawTexture(game.ButtonStartFade,600-250/2,400-85/2+200,WHITE);
        DrawTextEx(game.Font,"Setting",(Vector2){600-150/2+6,400-80/2+200+6},60,3,BLACK);
    } else 
    {
        game.curSetting=0;
        DrawTexture(game.ButtonStart,600-250/2,400-85/2+200,WHITE);
        DrawTextEx(game.Font,"Setting",(Vector2){600-150/2+6,400-80/2+200+6},60,3,{0,0,0,200});
    }
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
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) MakeSound(game);
}
void PopUp(State &game)
{
    if (game.PopUpScale+0.05f-game.PopUpScale/50.0<=1.0f)
    {
        game.PopUpScale+=0.05f-game.PopUpScale/50.0;
    }
    float lenX=900.0*game.PopUpScale,lenY=600.0*game.PopUpScale;
    float X=600.0-lenX/2.0,Y=400.0-lenY/2.0;
    DrawRectangleRounded(Rectangle{X,Y,lenX,lenY},0.1f,20,Fade(RAYWHITE,0.9f));
    DrawRectangleRoundedLines(Rectangle{X,Y,lenX,lenY},0.1f,20,BLACK);
}
