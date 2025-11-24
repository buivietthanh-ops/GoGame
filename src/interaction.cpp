#include "include/interaction.h"
#include<filesystem>
using namespace std;

namespace fs = std::filesystem;
void MakeSound(State &game)
{
    PlaySound(game.sound[game.isSound].Click.first);
}
void MakeSoundGetScore(State &game)
{
    PlaySound(game.sound[game.isSound].Getscore.first);
}
void MakeSoundEndGame(State &game)
{
    PlaySound(game.sound[game.isSound].Endgame.first);
}


void isValid(State &game, int &invalid, int &used, int &time, string &line)
{
    if (invalid==3) line="  CAPTURE! ";
    if (invalid==2) line="KO THREATS!";
    if (invalid==1) line="NO SUICIDE!";
    if (invalid)
    {
        time=GetTime();
        used=1;
    }
    if (used==1)
    {
        if (GetTime()-time>=1.5)
            {
                time=0;
                used=0;
            } else 
            {
                DrawRectangleRounded(
                    Rectangle{400,300,530,100},
                    0.5,
                    20,
                    Color{255,255,255,100}
                );
                DrawTextEx(game.Font,line.c_str(),(Vector2){400,300},100,5,LIGHTGRAY);
                DrawTextEx(game.Font,line.c_str(),(Vector2){403,303},100,5,BLACK);
            }
    }
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
void Player::InputStone(State &game, int &invalid)
{
    vector<vector<int>> board (23, vector<int>(23,0));

    Vector2 mousePos = GetMousePosition();

    position Pos=real_pos(mousePos,game.cell_sz);

    Pos.x-=game.outside;
    
    if (Pos.x/game.cell_sz>=1 && Pos.x/game.cell_sz<=game.size && Pos.y/game.cell_sz>=1 && Pos.y/game.cell_sz<=game.size && game.board[Pos.x/game.cell_sz][Pos.y/game.cell_sz]==0)
    {
        if (game.PlayerPos==1) DrawCircle(Pos.x+game.outside,Pos.y+2.5,game.cell_sz/3, (Color){0,0,0,60}); else
        DrawCircle(Pos.x+game.outside,Pos.y+2.5,game.cell_sz/3, (Color){255,255,255,60});
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
       {
            MakeSound(game);
            //Vector2 mousePos = GetMousePosition();
            //position Pos=real_pos(mousePos,game.cell_sz);
            //Pos.x-=game.outside;
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
                    if (getscore) 
                    {
                        MakeSoundGetScore(game);
                        invalid=3;
                    }
                    game.Redo.clear();
                }
            }
            //cout<<Pos.x<<' '<<Pos.y<<endl;
       }
}


bool InsideButton::Inside()
{
    Vector2 MousePos=GetMousePosition();
    if (MousePos.x>=x && MousePos.y>=y && MousePos.x<=w && MousePos.y<=h) return 1;
    return 0;
}

void InsideButton::Input(State &game){}
void InsideButton::SaveDraw(State &game){}
void InsideButton::SaveGame(State &game, char filename[]){}
void InsideButton::LoadDraw(State &game){}
void InsideButton::LoadGame(State &game, string filename){}
bool InsideButton::isUsing(){}
void InsideButton::Draw(State &game)
{
    int c=0,k=0;
    if (line=="Reset") c=8;
    if (line=="Play Again") c=47,k=5;
    if (InsideButton::Inside())
    {
        DrawTexturePro(
            game.PassButton,
            Rectangle{0,0,(float)game.PassButton.width,(float)game.PassButton.height},
            Rectangle{x-2,y-2,(float)game.PassButton.width+4,(float)game.PassButton.height+4},
            Vector2{0,0},
            0.0f,
            WHITE
        );
        DrawTextEx(game.Font,line.c_str(),Vector2{x+63-c,y+8},45-k,3,BLACK);
        return;
    } else
    {
        DrawTexture(game.PassButton,x,y,WHITE);
        DrawTextEx(game.Font,line.c_str(),Vector2{x+65-c,y+10},40-k,3,BLACK);
    }
}

