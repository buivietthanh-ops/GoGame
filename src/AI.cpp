#include "include/AI.h"
using namespace std;
int inf=1e8;
int used[]={0,3,5,6,10,10,20};
int atari_score[3]{0,30000,10000};
int dx[]={0,0,-1,1};
int dy[]={-1,1,0,0};
int distanceInfluence[]={100,50,25,12,6};
bool ck1[23][23], ck2[403];
vector<vector<int>> board (23, vector<int>(23,0));
bool emptyCell[23][23];
int group[23][23], sz[403];

int type_stone[]={0,-5,-1,1,10,5};





int score_connect=0;
pair<int,int> OptimalMove;




struct ff
{
    int val, x, y;
};

void Atari(State &game)
{
    for (int x=1;x<=19;x++) for (int y=1;y<=19;y++) ck1[x][y]=emptyCell[x][y]=0;
    
    int type=0;
    score_connect=0;
    for (int x=1;x<=19;x++)
    {
        for (int y=1;y<=19;y++)
        {
            if (game.board[x][y] && !ck1[x][y])
            {
                

                type++; 
                queue<pair<int,int>> q;
                vector<pair<int,int>> pos;
                int cnt=0, sum=0;
                ck1[x][y]=1;
                q.push({x,y});
                while(q.size())
                {
                    
                    
                    pair<int,int> node=q.front();
                    group[node.first][node.second]=type; 
                    
                    q.pop();
                    sum++;
                    for (int i=0;i<4;i++)
                    {
                        int u=node.first+dx[i],v=node.second+dy[i];
                        if (u>=1 && u<=19 && v>=1 && v<=19)
                        {
                            
                            if (game.board[x][y]==game.board[u][v] && !ck1[u][v])
                            {
                                ck1[u][v]=1;
                                q.push({u,v});
                                
                            } 
                            else if (!game.board[u][v] && !emptyCell[u][v] && cnt<=2)
                            {
                                cnt++;
                                emptyCell[u][v]=1;
                                pos.push_back({u,v});
                                
                            }
                        }
                    }
                    
                }
                if (cnt<=2)
                {
                    for (pair<int,int> c: pos)
                    {
                        game.HeuristicMap[c.first][c.second] += atari_score[cnt]+sum;
                        
                    }
                    
                    
                }
                for (pair<int,int> c: pos)
                {
                    
                    emptyCell[c.first][c.second]=0;

                    
                }

                sz[type]=sum;
                if (game.board[x][y]==2) score_connect+=sum*sum;
                
            }
            

        }
    }
    
}


void Local(State &game)
{
    for (int x=1;x<=19;x++)
    {
        for (int y=1;y<=19;y++)
        {
            if (game.board[x][y])
            {
                for (int u=-2;u<=2;u++)
                {
                    for (int v=-2;v<=2;v++)
                    {
                        
                        if (x+u>=1 && x+u<=19 && y+v>=1 && y+v<=19 && !game.board[x+u][y+v]) 
                        {
                            int posX=min(x+u,20-x-u), posY=min(y+v,20-y-v);
                            game.HeuristicMap[x+u][y+v]=type_stone[min({posX,posY,5})];
                            if (posX<=4 && posY<=4 && posX>=3 && posY>=3) game.HeuristicMap[x+u][y+v]+=100;

                        }
                    }
                }
            }
        }
    }
    
}

void Influence(State &game)
{
    for (int x=1;x<=19;x++)
    {
        for (int y=1;y<=19;y++)
        {
            if (game.board[x][y])
            {
                int mul=1; 
                if (game.board[x][y]==1) mul=-1;
                for (int u=-4;u<=4;u++)
                {
                    for (int v=-4;v<=4;v++)
                    {
                        
                        int d=abs(u)+abs(v);
                        if (d<=4 && x+u>=1 && x+u<=19 && y+v>=1 && y+v<=19) 
                        {
                            game.InfluenceMap[x+u][y+v]+=distanceInfluence[d]*mul;
                        }
                    }
                }
            }
        }
    }
}




void SufWork(State &game)
{
    game.SaveBoard.pop_back(); 
    for (int x=1;x<=19;x++)
    {
        for (int y=1;y<=19;y++)
        {

            
            game.board[x][y]=game.SaveBoard.back()[x][y]; 
        }
    }
    game.PlayerPos=(game.PlayerPos==1?2:1);
    
}

