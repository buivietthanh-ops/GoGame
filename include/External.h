#pragma once
#include "include/Game.h"
#include "include/interaction.h"


class Button {

protected:
    int x,y,w,h;
public:
    int used;
    Button(int x1, int y1, int w1, int h1) :x(x1),y(y1),w(w1),h(h1),used(0) {}; 
    bool Inside();
    virtual void Input(State &game);
    virtual void Draw(State &game);
    virtual void keep(Button* button);
    virtual ~Button() = default;
};

class StartButton : public Button
{
    private:
    int Cur;

    public:
    StartButton(int x1, int y1, int w1, int h1) : Button(x1,y1,w1,h1),Cur(0) {};
    void Input(State &game) override;
    void Draw(State &game) override;

};
class ModeButton : public Button
{
    private:
    int Cur;

    public:
    ModeButton(int x1, int y1, int w1, int h1) : Button(x1,y1,w1,h1),Cur(0) {};
    void Input(State &game) override;
    void Draw(State &game) override;

};
class SettingButton : public Button
{
    private:
    int Cur;

    public:
    SettingButton(int x1, int y1, int w1, int h1) : Button(x1,y1,w1,h1),Cur(0) {};
    void Input(State &game) override;
    void Draw(State &game) override;

};
class BoardThemeButton : public SettingButton // Default setting -> used = 1
{
    private:
    int Cur;
    Button* modernboardbutton;
    
    public:
    BoardThemeButton(int x1, int y1, int w1, int h1) : SettingButton(x1,y1,w1,h1),Cur(0){
        used=1;
    };
    void Input(State &game) override;
    void Draw(State &game) override;
    void keep(Button* button) override;
    
};
class ModernBoardButton : public SettingButton
{
    private:
    int Cur;
    Button* boardthemebutton;
    public:
    ModernBoardButton(int x1, int y1, int w1, int h1) : SettingButton(x1,y1,w1,h1),Cur(0){}
    void Input(State &game) override;
    void Draw(State &game) override;
    void keep(Button* button) override;
};

class ExitButton : public SettingButton
{
    private:
    Button* settingbutton;
    public:
    ExitButton(int x1, int y1, int w1, int h1, Button* button) : SettingButton(x1,y1,w1,h1),settingbutton(button){}
    void Input(State &game) override;
    void Draw(State &game) override;
};

class StoneButton : public SettingButton
{
    private:
    int Cur;
    Button* modernstonebutton;
    public:
    StoneButton(int x1, int y1, int w1, int h1) : SettingButton(x1,y1,w1,h1),Cur(0){
        used=1;
    }
    void Input(State &game) override;
    void Draw(State &game) override;
    void keep(Button* button) override;
};
class ModernStoneButton : public SettingButton
{
    private:
    int Cur;
    Button* stonebutton;
    public:
    ModernStoneButton(int x1, int y1, int w1, int h1) : SettingButton(x1,y1,w1,h1),Cur(0){}
    void Input(State &game) override;
    void Draw(State &game) override;
    void keep(Button* button) override;
};
void External(State &game, Button* startbutton, Button* modebutton, Button* settingbutton);

void PopUp(State &game, vector<Button*> button);

void InputOptions(State &game, Button* modebutton);
void transition(double &a, bool &fadeOut);
void DrawFast(State &game);