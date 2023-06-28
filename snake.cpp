#include<iostream>
#include<conio.h>
#include<windows.h>
#include <unistd.h>
#include<fstream>
using namespace std;

const int width=119;
const int height=29;

void Logic();
bool GameOver;
int x,y,fruitX, fruitY, score;
enum eDirection {STOP=0, UP, DOWN, LEFT, RIGHT};
eDirection dir;
int tailX[100], tailY[100], ntail;


void Setup();
void preview (string name)
{
    cout<<"\n            /^\\/^\\                                             ";
    cout<<"\n          _|__|  O|                                              ";
    cout<<"\n \\/     /~     \\_/ \\                                          ";
    cout<<"\n  \\____|__________/  \\                                         ";
    cout<<"\n         \\_______      \\                                       ";
    cout<<"\n                 `\\     \\                 \\                   ";
    cout<<"\n                   |     |                  \\                   ";
    cout<<"\n                  /      /                    \\                 ";
    cout<<"\n                 /     /                       \\\\              ";
    cout<<"\n               /      /                         \\ \\            ";
    cout<<"\n              /     /                            \\  \\          ";
    cout<<"\n            /     /             _----_            \\   \\        ";
    cout<<"\n           /     /           _-~      ~-_         |   |          ";
    cout<<"\n          (      (        _-~    _--_    ~-_     _/   |          ";
    cout<<"\n           \\      ~-____-~    _-~    ~-_    ~-_-~    /          ";
    cout<<"\n             ~-_           _-~          ~-_       _-~    -"<<name;
    cout<<"\n                ~--______-~                ~-___-~               ";
    cout<<"\n Game rules:";
    cout<<"\n1. player should use this notation: "<<endl;
    cout<<"To go up use alphabet 'w"<<endl;
    cout<<"To go down use alphabet 's'"<<endl;
    cout<<"To go left use alphabet 'a'"<<endl;
    cout<<"To go right use alphabet 'd'"<<endl;
    cout<<"2.for eating one fruit (which is just have figure like '*') the user will get 10 points."<<endl;
    cout<<"3.The game will beover in the following cases: \n\t1.if the snake bite itself ,\n\t 2.the snake go out of the palying area, etc."<<endl;
    GameOver=false;
    cout<<"Enter any key to stath the game:"<<endl;
    getch();
    Setup();
}

void Setup(){
    dir=STOP;
    x=width/2;
    y=height/2;
    fruitX=rand()%width;
    fruitY=rand()%height;
}

void Draw(){
    system("cls");
    for(int i=0;i<width;i++)
    {
        cout<<"#";
    }
    cout<<endl;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(j==0||j==width-1)
            {
                cout<<"#";
            }
            else if(i==y&&j==x)
            {
                cout<<"O";
            }
            else if(i==fruitY&&j==fruitX)
            {
                cout<<"*";
            }
            else
            {
                bool print = false;
                for(int k=0;k<ntail;k++)
                {
                    if(i==tailY[k]&&j==tailX[k])
                    {
                        cout<<"O";
                        print=true;
                    }
                }
                if(!print)
                cout<<" ";
            }
        }
        cout<<endl;
    }
    //cout<<endl;
    for(int i=0;i<width;i++)
    {
        cout<<"#";
    }
    cout<<endl;
    //system("cls");
    cout<<endl<<"SCORE:"<<score<<endl;
}

void input(){
    //cout<<"E"<<endl;
    if(_kbhit())
    {
        //cout<<"E"<<endl;
        switch(_getch())
        {
            cout<<"L"<<endl;
            case 'w':
                dir=UP;
                break;
            case 's':
                dir=DOWN;
                //Logic();
                break;
            case 'a':
                dir=LEFT;
                //Logic();
                break;
            case 'd':
                dir=RIGHT;
                //Logic();
                break;
            default:
                break;
        }
    }
}

void Logic(){
    int prevX = tailX[0];
    int prevY=tailY[0];

    tailX[0]=x;
    tailY[0]=y;
    int prev2X, prev2Y;

    for(int i=1; i<ntail;i++)
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }

    switch(dir)
    {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case RIGHT:
            x++;
            break;
        case LEFT:
            x--;
            break;
        default:
            break;
    }
    if(x<0||x>width||y<0||y>height)
    {
        GameOver=true;
    }

    for(int i=0;i<ntail;i++)
    {
        if(x==tailY[i]&&y==tailX[i])
        {
            GameOver=true;
        }
    }
    if(x==fruitX&&y==fruitY)
    {
        score+=10;
        fruitX=rand()%width;
        fruitY=rand()%height;
        ntail++;
    }
}


 int main()
 {
    p:
    system("cls");
    string name;
    cout<<"Enter your name:"<<endl;
    cin>>name;
    preview(name);
    Setup();
    while(!GameOver)
    {
        Draw();
        input();
        Logic();
        usleep(50000);
    }
    fstream file,file1;
    int score1;
    file.open("snake.txt",ios::in);
    if(!file){
        file.open("snake.txt",ios::app|ios::out);
        file<<score<<" ";
        file.close();
    }else
    {
        file>>score1;
        while(file)
        {
            if(score>score1)
            {
                file1.open("snake1.txt", ios::app| ios::out);
                cout<<"Congratulation"<<name<<", you have scored maximum score till now..."<<endl;
                score1=score;
                file1<<score1<<" ";
                file1.close();
                file.close();
                remove("snake.txt");
                rename("snake1.txt", "snake.txt");
                break;
            }
            file>>score1;
        }
        file.close();
    }
    char i;
    cout<<"If you want to play again press any button except 'o'";
    cin>>i;
    if(i=='o')
    exit(0);
    else
    {
        score=0;
        ntail=0;
        goto p;
    }
    return 0;
 }