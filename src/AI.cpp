#include "include/AI.h"
using namespace std;
int inf=1e9;
int used=10;
int atari_score[3]{0,2000,1000};
int dx[]={0,0,-1,1};
int dy[]={-1,1,0,0};
int distanceInfluence[]={100,50,25,12,6};
bool ck1[23][23];
vector<vector<int>> board (23, vector<int>(23,0));
bool emptyCell[23][23];
pair<int,int> OptimalMove;




struct ff
{
    int val, x, y;
};

void Atari(State &game)
{
    for (int x=1;x<=19;x++) for (int y=1;y<=19;y++) ck1[x][y]=emptyCell[x][y]=0;
    for (int x=1;x<=19;x++)
    {
        for (int y=1;y<=19;y++)
        {
            if (game.board[x][y] && !ck1[x][y])
            {
                game.dem++;
                queue<pair<int,int>> q;
                vector<pair<int,int>> pos;
                int cnt=0, sum=0;
                ck1[x][y]=1;
                q.push({x,y});
                while(q.size())
                {
                    game.dem++;
                    pair<int,int> node=q.front();
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
                        game.HeuristicMap[c.first][c.second] = atari_score[cnt]+sum;
                        //cout<<c.first<<' '<<c.second<<"ATARI"<<endl;
                    }
                    
                    //cout<<1<<endl;
                }
                for (pair<int,int> c: pos)
                {
                    
                    emptyCell[c.first][c.second]=0;

                    
                }
                
            }
            

        }
    }
    
}