void preWork(State &game, ff node, int &invalid, int cur)
{
    
    

    for (int x=1;x<=19;x++) 
    {
        for (int y=1;y<=19;y++)
        {
            
            board[x][y]=game.board[x][y];
        }
    }


    game.board[node.x][node.y]=cur;
    
    int c;
    CaptureStone(game,invalid,c);
    if (invalid)
    {
        for (int x=1;x<=19;x++) 
        {
            for (int y=1;y<=19;y++)
            {
                
                game.board[x][y]=board[x][y]; 
            }
        }
                
    } else
    {
        
        for (int x=1;x<=19;x++) 
        {
            for (int y=1;y<=19;y++)
            {
                
                board[x][y]=game.board[x][y];
            }
        }
        game.SaveBoard.push_back(board); 

        game.PlayerPos=(game.PlayerPos==1?2:1);


                
    }

    

}

void Connect_Suicide(State &game, bool maximize)
{
    int cur,enemy;
    if (maximize) cur=2,enemy=1; else cur=1,enemy=2;
    for (int x=1;x<=19;x++)
    {
        for (int y=1;y<=19;y++)
        {
            
            if (game.board[x][y]==0)
            {   
                int sum=0,cost=0, dif=0, near_enemy=0, idGroup=0,libs_around=0;
                
                pair<int,int> node;
                for (int i=0;i<4;i++)
                {
                    int u=x+dx[i],v=y+dy[i];
                    if (game.board[u][v]==cur && !ck2[group[u][v]])
                    {

                        dif++;
                        idGroup=group[u][v];
                        int d=sz[group[u][v]];
                        sum+=d;
                        cost-=d*d;
                        ck2[group[u][v]]=1;
                    }
                    if (game.board[u][v]==enemy) near_enemy=1;
                    if (game.board[u][v]==0) libs_around++;
                }
                cost+=sum*sum;
                if (game.HeuristicMap[x][y]<25000) 
                {
                
                    
                    
                    if (dif==1 && !near_enemy) 
                    {
                        int libs=-1;
                        for (int i=0;i<4;i++)
                        {
                            int u=x+dx[i],v=y+dy[i];
                            if (u>=1 && u<=19 && v>=1 && v<=19)
                            {
                                
                                int success=1;
                                for (int j=0;j<4;j++)
                                {
                                    int u_new=u+dx[j],v_new=v+dy[j];
                                    if (u_new>=1 && u_new<=19 && v_new>=1 && v_new<=19)
                                    {
                                        if (group[u_new][v_new]==idGroup) 
                                        {
                                            success=0;
                                            break;
                                        }
                                    }
                                }
                                libs+=success;
                            }
                        }
                        if (libs<0) game.HeuristicMap[x][y]=-inf;
                    }
                    

                    if (dif>1 && !near_enemy && libs_around==0) 
                    {
                        game.HeuristicMap[x][y]=-inf;
                    }
                }
                


                for (int i=0;i<4;i++)
                {
                    int u=x+dx[i],v=y+dy[i];
                    if (game.board[u][v]==cur) ck2[group[u][v]]=0;
                }
                
                game.HeuristicMap[x][y]+=cost*10+(cost>0?200:0);



                

            }
            

        }
    }
}


int Evaluate(State &game)
{

    
    int score=0;
    
    for (int x=1;x<=19;x++)
    {
        for (int y=1;y<=19;y++)
        {
            
            int cost=0;
            
            if (game.board[x][y]==2)
            {
                cost=1000;
                int posX=min(x,20-x), posY=min(y,20-y);
                cost+=type_stone[min({posX,posY,5})];
                if (posX<=4 && posY<=4 && posX>=3 && posY>=3) cost+=100;
                
            }
            if (game.board[x][y]==1)
            {
                
                cost=-1000;
                int posX=min(x,20-x), posY=min(y,20-y);
                cost-=type_stone[min({posX,posY,5})];
                if (posX<=4 && posY<=4 && posX>=3 && posY>=3) cost-=100;
                
            }
            if (game.board[x][y]==0)
            {
                int Influence=game.InfluenceMap[x][y];
                if (Influence>65) Influence=65;
                if (Influence<-65) Influence=-65;
                score+=Influence/20;
            }
            score+=cost;


        }
    }
    
    return score+score_connect;

}




