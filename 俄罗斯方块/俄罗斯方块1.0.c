#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>

#define H 29
#define L 20
int V = 200;
int score =0;

void GameStart(int (*a)[60]);
void Change1(int (*a)[60], int count);
void Change2(int (*a)[60], int count);
void Change3(int (*a)[60]);
void Change4(int (*a)[60], int count);
void Change5(int (*a)[60], int count);
void Show(int (*a)[60]);
void Show2(int (*a)[60]);
void Play(int (*a)[60]);
void Down(int (*a)[60]);
void gotoxy(int x, int y);
void DownFinish(int (*a)[60]);
void Full(int (*a)[60]);

int a[50][60] = {0};

int main()
{
    GameStart(a);
    Play(a);
}
void gotoxy(int x, int y)//位置函数
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void GameStart(int (*a)[60])       //初始化数据
{
    int i, j;
    for(i=0; i<=H; i++)
    {
        for(j=0; j<=L; j++)
        {
            if(i == H || j == L|| j==0)
                a[i][j] = -1;                      //画围墙
            else
                a[i][j] = 0;
        }
    }

    Show(a);
    gotoxy(0, 0);
}
void Change1(int (*a)[60], int count)      //图1T
{
    int i, j;
    for(i=0; i<=H; i++)
    {
        for(j=0; j<=L; j++)
        {
            if(a[i][j] == 2 &&count == 1)   //向上
            {
                a[i+1][j] = 0;

                a[i][j-1] = 3;
                a[i][j+1] = 3;
                a[i-1][j] = 3;
            }

            if(a[i][j] == 2 &&count == 2)
            {
                a[i][j-1] = 0;

                a[i][j+1] = 3;
                a[i+1][j] = 3;
                a[i-1][j] = 3;
            }

            if(a[i][j] == 2 &&count == 3)
            {
                a[i-1][j] = 0;

                a[i][j-1] = 3;
                a[i][j+1] = 3;
                a[i+1][j] = 3;
            }

            if(a[i][j] == 2 &&count == 4)
            {
                a[i][j+1] = 0;

                a[i+1][j] = 3;
                a[i][j-1] = 3;
                a[i-1][j] = 3;
            }
        }
    }
}
void Change2(int (*a)[60], int count)      //图2 横竖
{
    int i, j;
    for(i=0; i<=H; i++)
    {
        for(j=0; j<=L; j++)
        {
            if(a[i][j] == 2 &&count%2!=0)
            {
                a[i-1][j] = 0;
                a[i+1][j] = 0;
                a[i+2][j] = 0;

                a[i][j-1] = 3;
                a[i][j-2] = 3;
                a[i][j+1] = 3;
            }

            if(a[i][j] == 2 &&count%2==0)
            {
                a[i][j-1] = 0;
                a[i][j-2] = 0;
                a[i][j+1] = 0;

                a[i-1][j] = 3;
                a[i+1][j] = 3;
                a[i+2][j] = 3;
            }
        }
    }
}
void Change3(int (*a)[60])      //图3 田
{
    int i, j;
    for(i=0; i<=H; i++)
    {
        for(j=0; j<=L; j++)
        {
            if(a[i][j] == 2)
            {
                a[i-1][j] = 3;
                a[i-1][j+1] = 3;
                a[i][j+1] = 3;
            }
        }
    }
}
void Change4(int (*a)[60], int count)      //图4L
{
    int i, j;
    for(i=0; i<=H; i++)
    {
        for(j=0; j<=L; j++)
        {
            if(a[i][j] == 2 &&count == 1)
            {
                a[i][j+2] = 0;
                a[i-1][j] = 0;

                a[i+1][j] = 3;
                a[i][j+1] = 3;
                a[i+2][j] = 3;
            }

            if(a[i][j] == 2 &&count == 2)
            {
                a[i][j+1] = 0;
                a[i+2][j] = 0;

                a[i][j-1] = 3;
                a[i+1][j] = 3;
                a[i][j-2] = 3;
            }

            if(a[i][j] == 2 &&count == 3)
            {
                a[i+1][j] = 0;
                a[i][j-2] = 0;

                a[i-2][j] = 3;
                a[i][j-1] = 3;
                a[i-1][j] = 3;
            }

            if(a[i][j] == 2 &&count == 4)
            {
                a[i-2][j] = 0;
                a[i][j-1] = 0;

                a[i][j+2] = 3;
                a[i][j+1] = 3;
                a[i-1][j] = 3;
            }
        }
    }
}
void Change5(int (*a)[60], int count)      //图5 折
{
    int i, j;
    for(i=0; i<=H; i++)
    {
        for(j=0; j<=L; j++)
        {
            if(a[i][j] == 2 &&count %2 != 0)
            {
                a[i+1][j] = 0;
                a[i+1][j-1] = 0;

                a[i][j+1] = 3;
                a[i-1][j] = 3;
                a[i+1][j+1] = 3;
            }

            if(a[i][j] == 2 && count %2 == 0)
            {
                a[i-1][j] = 0;
                a[i+1][j+1] = 0;

                a[i][j+1] = 3;
                a[i+1][j] = 3;
                a[i+1][j-1] = 3;
            }
        }
    }
}
void Show(int (*a)[60])
{
    int i, j;
    gotoxy(0, 0);
    system("color 90");
    Sleep(V);
    for(i=0; i<=H; i++)
    {
        for(j=0; j<=L; j++)
        {
            if(a[i][j] == -1)
                printf("* ");
            if(a[i][j] == 0)
                printf("  ");
            if(a[i][j]>0)
               printf("■");
        }
        printf("\n");
    }
    gotoxy(50, 5);
    printf("【回车键】开始游戏及旋转方快");
    gotoxy(50, 7);
    printf("【英文状态下】 【a】左移 【d】右移 【s】加速滑下");
    gotoxy(50, 9);
    printf("你目前得分是%d", score);
}
void Play(int (*a)[60])                //游戏中
{
    char ch;
    int count =0, i, j, op=1, keyR, keyL, k, keyNext=0;
    int key = 1;
    fflush(stdin);
    ch = getch();

    srand(time(NULL));
    op = rand()%5 + 1;
    count = rand()%3 + 1;
    a[3][15] = 2;

    while(1)
    {
        for(i=0; i<=H; i++)      //判断是否落地及游戏结束及是否得分
        {
            for(j=0; j<=L; j++)
            {
                if(i==0)         //结束
                    if(a[i][j] == 10)
                        return ;

                if(a[i][j] == 10 || a[i][j]==-1)
                {
                     if(a[i-1][j]==2 || a[i-1][j]==3) //落定
                    {
                        DownFinish(a);
                        srand(time(NULL));
                        op = rand()%5 + 1;
                        count = rand()%3 + 1;
                        a[3][15] = 2;
                        keyNext = 1;
                    }
                }
            }
        }
        key = 1;
        for(k=1; k<L-1; k++)   //得分
        {
             if(a[H-1][k] != 10)
            {
                key=0;
                break;
            }
        }
        if(key == 1)                                 //消除
        {
            Full(a);
            key=1;
        }
        fflush(stdin);
        if(kbhit())
            ch = getch();
        if(ch == 13 || keyNext == 1)         //转换形状
        {
            count ++;
            switch(op)
            {
            case 1 :
                Change1(a, count);
                if(count == 4)
                {
                    count = 0;
                    keyR = 1;
                }
                else
                    keyR =2;
                if(count == 2)
                    keyL = 1;
                else
                    keyL =2;
                break;
            case 2 :
                Change2(a, count);
                if(count == 4)
                    count = 0;
                if(count%2== 0)
                    keyR = keyL = 1;
                else
                {
                    keyR = 2;  keyL = 3;
                }
                break;
            case 3 :
                Change3(a);
                keyR = 2;  keyL = 1;
                break;
            case 4 :
                Change4(a, count);
                if(count == 1)
                {
                    keyR = 2; keyL = 1;
                }
                if(count == 2)
                {
                    keyR = 1; keyL = 3;
                }
                if(count == 3)
                {
                    keyR = 1; keyL = 2;
                }
                if(count == 4)
                {
                    count = 0;
                    keyR = 3; keyL = 1;
                }

                break;
            case 5 :
                Change5(a, count);
                if(count%2== 0)
                    keyR = keyL = 2;
                else
                {
                    keyR = 2;  keyL = 1;
                }
                if(count == 4)
                    count = 0;
                break;
            }
            keyNext =0;
        }
        else{
            if(ch == 'd')                      //右
            {
                for(i=0; i<=H; i++)
                {
                    for(j=0; j<=L; j++)
                    {
                        if(a[i][j]==2){
                            if(a[i][j+keyR]==0)
                            {
                                for(i=1; i<H; i++)
                                    {
                                        for(j=L-1; j>1; j--)
                                        {
                                            if(a[i][j] !=10 && a[i][j-1] !=10)
                                            {
                                                a[i][j] = a[i][j-1];
                                                a[i][j-1] = 0;
                                            }
                                        }
                                    }
                            }
                            i=H+1;
                            j=L+1;
                        }
                    }
                }
            }
            else{
                if(ch == 'a')                      //左
                {
                    for(i=0; i<=H; i++)
                    {
                        for(j=0; j<=L; j++)
                        {
                            if(a[i][j]==2){
                                if(a[i][j-keyL]==0)
                                {
                                    for(i=1; i<H; i++)
                                    {
                                        for(j=1; j<L-1; j++)
                                        {
                                            if(a[i][j] !=10 && a[i][j+1] !=10)
                                            {
                                                 a[i][j]=a[i][j+1];
                                                 a[i][j+1] = 0;
                                            }
                                        }
                                    }
                                }
                                i=H+1;
                                j=L+1;
                            }
                        }
                    }
                }
                else{
                    if(ch == 's')
                        V-=220;
                    Down(a);
                }
            }
        }
        ch = '0';

        Show(a);
        V=250;
        gotoxy(0, 0);
    }
}
void Down(int (*a)[60])
{
    int i, j;
    for(i=H-1; i>0; i--)
    {
        for(j=1; j<L; j++)
        {
            if(a[i-1][j] !=10 && a[i][j] !=10)
                a[i][j] = a[i-1][j];
        }
    }
}
void DownFinish(int (*a)[60])
{
    int i, j;
    for(i=0; i<=H; i++)
    {
        for(j=0; j<=L; j++)
        {

            if(a[i][j]==2 || a[i][j]==3)
                a[i][j] = 10;
        }
    }
}
void Full(int (*a)[60])
{
    int i, j;
    for(j=1; j<L; j++)
        a[H-1][j] = 0;
    Show(a);

     for(i=H-1; i>0; i--)
        for(j=1; j<L; j++)
            a[i][j] = a[i-1][j];
     Show(a);

     score+=50;
}




