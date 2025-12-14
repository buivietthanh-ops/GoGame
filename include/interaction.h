#pragma once
#include<iostream>
#include "include/Game.h"
#include "include/GameLogic.h"
#include <raylib.h>
#include<string>
#include "raygui.h"
#include "json.hpp"
#include<fstream>
using json=nlohmann::json;
class Player
{
    
    public:
    int score;
    Player():score(0){};
    void InputStone(State &game, int &invalid);
    
};

class InsideButton
{
    protected:
    float x,y,w,h;
    string line;
    public:
    InsideButton(float x1, float y1, float w1, float h1, string line1):
    x(x1),y(y1),w(w1),h(h1),line(line1){}
    bool Inside();
    virtual void Input(State &game);
    virtual void SaveDraw(State &game);
    virtual void SaveGame(State &game, char filename[]);
    virtual void LoadDraw(State &game);
    virtual void LoadGame(State &game, string filename);
    virtual bool isUsing();
    virtual void Warning(State &game);
    void Draw(State &game);
    
    virtual ~InsideButton()= default;
};
class PassButton : public InsideButton
{
    
    public:
    PassButton(float x1, float y1, float w1, float h1,string line1): InsideButton(x1,y1,w1,h1,line1){}
    void Input(State &game) override;
    
};

class UndoButton : public InsideButton
{
    public:
    UndoButton(float x1, float y1, float w1, float h1, string line1): InsideButton(x1,y1,w1,h1,line1){}
    void Input(State &game) override;

};
class RedoButton : public InsideButton
{
    public:
    RedoButton(float x1, float y1, float w1, float h1, string line1): InsideButton(x1,y1,w1,h1,line1){}
    void Input(State &game) override;
};


class ResetButton : public InsideButton
{
    public:
    int used,share_for_playagain=0;
    ResetButton(float x1, float y1, float w1, float h1, string line1, bool share): InsideButton(x1,y1,w1,h1,line1),used(0),share_for_playagain(share){}
    void Input(State &game) override;
    bool isUsing() override;
    void Warning(State &game) override;
};

class SaveButton : public InsideButton
{
    public:
    char filename[1003];
    bool SaveText;
    SaveButton(float x1, float y1, float w1, float h1, string line1): InsideButton(x1,y1,w1,h1,line1),SaveText(0){}
    void Input(State &game) override;
    void SaveDraw(State &game) override;
    void SaveGame(State &game, char filename[]) override;
    bool isUsing() override;
};

class LoadButton : public InsideButton
{
    public:
    
    int used,rowClick,rowInside,scroll;
    LoadButton(float x1, float y1, float w1, float h1, string line1): InsideButton(x1,y1,w1,h1,line1),used(0),rowClick(-1),rowInside(-1),scroll(0){}
    void Input(State &game) override;
    void LoadDraw(State &game) override;
    void LoadGame(State &game, string filename) override;
    bool isUsing() override;
};

class QuitButton : public InsideButton
{
    public:
    QuitButton(): InsideButton(1,1,1,1,"A"){}
    void Input_Draw(State &game);
};
void MakeSound(State &game);
void MakeSoundGetScore(State &game);
void isValid(State &game, int &invalid, int &used, int &time, string &line);
void GameOver(State &game, bool &isOver, int score[], InsideButton* playagain);

