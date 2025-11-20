#include<iostream>
#include "include/External.h"

void InputOptions(State &game, Button* modebutton)
{   // -> Draw2Options
    
     Vector2 mousePos=GetMousePosition();
    if (mousePos.x>=469 && mousePos.x<=785 && mousePos.y>=200 && mousePos.y<=325)
    {
        if (game.curPlayers==0) MakeSound(game),game.curPlayers=1;
        DrawTexture(game.TwoPlayers,469-30,200-30,WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            game.mode=1;
            modebutton->used=0;
        }

    } else game.curPlayers=0;
    if (mousePos.x>=469 && mousePos.x<=785 && mousePos.y>=471 && mousePos.y<=600)
    {
        if (game.curComputer==0) MakeSound(game),game.curComputer=1;
        DrawTexture(game.Computer,469-30,471-30,WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            game.mode=2;
            modebutton->used=0;
        }
    } else game.curComputer=0;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) MakeSound(game);
}
void transition(double &a, bool &fadeOut)
{
    if (fadeOut)
    {
        a=a+5.0;
        if (a>255)
        {
            a=255;
            fadeOut=0;
        }
    }
    DrawRectangle(0,0,1200,800,(Color){0,0,0,(unsigned char)a});
}





bool Button::Inside()
{
    Vector2 MousePos=GetMousePosition();
    if (MousePos.x>=x && MousePos.y>=y && MousePos.x<=w && MousePos.y<=h) return 1;
    return 0;
}
void Button::Input(State &game){}
void Button::Draw(State &game){}
void Button::keep(Button* button){}
void StartButton::Input(State &game)
{
    if (Button::Inside() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        MakeSound(game);
        used=1;
    }
}

void StartButton::Draw(State &game)
{
    if (Button::Inside())
    {
        if (Cur==0) MakeSound(game),Cur=1;
        DrawTexture(game.ButtonStartFade,x,y,WHITE);
        DrawTextEx(game.Font,"Start",(Vector2){600-150/2+18,400-80/2+6},60,3,BLACK);
    } else 
    {
        Cur=0;
        DrawTexture(game.ButtonStart,x,y,WHITE);
        DrawTextEx(game.Font,"Start",(Vector2){600-150/2+18,400-80/2+6},60,3,{0,0,0,200});
    }
}

void ModeButton::Input(State &game)
{
    if (Button::Inside() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        MakeSound(game);
        used=1;
    }
}

void ModeButton::Draw(State &game)
{
    if (Button::Inside())
    {
        if (Cur==0) MakeSound(game),Cur=1;
        DrawTexture(game.ButtonStartFade,x,y,WHITE);
        DrawTextEx(game.Font,"Mode",(Vector2){600-150/2+18,400-80/2+100+6},60,3,BLACK);
    } else 
    {
        Cur=0;
        DrawTexture(game.ButtonStart,x,y,WHITE);
        DrawTextEx(game.Font,"Mode",(Vector2){600-150/2+18,400-80/2+100+6},60,3,{0,0,0,200});
    }
}
void SettingButton::Input(State &game)
{
    if (Button::Inside() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        MakeSound(game);
        used=1;
    }
}

void SettingButton::Draw(State &game)
{
    if (Button::Inside())
    {
        if (Cur==0) MakeSound(game),Cur=1;
        DrawTexture(game.ButtonStartFade,x,y,WHITE);
        DrawTextEx(game.Font,"Setting",(Vector2){600-150/2+6,400-80/2+200+6},60,3,BLACK);
    } else 
    {
        Cur=0;
        DrawTexture(game.ButtonStart,x,y,WHITE);
        DrawTextEx(game.Font,"Setting",(Vector2){600-150/2+6,400-80/2+200+6},60,3,{0,0,0,200});
    }
}
void BoardThemeButton::Input(State &game)
{
    if (Button::Inside() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        MakeSound(game);
        used=1;
        modernboardbutton->used=0;
        game.PlayBoard=game.Board;
    }
}
void BoardThemeButton::Draw(State &game)
{
    DrawTexturePro(
            game.Board,
            Rectangle{0,0,(float)game.Board.width,(float)game.Board.height},
            Rectangle{(float)x,(float)y,120*2,80*2},
            Vector2{0,0},
            0.0f,
            WHITE
            
    );
    if (used) DrawRectangle(x,y,120*2,80*2, (Color){0,0,0,60});
    if (Button::Inside())
    {
        if (Cur==0) MakeSound(game),Cur=1;
        if (!used) DrawRectangle(x,y,120*2,80*2, (Color){0,0,0,60});
    } else
    {
        Cur=0;
        
    }
};
void BoardThemeButton::keep(Button* button)
{
    modernboardbutton=button;
}
void ModernBoardButton::Input(State &game)
{
    if (Button::Inside() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        MakeSound(game);
        used=1;
        boardthemebutton->used=0;
        game.PlayBoard=game.ModernBoard;
    }
}
void ModernBoardButton::Draw(State &game)
{
    DrawTexturePro(
            game.ModernBoard,
            Rectangle{0,0,(float)game.Board.width,(float)game.Board.height},
            Rectangle{(float)x,(float)y,120*2,80*2},
            Vector2{0,0},
            0.0f,
            WHITE
            
    );
    if (used) DrawRectangle(x,y,120*2,80*2, (Color){0,0,0,60});
    if (Button::Inside())
    {
        if (Cur==0) MakeSound(game),Cur=1;
        if (!used) DrawRectangle(x,y,120*2,80*2, (Color){0,0,0,60});
    } else
    {
        Cur=0;
        
    }
}
void ModernBoardButton::keep(Button* button)
{
    boardthemebutton=button;
}

