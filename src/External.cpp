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
    if (used) DrawRectangle(x,y,57,27, (Color){0,0,0,60});
    if (Button::Inside())
    {
        if (Cur==0) MakeSound(game),Cur=1;
        if (!used) DrawRectangle(x,y,57,27, (Color){0,0,0,60});
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
    if (used) DrawRectangle(x,y,57,27, (Color){0,0,0,60});
    if (Button::Inside())
    {
        if (Cur==0) MakeSound(game),Cur=1;
        if (!used) DrawRectangle(x,y,57,27, (Color){0,0,0,60});
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
        
        if (!used) DrawRectangle(x,y,50,50, (Color){0,0,0,60});
    }
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