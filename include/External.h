#pragma once
#include "include/Game.h"
#include "include/interaction.h"


class Button {

protected:
    float x,y,w,h;
public:
    int used;
    Button(float x1, float y1, float w1, float h1) :x(x1),y(y1),w(w1),h(h1),used(0) {}; 
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
class ThemeOneButton : public SettingButton
{
    private:
    int Cur;
    Button* themesecondbutton;
    public:
    ThemeOneButton(int x1, int y1, int w1, int h1) : SettingButton(x1,y1,w1,h1),Cur(0){
        used=1;
    }
    void Input(State &game) override;
    void Draw(State &game) override;
    void keep(Button* button) override;  
};
class ThemeSecondButton : public SettingButton
{
    private:
    int Cur;
    Button* themeonebutton;
    public:
    ThemeSecondButton(int x1, int y1, int w1, int h1) : SettingButton(x1,y1,w1,h1),Cur(0){}
    void Input(State &game) override;
    void Draw(State &game) override;
    void keep(Button* button) override;  
};

class SoundButton : public SettingButton
{ 
    protected:
    float xP,yP,wP,hP,xM,yM,wM,hM;
    public:
    SoundButton(int xP1,int yP1, int wP1, int hP1,int xM1, int yM1, int wM1, int hM1):
     SettingButton(xP1,yP1,wP1,hP1),xP(xP1),yP(yP1),wP(wP1),hP(hP1),xM(xM1),yM(yM1),wM(wM1),hM(hM1){};
    bool InsidePlus();
    bool InsideMinus();
    

};

class SoundEffectButton : public SoundButton
{
    private:
    pair<Sound,float>* soundeffectbutton1;
    pair<Sound,float>* soundeffectbutton2;
    string line;
    public:
    SoundEffectButton(int xP, int yP, int wP, int hP, int xM, int yM, int wM, int hM, pair<Sound,float>* sound1,
     pair<Sound,float>* sound2, string c):
    SoundButton(xP,yP,wP,hP,xM,yM,wM,hM),soundeffectbutton1(sound1),soundeffectbutton2(sound2),line(c){};
    void InputPlus(State &game);
    void InputMinus(State &game);
    void Input(State &game) override;
    void Draw(State &game) override;
    
};
class MusicButton : public SoundButton
{
    private:
    pair<Music,float>* musicbutton1;
    pair<Music,float>* musicbutton2;
    string line;
    public:
    MusicButton(int xP, int yP, int wP, int hP, int xM, int yM, int wM, int hM, pair<Music,float>* sound1,
     pair<Music,float>* sound2, string c):
    SoundButton(xP,yP,wP,hP,xM,yM,wM,hM),musicbutton1(sound1),musicbutton2(sound2),line(c){};
    void InputPlus(State &game);
    void InputMinus(State &game);
    void Input(State &game) override;
    void Draw(State &game) override;
    
};
void External(State &game, Button* startbutton, Button* modebutton, Button* settingbutton);

void PopUp(State &game, vector<Button*> button);

void InputOptions(State &game, Button* modebutton);
void transition(double &a, bool &fadeOut);
void DrawFast(State &game);