void StoneButton::Input(State &game)
{
    if (Button::Inside() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        MakeSound(game);
        used=1;
        modernstonebutton->used=0;
        game.isClassic=1;
    }
}
void StoneButton::Draw(State &game)
{
    DrawCircleGradient(x+game.cell_sz/3,y+game.cell_sz/3,game.cell_sz/3,DARKGRAY,BLACK); 
    DrawCircleGradient(x+game.cell_sz/3+30,y+game.cell_sz/3,game.cell_sz/3,WHITE,LIGHTGRAY);
    if (used)
    {
        DrawRectangleRounded(
           (Rectangle){x,y,57,27}, 
           0.5f,
           20,
           (Color){0,0,0,60}
        );
    }
    if (Button::Inside())
    {
        if (Cur==0) MakeSound(game),Cur=1;
        if (!used)
        {
            DrawRectangleRounded(
                (Rectangle){x,y,57,27}, 
                0.5f,
                20,
                (Color){0,0,0,60}
            );
        }
    } else
    {
        Cur=0;
        
    }
}
void StoneButton::keep(Button* button)
{
    modernstonebutton=button;

}

void ModernStoneButton::Input(State &game)
{
    if (Button::Inside() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        MakeSound(game);
        used=1;
        stonebutton->used=0;
        game.isClassic=0;
    }
}
void ModernStoneButton::Draw(State &game)
{
    DrawTexture(game.BlackStone,x,y,WHITE);
    DrawTexture(game.WhiteStone,x+30,y,WHITE);
    if (used)
    {
        DrawRectangleRounded(
           (Rectangle){x,y,57,27}, 
           0.5f,
           20,
           (Color){0,0,0,60}
        );
    }
    if (Button::Inside())
    {
        if (Cur==0) MakeSound(game),Cur=1;
        if (!used)
        {
            DrawRectangleRounded(
            (Rectangle){x,y,57,27}, 
            0.5f,
            20,
            (Color){0,0,0,60}
            );
        }
    } else
    {
        Cur=0;
        
    }
}
void ModernStoneButton::keep(Button* button)
{
    stonebutton=button;
}
void ExitButton::Input(State &game)
{
    if (Button::Inside() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        MakeSound(game);
        settingbutton->used=0;
    }
}

void ExitButton::Draw(State &game)
{
    DrawTexturePro(
            game.ExitButton,
            Rectangle{0,0,(float)game.ExitButton.width,(float)game.ExitButton.height},
            Rectangle{(float)x,(float)y,50,50},
            Vector2{0,0},
            0.0f,
            WHITE
            
    );
    
    if (Button::Inside())
    {
        
        if (!used) DrawRectangleRounded(
           (Rectangle){x,y,50,50}, 
           0.3f,
           20,
           (Color){0,0,0,60}
        );
    }
}

void ThemeOneButton::Input(State &game)
{
    if (Button::Inside() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        MakeSound(game);
        used=1;
        themesecondbutton->used=0;
        game.isSound=0;
    }
    
}
void ThemeOneButton::Draw(State &game)
{
    DrawTextEx(game.Font,"Theme one", Vector2{x+45,y},30,3,BLACK);
    DrawRectangleRounded(
           (Rectangle){x,y,200,30}, 
           0.5f,
           20,
           (Color){0,0,0,60}
        );
    if (used)
    {
        DrawTextEx(game.Font,"Theme one", Vector2{x+45+1,y+1},30,3,LIGHTGRAY);
        DrawRectangleRounded(
           (Rectangle){x,y,200,30}, 
           0.5f,
           20,
           (Color){0,0,0,60}
        );
        
    }
    if (Button::Inside())
    {
        if (Cur==0) MakeSound(game),Cur=1;
        if (!used)
        {
            DrawTextEx(game.Font,"Theme one", Vector2{x+45+1,y+1},30,3,LIGHTGRAY);
            DrawRectangleRounded(
            (Rectangle){x,y,200,30}, 
            0.5f,
            20,
            (Color){0,0,0,60}
            );
        }
    } else
    {
        Cur=0;
        
    }
}

