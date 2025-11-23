#include "include/BoardRender.h"




void DrawBoard(State &game)
{
    ClearBackground(RAYWHITE);
    //game.Board=game.ModernBoard; //
    DrawTexture(game.PlayBoard,0,0,WHITE);
    for (int x=1;x<=game.size;x++)
    {
        for (int y=1;y<=game.size;y++)
        {
            if (game.board[x][y]>0)
            {
                double pixelX=x*game.cell_sz+game.outside;
                double pixelY=y*game.cell_sz;
                Color shadow= (Color){0,0,0,80};
                DrawCircle(pixelX+4, pixelY+4,game.cell_sz/3,shadow);
                if (game.board[x][y]==1)
                {
                    if (game.isClassic) DrawCircleGradient(pixelX,pixelY,game.cell_sz/3,DARKGRAY,BLACK); 
                    else DrawTexture(game.BlackStone,pixelX-13,pixelY-13,WHITE);
                }
                else 
                {
                    if (game.isClassic) DrawCircleGradient(pixelX,pixelY,game.cell_sz/3,WHITE,LIGHTGRAY);
                    else  DrawTexture(game.WhiteStone,pixelX-13,pixelY-13,WHITE);
                    
                }
            }
        }
    }
    if (game.PlayerPos==1)
    {
        DrawRectangleRounded(
            (Rectangle){100,75,230,60},
            0.5f,
            20,
            (Color){255,255,255,80}
        );
        DrawTextEx(game.Font,"Black Turn",(Vector2){100,75},60,2,BLACK);
        DrawTextEx(game.Font,"Black Turn",(Vector2){100,75},60,2,BLACK);
    } else 
    {
        DrawRectangleRounded(
            (Rectangle){100,75,230,60},
            0.5f,
            20,
            (Color){0,0,0,80}
        );
        DrawTextEx(game.Font,"White Turn",(Vector2){100,75},60,2,WHITE);
    }
}
void DrawInvalidOption(State &game, int x, int y)
{
    DrawTexture(game.InvalidOption,x,y,WHITE);
}
void Draw2Options(State &game)
{
    DrawTexture(game.TwoOptions,600-270,400-270,WHITE);
    // -> InputOptions
}