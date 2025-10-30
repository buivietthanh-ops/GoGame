#include "include/interaction.h"
#include<iostream>
using namespace std;
vector<vector<int>> board (23, vector<int>(23,0));
void MakeSound(State &game)
{
    PlaySound(game.click);
}
void MakeSoundGetScore(State &game)
{
    PlaySound(game.GetScore);
}
position real_pos(Vector2 mousePos, int cell_sz)
{
    int mul_x=(int)mousePos.x/cell_sz;
    double posX=mousePos.x-cell_sz*mul_x;
    position board;
    if (posX*2.0<=cell_sz) board.x=cell_sz*mul_x; else board.x=cell_sz*(mul_x+1);
    int mul_y=(int)mousePos.y/cell_sz;
    double posY=mousePos.y-cell_sz*mul_y;
    if (posY*2.0<=cell_sz) board.y=cell_sz*mul_y; else board.y=cell_sz*(mul_y+1);
    return board;
}
void InputStone(State &game, int &invalid)
{

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
       {
            MakeSound(game);
            Vector2 mousePos = GetMousePosition();
            position Pos=real_pos(mousePos,game.cell_sz);
            Pos.x-=game.outside;
            if (Pos.x/game.cell_sz>=1 && Pos.x/game.cell_sz<=game.size && Pos.y/game.cell_sz>=1 && Pos.y/game.cell_sz<=game.size && game.board[Pos.x/game.cell_sz][Pos.y/game.cell_sz]==0)
            {
                for (int x=1;x<=19;x++) 
                {
                    for (int y=1;y<=19;y++)
                    {
                        board[x][y]=game.board[x][y];
                    }
                }
                    
                game.board[Pos.x/game.cell_sz][Pos.y/game.cell_sz]=game.PlayerPos;
                int getscore=0;
                CaptureStone(game,invalid,getscore);
                if (invalid)
                {
                    for (int x=1;x<=19;x++) 
                    {
                        for (int y=1;y<=19;y++)
                        {
                            game.board[x][y]=board[x][y];
                        }
                    }
                    DrawText("Invalid!",500,300,50,ORANGE);
                } else
                {
                    game.PlayerPos=(game.PlayerPos==1?2:1);
                    for (int x=1;x<=19;x++) 
                    {
                        for (int y=1;y<=19;y++)
                        {
                            board[x][y]=game.board[x][y];
                        }
                    }
                    game.SaveBoard.push_back(board);
                    if (getscore) MakeSoundGetScore(game);
                }
            }
            //cout<<Pos.x<<' '<<Pos.y<<endl;
       }
}

