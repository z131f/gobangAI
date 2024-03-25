#include "ai.h"
#include <graphics.h>
#include <conio.h>

const int gui_length = 30;

void gui_drawwindow()
{
    cleardevice();
    setlinecolor(BLUE);
    for(int i = 1; i <= MAX; i++)
    {
        line(gui_length*i,gui_length,gui_length*i,gui_length*MAX);
    }
    for(int i = 1; i <= MAX; i++)
    {
        line(gui_length,gui_length*i,gui_length*MAX,gui_length*i);
    }
}

void gui_drawchess(int x, int y, int player)
{
    setfillcolor(player == AIchess ? BLACK : WHITE);
    solidcircle(x*gui_length,y*gui_length,gui_length/2-2);
}

int main()
{

    int** chessboard = AI_start(AIBLACK, AIWHITE);

    //printf("%f",boardscore(chessboard,AIchess));

    //printf("%f\n", search_DFS(search_generate(chessboard),1,chessboard,SCOREMAX,-SCOREMAX));
    //printf("%d,%d",search_result.x,search_result.y);    //第一个是行数，第二个是列数
/*
    while(1) {
        printf("\n");
        for (int i = 1; i <= MAX; i++) {
            for (int j = 1; j <= MAX; j++) {
                printf("%d ", chessboard[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        int x, y;
        scanf("%d,%d", &x, &y);
        chessboard[x][y] = HUchess;
        search_DFS(search_generate(chessboard), 1, chessboard, -SCOREMAX, SCOREMAX);
        chessboard[search_result.x][search_result.y] = AIchess;
    }

    getchar();
    /*
    printf("%d",chessboard[4][7]);
    */

    initgraph(gui_length*(MAX+1), gui_length*(MAX+1));
    setbkcolor(GREEN);
    MOUSEMSG m;
    gui_drawwindow();

    chessboard[MAX/2][MAX/2] = AIchess;
    gui_drawchess(MAX/2,MAX/2,AIchess);

    while(1)    //loop
    {
        m = GetMouseMsg();
        if(m.uMsg == WM_LBUTTONDOWN)
        {
            int isfind = 0;
            for(int i = 1; i <= MAX; i++) {
                for (int j = 1; j <= MAX; j++) {
                    if (abs(j * gui_length - m.y) < 10 && abs(i * gui_length - m.x) < 10) {
                        printf("\n??%d??\n",chessboard[j][i]);
                        if(chessboard[j][i] == EMPTY)
                        {
                            gui_drawchess(i, j, HUchess);
                            chessboard[j][i] = HUchess;
                            printf("%d,%d\n",j,i);
                            search_DFS(search_generate(chessboard),1,chessboard,-SCOREMAX,SCOREMAX);
                            printf("ai:%d,%d\n",search_result.x,search_result.y);
                            chessboard[search_result.x][search_result.y] = AIchess;
                            gui_drawchess(search_result.y,search_result.x,AIchess);
                            isfind = 1;


                            printf("\n");
                            for (int i = 1; i <= MAX; i++) {
                                for (int j = 1; j <= MAX; j++) {
                                    printf("%d ", chessboard[i][j]);
                                }
                                printf("\n");
                            }
                            printf("\n");



                            break;
                        }
                    }
                }
                if(isfind == 1)
                {
                    break;
                }
            }
        }
    }
    return 0;

}
