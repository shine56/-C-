#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define _X 35                               //光标x
#define _Y 5                                //光标y

//定义记录结构体
typedef struct AbRecord{
    int Y;                                          //缺课日期,年
    int M;                                         //月
    int D;                                         //日
    char LNum[20];                             //缺课节数
    char LName[50];                            //课程名称
    char StuName[25];                         //学生姓名
    int  Type;                                    //缺课类型：迟到，早退，旷课，请假
    struct AbRecord *next;                   //指向下一个节点的指针
}Record;
int LEN = sizeof(struct AbRecord);         //结构体大小

void AddStu(Record *head);                                                 //录入学生缺课信息
void ChangeStu(Record *head);                                            //修改学生缺课信息
void LookupStu(Record *head);                                            //查找某个学生缺课记录
void DeleteStu(Record *head);                                              //删除某条信息
void CountStuRecord(Record suit[100], int m);                         //统计某段时间旷课的学生
void CountClassRecord(Record suit[100], int m);                       //统计某段时间有学生旷课的课程
void gotoxy(int x, int y);                                                     //设置光标
void ShowRecord(Record *p);                                               //显示记录
Record* Fread();                                                               //将文件信息写进链表
void Fwrite(Record* head);                                                 //将链表写入文件
void SuitTime(Record *head, char ch);                                  //符合条件时间段的记录
int main()
{
    //创建相关文件
    FILE *fp;
    if((fp = fopen("record.txt", "a")) == NULL)
        printf("创建文件失败");
    fclose(fp);

    while(1)
    {
        system("cls");
        system("color F0");
        printf("\n\n\n\n");
        printf("\t\t\t\t\t■------欢-------迎------使------用------■\n\n");
        printf("\t\t\t\t\t    --------【1】录入缺课信息-----------\n\n");
        printf("\t\t\t\t\t    --------【2】修改缺课信息-----------\n\n");
        printf("\t\t\t\t\t    --------【3】查询缺课记录-----------\n\n");
        printf("\t\t\t\t\t    --------【4】删除缺课记录-----------\n\n");
        printf("\t\t\t\t\t    --------【5】学生缺课情况-----------\n\n");
        printf("\t\t\t\t\t    --------【6】课程缺课情况-----------\n\n");
        printf("\t\t\t\t\t    --------【0】退出系统----------------\n\n");
        printf("\t\t\t\t\t■--------考--勤--管--理--系--统---------■\n\n\n");
        printf("\t\t\t\t\t\t\t【   】");

        //获取用户选择
        gotoxy(_X+24, _Y+18);
        fflush(stdin);
        char ch = getch();

        Record *head = Fread();            //获取表头
        switch(ch)
        {
        case '0':
            return 0;
        case '1' :
            AddStu(head);
            break;
        case '2' :
            ChangeStu(head);
            break;
        case '3' :
            LookupStu(head);
            break;
        case '4' :
            DeleteStu(head);
            break;
        case '5':
            SuitTime(head, ch);
            break;
        case '6':
            SuitTime(head, ch);
            break;
        }
    }
    return 0;
}
//设置光标
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);        //获取光标当前位置
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);                                 //设置光标位置
}
//将文件数据写入链表
Record* Fread()
{
    Record *head =NULL, *last, *p;

    FILE *fa;
    if((fa = fopen("record.txt", "r")) == NULL)
        printf("创建文件失败");
    while(!feof(fa))
    {
        if((p = (Record*)malloc(LEN)) == NULL)
            printf("申请内存出错！");

        if(fread(p, LEN, 1, fa) == 1)
        {
            if(head == NULL)
            {
                head = p;
                last = p;
            }
            else{
                last->next = p;
                last = p;
                last->next = NULL;
            }
        }
    }
    fclose(fa);
    return head;
}
//数据存盘
void Fwrite(Record* head)
{
    Record *p;

    FILE *fb;
    if((fb = fopen("record.txt", "w")) == NULL)
        printf("创建文件失败");
    for(p=head; p; p=p->next)
    {
        if(fwrite(p, LEN, 1, fb) != 1)
            printf("写入文件错误！");
    }
    fclose(fb);
}
//录入学生缺课记录
void AddStu(Record *head)
{
    while(1)
    {
        char ch1;                                                        //确认是否继续循环
        system("cls");
        printf("\n\t\t\t\t\t\t录入学生缺课信息");
        printf("\n\n\n\t\t\t\t学生姓名：");
        printf("\n\t\t\t\t\t ￣￣￣￣￣￣￣￣￣￣");
        printf("\n\n\t\t\t\t缺课日期：     年      月      日   ");
        printf("\n\t\t\t\t\t ￣￣￣  ￣￣￣  ￣￣￣");
        printf("\n\n\t\t\t\t缺课节次：                   （如：第七八节）");
        printf("\n\t\t\t\t\t ￣￣￣￣￣￣￣￣￣￣");
        printf("\n\n\t\t\t\t科目名称：                   （如：包装教育）   ");
        printf("\n\t\t\t\t\t ￣￣￣￣￣￣￣￣￣￣");
        printf("\n\n\t\t\t\t缺课类型：    【   】");
        printf("\n\t\t\t\t\t ￣￣￣￣￣￣￣￣￣￣");
        printf("\n\n\t\t\t\t【1】迟到   【2】早退   【3】旷课   【4】请假");
        printf("\n\n\t\t\t\t                  【   】");
        printf("\n\n\t\t\t\t【0】取消录入返回菜单    【其他键】确认录入");

       //************************************输入缺课信息***************************
        Record *p = (Record*)malloc(LEN), *q = head;             //增加一个新节点
        gotoxy(_X+7, _Y-1);  scanf("%s", p->StuName);             //姓名
        gotoxy(_X+7, _Y+2);  scanf("%d", &p->Y);                    //年
        while(1)
        {
            gotoxy(_X+16, _Y+2);  scanf("%d", &p->M);              //月
            if(p->M>0 && p->M<13)
            {
                printf("\t\t\t\t\t\t\t\t\t\t\t                  ");
                break;
            }
            else{
                printf("\t\t\t\t\t\t\t\t\t\t\t月份输入有误！");
                gotoxy(_X+16, _Y+2);  printf("    ");
            }
        }
        while(1)
        {
            gotoxy(_X+24, _Y+2);  scanf("%d", &p->D);               //日
            if(p->D>0 && p->D<32)
            {
                printf("\t\t\t\t\t\t\t\t\t\t\t                  ");
                break;
            }
            else
            {
                printf("\t\t\t\t\t\t\t\t\t\t\t日份输入有误！");
                gotoxy(_X+24, _Y+2);   printf("    ");
            }

        }
        gotoxy(_X+7, _Y+5);  scanf("%s", p->LNum);                //课程节次
        gotoxy(_X+7, _Y+8);  scanf("%s", p->LName);               //课程名称
        while(1)
        {
            gotoxy(_X+14, _Y+11);  char typee = getch();          //选择缺课类型
            gotoxy(_X+14, _Y+11);  printf("%c", typee);
            p->Type = typee - '0';
            if(p->Type>0 && p->Type<5)
                break;
            else
                printf("\n\t\t\t\t选择错误，请重新选择");
        }
        p->next = NULL;

        gotoxy(_X+18, _Y+16); char ch=getch();                 //确认是否录入

        if(ch!='0')
        {
            if(head == NULL)
                head = p;
            else{
                while(q->next)                                             //找到链尾
                {
                    q = q->next;
                }
                q->next = p;
                q=p;                                                        //接上新节点
                q->next = NULL;
            }
                Fwrite(head);
                system("cls");
                ShowRecord(p);
                printf("\n\t\t\t\t信息录入成功........【1】继续录入信息   任意键返回菜单");
                gotoxy(_X+18, _Y+16); ch1 = getch();
        }
        if(ch1 != '1')                                                        //确认是否继续循环
            return;
    }
}
//修改学生缺课记录
void ChangeStu(Record *head)
{
    char ch1;                                           //确认是否修改
    char stuName[25];
    system("cls");
    printf("\n\t\t\t\t\t\t修改学生缺课信息");
    printf("\n\n\t\t\t\t输入学生姓名：");
    printf("\n\t\t\t\t\t     ￣￣￣￣￣￣￣￣￣￣");
    gotoxy(_X+11, _Y-2);     scanf("%s", stuName);

    Record *q;
    int num=0,  count=0;                          //该学生缺课记录有多少条

    for(q=head; q; q=q->next)
        if(strcmp(q->StuName, stuName) == 0)
        {
            num++;
            printf("\n\t\t\t\t******************第%d条******************", num);
            ShowRecord(q);
        }
    if(num>0)
    {
        printf("\n\t\t\t\t输入您要修改该学生缺课条次：");
         char No = getch();
         for(q=head; q; q = q->next)                       //查找目标人名
        {
            if(strcmp(q->StuName, stuName) == 0)
            {
                count++;
                if(count == No-'0')
                {
                    system("cls");
                    printf("\n\t\t\t\t该学生信息如下：");
                    ShowRecord(q);
                    printf("\n\t\t\t\t选择要修改的信息  【   】");
                    printf("\n\n\t【1】学生姓名 【2】缺课日期 【3】缺课节次 【4】科目名称 【5】缺课类型 【0】返回菜单");
                    gotoxy(_X+18, _Y+13); char ch = getch();                                //选择修改的项目
                    gotoxy(_X+18, _Y+13);  printf("%c", ch);

                    //*********************输入修改的信息*********************

                    switch(ch)
                    {
                    case '0':
                        return;
                    case '1' :
                        printf("\n\n\n\n\t\t\t\t输入学生姓名：");
                        printf("\n\t\t\t\t\t    ￣￣￣￣￣￣￣￣￣￣");
                        gotoxy(_X+10, _Y+17);  scanf("%s", q->StuName);
                        break;
                    case '2' :
                        printf("\n\n\n\n\t\t\t\t缺课日期：     年      月      日   ");
                        printf("\n\t\t\t\t\t ￣￣￣  ￣￣￣  ￣￣￣");
                        gotoxy(_X+7, _Y+17);  scanf("%d", &q->Y);
                        gotoxy(_X+15, _Y+17);  scanf("%d", &q->M);
                        gotoxy(_X+23, _Y+17);  scanf("%d", &q->D);
                        break;
                    case '3' :
                        printf("\n\n\n\n\t\t\t\t缺课节次：                   （如：第七八节）");
                        printf("\n\t\t\t\t\t ￣￣￣￣￣￣￣￣￣￣");
                        gotoxy(_X+6, _Y+17);  scanf("%s", q->LNum);
                        break;
                    case '4' :
                        printf("\n\n\n\n\t\t\t\t缺课名称：                   （如：包装教育）   ");
                        printf("\n\t\t\t\t\t ￣￣￣￣￣￣￣￣￣￣");
                        gotoxy(_X+6, _Y+17);  scanf("%s", q->LName);
                        break;
                    case '5' :
                        printf("\n\n\n\n\t\t\t\t缺课类型：    【   】");
                        printf("\n\n\t\t\t\t【1】迟到   【2】早退   【3】旷课   【4】请假");
                        while(1)
                        {
                            gotoxy(_X+14, _Y+17);  char typee = getch();          //选择缺课情况
                            gotoxy(_X+14, _Y+17);  printf("%c", typee);
                            q->Type = typee - '0';
                            if(q->Type>0 && q->Type<5)
                                break;
                            else
                                printf("\n\t\t\t\t选择错误，请重新选择");
                        }
                    }
                    system("cls");
                    printf("\n\n\t\t\t\t修改后信息如下：");
                    ShowRecord(q);
                    printf("\n\n\t\t\t\t【任意键】确认 【0】取消并返回菜单........ ");
                    gotoxy(_X+38, _Y+15);  ch1 = getch();                   //确认修改
                    break;
                }
            }
        }
    }
    else{                                                                            //无该学生的记录
        printf("\n\t\t\t\t\t该学生有%d条缺课记录", num);
        printf("\n\n\t\t\t\t【任意键】并返回菜单........ ");
        getch();
    }

    if(ch1 != '0')
    {
        Fwrite(head);
    }
    return;
}
//显示记录
void ShowRecord(Record *p)
{
    printf("\n\n\n\t\t\t\t学生姓名：%s", p->StuName);
    printf("\n\t\t\t\t\t ￣￣￣￣￣￣￣￣￣￣");
    printf("\n\n\t\t\t\t缺课日期：%d  年  %d  月  %d 日   ", p->Y, p->M, p->D);
    printf("\n\t\t\t\t\t ￣￣￣  ￣￣￣  ￣￣￣");
    printf("\n\n\t\t\t\t缺课节次：%s ", p->LNum);
    printf("\n\t\t\t\t\t ￣￣￣￣￣￣￣￣￣￣");
    printf("\n\n\t\t\t\t缺课名称：%s ", p->LName);
    printf("\n\t\t\t\t\t ￣￣￣￣￣￣￣￣￣￣");
    char *s;
    if(p->Type == 1)
        s = "迟到";
    if(p->Type == 2)
        s = "早退";
    if(p->Type == 3)
        s = "旷课";
    if(p->Type == 4)
        s = "请假";
    printf("\n\n\t\t\t\t缺课类型：%s", s);
    printf("\n\t\t\t\t\t ￣￣￣￣￣￣￣￣￣￣");
    return;
}
//查询学生记录
void LookupStu(Record *head)
{
    while(1)
    {
        char stuName[25];
        system("cls");
        printf("\n\t\t\t\t\t\t查询学生缺课信息");
        printf("\n\n\t\t\t\t输入学生姓名：");
        printf("\n\t\t\t\t\t     ￣￣￣￣￣￣￣￣￣￣");
        gotoxy(_X+11, _Y-2);     scanf("%s", stuName);

        int key =0 ;              //检查有无此人
        Record *q;
        for(q=head; q; q = q->next)                       //查找目标人名
        {
            if(strcmp(q->StuName, stuName) == 0)
            {
                key++;
                printf("\n\t\t\t\t***************************第%d条****************************", key);
                ShowRecord(q);
            }
        }
        printf("\n\t\t\t\t*********************************************************************");
        if(key == 0)
            printf("\n\t\t\t\t找不到此学生缺课记录");
        printf("\n\n\t\t\t\t【任意键】继续查询 【0】返回菜单");
        printf("\n\n\t\t\t\t........");
        char ch = getch();
        if(ch == '0')
            return;
    }
}
//删除学生记录
void DeleteStu(Record *head)
{
    char ch1;                                           //确认是否删除
    char stuName[25];
    system("cls");
    printf("\n\t\t\t\t\t\t修改学生缺课信息");
    printf("\n\n\t\t\t\t输入学生姓名：");
    printf("\n\t\t\t\t\t     ￣￣￣￣￣￣￣￣￣￣");
    gotoxy(_X+11, _Y-2);     scanf("%s", stuName);

    Record *q, *p;
    int num=0,  count=0;                          //该学生缺课记录有多少条

    for(q=head; q; q=q->next)
        if(strcmp(q->StuName, stuName) == 0)
        {
            num++;
            printf("\n\t\t\t\t******************第%d条******************", num);   //找到记录并输出
            ShowRecord(q);
        }
    if(num>0)
    {
        printf("\n\t\t\t\t输入您要修改该学生缺课条次：");
         char No = getch();
         for(q=head; q; q = q->next)                       //查找目标人名
        {
            if(strcmp(q->StuName, stuName) == 0)
            {
                count++;
                if(count == No-'0')                              //找到该节点
                {
                    system("cls");
                    ShowRecord(q);
                    printf("\n\t\t\t\t【0】取消并返回菜单 ,其它键确认删除........");
                    ch1 = getch();
                    if(q == head)                                 //要删除节点在头
                    {
                        printf("*******************头");
                         head = q->next;
                        free(q);
                        break;
                    }
                    if(q->next == NULL)                        //要删除节点在尾
                    {
                        printf("***************尾巴");
                        p->next =NULL;
                        free(q);
                        break;
                    }
                    p->next = q->next;
                    free(q);
                    break;
                }
            }
            p = q;
        }
        if(ch1!='0')
        {
            Fwrite(head);                                               //保存修改后链表到文件
            printf("\n\t\t\t\t删除成功! 任意键返回..........");
            getch();
        }
    }
    else{
        printf("\n\t\t\t\t\t该学生有%d条缺课记录", num);     //没找到要删除的信息
        printf("\n\n\t\t\t\t【任意键】并返回菜单........ ");
        getch();
    }
}
//统计某段时间旷课的学生,
void SuitTime(Record *head, char ch)
{
    //输入查找区间
    int y1, y2, m1, m2, d1, d2;
    system("cls");
    printf("\n请输入查找区间");
    printf("\n\n      年       月     日->");
    printf("\n￣￣￣  ￣￣￣  ￣￣￣");
    printf("\n      年      月      日");
    printf("\n￣￣￣  ￣￣￣  ￣￣￣");
    gotoxy(_X-34, _Y-2);  scanf("%d", &y1);
    gotoxy(_X-24, _Y-2);  scanf("%d", &m1);
    gotoxy(_X-16, _Y-2);  scanf("%d", &d1);
    gotoxy(_X-34, _Y);  scanf("%d", &y2);
    gotoxy(_X-24, _Y);  scanf("%d", &m2);
    gotoxy(_X-16, _Y);  scanf("%d", &d2);

    //查找符合条件的节点并将存好
    Record *p, suit[100];
    int m = 0;
    for(p=head; p; p=p->next)
    {
        if(p->Type == 3)                                          //旷课的学生
        {
            if(p->Y < y1 || p->Y>y2)                           //不符合年份区分
                continue;
            else{
                if( (p->M<m1 && p->Y==y1) || (p->M>y2 && p->Y==y2))     //不符合月份区间
                    continue;
                else{
                    if( (p->M==m1 && p->Y==y1 && p->D<d1)|| (p->M==y2 && p->Y==y2 && p->D>d2))  //同年同月日分不符合
                        continue;
                    else{
                        suit[m].Y=p->Y;  suit[m].M=p->M; suit[m].D=p->D;
                        strcpy(suit[m].StuName, p->StuName);
                        strcpy(suit[m].LName, p->LName);
                        strcpy(suit[m].LNum, p->LNum);
                        suit[m].Type=p->Type;
                        m++;
                       // printf("***%s", suit[0].StuName);
                    }
                }
            }
        }
    }
    if(ch == '5')
        CountStuRecord(suit, m);
    if(ch == '6')
        CountClassRecord(suit, m);
}
//按照学生旷课次数排序
void CountStuRecord(Record suit[100], int m)
{
    int i, j, a[100]={0}, sum;
    for(i=0; i<m; i++)
    {
        sum=1;
        if(suit[i].Type != 0)                                 //未被统计过的名字
        {
            for(j=i+1; j<m; j++)                            //统计名字出现的次数
                if(strcmp(suit[i].StuName, suit[j].StuName) == 0)
                {
                    sum++;
                     suit[j].Type = 0;
                }
            a[i] = sum;
        }
    }
    int t;   Record tt;
    for(i=0; i<m; i++)
    {
        if(a[i]!=0)
        {
            for(j=i+1; j<m; j++)
            {
                if(a[i]<a[j])
                {
                    t = a[i];
                    a[i] = a[j];
                    a[j] = t;

                    tt = suit[i];
                    suit[i] = suit[j];
                    suit[j] = tt;
                }
            }
        }
    }

    gotoxy(0, 0);
    printf("\n\t\t\t\t\t**********************************");
    printf("\n\t\t\t\t\t*  姓名               旷课次数  *");
    printf("\n\t\t\t\t\t**********************************");
    for(i=0; i<m; i++)
    {
        if(a[i]!=0)
        {
            printf("\n\n\t\t\t                   %-15s         %-5d", suit[i].StuName, a[i]);
            printf("\n\t\t\t\t\t**********************************");
        }
    }
    printf("\n\n\t\t\t\t任意键返回菜单..........");
    getch();
}
//按照科目旷课人次排序
void CountClassRecord(Record suit[100], int m)
{
    int i, j, a[100]={0}, sum;
    for(i=0; i<m; i++)
    {
        sum=1;
        if(suit[i].Type != 0)                                 //未被统计过的科目
        {
            for(j=i+1; j<m; j++)                            //统计科目出现的次数
                if(strcmp(suit[i].LName, suit[j].LName) == 0)
                {
                    sum++;
                     suit[j].Type = 0;
                }
            a[i] = sum;
        }
    }
    int t;   Record tt;
    for(i=0; i<m; i++)
    {
        if(a[i]!=0)
        {
            for(j=i+1; j<m; j++)
            {
                if(a[i]<a[j])
                {
                    t = a[i];
                    a[i] = a[j];
                    a[j] = t;

                    tt = suit[i];
                    suit[i] = suit[j];
                    suit[j] = tt;
                }
            }
        }
    }

    gotoxy(0, 0);
    printf("\n\t\t\t\t\t  **********************************");
    printf("\n\t\t\t\t\t  *   科目               旷课人数  *");
    printf("\n\t\t\t\t\t  **********************************");
    for(i=0; i<m; i++)
    {
        if(a[i]!=0)
        {
            printf("\n\n\t\t\t                    %-15s         %-5d", suit[i].LName, a[i]);
            printf("\n\t\t\t\t\t  **********************************");
        }
    }
    printf("\n\n\t\t\t\t\t\t任意键返回菜单..........");
    getch();
}