int minimax(int depth, int alpha, int beta, bool maximize, State &game, int pass_move)
{
    
    long long hash=game.keyturn[game.PlayerPos];
    
    for (int x=1;x<=19;x++)
    {
        for (int y=1;y<=19;y++)
        {
            hash^=game.zorHash[x][y][game.board[x][y]];
        }
    }
    auto it=game.usedState.find(hash);
    if (it!=game.usedState.end())
    {
        return (*it).second;
    }
    
    if (depth==0 || pass_move==2)
    {
        
        int score=Evaluate(game);
        game.usedState[hash]=score;
        return score;
    }
    
    

    


    
    vector<ff> OptimalCell;
    for (int x=1;x<=19;x++)
    {
        for (int y=1;y<=19;y++) 
        {
            game.InfluenceMap[x][y]=0;
            game.HeuristicMap[x][y]=-inf;
        }
    }

    
    Local(game);
    

    Atari(game);
    
    Influence(game);

    Connect_Suicide(game,maximize);


    

    if (maximize)
    {
        

        for (int x=1;x<=19;x++)
        {
            for (int y=1;y<=19;y++)
            {
                if (game.HeuristicMap[x][y]>=-10000)
                {
                    int cost=game.HeuristicMap[x][y]-abs(game.InfluenceMap[x][y]);
                    OptimalCell.push_back({cost,x,y});
                }
            }
        }
        if (OptimalCell.size()==0)
        {
            srand(time(NULL));
            OptimalCell.push_back({0,rand()%19+1,rand()%19+1});
        }
        
        sort(OptimalCell.begin(),OptimalCell.end(),[](ff u, ff v){return u.val>v.val;});

        
        int maxValue=-inf,isExist=0,dem=0;
        for (int i=0;i<OptimalCell.size();i++)
        {
            if (dem>used[depth]) break;

            int invalid=0;
            preWork(game,OptimalCell[i],invalid,2);
            if (!invalid)
            {
                dem++;
                isExist=1;
                int val=minimax(depth-1,alpha,beta,0,game,0);
                
                if (maxValue<val)
                {
                    maxValue=val;
                    if (depth==game.depth) game.AIMove={OptimalCell[i].x,OptimalCell[i].y};
                }
                
                alpha=max(alpha,val);
                SufWork(game);

                if (beta<=alpha)
                {
                    break;
                }

            }

            if (!isExist)
            {
                
                int invalid=0;
                preWork(game,{0,0},invalid,2);
                int val=minimax(depth-1,alpha,beta,0,game,pass_move+1);
                if (maxValue<val)
                {
                    maxValue=val;
                    if (depth==game.depth) game.AIMove={0,0};
                }
                alpha=max(alpha,val);
                SufWork(game);
            }
            
            

        }
        game.usedState[hash]=maxValue;
        return maxValue;

    } else
    {
          

        for (int x=1;x<=19;x++)
        {
            for (int y=1;y<=19;y++)
            {
                if (game.HeuristicMap[x][y]>=-10000) 
                {
                    int cost=game.HeuristicMap[x][y]-abs(game.InfluenceMap[x][y]);
                    OptimalCell.push_back({cost,x,y});
                    
                }
            }
        }
        sort(OptimalCell.begin(),OptimalCell.end(),[](ff u, ff v){return u.val>v.val;});
        
        int minValue=inf,isExist=0,dem=0;

        for (int i=0;i<OptimalCell.size();i++)
        {
            int invalid=0;
            if (dem>used[depth]) break;

            preWork(game,OptimalCell[i],invalid,1);
            if (!invalid)
            {
                dem++;
                isExist=1;
                int val=minimax(depth-1,alpha,beta,1,game,0);
                minValue=min(minValue,val);
                beta=min(beta,val);
                SufWork(game);

                if (beta<=alpha)
                {
                    break;
                }

            }

        }
        if (!isExist)
        {
            int invalid=0;
            preWork(game,{0,0},invalid,1);
            int val=minimax(depth-1,alpha,beta,1,game,pass_move+1);
            minValue=min(minValue,val);
            beta=min(beta,val);
            SufWork(game);

        }
        game.usedState[hash]=minValue;
        return minValue;


    }
    
}


State gameCopy(State &game)
{
    State gameCopy;

    for (int x=1;x<=19;x++)
    {
        for (int y=1;y<=19;y++) 
        {
            gameCopy.board[x][y]=game.board[x][y];
            gameCopy.HeuristicMap[x][y]=game.HeuristicMap[x][y];
            gameCopy.InfluenceMap[x][y]=game.InfluenceMap[x][y];
            for (int i=0;i<=2;i++)
            {
                gameCopy.zorHash[x][y][i]=game.zorHash[x][y][i];
            }
        }
    }
    gameCopy.PlayerPos=game.PlayerPos;
    gameCopy.level=game.level;
    gameCopy.keyturn[1]=game.keyturn[1];
    gameCopy.keyturn[2]=game.keyturn[2];

    if (game.SaveBoard.size()>=2)
    {
        gameCopy.SaveBoard.push_back(game.SaveBoard[game.SaveBoard.size()-2]);
    }
    gameCopy.SaveBoard.push_back(game.SaveBoard.back());
    return gameCopy;

}
pair<int,int> AI(State game)
{

    game.usedState.clear();
    if (game.level==1) game.depth=1;
    if (game.level==2) game.depth=3;
    if (game.level==3) game.depth=6;
    minimax(game.depth,-inf,inf,1,game,0);
    return game.AIMove;
    
}