void PassButton::Input(State &game)
{
    if (InsideButton::Inside() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        MakeSound(game);
        game.PlayerPos=(game.PlayerPos==1?2:1);
        game.Redo.clear();
        vector<vector<int>> board (23, vector<int>(23,0));
        for (int x=1;x<=19;x++) for (int y=1;y<=19;y++) board[x][y]=game.board[x][y];
        game.SaveBoard.push_back(board);
        
    }
}



void UndoButton::Input(State &game)
{
    if (InsideButton::Inside() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        MakeSound(game);
        if (game.SaveBoard.size()>=3)
        {
            game.Redo.push_back(game.SaveBoard.back());
            game.SaveBoard.pop_back();
            game.Redo.push_back(game.SaveBoard.back());
            game.SaveBoard.pop_back();
            for (int x=1;x<=19;x++)
            {
                for (int y=1;y<=19;y++) game.board[x][y]=game.SaveBoard[game.SaveBoard.size()-1][x][y];
            }
        }
        
    }
}

void RedoButton::Input(State &game)
{
    if (InsideButton::Inside() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        MakeSound(game);
        if (game.Redo.size()>=2)
        {
            game.SaveBoard.push_back(game.Redo.back());
            game.Redo.pop_back();
            game.SaveBoard.push_back(game.Redo.back());
            game.Redo.pop_back();
            for (int x=1;x<=19;x++)
            {
                for (int y=1;y<=19;y++) game.board[x][y]=game.SaveBoard[game.SaveBoard.size()-1][x][y];
            }
        }
        
    }
}

void ResetButton::Input(State &game)
{
    if (InsideButton::Inside() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        MakeSound(game);
        while(game.SaveBoard.size()>=2) game.SaveBoard.pop_back();
        game.Redo.clear();
        for (int x=1;x<=19;x++)
        {
            for (int y=1;y<=19;y++) game.board[x][y]=0;
        }
        game.PlayerPos=1;
    }
}

void SaveButton::SaveGame(State &game, char filename[])
{
    json j;

    j["SaveBoard"]=game.SaveBoard;
    j["Redo"]=game.Redo;
    
    string name="save/";
    name+=filename;
    name+=".json";
    ofstream fout(name);

    fout<<j.dump(4);
    
    fout.close();


}

void SaveButton::Input(State &game)
{
    if (InsideButton::Inside() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        
        MakeSound(game);
        SaveText=1;
        filename[0]='\0';
        
    }
    
}

void SaveButton::SaveDraw(State &game)
{
    if (!SaveText) return;

    if (GuiWindowBox({600-800/2,400-500/2,800,300},"Save Game"))
    {
        SaveText=0;
    }

    GuiTextBox({600-600/2,250,600,45},filename,50, SaveText);

    if (GuiButton({600-200/2,350,200,50}, "Save"))
    {
        SaveGame(game,filename);
        SaveText=0;
    }
}

bool SaveButton::isUsing()
{
    return SaveText;
}
void LoadButton::LoadGame(State &game, string filename)
{
    ifstream fin("save/"+filename);
    //cout<<filename<<endl;
    json j;
    fin>>j;
    fin.close();
    game.SaveBoard=j["SaveBoard"];
    game.Redo=j["Redo"];

    for (int x=1;x<=19;x++)
    {
        for (int y=1;y<=19;y++)
        {
            game.board[x][y]=game.SaveBoard[game.SaveBoard.size()-1][x][y];
        }
    }
    if (game.SaveBoard.size()%2) game.PlayerPos=1; else game.PlayerPos=2;

}

void LoadButton::Input(State &game)
{
    if (InsideButton::Inside() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        
        MakeSound(game);

        used=1;
        rowClick=-1;
        rowInside=-1;
        scroll=0;
        game.filelist.clear();
        for (auto &entry : fs::directory_iterator("save"))
        {
            string name=entry.path().filename().string();
            game.filelist.push_back(name);
        }
    }
    
}

