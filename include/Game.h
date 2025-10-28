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
    int board[23][23],size,cell_sz,PlayerPos,outside,option,mode,curMode,curStart,curPlayers,curComputer;
    // option 0 -> nothing , option 1 -> start
    Texture2D background,ButtonStart,External,ButtonStartFade,GameMode,GameModeFade,TwoOptions,TwoPlayers,Computer,InvalidOption;
    vector<vector<vector<int>>> SaveBoard;
    Sound click;
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
        curComputer=0;
        background=LoadTexture("assets/Board.png");
        ButtonStart=LoadTexture("assets/ButtonStart.png");
        External=LoadTexture("assets/External.png");
        ButtonStartFade=LoadTexture("assets/ButtonStartFade.jpg");
        GameMode=LoadTexture("assets/GameMode.png");
        GameModeFade=LoadTexture("assets/GameModeFade.jpg");
        TwoOptions=LoadTexture("assets/TwoOptions.png");
        TwoPlayers=LoadTexture("assets/TwoPlayers.png");
        Computer=LoadTexture("assets/Computer.png");
        click=LoadSound("assets/Click.wav");
        InvalidOption=LoadTexture("assets/InvalidOption.png");
    }
};