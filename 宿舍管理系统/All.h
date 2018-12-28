void showLogin();                         //显示登陆界面
void showStuMenu(int flag);             //显示学生功能菜单
void showTeaMenu(int flag);               //老师功能菜单
void ShowSignup();                        //显示注册界面
void ShowStu(int i);                         //显示学生个人信息
void Showfeedcontent(int x, int y, int n, char *Dor); //查看个人反馈信息
void ShowFeedAllList();                                    //查看所有人反馈信息

void gotoxy(int x, int y);                   //设置光标
void Signup();                               //注册账号  区分老师学生
int Login(int a);                               //登录账号
void AddStuIfor();                            //增加学生信息
void Lookup();                                //查看学生信息
void Update();                                //修改学生信息
void DeleteStu();                             //删除寝室信息
int UpdateAccount(int flag);              //修改个人信息
void Feed();                                   //学生反馈信息
void UpdateCon();                                           //修改反馈信息


struct Account                                               //注册账号的结构体数组
{
    char Occ;                       //身份
    char name[20];                //用户名
    char passward1[20];         //密码
    char passward2[20];        //再次输入密码
}account[100];

struct Infor
{
    char college[25];           //学院
    char Id[20];                 //学号
    char name[10];             //姓名
    char DorNum[10];         //寝室号码
    char PhoneN[20];          //联系电话
}StuIfor[1000];

struct Feed
{
    char DorNum[10];       //宿舍号
    char content[1000];      //反馈内容
    int Y;                        //反馈时间， 年月日
    int M;
    int D;
} feed[1000];

/*想写多一个老师可以删除学生账号， 发现和前面删除学生信息代码内容与思路几乎一样
想想没啥必要， 所以写了一半就不写了*/
/*void DelStuAcc()
{
    char ch='3';
    while(1)
    {
        int SignupN=0, i, j=-1;                 //记录已经注册的人数
        char Temacc[20];
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
        gotoxy(LIE, HANG-8);
        if(ch!='3')
            printf("删除成功！");
        gotoxy(LIE, HANG-7);
        printf("输入要删除学生的用户名：");
        gotoxy(LIE+20, HANG-6);
        printf("￣￣￣￣￣￣￣￣￣")
        gotoxy(LIE+20, HANG-5);
        scanf("%s", Temacc);

        for(i=0; i<SignupN; i++)
        {
            if(strcmp(Temacc, account[i].name)==0)
            {
                j=i;
                break;
            }
        }
        if(j!=1)
        {
            gotoxy(LIE, HANG-3);
            printf("_________")
            gotoxy(LIE, HANG-1);
            printf("【1】确认删除       【0】取消")
        }
    }
}*/


