#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h> 

#define H 30
#define K 59
int V=300;   //默认速度 
int score=0, ko=-6, foodsum=0;   //分数 , ko控制score是n位数画n个空格，  foodsum记录吃到的食物数量 
int a[H][K];

void gamestart(int (*a)[K]);         //游戏初始化 
void show(int (*a)[K]);             // 画面显示 
void gameplay(int (*a)[K]);         // 游戏操作 
void Smove(char move, int (*a)[K]); //蛇的移动 
void gotoxy(int x, int y);           //坐标函数
void food(int (*a)[K]); 			//生成食物 	
void changevelocity();     		//改变速度 
void gameover();               //游戏结束 
void show2(int m);               //速度选择界面 


int main()
{
	
	gamestart(a); 
	changevelocity(); 
	gameplay(a);
	gameover();
	
	return 0;
}
void gotoxy(int x, int y)//位置函数 
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
} 

void gamestart(int (*a)[K]) //初始化开始画面 
{
	int i, j, k;
	for(i=0; i<H-2; i++)
	{
		for(j=0; j<K; j++)
		{
			if(i==0 ||i==H-3 || j==0 || j==K-1 ||j==10)//画边框 
				a[i][j]=-1;
			else
				a[i][j]=0;
		}
	}
	for(i=5; i>0; i--)//画蛇 
	a[15][25-i]=i;
	
	int fx, fy;    //画食物 
	srand(time(NULL));
	do{
		fx=rand()%25 + 2;
		fy=rand()%45 + 14;
	}while(a[fx][fy]!=0); 
	a[fx][fy]=-2;
	
	//画开始文字和分数, -5不画空格 ， -6画1空格 , 0画2空格 
	a[9][2]=-11;
	for(k=3; k<7; k++)
		a[9][k]=-5;
	a[9][7]=-6;
	
	a[11][2]=-9;
	a[12][2]=-8; 
	for(k=3; k<7; k++)
	{
		a[11][k]=-5;  a[12][k]=-5;
	}
	a[11][7]=-6; a[12][7]=-6;
	
	a[24][2]=-10; a[24][3]=-5; a[24][4]=-5; a[24][5]=-6;
	
	show(a);
}

void show(int (*a)[K])//游戏显示 
{
	gotoxy(0, 0);
	int i, j;
	system("color b0");
	for(i=0; i<H-1; i++)           
	{
		for(j=0; j<K; j++)
		{
			if(a[i][j]==0)
				printf("  ");
			if(a[i][j]==-6)
				printf(" ");
			if(a[i][j]==-1)
				printf("■");
			if(a[i][j]>1)
				printf("◆");
			if(a[i][j]==1)
				printf("●");
			if(a[i][j]==-2)
				printf("◆");
			if(a[i][j]==-20)
				printf("■");
			if(a[i][j]==-9)
				printf("[w]上 [s]下");
			if(a[i][j]==-8)
				printf("[a]左 [d]右"); 
			if(a[i][j]==-10)
				printf("得分：%d", score);
			if(a[i][j]==-11)
				printf("[j]选择速度");
		}
		printf("\n");
	}
	//getchar();
}

void gameplay(int (*a)[K])        //游戏中 
{
	char move, move1;
	while(1)
	{
		move=getch();
		if(move=='d' || move=='w' || move=='s')
		break;
	}
	while(1)
	{
		if(a[0][0]==-3)
		break;
		if(kbhit())
		move=getch();
		if(move=='a'&&move1!='d'||move=='d'&&move1!='a'||
		move=='w'&&move1!='s'||move=='s'&&move1!='w')
		{
			move1=move;
			Smove(move1, a);
			show(a);
			Sleep(V);
		}
		if(move=='a'&&move1=='d'||move=='d'&&move1=='a'||
		move=='w'&&move1=='s'||move=='s'&&move1=='w')
		{
			Smove(move1, a);
			show(a);
			Sleep(V);
		}
	}
}

void Smove(char move, int (*a)[K])         //控制蛇上下左右移动 
{
	int i, j, hx, hy, max=0, wx, wy;
	for(i=1; i<H-1; i++)
	{
		for(j=1; j<K-1; j++)
		{
			if(a[i][j]>0)
			{
				a[i][j]++;
				if(a[i][j]>max)
				{
					max=a[i][j];
					wx=i; wy=j;
				} 
				if(a[i][j]==2)
				{
					hx=i; hy=j;
				}
			}	
		}
	}
	int hx1, hy1;
	if(move=='d')//右移
	{
		hx1=hx; hy1=hy+1;
	}
	if(move=='w')//上 
	{
		hx1=hx-1; hy1=hy;
	}
	if(move=='s')//下 
	{
		hx1=hx+1; hy1=hy;
	}
	if(move=='a')//左 
	{
		hx1=hx; hy1=hy-1;
	}
	
	if(a[hx1][hy1]==-2 || a[hx1][hy1]==-20)  //吃到食物 
	{
		if(a[hx1][hy1]==-2)
		{
			foodsum++;
			score+=10;
		} 
		else
			score+=100;
			
		if(score>9 && score<100) a[24][5]=-5;
		if(score>99) a[24][6]=-6; 
		if(score>999) a[24][6]=-5;
		a[hx1][hy1]=0;
		food(a);
	}
	else{
		a[wx][wy]=0;
	}
	if(a[hx1][hy1]>1 || a[hx1][hy1]==-1) //吃自己或撞墙 
	{
		a[0][0]=-3;
	}
	else
	{
		a[hx1][hy1]=1;
	}
}

void food(int (*a)[K])//生成新的食物 
{
	int fx, fy;
	srand(time(NULL));
	do{
		fx=rand()%25 + 2;
		fy=rand()%45 + 14;
	}while(a[fx][fy]!=0);
	//printf("%d %d\n", fx, fy);
	if(foodsum==5)
	{
		foodsum=0;
		a[fx][fy]=-20;
	}
	else
		a[fx][fy]=-2;
} 

void changevelocity()
{
	int m=2;
	char ve, ch;
	ch=getch();
	show2(m);
	if(ch=='j')
	{
		while(1)
		{
			ve=getch();
			if(ve=='=')
			{
				V-=50;
				m++;
				if(V<=350 && V>=0)
				show2(m);
			}
			if(ve=='-')
			{
				V+=50;
				m--;
				if(V<=350 && V>=0)
				show2(m);
			}
			if(ve==13)
			{
				system("cls");
				show(a);
				break;
			}
		}
	}
}

void gameover()
{
	//system("cls");
	gotoxy(50, 12);
	printf("GAME OVER!");
	gotoxy(50, 13);
	printf("你的得分：%d", score);
}

void show2(int m)
{
	int i;
	gotoxy(55, 7);
	printf("【"); 
	for(i=0; i<m; i++)
	{
		printf("■");
	}
	for(i=0; i<(8-m); i++)
		printf("  ");
	printf("】");
	gotoxy(58, 8);
	printf("-   回车确认  +");
	
}
 