void ThemeOneButton::keep(Button* button)
{
    themesecondbutton=button;
}

void ThemeSecondButton::Input(State &game)
{
    if (Button::Inside() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        MakeSound(game);
        used=1;
        themeonebutton->used=0;
        game.isSound=1;
    }
    
}
void ThemeSecondButton::Draw(State &game)
{
    DrawTextEx(game.Font,"Theme second", Vector2{x+25,y},30,3,BLACK);
    DrawRectangleRounded(
           (Rectangle){x,y,200,30}, 
           0.5f,
           20,
           (Color){0,0,0,60}
        );
    if (used)
    {
        DrawTextEx(game.Font,"Theme second", Vector2{x+25+1,y+1},30,3,LIGHTGRAY);
        DrawRectangleRounded(
           (Rectangle){x,y,200,30}, 
           0.5f,
           20,
           (Color){0,0,0,60}
        );
    }
    if (Button::Inside())
    {
        if (Cur==0) MakeSound(game),Cur=1;
        if (!used)
        {
            DrawTextEx(game.Font,"Theme second", Vector2{x+25+1,y+1},30,3,LIGHTGRAY);
            DrawRectangleRounded(
            (Rectangle){x,y,200,30}, 
            0.5f,
            20,
            (Color){0,0,0,60}
            );
        }
    } else
    {
        Cur=0;
        
    }
}

void ThemeSecondButton::keep(Button* button)
{
    themeonebutton=button;
}

bool SoundButton::InsidePlus()
{
    Vector2 MousePos=GetMousePosition();
    if (MousePos.x>=xP && MousePos.y>=yP && MousePos.x<=wP && MousePos.y<=hP) return 1;
    return 0;
}

bool SoundButton::InsideMinus()
{
    Vector2 MousePos=GetMousePosition();
    if (MousePos.x>=xM && MousePos.y>=yM && MousePos.x<=wM && MousePos.y<=hM) return 1;
    return 0;
}

void SoundEffectButton::InputPlus(State &game)
{
    if (SoundButton::InsidePlus() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        MakeSound(game);
        if (soundeffectbutton1->second<=0.9){
            soundeffectbutton1->second+=0.1;
            soundeffectbutton2->second+=0.1;
        }
        SetSoundVolume(soundeffectbutton1->first,soundeffectbutton1->second);
        SetSoundVolume(soundeffectbutton2->first,soundeffectbutton2->second);
    }
}

void SoundEffectButton::InputMinus(State &game) 
{
    if (SoundButton::InsideMinus() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        MakeSound(game);
        if (soundeffectbutton1->second>=0.09){ // Sai số 0.1 -> 0.0999
            soundeffectbutton1->second-=0.1;
            soundeffectbutton2->second-=0.1;
        }
        SetSoundVolume(soundeffectbutton1->first,soundeffectbutton1->second);
        SetSoundVolume(soundeffectbutton2->first,soundeffectbutton2->second);
    }
}

void SoundEffectButton::Input(State &game)
{
    SoundEffectButton::InputMinus(game);
    SoundEffectButton::InputPlus(game);
}
void SoundEffectButton::Draw(State &game)
{

    /*DrawTextEx(game.Font,"Background Music", Vector2{700,250},25,3,BLACK);
    DrawRectangleRounded(
        Rectangle{700+80,250+40,150,20},    
        0.5f,
        20,
        WHITE
    );
    DrawTexture(game.MinusButton,700+50,250+40,WHITE);
    DrawTexture(game.PlusButton,700+80+150+10,250+40,WHITE);
    DrawTexture(game.MusicButton,700,250+35,WHITE);*/
    DrawTextEx(game.Font,line.c_str(), Vector2{xM-50,y-40},25,3,BLACK);
    DrawRectangleRounded(
        Rectangle{xM+30,yM,150,20},
        0.5f,
        20,
        WHITE
    );
   
    DrawTexture(game.MinusButton,xM,yM,WHITE);
    DrawTexture(game.PlusButton,xP,yP,WHITE);
    DrawRectangleRounded(
        Rectangle{xM+30,yM,150*soundeffectbutton1->second,20},
        0.5f,
        20,
        GREEN
    );
    
}

void MusicButton::InputPlus(State &game)
{
    if (SoundButton::InsidePlus() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        MakeSound(game);
        if (musicbutton1->second<=0.9){
            musicbutton1->second+=0.1;
            musicbutton2->second+=0.1;
        }
        SetMusicVolume(musicbutton1->first,musicbutton1->second);
        SetMusicVolume(musicbutton2->first,musicbutton2->second);
    }
}

