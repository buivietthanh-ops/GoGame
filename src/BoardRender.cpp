#include "include/BoardRender.h"


void DrawBoard(State &game)
{
    ClearBackground(RAYWHITE);
    
    DrawTexture(game.PlayBoard,0,0,WHITE);
    for (int x=1;x<=19;x++)
    {
        for (int y=1;y<=19;y++)
        {
            if (game.board[x][y]>0)
            {
                float pixelX=x*game.cell_sz+game.outside;
                float pixelY=y*game.cell_sz;
                Color shadow= (Color){0,0,0,80};
                DrawCircle(pixelX+3, pixelY+3,game.cell_sz/2.5f,shadow);
                if (game.board[x][y]==1)
                {
                    if (game.isClassic) DrawCircleGradient(pixelX,pixelY,game.cell_sz/2.5f,DARKGRAY,BLACK); 
                    else DrawTextureEx(game.BlackStone,{pixelX-16,pixelY-16},0.0f,0.2f,WHITE);
                }
                else 
                {
                    if (game.isClassic) DrawCircleGradient(pixelX,pixelY,game.cell_sz/2.5f,WHITE,LIGHTGRAY);
                    else  DrawTextureEx(game.WhiteStone,{pixelX-16,pixelY-16},0.0f,0.2f,WHITE);
                    
                }
            }
        }
    }
    if (game.board[0][1]>0){
        float pixelX=game.board[0][1]*game.cell_sz+game.outside;
        float pixelY=game.board[0][2]*game.cell_sz;
        Color color;
        float c=0,d=0;
        if (game.board[game.board[0][1]][game.board[0][2]]==1) color=WHITE; else color=BLACK,c=1,d=0.3;
        DrawRing(
            {pixelX+d,pixelY},
            game.cell_sz/6,
            game.cell_sz/5+c,
            0,
            360,
            64,
            color
        );
    }
    if (game.PlayerPos==1)
    {
        DrawRectangleRounded(
            (Rectangle){80,75,230,60},
            0.5f,
            20,
            (Color){255,255,255,80}
        );
        DrawTextEx(game.Font,"Black Turn",(Vector2){85,75},60,2,BLACK);
    } else 
    {
        DrawRectangleRounded(
            (Rectangle){80,75,230,60},
            0.5f,
            20,
            (Color){0,0,0,80}
        );
        DrawTextEx(game.Font,"White Turn",(Vector2){85,75},60,2,WHITE);
    }
}
void DrawInvalidOption(State &game)
{
    float x=600-game.InvalidOption.width/2,y=400-game.InvalidOption.height/2;
    DrawTexture(game.InvalidOption,x,y,WHITE);
    Vector2 size=MeasureTextEx(game.Font,"SELECT GAME MODE",50,5);
    DrawTextEx(game.Font,"SELECT GAME MODE",{600-size.x/2+1,y+70+1},50,5,{30,30,30,255});
    DrawTextEx(game.Font,"SELECT GAME MODE",{600-size.x/2,y+70},50,5,{230,220,200,255});
    size=MeasureTextEx(game.Font,"TO CONTINUE!",50,5);
    DrawTextEx(game.Font,"TO CONTINUE!",{600-size.x/2+1,y+150+1},50,5,{30,30,30,255});
    DrawTextEx(game.Font,"TO CONTINUE!",{600-size.x/2,y+150},50,5,{230,220,200,255});
}
