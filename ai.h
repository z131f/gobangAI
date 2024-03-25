//初始化，定义常量
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//棋盘参数
#define MAX 15
//状态表
#define EMPTY 0
#define BLACK 1
#define WHITE 2
//评分表
#define SCOREMAX 10000000.0f
#define A 500000.0f
#define B 4320.0f
#define C 720.0f
#define D 120.0f
#define E 20.0f
//六个子的棋形
#define num_six 12
const float score_six[num_six] = {B,C,C,C,C,C,C,D,D,D,E,E};
const char name_six[num_six][7] = {"011110","211110","011112","011100","001110","011010","010110","001100","211100","001112","211000","000112"};
//五个子的棋形

#define num_five 3
const float score_five[num_five] = {A,B,E};
const char name_five[num_five][6] = {"11111","11011","00100"};
//搜索相关
const int MAXlayer = 5; //设置成奇数层使落在MAX
typedef struct location location;
typedef struct location  //用一个特定函数生成含可落子点的坐标的链表，返回头，每用一个释放一个
{
    int x;
    int y;
    float score;  //这个位置的分数
    location* next;
}location;
//变量
int c[MAX+2][MAX+2] =    //第一个是行数，第二个是列数   //这个是用来调试的棋盘复制
        {
                {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},

                {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
                {0,    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0    ,0},
                {0,    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0    ,0},
                {0,    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0    ,0},
                {0,    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0    ,0},
                {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
                {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
                {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
                {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
                {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
                {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
                {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
                {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
                {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
                {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},

                {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
        };
/*
int chessboard[MAX+2][MAX+2] =    //第一个是行数，第二个是列数
{
    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},

    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},

    {0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0    ,0},
};
*/
int AIchess = 0;
int HUchess = 0;
//初始化函数
int** AI_start(int AI, int HU)
{
    int** chessboard = (int**)malloc((MAX+2) * sizeof(int*));
    for (int i = 0; i < MAX+2; i++)
    {
        chessboard[i] = (int*)malloc((MAX+2) * sizeof(int));
    }
    for(int i = 0; i < MAX+2; i++)
    {
        for(int j = 0; j < MAX+2; j++)
        {
            chessboard[i][j] = c[i][j];
        }
    }
    AIchess = AI;
    HUchess = HU;
    return chessboard;
}

float max(float num1, float num2)
{
    return num1 > num2 ? num1 : num2;
}

float min(float num1, float num2)
{
    return num1 < num2 ? num1 : num2;
}

//引入 boardscore和score_location，这两个都只能判断一方，需要相减
//整个过程不涉及棋盘的更改
//---------------------------------------------------------------------------------------------------------
//以下几个函数用来计算局面分数
float boardscore_compare(const char* search, int chess_num)
{
    if(chess_num == 5)
    {
        for(int i = 0; i < num_five; i++)
        {
            if(strcmp(search, name_five[i]) == 0)
            {
                return score_five[i];
            }
        }
    }
    else if(chess_num == 6)
    {
        for(int i = 0; i < num_six; i++)
        {
            if(strcmp(search, name_six[i]) == 0)
            {
                return score_six[i];
            }
        }
    }
    return 0;
}
//j表示长度-1
void boardscore_upadte(int** chessboard,float *score,const int i,const int j,const int len,const int player,char* process,char* process2,char* search_five,char* search_six)
{
    if(j <= 0 || j >= MAX + 1 || i <= 0 || i >= MAX+1)
    {
        strcpy(process, "2");
    }
    else
    {
        strcpy(process, chessboard[i][j] == player ? "1" : chessboard[i][j] == EMPTY ? "0" : "2");
    }
    if(len < 6)
    {
        if(len < 5)
        {
            strcat(search_five, process);
            if(len == 4)
            {
                *score += boardscore_compare(search_five, 5);
            }
            strcat(search_six, process);
        }
        else
        {
            strncpy(process2, search_five + 1, 5);
            strcpy(search_five, process2);
            strcat(search_five, process);
            *score += boardscore_compare(search_five, 5);
            strcat(search_six, process);
            *score += boardscore_compare(search_six, 6);
        }
    }
    else
    {
        //5的处理
        strncpy(process2, search_five + 1, 5);
        strcpy(search_five, process2);
        strcat(search_five, process);
        *score += boardscore_compare(search_five, 5);
        //6的处理
        strncpy(process2, search_six + 1, 6);
        strcpy(search_six, process2);
        strcat(search_six, process);
        *score += boardscore_compare(search_six, 6);
    }
}
//与棋子个数为5的棋形比较，没有则返回0
//这个函数只负责根据传入的执棋人计算分数，不相减
float boardscore(int** chessboard,int player)
{
    float score = 0;
    char search_five[6] = "";
    char search_six[7] = "";
    // 行搜索
    memset(search_five, 0, sizeof(search_five));
    memset(search_six, 0, sizeof(search_six));
    for(int i = 1; i <= MAX; i++)
    {
        for(int j = 0; j <= MAX+1; j++)
        {
            char process[2];  //表示棋子
            char process2[7];  //存储前几个字符
            memset(process, 0, sizeof(process));
            memset(process2, 0, sizeof(process2));
            boardscore_upadte(chessboard,&score,i,j,(int)strlen(search_six),player,process,process2,search_five,search_six);
        }
        memset(search_five, 0, sizeof(search_five));
        memset(search_six, 0, sizeof(search_six));
    }
    // 列搜索
    memset(search_five, 0, sizeof(search_five));
    memset(search_six, 0, sizeof(search_six));
    for(int i = 1; i <= MAX; i++)
    {
        for(int j = 0; j <= MAX+1; j++)
        {
            char process[2] = "";   //表示棋子
            char process2[6] = "";  //存储前几个字符
            boardscore_upadte(chessboard,&score,j,i,(int)strlen(search_six),player,process,process2,search_five,search_six);
        }
        memset(search_five, 0, sizeof(search_five));
        memset(search_six, 0, sizeof(search_six));
    }
    // /搜索
    char search_five2[6] = "";
    char search_six2[7] = "";
    memset(search_five, 0, sizeof(search_five));
    memset(search_six, 0, sizeof(search_six));
    for(int i = 4; i < MAX; i++)
    {
        int x = i+1;
        int y = 1-1;
        for(int j = 1; j <= i+2; j++)
        {
            char process[2] = "";   //表示棋子
            char process2[6] = "";  //存储前几个字符
            boardscore_upadte(chessboard,&score,x,y,(int)strlen(search_six),player,process,process2,search_five,search_six);
            memset(process, 0, sizeof(process));
            memset(process2, 0, sizeof(process2));
            boardscore_upadte(chessboard,&score,MAX+1-x,MAX+1-y,(int)strlen(search_six2),player,process,process2,search_five2,search_six2);
            x--;
            y++;
        }
        memset(search_five, 0, sizeof(search_five));
        memset(search_six, 0, sizeof(search_six));
        memset(search_five2, 0, sizeof(search_five2));
        memset(search_six2, 0, sizeof(search_six2));
    }
    int xx = MAX+1;
    int yy = MAX+1;
    memset(search_five, 0, sizeof(search_five));
    memset(search_six, 0, sizeof(search_six));
    for(int j = 1; j <= MAX+2; j++)
    {
        char process[2] = "";   //表示棋子
        char process2[6] = "";  //存储前几个字符
        boardscore_upadte(chessboard,&score,xx,yy,(int)strlen(search_six),player,process,process2,search_five,search_six);
        memset(process, 0, sizeof(process));
        memset(process2, 0, sizeof(process2));
        xx--;
        yy++;
    }
    // \搜索
    memset(search_five2, 0, sizeof(search_five2));
    memset(search_six2, 0, sizeof(search_six2));
    memset(search_five, 0, sizeof(search_five));
    memset(search_six, 0, sizeof(search_six));
    for(int i = MAX + 1 - 4; i > 1; i--)
    {
        int x = i-1;
        int y = 1-1;
        for(int j = 1; j <= MAX-i+3; j++)
        {
            char process[2] = "";   //表示棋子
            char process2[6] = "";  //存储前几个字符
            boardscore_upadte(chessboard,&score,x,y,(int)strlen(search_six),player,process,process2,search_five,search_six);
            memset(process, 0, sizeof(process));
            memset(process2, 0, sizeof(process2));
            boardscore_upadte(chessboard,&score,MAX-x+1,MAX+1-y,(int)strlen(search_six2),player,process,process2,search_five2,search_six2);
            x++;
            y++;
        }
        memset(search_five, 0, sizeof(search_five));
        memset(search_six, 0, sizeof(search_six));
        memset(search_five2, 0, sizeof(search_five2));
        memset(search_six2, 0, sizeof(search_six2));
    }
    xx = 0;
    yy = 0;
    memset(search_five, 0, sizeof(search_five));
    memset(search_six, 0, sizeof(search_six));
    for(int j = 1; j <= MAX+2; j++)
    {
        char process[2] = "";   //表示棋子
        char process2[6] = "";  //存储前几个字符
        boardscore_upadte(chessboard,&score,xx,yy,(int)strlen(search_six),player,process,process2,search_five,search_six);
        memset(process, 0, sizeof(process));
        memset(process2, 0, sizeof(process2));
        xx++;
        yy++;
    }
    return score;
}
float score_location(int** board,int x,int y,int player)
{
    float score = 0;
    char search_five[6] = "";
    char search_six[7] = "";
    memset(search_five, 0, sizeof(search_five));
    memset(search_six, 0, sizeof(search_six));
    for(int i = x-5; i <= x+5; i++)
    {
        char process[2];  //表示棋子
        char process2[7];  //存储前几个字符
        memset(process, 0, sizeof(process));
        memset(process2, 0, sizeof(process2));
        boardscore_upadte(board,&score,i,y,(int)strlen(search_six),player,process,process2,search_five,search_six);
    }
    memset(search_five, 0, sizeof(search_five));
    memset(search_six, 0, sizeof(search_six));
    for(int i = y-5; i <= y+5; i++)
    {
        char process[2];  //表示棋子
        char process2[7];  //存储前几个字符
        memset(process, 0, sizeof(process));
        memset(process2, 0, sizeof(process2));
        boardscore_upadte(board,&score,x,i,(int)strlen(search_six),player,process,process2,search_five,search_six);
    }
    memset(search_five, 0, sizeof(search_five));
    memset(search_six, 0, sizeof(search_six));
    for(int i = -5; i <= 5; i++)
    {
        char process[2];  //表示棋子
        char process2[7];  //存储前几个字符
        memset(process, 0, sizeof(process));
        memset(process2, 0, sizeof(process2));
        boardscore_upadte(board,&score,x+i,y+i,(int)strlen(search_six),player,process,process2,search_five,search_six);
    }
    memset(search_five, 0, sizeof(search_five));
    memset(search_six, 0, sizeof(search_six));
    for(int i = -5; i <= 5; i++)
    {
        char process[2];  //表示棋子
        char process2[7];  //存储前几个字符
        memset(process, 0, sizeof(process));
        memset(process2, 0, sizeof(process2));
        boardscore_upadte(board,&score,x+i,y-i,(int)strlen(search_six),player,process,process2,search_five,search_six);
    }
    return score;
}
//---------------------------------------------------------------------------------------------------------
//极大极小搜索相关函数
location* search_generate(int** board)
{
    float pointnum = 0;
    float pointmax = -SCOREMAX;
    float pointmin = SCOREMAX;
    location* start = (location*)malloc(sizeof(location));
    location* now = start;
    start->next = NULL;
    start->x = -1;  //有一个头
    start->y = -1;
    for(int i = 1; i <= MAX; i++)
    {
        for(int j = 1; j <= MAX; j++)
        {
            if(board[i][j] == EMPTY)
            {
                //测试用
/*
                if(!(i<=2))
                continue;

                if(!(j<=9&&j>=7))
                continue;
*/
                ///////////////
                location* next = (location*)malloc(sizeof(location));
                now->next = next;
                next->x = i;
                next->y = j;
                next->score = score_location(board,i,j,AIchess)-score_location(board,i,j,HUchess);
                now = next;
                now->next = NULL;
                pointnum++;
                pointmax = max(pointmax,now->score);
                pointmin = min(pointmin,now->score);
            }
        }
    }
    float limit;
    if(pointnum > 7)
    {
        if(pointnum < 30)
        {
            limit = pointmin + (pointmax - pointmin) * 0.5f;
        }
        else if(pointnum < 70)
        {
            limit = pointmin + (pointmax - pointmin) * 0.6f;
        }
        else if(pointnum < 120)
        {
            limit = pointmin + (pointmax - pointmin) * 0.7f;
        }
        else
        {
            limit = pointmin + (pointmax - pointmin) * 0.8f;
        }
    }
    now = start->next != NULL ? start->next : NULL;
    if(now != NULL)
    {
        location* last = start;
        while(now->next != NULL)
        {
            if(now->score < limit)
            {
                last->next = now->next;
                free(now);
                now = last->next;
            }
            else
            {
                last = now;
                now = now->next;
            }
        }
    }
    return start;
}
int** search_copy(int** from)
{
    int** to = (int**)malloc((MAX+2) * sizeof(int*));
    for (int i = 0; i < MAX+2; i++)
    {
        to[i] = (int*)malloc((MAX+2) * sizeof(int));
    }
    for(int i = 0; i < MAX+2; i++)
    {
        for(int j = 0; j < MAX+2; j++)
        {
            to[i][j] = from[i][j];
        }
    }
    return to;
}
void search_freeboard(int** mfree)   //模仿申请空间的方式释放空间，待实现
{
    for (int i = 0; i < MAX+2; i++)
    {
        free(mfree[i]);
    }
    free(mfree);
}
location search_result;
float search_DFS(location* now,int layer, int** board,float lastmax,float lastmin)
{
    if(layer == MAXlayer)   //传入的是最大奇数，MAX层
    {
        float maxnum = -SCOREMAX;
        while(now->next != NULL)
        {
            if(now->x == -1 && now->y == -1)
            {
                now = now->next;
                continue;
            }
            int** newboard = search_copy(board);
            newboard[now->x][now->y] = AIchess;

/*
            for (int i = 1;i<=MAX; i++)
                        {
                            for(int j = 1;j<=MAX;j++)
                            {
                                printf("%d ",newboard[i][j]);
                            }
                            printf("\n");
                        }
*/
            maxnum = max(maxnum, boardscore(newboard, AIchess)-boardscore(newboard,HUchess));
            //printf("%f \n",maxnum);
            if(maxnum >= lastmin){
                return maxnum;
            }
            search_freeboard(newboard);
            location* freelocation = now;
            now = now->next;
            free(freelocation);
        }
        int** newboard = search_copy(board);
        newboard[now->x][now->y] = AIchess;
        maxnum = max(maxnum, boardscore(newboard, AIchess)-boardscore(newboard,HUchess));
        search_freeboard(newboard);
        free(now);
        return maxnum * (1.0f - (float)layer * 0.03f);
    }
    else
    {
        if(layer%2 == 0)    //偶数，MIN层
        {
            float minnum = SCOREMAX;
            while(now->next != NULL)
            {
                if(now->x == -1 && now->y == -1)
                {
                    now = now->next;
                    continue;
                }
                int** newboard = search_copy(board);
                newboard[now->x][now->y] = HUchess;
                minnum = min(minnum, search_DFS(search_generate(newboard),layer+1,newboard,lastmax,minnum));
                if(minnum <= lastmax){
                    return minnum;
                }
                search_freeboard(newboard);
                location* freelocation = now;
                now = now->next;
                free(freelocation);
            }
            int** newboard = search_copy(board);
            newboard[now->x][now->y] = HUchess;
            minnum = min(minnum, search_DFS(search_generate(newboard),layer+1,newboard,lastmax,minnum));
            search_freeboard(newboard);
            free(now);
            return minnum;
        }
        else    //奇数，MAX层
        {
            float maxnum = -SCOREMAX;
            while(now->next != NULL)
            {
                if(now->x == -1 && now->y == -1)
                {
                    now = now->next;
                    continue;
                }
                int** newboard = search_copy(board);
                newboard[now->x][now->y] = AIchess;
                if(layer == 1)
                {
                    float searchscore = search_DFS(search_generate(newboard),layer+1,newboard,lastmax,lastmin);
                    if(maxnum < searchscore)
                    {
                        /*
                        for (int i = 1;i<=MAX; i++)
                        {
                            for(int j = 1;j<=MAX;j++)
                            {
                                printf("%d ",newboard[i][j]);
                            }
                            printf("\n");
                        }
                        printf("%d \n\n\n\n",searchscore);
                        */
                        search_result.x = now->x;
                        search_result.y = now->y;
                        maxnum = searchscore;
                    }
                }
                else
                {
                    maxnum = max(maxnum, search_DFS(search_generate(newboard),layer+1,newboard,maxnum,lastmin));
                    if(maxnum >= lastmin){
                        return maxnum;
                    }
                }
                search_freeboard(newboard);
                location* freelocation = now;
                now = now->next;
                free(freelocation);
            }
            int** newboard = search_copy(board);
            newboard[now->x][now->y] = AIchess;
            if(layer == 1)
            {
                float searchscore = search_DFS(search_generate(newboard),layer+1,newboard,lastmax,lastmin);
                if(maxnum < searchscore)
                {
                    search_result.x = now->x;
                    search_result.y = now->y;
                    maxnum = searchscore;
                }
            }
            else
            {
                maxnum = max(maxnum, search_DFS(search_generate(newboard),layer+1,newboard,maxnum,lastmin));
            }
            search_freeboard(newboard);
            free(now);
            return maxnum*(1.0f - (float)layer * 0.03f);
        }
    }
}
