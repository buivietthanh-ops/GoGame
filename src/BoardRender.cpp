#include "include/BoardRender.h"
#include <iostream>
#include <random>



void DrawBoard(State &game)
{
    ClearBackground(RAYWHITE);
    DrawTexture(game.background,0,0,WHITE);
    for (int x=1;x<=game.size;x++)
    {
        for (int y=1;y<=game.size;y++)
        {
            if (game.board[x][y]>0)
            {
                double pixelX=x*game.cell_sz+game.outside;
                double pixelY=y*game.cell_sz;
                Color cell_col = (game.board[x][y]==1? BLACK : WHITE);
                DrawCircle(pixelX, pixelY,game.cell_sz/3,cell_col);
            }
        }
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