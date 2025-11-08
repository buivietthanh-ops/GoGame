#pragma once
#include<raylib.h>
#include<vector>
using namespace std;
struct position
{
    int x,y;
};

struct State
{
    int board[23][23],size,cell_sz,PlayerPos,outside,option,mode,curMode,curStart,curPlayers,curComputer,curSetting;
    double PopUpScale;
    // option 0 -> nothing , option 1 -> start
    Texture2D background,ButtonStart,External,ButtonStartFade,GameMode,GameModeFade,TwoOptions,TwoPlayers,Computer,InvalidOption
    ,ModernBoard,SettingButton,SettingButtonFade;
    vector<vector<vector<int>>> SaveBoard;
    Sound click,GetScore;
    Font Font;
    State()
    {
        for (int x=1;x<=19;x++) for (int y=1;y<=19;y++) board[x][y]=0;
        size=19;
        outside=400;
        cell_sz=40;
        PlayerPos=1;
        option=0;
        mode=0;
        curMode=0;
        curStart=0;
        curPlayers=0;
        curSetting=0;
        curComputer=0;
        PopUpScale=0.0f;
        background=LoadTexture("assets/Board.png");
        ButtonStart=LoadTexture("assets/ButtonStart.png");
        External=LoadTexture("assets/External.png");
        ButtonStartFade=LoadTexture("assets/ButtonStartFade.png");
        GameMode=LoadTexture("assets/GameMode.png");
        GameModeFade=LoadTexture("assets/GameModeFade.jpg");
        TwoOptions=LoadTexture("assets/TwoOptions.png");
        TwoPlayers=LoadTexture("assets/TwoPlayers.png");
        Computer=LoadTexture("assets/Computer.png");
        click=LoadSound("assets/Click.wav");
        InvalidOption=LoadTexture("assets/InvalidOption.png");
        GetScore=LoadSound("assets/GetScore.wav");
        ModernBoard=LoadTexture("assets/ModernBoard.png");
        SettingButton=LoadTexture("assets/SettingButton.png");
        SettingButtonFade=LoadTexture("assets/SettingButtonFade.jpg");
        Font=LoadFontEx("assets/MaShanZheng-Regular.ttf",256,nullptr,0);
    }
};