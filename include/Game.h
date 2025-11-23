#pragma once
#include<raylib.h>
#include<vector>
#include<string>
using namespace std;
struct position
{
    int x,y;
};
struct StateSound
{
    pair<Sound,float> Click,Getscore,Endgame;
};
struct State
{
    int board[23][23],size,cell_sz,PlayerPos,outside,option,mode,curPlayers,curComputer,isClassic,isSound, isClose;
    double PopUpScale;
    Texture2D Board,ButtonStart,External,ButtonStartFade,TwoOptions,TwoPlayers,Computer,InvalidOption
    ,ModernBoard,SettingBackground,PlayBoard,ExitButton,BlackStone,WhiteStone,MinusButton,PlusButton
    ,MusicButton,MuteMusicButton,SoundButton,MuteSoundButton,PassButton,GameOver;
    vector<vector<vector<int>>> SaveBoard,Redo;
    vector<string> filelist;
    StateSound sound[2];
    pair<Music,float> music[2];
    Font Font;
    State()
    {
        isClose=0;
        for (int x=1;x<=19;x++) for (int y=1;y<=19;y++) board[x][y]=0;
        size=19;
        outside=400;
        cell_sz=40;
        PlayerPos=1;
        option=0;
        mode=0;
        curPlayers=0;
        curComputer=0;
        PopUpScale=0.0f;


        Board=LoadTexture("assets/Board.png");
        ButtonStart=LoadTexture("assets/ButtonStart.png");
        External=LoadTexture("assets/External.png");
        ButtonStartFade=LoadTexture("assets/ButtonStartFade.png");
        TwoOptions=LoadTexture("assets/TwoOptions.png");
        TwoPlayers=LoadTexture("assets/TwoPlayers.png");
        Computer=LoadTexture("assets/Computer.png");

        sound[0].Click={LoadSound("assets/Click.wav"),1};
        sound[1].Click={LoadSound("assets/Click2.wav"),1};
        sound[0].Getscore={LoadSound("assets/GetScore.wav"),1}; // SOUND
        sound[1].Getscore={LoadSound("assets/GetScore2.wav"),1};
        sound[0].Endgame={LoadSound("assets/EndGame.wav"),1};
        sound[1].Endgame={LoadSound("assets/EndGame1.wav"),1};
        music[0]={LoadMusicStream("assets/BackgroundMusic.mp3"),1};
        music[1]={LoadMusicStream("assets/BackgroundMusic2.mp3"),1};
        isSound=0;
        

        ModernBoard=LoadTexture("assets/ModernBoard.png");
        ExitButton=LoadTexture("assets/ExitButton.png");
        
        InvalidOption=LoadTexture("assets/InvalidOption.png");

        Font=LoadFontEx("assets/MaShanZheng-Regular.ttf",256,nullptr,0); // FONT
        SettingBackground=LoadTexture("assets/SettingBackground.png");
        SetTextureFilter(SettingBackground, TEXTURE_FILTER_TRILINEAR);
        PlayBoard=Board;
        BlackStone=LoadTexture("assets/BlackStone.png");
        WhiteStone=LoadTexture("assets/WhiteStone.png");
        isClassic=1;

        MinusButton=LoadTexture("assets/MinusButton.png");
        PlusButton=LoadTexture("assets/PlusButton.png");

        MusicButton=LoadTexture("assets/MusicButton.png");
        MuteMusicButton=LoadTexture("assets/MuteMusicButton.png");
        SoundButton=LoadTexture("assets/SoundButton.png");
        MuteSoundButton=LoadTexture("assets/MuteSoundButton.png");
        


        PassButton=LoadTexture("assets/PassButton.png");
        GameOver=LoadTexture("assets/GameOver.png");

        vector<vector<int>> board (23, vector<int>(23,0));
        SaveBoard.push_back(board);
        Redo.push_back(board);

        
    }
};