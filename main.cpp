#include <iostream>
#include <raylib.h>
#include <future>
#include <vector>
#include "json.hpp"
#include "include/interaction.h"
#include "include/BoardRender.h"
#include "include/Game.h"
#include "include/External.h"
#include "include/AI.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
using namespace std;


int main () {

    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 800;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Go Game");
    SetTargetFPS(60);
    InitAudioDevice();
    State game;
    game.Build();
    PlayMusicStream(game.music[0].first);
    PlayMusicStream(game.music[1].first);
    
    bool isOver=0;
    int time=0,used=0,dem=0,score[2]={0,0};
    bool fadeOut=0;
    double a=0;
    
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

    Button* leftbutton= new LevelButton(450,540,485,575,-1,game.LeftButton);
    Button* rightbutton= new LevelButton(720,540,755,575,1,game.RightButton);


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
    line="Pass";
    InsideButton* passbutton= new PassButton(100,200,100+game.PassButton.width,200+game.PassButton.height,line);

    line="Undo";
    InsideButton* undobutton= new UndoButton(100,300,100+game.PassButton.width,300+game.PassButton.height,line);
    
    line="Redo";
    InsideButton* redobutton= new RedoButton(100,400,100+game.PassButton.width,400+game.PassButton.height,line);

    line="Reset";
    InsideButton* resetbutton= new ResetButton(100,500,100+game.PassButton.width,500+game.PassButton.height,line,0);

    line="Save";
    InsideButton* savebutton= new SaveButton(100,600,100+game.PassButton.width,600+game.PassButton.height,line);

    line="Load";
    InsideButton* loadbutton= new LoadButton(100,700,100+game.PassButton.width,700+game.PassButton.height,line);

    QuitButton* quitbutton= new QuitButton();

    line="Play Again";
    InsideButton* playagain= new ResetButton(500,600,500+game.PassButton.width,600+game.PassButton.height,line,1);
    

    CloseGameButton* closegamebutton= new CloseGameButton();

    TwoOptions* twooptions= new TwoOptions();
    vector<InsideButton*> insidebutton;
    insidebutton.push_back(passbutton);
    insidebutton.push_back(undobutton);
    insidebutton.push_back(redobutton);
    insidebutton.push_back(resetbutton);
    insidebutton.push_back(savebutton);
    insidebutton.push_back(loadbutton);


    future<pair<int,int>>  futureAI;
    bool isAIRunning=0;
    filesystem::create_directory("save");
    while (WindowShouldClose() == false){

        UpdateMusicStream(game.music[game.isSound].first);
        
        BeginDrawing();
        GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
        GuiSetFont(game.Font);

        
        if (game.option==0)
        {
            
            //cout<<startbutton->used<<' '<<modebutton->used<<' '<<settingbutton->used<<endl;
            if (startbutton->used==1)
            {
                if (game.mode==0)
                {
                    DrawInvalidOption(game);
                    if (used==0)
                    {
                        time=GetTime();
                        used=1;
                    } 
                    if (GetTime()-time>=2){
                        time=0;
                        used=0;
                        startbutton->used=0;
                        
                    }
                } 
                
                else 
                {
                    dem++;
                    if (fadeOut==0) fadeOut=1;
                    transition(a,fadeOut);
                    if (dem==50)
                    {
                        game.option=1,startbutton->used=0,dem=0,a=0;
                    }
                }
            }
            
            else
            if (modebutton->used==1)
            {
                twooptions->Input_Draw(game,modebutton);
                if (twooptions->isFirstTime){
                    leftbutton->Input(game);
                    leftbutton->Draw(game);
                    rightbutton->Input(game);
                    rightbutton->Draw(game);
                }
            }

            else
            if (settingbutton->used==1)
            {
                PopUp(game, button);
            }

            else
            External(game,startbutton,modebutton,settingbutton, closegamebutton);
        }
         else
        {
            int invalid=0;
            DrawBoard(game);

            
            if (!isOver && savebutton->isUsing()==0 && loadbutton->isUsing()==0 && resetbutton->isUsing()==0)
            {
                
                if (game.PlayerPos==1)
                {
                    player1->InputStone(game,invalid);
                } else 
                {
                    if (game.mode==2) 
                    {
                        if (!isAIRunning)
                        {
                            isAIRunning=1;
                            
                            futureAI= async(launch::async,AI,gameCopy(game));
                        }
                        if (isAIRunning)
                        {
                            if (futureAI.wait_for(0ms) == future_status::ready)
                            {
                                auto AIMove= futureAI.get();

                                game.AIMove=AIMove;
                                player2->InputStone(game, invalid);
                                isAIRunning=0;
                            }
                        }
                    } else player2->InputStone(game, invalid);

                    
                }
            }
            

            for (InsideButton* a:insidebutton)
            {
                if (!isOver && !isAIRunning && savebutton->isUsing()==0 && loadbutton->isUsing()==0 && resetbutton->isUsing()==0) a->Input(game);
                a->Draw(game);
            }
            resetbutton->Warning(game);
            savebutton->SaveDraw(game);
            loadbutton->LoadDraw(game);
            quitbutton->Input_Draw(game);
            isValid(game,invalid,used,time,line);
            
            GameOver(game,isOver,score, playagain);
        }
        
        EndDrawing();
        if (game.isClose) break;
    }
    UnloadMusicStream(game.music[0].first);
    UnloadMusicStream(game.music[1].first);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}