void MusicButton::InputMinus(State &game) 
{
    if (SoundButton::InsideMinus() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        MakeSound(game);
        if (musicbutton1->second>=0.09){ // Sai số 0.1 -> 0.0999
            musicbutton1->second-=0.1;
            musicbutton2->second-=0.1;
        }
        SetMusicVolume(musicbutton1->first,musicbutton1->second);
        SetMusicVolume(musicbutton2->first,musicbutton2->second);
    }
}

void MusicButton::Input(State &game)
{
    MusicButton::InputMinus(game);
    MusicButton::InputPlus(game);
}
void MusicButton::Draw(State &game)
{

    
    DrawTextEx(game.Font,line.c_str(), Vector2{xM-50,y-40},25,3,BLACK);
    DrawRectangleRounded(
        Rectangle{xM+30,yM,150,20},
        0.5f,
        20,
        WHITE
    );
   
    DrawTexture(game.MinusButton,xM,yM,WHITE);
    DrawTexture(game.PlusButton,xP,yP,WHITE);
    DrawRectangleRounded(
        Rectangle{xM+30,yM,150*musicbutton1->second,20},
        0.5f,
        20,
        GREEN
    );
    
}


void External(State &game, Button* startbutton, Button* modebutton, Button* settingbutton)
{
    ClearBackground(RAYWHITE);
    DrawTexture(game.External,0,0,WHITE);
    vector<Button*> work = {startbutton, modebutton, settingbutton};
    for (Button* a:work)
    {
        a->Draw(game);
        a->Input(game);
    }
    DrawTextEx(game.Font,"GO GAME",Vector2{600-200,100},100,10,LIGHTGRAY); 
    DrawTextEx(game.Font,"GO GAME",Vector2{600-200-3,100-3},100,10,BLACK); 
    DrawTextEx(game.Font,"Choose mode first!",Vector2{800,30},30,10,BLACK);
}

void PopUp(State &game, vector<Button*> button)
{
    if (game.PopUpScale+0.05f<=1.0f)
    {
        game.PopUpScale+=0.05f;
    }
    float lenX=1000.0*game.PopUpScale,lenY=642.0*game.PopUpScale;
    DrawFast(game);
    DrawRectangle(0,0,1200,800,Color {0,0,0,100});
    DrawTexturePro(
        game.SettingBackground,
        Rectangle{0,0,(float)game.SettingBackground.width,(float)game.SettingBackground.height},
        Rectangle{600-lenX/2,400-lenY/2,lenX,lenY},
        Vector2{0,0},
        0.0f,
        WHITE
    );
    
    if (game.PopUpScale<0.9f) return;
    DrawTextEx(game.Font,"Board Theme", Vector2{200,200},40,3,BLACK);
    DrawTextEx(game.Font,"Stone Style", Vector2{200,430},40,3,BLACK);

    DrawTextEx(game.Font,"Sound Theme", Vector2{450,430},40,3,BLACK);
    
    
    DrawTexture(game.MusicButton,700,250+35,WHITE);
    
    DrawTexture(game.SoundButton,700,250+35+75,WHITE);
    
    DrawTexture(game.SoundButton,700,250+35+75+75,WHITE);
    
    DrawTexture(game.SoundButton,700,250+35+75+75+75,WHITE);

    for (Button* a:button)
    {
        
        a->Draw(game);
        a->Input(game);

    }
    
}

void DrawFast(State &game)
{
    ClearBackground(RAYWHITE);
    DrawTexture(game.External,0,0,WHITE);

    DrawTexture(game.ButtonStart,600-250/2,400-85/2,WHITE);
    DrawTextEx(game.Font,"Start",(Vector2){600-150/2+18,400-80/2+6},60,3,{0,0,0,200});

    DrawTexture(game.ButtonStart,600-250/2,400-85/2+100,WHITE);
    DrawTextEx(game.Font,"Mode",(Vector2){600-150/2+18,400-80/2+100+6},60,3,{0,0,0,200});

    DrawTexture(game.ButtonStart,600-250/2,400-85/2+200,WHITE);
    DrawTextEx(game.Font,"Setting",(Vector2){600-150/2+6,400-80/2+200+6},60,3,{0,0,0,200});

    DrawTextEx(game.Font,"GO GAME",Vector2{600-200,100},100,10,LIGHTGRAY); 
    DrawTextEx(game.Font,"GO GAME",Vector2{600-200-3,100-3},100,10,BLACK); 
    DrawTextEx(game.Font,"Choose mode first!",Vector2{800,30},30,10,BLACK);

}