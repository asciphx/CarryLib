#include"graphics.h"
#include<conio.h>
#include<time.h>
#include<windows.h>
// #pragma comment( linker, "/subsystem:windows /entry:WinMainCRTStartup")
#pragma comment( linker, "/subsystem:console /entry:mainCRTStartup" )
#define MAX 1000
#define SIZE 20
struct COOR
{
  int x;int y;
};
enum CH
{
  up=72,down=80,left=75,right=77
};
struct SNAKE
{
  int n;COOR scr[MAX];CH ch;

}snake;
struct FOOD
{
  COOR fcr;int flag;
}food;
void initGame(){
  initgraph(640,480);snake.n=1;
  snake.scr[0].x=0;snake.scr[0].y=0;
  snake.ch=right;
  food.flag=0;
}
void SnakePaint(){
  fillrectangle(snake.scr[0].x,snake.scr[0].y,snake.scr[0].x+SIZE,snake.scr[0].y+SIZE);
  for(int i=snake.n-1;i>0;--i){
    fillrectangle(snake.scr[i].x,snake.scr[i].y,snake.scr[i].x+SIZE,snake.scr[i].y+SIZE);
  }
}
void SnakeMove(){
  for(int i=snake.n-1;i>0;--i){
    snake.scr[i].x=snake.scr[i-1].x;
    snake.scr[i].y=snake.scr[i-1].y;
  }
  switch(snake.ch){
    case up:snake.scr[0].y-=SIZE;break;
    case down:snake.scr[0].y+=SIZE;break;
    case left:snake.scr[0].x-=SIZE;break;
    case right:snake.scr[0].x+=SIZE;break;
    default:break;
  }
}
void ChangeSnakeCh(){
  switch (getch()){
  case 72:if(snake.ch!=down)snake.ch=up;
    break;
  case 80:if(snake.ch!=up)snake.ch=down;
    break;
  case 75:if(snake.ch!=right)snake.ch=left;
    break;
  case 77:if(snake.ch!=left)snake.ch=right;
    break;
  default:break;
  }
}
void FoodCoor(){
  srand((unsigned)time(NULL));
  food.fcr.x=rand()%32*SIZE;//0-640
  food.fcr.y=rand()%24*SIZE;//0-480
  food.flag=1;
}
void FoodPaint(){
  setlinecolor(BLUE);
  roundrect(food.fcr.x,food.fcr.y,food.fcr.x+SIZE,food.fcr.y+SIZE,10,10);//绘制圆角矩形
}
void EatFood(){
  if(snake.scr[0].x==food.fcr.x&&snake.scr[0].y==food.fcr.y)
  {
    snake.n++;food.flag=0;
  }
}
void judge(){
  cleardevice();
  settextcolor(LIGHTMAGENTA);
  outtextxy(300,200,"game over");
  settextstyle(50,0,"黑体");
  Sleep(3000);exit(0);
}
void GameOver(){
  if(snake.scr[0].x<0||snake.scr[0].x>620||snake.scr[0].y<0||snake.scr[0].y>460)
  {
    judge();
  }
  for(int i=snake.n-1;i>0;i--){
    if(snake.scr[0].x==snake.scr[i].x&&snake.scr[0].y==snake.scr[i].y){
      judge();
    }
  }
}
int main(){
  initGame();
  while(1){
		while(!kbhit()){
      if(food.flag==0)FoodCoor();
      cleardevice();
      GameOver();
      FoodPaint();
      SnakeMove();
      SnakePaint();
      Sleep(210);
      EatFood();
    }
    ChangeSnakeCh();
  };

  return 0;
}
// int APIENTRY WinMain(HINSTANCE hInstance,
// HINSTANCE hPrevInstance,
// LPSTR     lpCmdLine,
// int       nCmdShow)
// {
// }