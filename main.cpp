#include <iostream>
#include <raylib.h>
#include <vector>
#include "include/interaction.h"
#include "include/BoardRender.h"
#include "include/Game.h"
#include "include/External.h"
using namespace std;


int main () {

    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 800;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Go Game");
    SetTargetFPS(60);
    InitAudioDevice();
    State game;
    PlayMusicStream(game.music[0].first);
    PlayMusicStream(game.music[1].first);
    // 0 -> stay    [1 -> Build board    2 -> Play game] (Option)
    // 0 -> No      1-> 2 players       2-> AI (Mode)
    // option 4 -> setting
    int time=0,used=0,dem=0;
    bool fadeOut=0;
    double a=0;
    int x=rand()%(1200-500),y=rand()%(800-300);
    Button* startbutton = new StartButton(600-250/2,400-85/2,600+250/2,400+85/2);
    Button* modebutton = new ModeButton(600-250/2,400-85/2+100,600+250/2,400+85/2+100);
    Button* settingbutton = new SettingButton(600-250/2,400-85/2+200,600+250/2,400+85/2+200);

    Button* boardthemebutton= new BoardThemeButton(200,250,200+120*2,250+80*2);
    Button* modernboardbutton= new ModernBoardButton(450,250,450+120*2,250+80*2);
    boardthemebutton->keep(modernboardbutton);
    modernboardbutton->keep(boardthemebutton);

    Button* exitbutton= new ExitButton(980,200,980+50,200+50,settingbutton);

    Button* stonebutton= new StoneButton(200,480,200+60,480+30);
    Button* modernstonebutton= new ModernStoneButton(290,480,290+60,480+30);
    stonebutton->keep(modernstonebutton);
    modernstonebutton->keep(stonebutton);

    Button* themeonebutton= new ThemeOneButton(450,480,650,510);
    Button* themesecondbutton= new ThemeSecondButton(450,520,650,550);
    themeonebutton->keep(themesecondbutton);
    themesecondbutton->keep(themeonebutton);


    string line="Placing Stone";
    Button* placingstonebutton= new SoundEffectButton(700+80+150+10, 250+75+40, 700+80+150+10+21, 250+75+40+21,
        700+50, 250+75+40, 700+50+21, 250+75+40+21,
        &game.sound[0].Click, &game.sound[1].Click,line);
    
    line = "Capturing Stone";
    Button* capturestonebutton= new SoundEffectButton(700+80+150+10,250+75+75+40,700+80+150+10+21,250+75+75+40+21,
        700+50,250+75+75+40,700+50+21,250+75+75+40+21,
        &game.sound[0].Getscore, &game.sound[1].Getscore,line);

    line = "End-Game Scoring";
    Button* endgamebutton= new SoundEffectButton(
        700+80+150+10,250+75+75+75+40,700+80+150+10+21,250+75+75+75+40+21,
        700+50,250+75+75+75+40,700+50+21,250+75+75+75+40+21,
        &game.sound[0].Endgame, &game.sound[1].Endgame,line);
    
    line = "Background Music";
    Button* backgroundmusic= new MusicButton(
        700+80+150+10,250+40,700+80+150+10+21,250+40+21,
        700+50,250+40,700+50+21,250+40+21,
        &game.music[0], &game.music[1],line);

    Button* muteplacingstonebutton= new MuteSoundButton(700,250+35+75,700+game.MuteSoundButton.width,250+35+75+game.MuteSoundButton.height,
    &game.sound[0].Click, &game.sound[1].Click);

    Button* mutecapturestonebutton= new MuteSoundButton(700,250+35+75*2,700+game.MuteSoundButton.width,250+35+75*2+game.MuteSoundButton.height,
    &game.sound[0].Getscore, &game.sound[1].Getscore);

    Button* muteendgamebutton= new MuteSoundButton(700,250+35+75*3,700+game.MuteSoundButton.width,250+35+75*3+game.MuteSoundButton.height,
    &game.sound[0].Endgame, &game.sound[1].Endgame);

    Button* mutemusicbutton= new MuteMusicButton(700,250+35,700+game.MuteMusicButton.width,250+35+game.MuteMusicButton.height,
    &game.music[0], &game.music[1]);
    
    Player* player1 = new Player();
    Player* player2 = new Player();

    vector<Button*> button;
    button.push_back(boardthemebutton);
    button.push_back(modernboardbutton);
    button.push_back(exitbutton);
    button.push_back(stonebutton);
    button.push_back(modernstonebutton);
    button.push_back(themeonebutton);
    button.push_back(themesecondbutton);
    button.push_back(placingstonebutton);
    button.push_back(capturestonebutton);
    button.push_back(endgamebutton);
    button.push_back(backgroundmusic);
    button.push_back(muteplacingstonebutton);
    button.push_back(mutecapturestonebutton);
    button.push_back(muteendgamebutton);
    button.push_back(mutemusicbutton);
    while (WindowShouldClose() == false){

        UpdateMusicStream(game.music[game.isSound].first);
        
        BeginDrawing();
        if (game.option==0)
        {
            
        
            if (startbutton->used==1)
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
                        startbutton->used=0;
                        x=rand()%(1200-500),y=rand()%(800-300);
                    }
                } 
                
                
                else 
                {
                    dem++;
                    if (fadeOut==0) fadeOut=1;
                    transition(a,fadeOut);
                    if (dem==50)
                    game.option=1;
                }
                
            }
            
            else
            if (modebutton->used==1)
            {
                
                Draw2Options(game);
                InputOptions(game,modebutton);
 
            }

            else
            if (settingbutton->used==1)
            {
                PopUp(game, button);
                
            }

            else
            External(game,startbutton,modebutton,settingbutton);
        }
         else
        {
            int invalid=0;
            DrawBoard(game);
            if (game.PlayerPos==1)
            player1->InputStone(game,invalid); else player2->InputStone(game, invalid);
            
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
                } else DrawTextEx(game.Font,"Invalid!",(Vector2){500,300},100,5,LIGHTGRAY),DrawTextEx(game.Font,"Invalid!",(Vector2){503,303},100,5,BLACK);
            }
            
        }
        EndDrawing();
    }
    UnloadMusicStream(game.music[0].first);
    UnloadMusicStream(game.music[1].first);

    CloseAudioDevice();
    CloseWindow();
}