void Manhattan(State &game)
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
                        game.dem++;
                        if (x+u>=1 && x+u<=19 && y+v>=1 && y+v<=19 && !game.board[x+u][y+v]) // o vuong 5x5 va la o trong
                        {
                            
                            game.HeuristicMap[x+u][y+v]=0;
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
                int mul=1; // if == 2 -> AI
                if (game.board[x][y]==1) mul=-1;
                for (int u=-4;u<=4;u++)
                {
                    for (int v=-4;v<=4;v++)
                    {
                        game.dem++;
                        int d=abs(u)+abs(v);
                        if (d<=4 && x+u>=1 && x+u<=19 && y+v>=1 && y+v<=19) // manhattan <=4 include current cell
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
    game.SaveBoard.pop_back(); // return old ver
    for (int x=1;x<=19;x++)
    {
        for (int y=1;y<=19;y++)
        {

            game.dem++;
            game.board[x][y]=game.SaveBoard.back()[x][y]; // set to old ver
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
            game.dem++;
            board[x][y]=game.board[x][y];
        }
    }


    game.board[node.x][node.y]=cur;
    
    int c;
    CaptureStone(game,invalid,c); // invalid or not?
    if (invalid)
    {
        for (int x=1;x<=19;x++) 
        {
            for (int y=1;y<=19;y++)
            {
                game.dem++;
                game.board[x][y]=board[x][y]; // return old ver
            }
        }
                
    } else
    {
        
        for (int x=1;x<=19;x++) 
        {
            for (int y=1;y<=19;y++)
            {
                game.dem++;
                board[x][y]=game.board[x][y];
            }
        }
        game.SaveBoard.push_back(board); // update & gameBoard already updated

        game.PlayerPos=(game.PlayerPos==1?2:1);


                
    }

    

}

int Evaluate(State &game)
{

    // Using the last Influence and board
    
    
    
    // Using boundary and limit to calculate score
    // To make sure that if one place is too high or low, it wont get more penalty or bonus


    int score=0;
    int c=0;
    for (int x=1;x<=19;x++)
    {
        for (int y=1;y<=19;y++)
        {
            game.dem++;
            int cost=0,Influence=game.InfluenceMap[x][y];
            if (game.board[x][y]==2) // AI
            {
                c++;
               
                if (Influence<=-50) cost=-200; // Waste one move and one stone
                else if (Influence<0) cost=90; else cost=100;
                //cost=10000;

                // If Influence is too low, mean that this stone is very weak
                // Guarantee that it still get a bonus score
            }
            if (game.board[x][y]==1) // Player
            {
                
                if (Influence>=50) cost=200;
                else if (Influence>0) cost=-90*2; else cost=-100*2;
                cost=-1000;
                
            }
            if (game.board[x][y]==0) // empty cell
            {
                
                if (Influence>100) Influence=100;
                if (Influence<-100) Influence=-100;
                cost=Influence/2;
                
                // To know if this cell belong to who, assume that the higher the influence is, the more it belongs to AI
                // Vice versa
                // Cannot make 100% sure if this cell belongs to who
            }
            score+=cost;
        }
    }
    //cout<<c<<' ';
    return score;

}


int minimax(int depth, int alpha, int beta, bool maximize, State &game)
{
    //game.dem++;

    if (depth==0)
    {
        for (int x=1;x<=19;x++) for (int y=1;y<=19;y++) game.InfluenceMap[x][y]=0;
        Influence(game);
        return Evaluate(game);
    }
    

    // Delete cells which reduce liberties (call them as Xcell) and vice versa

    // Only Xcells is ABSOLUTE unacceptable


    // Heuristic for cell
    vector<ff> OptimalCell;
    for (int x=1;x<=19;x++)
    {
        for (int y=1;y<=19;y++) 
        {
            game.InfluenceMap[x][y]=0;
            game.HeuristicMap[x][y]=-inf;
        }
    }

    
    Manhattan(game); // Allow necessary moves -> reset value to 0 (Around stones)
    

    Atari(game); // Prioritize emergent moves -> set value (Liberties of both AI and Stone)
    
    Influence(game); // Build a map for checking safety (+ for close to AI, - for close to player)

    //Bonus score for connect 2 components

    //


    //

    // After heuristic, check if Illegal or not

    if (maximize)
    {
        

        for (int x=1;x<=19;x++)
        {
            for (int y=1;y<=19;y++)
            {
                if (game.HeuristicMap[x][y]>=-10000)
                {
                    int cost=game.HeuristicMap[x][y]-abs(game.InfluenceMap[x][y]); // Too close to teammate or opponent get a penalty
                    OptimalCell.push_back({cost,x,y});
                }
            }
        }
        //cout<<OptimalCell[0].x<<' '<<OptimalCell[0].y<<endl;
        sort(OptimalCell.begin(),OptimalCell.end(),[](ff u, ff v){return u.val>v.val;});
        //if (OptimalCell[0].val>=1500) cout<<1<<endl;


        // After this sort, game.HeuristicMap and game.InfluenceMap is unnecessary
        // Except in depth 1, when move to depth 0, the loop does not change these, only using for calculate score

        // Only game.Board and game.SaveBoard using their old ver through each loop

        // Consider pass move
        int maxValue=-inf;
        for (int i=0;i<min(used,(int)OptimalCell.size());i++)
        {
            int invalid=0;
            preWork(game,OptimalCell[i],invalid,2); // build board and history board for next depth
            if (!invalid)
            {
                int val=minimax(depth-1,alpha,beta,0,game);
                //cout<<"MAX"<<' '<<OptimalCell[i].x<<' '<<OptimalCell[i].y<<' '<<val<<' '<<game.HeuristicMap[4][3]-abs(game.InfluenceMap[4][3])<<' '
                //<<game.HeuristicMap[OptimalCell[i].x][OptimalCell[i].y]-abs(game.InfluenceMap[OptimalCell[i].x][OptimalCell[i].y])<<endl;
                if (maxValue<val)
                {
                    maxValue=val;
                    if (depth==5) game.AIMove={OptimalCell[i].x,OptimalCell[i].y};
                }
                
                alpha=max(alpha,val);
                SufWork(game); // return to old ver

                if (beta<=alpha)
                {
                    break;
                }


            }

        }

        return maxValue;

    } else
    {
          

        for (int x=1;x<=19;x++)
        {
            for (int y=1;y<=19;y++)
            {
                if (game.HeuristicMap[x][y]>=-10000) 
                {
                    int cost=game.HeuristicMap[x][y]-abs(game.InfluenceMap[x][y]); // Too close to teammate or opponent get a penalty
                    OptimalCell.push_back({cost,x,y});
                    if (cost>=1000)
                    {
                        //cout<<"FOUND THIS"<<' '<<OptimalCell.back().val<<' '<<OptimalCell.back().x<<' '<<OptimalCell.back().y<<endl;
                    }
                }
            }
        }
        sort(OptimalCell.begin(),OptimalCell.end(),[](ff u, ff v){return u.val>v.val;});
        // After this sort, game.HeuristicMap and game.InfluenceMap is unnecessary
        // Only game.Board and game.SaveBoard using their old ver through each loop
        // Consider pass move
        int minValue=inf;
        
        int dd=game.InfluenceMap[4][3];
        
        for (int i=0;i<min(used,(int)OptimalCell.size());i++)
        {
            int invalid=0;
            preWork(game,OptimalCell[i],invalid,1); // build board and history board for next depth
            //cout<<OptimalCell[i].val<<' '<<invalid<<endl;
            if (!invalid)
            {
                int val=minimax(depth-1,alpha,beta,1,game);
                
                /*cout<<"MIN"<<' '<<OptimalCell[i].x<<' '<<OptimalCell[i].y<<' '<<val<<' '<<game.HeuristicMap[4][3]-dd<<' '
                <<OptimalCell[i].val<<endl;  */
                minValue=min(minValue,val);
                beta=min(beta,val);
                SufWork(game); // return to old ver

                if (beta<=alpha)
                {
                    break;
                }


            }

        }

        return minValue;


    }
    

    // Remember to push newboard to game.undo for checking rule
}



void AI(State &game)
{
    minimax(5,-inf,inf,1,game);
    
    
}

