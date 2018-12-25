#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "All.h"
#define LIE 40         //光标X
#define HANG 8      //光标Y

int LEN=sizeof(account[0]);              //注册结构体的大小
int LENStu=sizeof(StuIfor[0]);           //记录学生信息结构体大小
int LENf=sizeof(feed[0]);                   //反馈条数的结构体大小

int main()
{
    int a;                   //控制注册，登录或者退出
    system("color b0");
    while(1)
    {
        gotoxy(40, 5);                                //开始界面
        printf("注册【0】  登录【1】 退出系统【2】");
        gotoxy(47, 7);
        printf("___________________");
        showLogin();                            //登录界面
        gotoxy(56, 7);
        scanf("%d", &a);
        if(a == 0)
        {
            system("cls");
            gotoxy(0,0);
            Signup();               //前往注册
            a=1;
        }
        if(a==1)
            a=Login(a);         //登录账号
        if(a==2)
        {
            return 0;
        }
    }
}
void gotoxy(int x, int y)       //设置光标
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void Signup()                    //注册账号
{
    int SignupN=0;                 //记录已经注册的人数
    int b=0;                       //检测密码是否正确
    FILE *fp;
    if((fp=fopen("faccount.txt", "ab+")) == NULL)
    {
        printf("不能打开文件\n");
        return;
    }
    while(!feof(fp))
    {
        if(fread(&account[SignupN], LEN, 1, fp)==1)
            SignupN++;
    }

    while(1)
    {
        if(b==1) break;

        ShowSignup();

        fflush(stdin);
        gotoxy(LIE+10, HANG-3);
        scanf("%c", &account[SignupN].Occ);           // 输入身份， 账号与密码。
        gotoxy(LIE+10, HANG+1);
        scanf("%s", account[SignupN].name);
        gotoxy(LIE+10, HANG+5);
        scanf("%s", account[SignupN].passward1);
        gotoxy(LIE+10, HANG+9);
        scanf("%s", account[SignupN].passward2);

        if(strcmp(account[SignupN].passward1, account[SignupN].passward2)!=0)
        {
            b=0;
            gotoxy(LIE, HANG+11);
            printf("两次输入的密码不一致");
        }
        else{
                if(fwrite(&account[SignupN], LEN, 1, fp)!=1)        //写入文件
                {
                    printf("注册失败：不能保存");
                    getch();
                }
                else{
                    b=1;
                    fclose(fp);         //关闭文件

                    system("cls");
                    gotoxy(LIE+5, HANG+8);
                    printf(" 注册账号成功！");
                    gotoxy(LIE+5, HANG+10);
                    printf("【任意键】前往登录");
                    fflush(stdin);
                    getchar();
                    return ;
                }
        }
    }
}
void ShowSignup()             //显示注册界面
{
    gotoxy(LIE+9, HANG-4);
    printf("______________________");
    gotoxy(LIE, HANG-3);
    printf("   你是 ┃                     ┃ 老师(0)/学生(1)");
    gotoxy(LIE+9, HANG-2);
    printf("￣￣￣￣￣￣￣￣￣￣￣");

    gotoxy(LIE+9, HANG);
    printf("______________________");
    gotoxy(LIE, HANG+1);
    printf("用户名  ┃                     ┃");
    gotoxy(LIE+9, HANG+2);
    printf("￣￣￣￣￣￣￣￣￣￣￣");

    gotoxy(LIE+9, HANG+4);
    printf("______________________");
    gotoxy(LIE, HANG+5);
    printf("  密码  ┃                     ┃");
    gotoxy(LIE+9, HANG+6);
    printf("￣￣￣￣￣￣￣￣￣￣￣");

    gotoxy(LIE+9, HANG+8);
    printf("______________________");
    gotoxy(LIE-6, HANG+9);
    printf("再次输入密码  ┃                     ┃");
    gotoxy(LIE+9, HANG+10);
    printf("￣￣￣￣￣￣￣￣￣￣￣");

    gotoxy(LIE+11, HANG+13);
    printf("【回车确认注册】");
}
int Login(int a)                  //登录函数
{
    struct TemLogin        //临时结构体
    {
        char TemOcc;
        char Temname[20];
        char Tempassward[20];
    }temlogin;

    int m=0, i;                       //记录已经注册的人数
    FILE *fp;
    if((fp=fopen("faccount.txt", "ab+"))==NULL)
    {
        printf("不能打开文件");
    }
    while(!feof(fp))
    {
        if(fread(&account[m], LEN, 1, fp)==1)
            m++;
    }
     fclose(fp);

    system("cls");
    showLogin();
    fflush(stdin);
    gotoxy(48, 11);
    scanf("%c", &temlogin.TemOcc);            // 输入身份， 账号，密码
    gotoxy(48, 14);
    scanf("%s", temlogin.Temname);
    gotoxy(48, 17);
    scanf("%s", temlogin.Tempassward);

    int k=0;          //检测是否登录成功
    for(i=0; i<m; i++)
    {
        if(strcmp(temlogin.Temname, account[i].name)==0)
        {
            if(temlogin.TemOcc==account[i].Occ)
            {
                if(strcmp(temlogin.Tempassward, account[i].passward1)==0)
                {
                    k=1;
                    if(temlogin.TemOcc=='1')
                        showStuMenu(i);
                    if(temlogin.TemOcc=='0')
                        showTeaMenu(i);
                    break;
                }
            }
        }
    }
    if(k==0)            //登陆失败
    {
        gotoxy(40, 25);
        printf(" 账号或密码错误！");
        gotoxy(40, 26);
        printf("【y】再次输入   【n】退出系统");
        gotoxy(48, 27);
        printf("__________");
        gotoxy(53, 27);
        char ch=getch();
        if(ch=='y')
            a=1;
        else
            a=2;
    }
    system("cls");
    return a;
}
void showLogin()                //显示登录界面
{
    gotoxy(44, 10);
    printf("   ____________________");
    gotoxy(40, 11);
    printf("你是：┃                   ┃老师(0)/学生(1)");
    gotoxy(44, 12);
    printf("   ￣￣￣￣￣￣￣￣￣￣");
    gotoxy(44, 13);
    printf("   ____________________");
    gotoxy(40, 14);
    printf("账号：┃                   ┃");
    gotoxy(44, 15);
    printf("   ￣￣￣￣￣￣￣￣￣￣");
    gotoxy(44, 16);
    printf("   ____________________");
    gotoxy(40, 17);
    printf("密码：┃                   ┃");
    gotoxy(44, 18);
    printf("   ￣￣￣￣￣￣￣￣￣￣");
    gotoxy(48, 22);
    printf("【回车确认登录】");
}
void showStuMenu(int flag)            //学生功能菜单
{
    while(1)
    {
        system("cls");
        printf("\n\n\n\n");
        printf("\t\t\t\t\t■--------宿--舍--管--理--系--统---------■\n\n\n");
        printf("\t\t\t\t\t学  --------【1】查看学生信息------------\n\n\n");
        printf("\t\t\t\t\t    --------【2】反馈宿舍信息------------\n\n\n");
        printf("\t\t\t\t\t生  --------【3】修改反馈信息------------\n\n\n");
        printf("\t\t\t\t\t    --------【4】修改账号信息------------\n\n\n");
        printf("\t\t\t\t\t端  --------【0】退出登录-----------------\n\n\n");
        printf("\t\t\t\t\t■--------学---------生--------端--------■\n\n\n");

        int c, d;
        gotoxy(LIE+18, HANG*3+1);
        printf("【   】");
        gotoxy(LIE+21, HANG*3+1);
        scanf("%d", &c);

        switch(c)
        {
        case 0:
            return ;
        case 1:
            Lookup();
            break;
        case 2:
            Feed();
            break;
        case 3:
            UpdateCon();
            break;
        case 4:
            d=UpdateAccount(flag);
            if(d==0)
                return ;
        }
    }
}
void showTeaMenu(int flag)            //教师功能菜单
{
    while(1)
    {
        system("cls");
        printf("\n\n\n\n");
        printf("\t\t\t\t\t■--------宿--舍--管--理--系--统---------■\n\n");
        printf("\t\t\t\t\t    --------【1】查看宿舍信息-----------\n\n");
        printf("\t\t\t\t\t老  --------【2】修改学生信息-----------\n\n");
        printf("\t\t\t\t\t    --------【3】增加学生信息-----------\n\n");
        printf("\t\t\t\t\t师  --------【4】删除学生信息-----------\n\n");
        printf("\t\t\t\t\t    --------【5】学生反馈列表-----------\n\n");
        printf("\t\t\t\t\t端  --------【6】修改账号信息-----------\n\n");
        printf("\t\t\t\t\t    --------【0】退出登录----------------\n\n");
        printf("\t\t\t\t\t■--------老---------师--------端--------■\n\n");

        int c;
        gotoxy(LIE+18, HANG*3+1);
        printf("【   】");
        gotoxy(LIE+21, HANG*3+1);
        scanf("%d", &c);
        getchar();

        int d;               //修改账号信息要用
        switch(c)
        {
        case 0:
            return ;
            break;
        case 1 :
            Lookup();
            break;
        case 2 :
            Update();
            break;
        case 3 :
            AddStuIfor();
            break;
        case 4:
            DeleteStu();
            break;
        case 5:
            ShowFeedAllList();
            break;
        case 6:
            d=UpdateAccount(flag);
            if(d==0)
                return ;
        }
    }
}
void AddStuIfor()        //录入学生信息
{
    FILE *fa;
    if((fa=fopen("Student Information.txt", "ab+")) == NULL)
    {
        printf("不能打开文件！");
        return ;
    }

    int Num=0;    //记录已有学生人数
    while(!feof(fa))
    {
        if(fread(&StuIfor[Num], LENStu, 1, fa) == 1)
        {
            Num++;
        }
    }

    system("cls");
    gotoxy(LIE, HANG);
    printf("请输入你要增加的学生的信息：");
    gotoxy(LIE, HANG+2);
    printf("学院：");
    gotoxy(LIE+4, HANG+3);
    printf("￣￣￣￣￣￣￣￣￣￣￣￣");
    gotoxy(LIE, HANG+4);
    printf("学号：");
    gotoxy(LIE+4, HANG+5);
    printf("￣￣￣￣￣￣￣￣￣￣￣￣");
    gotoxy(LIE, HANG+6);
    printf("姓名：");
    gotoxy(LIE+4, HANG+7);
    printf("￣￣￣￣￣￣￣￣￣￣￣￣");
    gotoxy(LIE-2, HANG+8);
    printf("宿舍号：                         (如：6栋316则填”6-316“)");
    gotoxy(LIE+4, HANG+9);
    printf("￣￣￣￣￣￣￣￣￣￣￣￣");
    gotoxy(LIE-4, HANG+10);
    printf("联系电话：");
    gotoxy(LIE+4, HANG+11);
    printf("￣￣￣￣￣￣￣￣￣￣￣￣");

    gotoxy(LIE+6, HANG+2);             //录入学生信息
    scanf("%s", StuIfor[Num].college);
    gotoxy(LIE+6, HANG+4);
    scanf("%s", StuIfor[Num].Id);
    gotoxy(LIE+6, HANG+6);
    scanf("%s", StuIfor[Num].name);
    gotoxy(LIE+6, HANG+8);
    scanf("%s", StuIfor[Num].DorNum);
    gotoxy(LIE+6, HANG+10);
    scanf("%s", StuIfor[Num].PhoneN);

    if(fwrite(&StuIfor[Num], LENStu, 1, fa)!=1)        //写入文件
    {
        printf("录入学生信息失败：不能保存");
        getchar();
    }
    else{
        fclose(fa);
        gotoxy(LIE+6, HANG+12);
        printf("录入学生信息成功！任意键返回。");
        char g;
        g=getch();
    }
}
void Lookup()               //查询学生信息
{
    int Num=0, i, j, FM=0;
    char ch1, TemId[20];
    FILE *fb;
    if((fb=fopen("Student Information.txt", "r")) == NULL)
    {
        printf("不能打开文件！");
    }
    while(!feof(fb))
    {
        if(fread(&StuIfor[Num], LENStu, 1, fb) == 1)
        {
            Num++;
        }
    }
    fclose(fb);

    FILE *fx;
    if((fx=fopen("feedcontext.txt", "ab+")) == NULL)
    {
        printf("不能打开此文件！");
        getchar();
    }
    while(!feof(fx))
    {
        if(fread(&feed[FM], LENf, 1, fx) == 1)
            FM++;
    }
    fclose(fx);

    while(1)
    {
        system("cls");
        gotoxy(LIE, HANG);
        printf("查找方式：________ 【0】按学号/【1】按宿舍号");
        gotoxy(LIE+14, HANG);
        scanf("%c", &ch1);

        char ch2='3';                    //判断有无此人
        if(ch1=='0')                               //按学号查个人信息
        {
            system("cls");
            gotoxy(LIE+9, HANG+2);
            printf("     ______________________");
            gotoxy(LIE, HANG+3);
            printf("输入所查学号 ┃                     ┃");
            gotoxy(LIE+9, HANG+4);
            printf("     ￣￣￣￣￣￣￣￣￣￣￣");
            gotoxy(LIE+15, HANG+3);
            scanf("%s", TemId);

            for(i=0; i<Num; i++)
            {
                if(strcmp(StuIfor[i].Id, TemId) == 0)
                {
                    ShowStu(i);                     //显示个人信息
                    printf("\t\t    学生所在宿舍违规信息：\n");
                    //printf("%s**", StuIfor[i].DorNum);
                    Showfeedcontent(LIE-17, HANG+7, FM, StuIfor[i].DorNum);      //显示宿舍反馈信息
                    gotoxy(0, HANG+17);
                    printf("\t\t■--------------------------所查学生信息如上-------------------------------■\n");
                    printf("\t\t             按【1】继续查询             按【0】退出\n");
                    printf("\t\t                                 【   】");
                    gotoxy(LIE+12, HANG+19);
                    ch2=getch();
                    break;
                }
            }
            if(ch2=='3')
            {
                printf("\n\t\t\t\t\t查无此人！\n\n");
                printf("\t\t\t\t\t【1】继续查询 【0】返回菜单  ");
                ch2=getch();
            }
        }
        if(ch1=='1')                            //按宿舍号查整个宿舍信息
        {
            system("cls");
            gotoxy(LIE+4, HANG-7);
            printf("________________");
            gotoxy(LIE-8, HANG-6);
            printf("所查宿舍号 ┃     x-xxx     ┃ ");
            gotoxy(LIE+3, HANG-5);
            printf(" ￣￣￣￣￣￣￣￣");
            gotoxy(LIE+9, HANG-6);
            scanf("%s", TemId);                   //输入宿舍号

            int a[4]; j=0;
            for(i=0; i<Num; i++)
            {
                if(strcmp(StuIfor[i].DorNum, TemId) == 0)
                {
                    a[j]=i;                                               //找到宿舍有几个人
                    j++;
                }
            }
            if(j==0)
            {
                printf("\n\t\t\t\t找不到此宿舍的信息！\n\n");
                printf("\t\t\t\t【1】继续查询 【0】返回菜单  ");
                ch2=getch();
            }
            else{
                printf("\n■-----------------------------------------------所查宿舍信息如下------------------------------------------------■\n\n");
                for(i=0; i<j; i++)
                    printf("学院：      %-18s", StuIfor[a[i]].college);
                printf("\n\n");
                for(i=0; i<j; i++)
                    printf("学号：      %-18s", StuIfor[a[i]].Id);
                printf("\n\n");
                for(i=0; i<j; i++)
                    printf("姓名：      %-18s", StuIfor[a[i]].name);
                printf("\n\n");
                for(i=0; i<j; i++)
                    printf("联系电话：  %-18s", StuIfor[a[i]].PhoneN);
                printf("\n\n");
                printf("该宿舍被反馈的信息：\n");
                Showfeedcontent(LIE-17, HANG+8, FM, TemId);           //显示宿舍反馈的信息
                gotoxy(0, HANG+18);
                printf("\t\t             按【1】继续查询             按【0】退出\n");
                printf("\t\t                                【   】");

                gotoxy(LIE+11, HANG+19);
                ch2=getch();
            }
        }
        if(ch2=='0')       //结束查询
        {
            break;
        }
    }

}
void  ShowStu(int i)        //显示学生个人信息
{
    system("cls");
    printf("\n");
    printf("\t\t■----------------------------该学生信息如下-----------------------------■\n\n");
    printf("\t\t    学院：%s\n\n", StuIfor[i].college);
    printf("\t\t    学号：%s\n\n", StuIfor[i].Id);
    printf("\t\t    姓名：%s\n\n", StuIfor[i].name);
    printf("\t\t    宿舍号：%s\n\n", StuIfor[i].DorNum);
    printf("\t\t    联系电话：%s\n\n", StuIfor[i].PhoneN);
}
void Update()                  //修改学生信息
{
    int Num=0, i, j=0;
    char Tem[20];
    FILE *fc;
    if((fc=fopen("Student Information.txt", "r+")) == NULL)
    {
        printf("不能打开文件！");
    }
    while(!feof(fc))
    {
        if(fread(&StuIfor[Num], LENStu, 1, fc) == 1)
        Num++;
    }
    fclose(fc);
    system("cls");
    fflush(stdin);
    gotoxy(LIE+17, HANG+2);
    printf("     ______________________");
    gotoxy(LIE, HANG+3);
    printf("输入要修改的学生学号 ┃                     ┃");
    gotoxy(LIE+17, HANG+4);
    printf("     ￣￣￣￣￣￣￣￣￣￣￣");
    gotoxy(LIE+23, HANG+3);
    scanf("%s", Tem);

    char ch='6';            //判断是否有此人及控制修改内容
    for(i=0; i<Num; i++)
    {
        if(strcmp(Tem, StuIfor[i].Id)==0)
        {
            j=i;
            ShowStu(i);
            printf("\t\t■----------------------------该学生信息如上-----------------------------■\n\n");
            printf("\t\t选择你要修改的学生信息：______\n\n");
            printf("\t\t【1】学院  【2】学号  【3】姓名  【4】宿舍号  【5】联系电话  【0】返回菜单\n");
            gotoxy(LIE+2, HANG+7);
            ch=getch();
            printf("%c", ch);
            gotoxy(0, HANG+12);
            printf("\t\t输入修改内容：\n\n\n");
            printf("\t\t￣￣￣￣￣￣￣￣￣￣￣");
            switch(ch)
            {
            case '0':
                return;
            case '1':
                gotoxy(16, HANG+14);
                scanf("%s", StuIfor[i].college);
                break;
            case '2':
                gotoxy(16, HANG+14);
                scanf("%s", StuIfor[i].Id);
                break;
            case '3':
                gotoxy(16, HANG+14);
                scanf("%s", StuIfor[i].name);
                break;
            case '4':
                gotoxy(16, HANG+14);
                scanf("%s", StuIfor[i].DorNum);
                break;
            case '5':
                gotoxy(16, HANG+14);
                scanf("%s", StuIfor[i].PhoneN);
                break;
            }
            break;
        }
    }
    if(ch=='6')
        printf("\n\t\t\t\t\t查无此学号！\n\n");
    else{
        if((fc=fopen("Student Information.txt", "w+")) == NULL)
        {
            printf("不能打开文件！");
            getchar();
        }
        for(i=0; i<Num; i++)
        {
            if(fwrite(&StuIfor[i], LENStu, 1, fc)!=1)        //写入文件
            {
                printf("修改学生信息失败：不能保存");
                getchar();
            }
        }
        fclose(fc);

        gotoxy(0,0);
        ShowStu(j);
        printf("\t\t\t\t\t修改成功！\n");
    }
    printf("\t\t\t\t\t【任意键】返回菜单");
    ch=getch();
    return ;
}
void DeleteStu()               //删除学生信息
{
    int Num=0, i, j;
    char Tem[20];
    FILE *fd;
    if((fd=fopen("Student Information.txt", "r+")) == NULL)
    {
        printf("不能打开文件！");
        getchar();
    }
    while(!feof(fd))
    {
        if(fread(&StuIfor[Num], LENStu, 1, fd) == 1)
        Num++;
    }
    fclose(fd);                         //关闭文件
    system("cls");
    fflush(stdin);
    gotoxy(LIE+17, HANG+2);
    printf("     ______________________");
    gotoxy(LIE, HANG+3);
    printf("输入要删除的学生学号 ┃                     ┃");
    gotoxy(LIE+17, HANG+4);
    printf("     ￣￣￣￣￣￣￣￣￣￣￣");
    gotoxy(LIE+23, HANG+3);
    scanf("%s", Tem);

    char ch='2';            //判断是否有此人及控制修改内容
    for(i=0; i<Num; i++)
    {
        if(strcmp(Tem, StuIfor[i].Id)==0)
        {
            j=i;
            ShowStu(j);
            printf("\t\t■----------------------------该学生信息如上-----------------------------■\n\n");
            printf("\t\t\t\t【0】返回菜单          【1】确认删除\n\n");
            printf("\t\t\t\t\t       【   】");
            gotoxy(LIE+10, HANG+9);
            ch=getch();
            break;
        }
    }

    if(ch=='1')
    {
        if((fd=fopen("Student Information.txt", "w+")) == NULL)
        {
            printf("不能打开文件！");
            getchar();
        }
        for(i=0; i<Num-1; i++)
        {
            if(i>=j)
                StuIfor[i]=StuIfor[i+1];
            if(fwrite(&StuIfor[i], LENStu, 1, fd)!=1)        //写入文件
            {
                printf("修改学生信息失败：不能保存");
                getchar();
            }
        }
        fclose(fd);
        system("cls");
        gotoxy(LIE, HANG);
        printf("删除成功！按【0】返回菜单。");
        ch=getch();
    }
    if(ch=='2')
    {
        gotoxy(LIE+10, HANG+11);
        printf("查无此人！任意键返回菜单");
        ch=getch();
    }
}
int UpdateAccount(int flag)      //修改账户信息
{
    char ch='3' ;//判此次操作是否修改过账号
    while(1)
    {
        int SignupN=0, i;                 //记录已经注册的人数
        FILE *fp;
        if((fp=fopen("faccount.txt", "r+")) == NULL)
        {
            printf("不能打开文件\n");
            getchar();
        }
        while(!feof(fp))
        {
            if(fread(&account[SignupN], LEN, 1, fp)==1)
                SignupN++;
        }
        fclose(fp);

        system("cls");
        gotoxy(LIE, HANG-7);
        if(ch=='1')
            printf("修改成功！");
        gotoxy(LIE, HANG-6);
        printf("%s，你的账户信息如下：", account[flag].name);
        gotoxy(LIE+9, HANG-4);
        printf("______________________");
        gotoxy(LIE, HANG-3);
        printf("   我是 ┃ %c                   ┃ 老师(0)/学生(1)", account[flag].Occ);
        gotoxy(LIE+9, HANG-2);
        printf("￣￣￣￣￣￣￣￣￣￣￣");

        gotoxy(LIE+9, HANG);
        printf("______________________");
        gotoxy(LIE, HANG+1);
        printf("用户名  ┃                     ┃");
        gotoxy(LIE+9, HANG+2);
        printf("￣￣￣￣￣￣￣￣￣￣￣");
        gotoxy(LIE+10, HANG+1);
        printf("%s", account[flag].name);

        gotoxy(LIE+9, HANG+4);
        printf("______________________");
        gotoxy(LIE, HANG+5);
        printf("  密码  ┃                     ┃");
        gotoxy(LIE+10, HANG+5);
        printf("%s", account[flag].passward1);
        gotoxy(LIE+9, HANG+6);
        printf("￣￣￣￣￣￣￣￣￣￣￣\n\n");

         printf("\t\t\t\t\t选择你要修改的学生信息：______\n\n");
         printf("\t\t\t\t\t【1】账户名  【2】密码  【0】返回菜单\n");
         gotoxy(LIE+27, HANG+8);
         ch=getch();

         if(ch=='1')
         {
             gotoxy(0, HANG+12);
             printf("\t\t\t\t\t输入新的账户名：\n\n\n");
             printf("\t\t\t\t\t￣￣￣￣￣￣￣￣￣￣￣");
             gotoxy(LIE+1, HANG+14);
             scanf("%s", account[flag].name);
         }
         if(ch=='2')
         {
             gotoxy(0, HANG+12);
             printf("\t\t\t\t\t输入新密码：\n\n\n");
             printf("\t\t\t\t\t￣￣￣￣￣￣￣￣￣￣￣");
             gotoxy(LIE+1, HANG+14);
             scanf("%s", account[flag].passward1);
             gotoxy(0, HANG+16);
             printf("\t\t\t\t\t再次输入新密码：\n\n\n");
             printf("\t\t\t\t\t￣￣￣￣￣￣￣￣￣￣￣");
             gotoxy(LIE+1, HANG+18);
             scanf("%s", account[flag].passward2);
         }
        if(ch=='0')
            return 1;

        if((fp=fopen("faccount.txt", "w+")) == NULL)
        {
            printf("不能打开文件\n");
            getchar();
        }
        for(i=0; i<SignupN; i++)
        {
          if(fwrite(&account[i], LEN, 1, fp)!=1)
          {
              printf("修改失败！无法写入");
              getchar();
          }
        }
        fclose(fp);

        if(ch=='2')
        {
            system("cls");
            gotoxy(LIE, HANG);
            printf("修改成功！任意键重新登录");
            fflush(stdin);
            ch=getch();
            return 0;
        }
    }

}
void Feed()                            //学生反馈信息
{
    int FM=0;    //反馈信息的条数
    FILE *fx;
    if((fx=fopen("feedcontext.txt", "ab+")) == NULL)
    {
        printf("不能打开此文件！");
        getchar();
    }
    while(!feof(fx))
    {
        if(fread(&feed[FM], LENf, 1, fx) == 1)
            FM++;
    }
    fclose(fx);

    system("cls");
    gotoxy(LIE+8, HANG-5);
    printf("______________________");
    gotoxy(LIE, HANG-4);
    printf("宿舍号:┃                     ┃");
    gotoxy(LIE+8, HANG-3);
    printf("￣￣￣￣￣￣￣￣￣￣￣\n");
    gotoxy(LIE+9, HANG-4);
    scanf("%s", feed[FM].DorNum);          //记录反馈信息的宿舍号
   // printf("%s", feed[FM].DorNum);

    printf("\t信息反馈：\n");
    printf("\t\t    |----------------------------------------------------------------------------------------|\n");
    printf("\t\t    |                                                                                        |\n");
    printf("\t\t    |                                                                                        |\n");
    printf("\t\t    |                                                                                        |\n");
    printf("\t\t    |----------------------------------------------------------------------------------------|\n\n");
    printf("\t\t             按【1】确认反馈             按【0】退出\n");
    printf("\t\t                                【   】");

    gotoxy(LIE-19, HANG-1);
    scanf("%s", feed[FM].content);      //反馈内容
    gotoxy(LIE+11, HANG+5);
    char ch=getch();

    time_t now;                    //反馈的时间
    struct tm *tmNow;
    time(&now);
    tmNow=localtime(&now);
    feed[FM].Y=tmNow->tm_year+1900;
    feed[FM].M=tmNow->tm_mon+1;
    feed[FM].D=tmNow->tm_mday;

    if(ch=='1')
    {
        if((fx=fopen("feedcontext.txt", "ab+")) == NULL)
        {
            printf("不能打开此文件！");
            getchar();
        }
        if(fwrite(&feed[FM], LENf, 1, fx)!=1)
        {
            printf("反馈失败！不能写入。");
            getchar();
        }
        else{
            printf("\n\n\t\t\t\t反馈成功！按任意键返回菜单");
            ch=getch();
        }
        fclose(fx);
    }
    return ;
}
void Showfeedcontent(int x, int y, int n, char *Dor)  //显示宿舍反馈信息
{
    printf("\t\t    |-------------------------------------------------------------------------------|\n");
    printf("\t\t    |                                                                               |\n");
    printf("\t\t    |                                                                               |\n");
    printf("\t\t    |                                                                               |\n");
    printf("\t\t    |                                                                               |\n");
    printf("\t\t    |                                                                               |\n");
    printf("\t\t    |                                                                               |\n");
    printf("\t\t    |                                                                               |\n");
    printf("\t\t    |                                                                               |\n");
    printf("\t\t    |-------------------------------------------------------------------------------|\n\n");

    gotoxy(x-2, y);  int i, j, m, t=1;
    for(j=0; j<n; j++)
    {
        if(strcmp(Dor, feed[j].DorNum) == 0)
        {
            m=strlen(feed[j].content);
            printf("【%d】", t);     t++;            //序号
            for(i=0; i<m; i++)
            {
                printf("%c", feed[j].content[i]);
                if(i==60)
                {
                    printf("\n");
                    gotoxy(x+3, ++y);
                }
            }
            printf("——%d.%d.%d\n", feed[j].Y, feed[j].M, feed[j].D);
            gotoxy(x-2, ++y);
        }
    }
}
void UpdateCon()                    //修改反馈信息
{
    int Num=0;
    char Tem[20];
    FILE *fy;
    if((fy=fopen("feedcontext.txt", "r+")) == NULL)
        printf("不能打开文件！");
    while(!feof(fy))
    {
        if(fread(&feed[Num], LENf, 1, fy) == 1)
        Num++;
    }
    fclose(fy);
    system("cls");
    fflush(stdin);
    gotoxy(LIE+17, HANG-5);
    printf("     ______________________");
    gotoxy(LIE, HANG-4);
    printf("输入修改信息的宿舍号 ┃                     ┃");
    gotoxy(LIE+17, HANG-3);
    printf("     ￣￣￣￣￣￣￣￣￣￣￣");
    gotoxy(LIE+23, HANG-4);
    scanf("%s", Tem);

    int mark[10], i, j=0;              //记录该宿舍的反馈信息在数组中的位置
    for(i=0; i<Num; i++)
    {
        if(strcmp(Tem, feed[i].DorNum) == 0)
        {
            if(j==0)
            {
                printf("\n\t\t该宿舍反馈信息如下：\n\n");
                Showfeedcontent(LIE-16, HANG+1, Num, Tem);
            }
            mark[j]=i;
            j++;
        }
    }

    gotoxy(0, HANG+11);
    printf("\t\t选择要修改的信息序号：_________\n\n\t\t");
    for(i=0; i<j; i++)
        printf("【%d】    ", i+1);
    gotoxy(LIE+2, HANG+11);
    fflush(stdin);
    char ch=getch();

    gotoxy(0, HANG+15);
    printf("\t\t输入修改内容：\n\n\n");
    printf("\t\t￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣");
    gotoxy(LIE-24, HANG+17);
    scanf("%s", feed[mark[ch-'1']].content);

    time_t now;                    //修改的时间
    struct tm *tmNow;
    time(&now);
    tmNow=localtime(&now);
    feed[mark[ch-'1']].Y=tmNow->tm_year+1900;
    feed[mark[ch-'1']].M=tmNow->tm_mon+1;
    feed[mark[ch-'1']].D=tmNow->tm_mday;


    if((fy=fopen("feedcontext.txt", "w+")) == NULL)
    {
        printf("不能打开文件！");
        getchar();
    }
    for(i=0; i<Num; i++)
    {
        if(fwrite(&feed[i], LENf, 1, fy)!=1)        //写入文件
        {
            printf("修改学生信息失败：不能保存");
            getchar();
        }
    }
    fclose(fy);

    gotoxy(LIE, HANG+19);        fflush(stdin);
    printf("修改成功！任意键返回菜单");
    ch=getch();
    return ;
}
void ShowFeedAllList()            //显示所有学生信息
{
    int FM=0;    //反馈信息的条数
    FILE *fz;
    if((fz=fopen("feedcontext.txt", "ab+")) == NULL)
    {
        printf("不能打开此文件！");
        getchar();
    }
    while(!feof(fz))
    {
        if(fread(&feed[FM], LENf, 1, fz) == 1)
            FM++;
    }
    fclose(fz);

    system("cls");
    int i, j, x=23, y=4, c=1;
    printf("\n\t学生反馈的信息如下：");
    for(i=0; i<FM; i++)
    {
        for(j=i-1; j>-1; j--)
        {
            if(strcmp(feed[i].DorNum, feed[j].DorNum) == 0)
            {
                c=0;
                break;
            }
        }
        if(c==1)
        {
            gotoxy(x+33, y-2);
            printf("%s\n", feed[i].DorNum);
            Showfeedcontent(x, y, FM, feed[i].DorNum);
            printf("\n\n\n");
            y+=11;
        }
        c=1;
    }
    printf("\n\n\n\n\n\n\n\n\t\t");
    printf("任意键返回菜单");
    char ch=getch();
    return;
}


