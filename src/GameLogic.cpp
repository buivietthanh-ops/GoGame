#include "include/GameLogic.h"
#include <iostream>
#include <queue>
using namespace std;
int ck[23][23];
int ud[]={0,0,-1,1};
int lr[]={-1,1,0,0};

void CaptureStone(State &game, int &invalid, int &getscore)
{
    for (int x=1;x<=19;x++) for (int y=1;y<=19;y++) ck[x][y]=0;
    bool ktr[3];
    ktr[1]=ktr[2]=0;
    vector<pair<int,int>> contain;
    for (int x_cur=1;x_cur<=19;x_cur++)
    {
        for (int y_cur=1;y_cur<=19;y_cur++)
        {
            if (game.board[x_cur][y_cur] && ck[x_cur][y_cur]==0)
            {
                int cnt=0;
                queue <pair<int,int>> q;
                vector<pair<int,int>> d;
                q.push({x_cur,y_cur});
                ck[x_cur][y_cur]=1;
                
                while(q.size())
                {
                    pair<int,int> pos=q.front();
                    q.pop();
                    d.push_back(pos);
                    for (int i=0;i<4;i++)
                    {
                        int x=pos.first+ud[i], y=pos.second+lr[i];
                        if (x>=1 && x<=19 && y>=1 && y<=19)
                        {
                            if (game.board[x][y]==game.board[x_cur][y_cur] && ck[x][y]==0) q.push({x,y}),ck[x][y]=1; else
                            if (game.board[x][y]==0) cnt++;
                        }
                    }
                }
                if (cnt==0)
                {
                    ktr[game.board[x_cur][y_cur]]=1;
                    if (game.board[x_cur][y_cur]!=game.PlayerPos) for (pair<int,int> u:d) contain.push_back(u);
                }

            }
        }
    }
    if (contain.size()>0) getscore=1;
    if (ktr[game.PlayerPos]==0)
    {
        for (pair<int,int> pos:contain)
        {
            game.board[pos.first][pos.second]=0;
        }
        return;
    }
    if (ktr[game.PlayerPos]==1 && ktr[(game.PlayerPos==1?2:1)]==0)
    {
        invalid=1;
        return;
    }
    if (game.SaveBoard.size()<2) return;
    for (pair<int,int> pos:contain)
    {
        game.board[pos.first][pos.second]=0;
    }
    int dif=0;
    for (int i=1;i<=19;i++)
    {
        for (int j=1;j<=19;j++)
        {
            if (game.board[i][j]!=game.SaveBoard[game.SaveBoard.size()-2][i][j]) dif=1;
        }
    }
    if (!dif)
    {
        invalid=1;

        return;
    }
}