void LoadButton::LoadDraw(State &game)
{
    
    if (!used) return;
    if (GuiWindowBox(Rectangle{600-900/2,400-600/2,900,600},"Load Game"))
    {
        used=0;
        return;
    }

    string filelist="";
    for (int i=0;i+1<game.filelist.size();i++)
    {
        filelist+=game.filelist[i];
        filelist+=";";
    }
    if (game.filelist.size()) filelist+=game.filelist.back();
    GuiListView(Rectangle{600-800/2,400-600/2+50,800,500},filelist.c_str(),&rowInside,&rowClick);
    
    if (GuiButton({600-200/2,655,200,40},"Load"))
    {
        if (rowClick>=0 && rowClick<game.filelist.size())
        {
            //cout<<1<<endl;
            LoadGame(game, game.filelist[rowClick]);
            
        }
        used=0;
    }
    

}


bool LoadButton::isUsing()
{
    return used;
}

void QuitButton::Input_Draw(State &game)
{
    if (GuiButton(Rectangle{20,20,250,30},"Back to Menu"))
    {
        game.option=0;
    }
}
void GameOver(State &game, bool &isOver, int score[], InsideButton* playagain)
{
    if (game.SaveBoard.size()>=3)
    {
        
        int sz=game.SaveBoard.size()-1;
        if (game.SaveBoard[sz]==game.SaveBoard[sz-1] && game.SaveBoard[sz-1]==game.SaveBoard[sz-2])
        {

            if (!isOver) // first time
            {
                CountScore(game,score[0],score[1]);
                //cout<<score[0]<<' '<<score[1]<<endl;
                MakeSoundEndGame(game);
                isOver=1;
            }
            
            

            if (game.PopUpScale+0.05f<=1.0f)
            {
                game.PopUpScale+=0.05f;
            }
            float lenX=600*game.PopUpScale,lenY=600*game.PopUpScale;
            
            
            DrawRectangle(0,0,1200,800,Color {0,0,0,100});
            DrawTexturePro(
                game.GameOver,
                Rectangle{0,0,(float)game.GameOver.width,(float)game.GameOver.height},
                Rectangle{600-lenX/2,400-lenY/2,lenX,lenY},
                Vector2{0,0},
                0.0f,
                WHITE
            );
            
            if (game.PopUpScale<0.9f) return;
            
            string player1=to_string(score[0]);
            string player2=to_string(score[1]);
            //cout<<score[0]<<' '<<score[1]<<endl;
            if (score[0]==score[1])
            {
                
                DrawTextEx(game.Font,"DRAW!",Vector2{600-130+3,400-220+3},100,5,LIGHTGRAY);
                DrawTextEx(game.Font,"DRAW!",Vector2{600-130,400-220},100,5,BLACK);
            }
            if (score[0]>score[1])
            {
                
                DrawTextEx(game.Font,"BLACK WIN!",Vector2{600-230+3,400-220+3},100,5,LIGHTGRAY);
                DrawTextEx(game.Font,"BLACK WIN!",Vector2{600-230,400-220},100,5,BLACK);
            }
            if (score[0]<score[1])
            {
                
                DrawTextEx(game.Font,"WHITE WIN!",Vector2{600-230+3,400-220+3},100,5,LIGHTGRAY);
                DrawTextEx(game.Font,"WHITE WIN!",Vector2{600-230,400-220},100,5,BLACK);
            }
            //cout<<player1<< ' '<<player2<<endl;
            player1="BLACK: "+player1;
            player2="WHITE: "+player2;
            DrawTextEx(game.Font,player1.c_str(),Vector2{600-230,400-220+200},50,3,BLACK);
            DrawTextEx(game.Font,player2.c_str(),Vector2{600-230,400-220+300},50,3,BLACK);

            playagain->Input(game);
            playagain->Draw(game);
            if (game.SaveBoard.size()==1)
            {
                isOver=0;
                score[0]=score[1]=0;
            }

            
            
            
            

            /*for (Button* a:button)
            {
                
                a->Draw(game);
                a->Input(game);

            }*/




        }
    }
}