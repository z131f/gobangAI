#include "ai.h"
#include <graphics.h>
#include <conio.h>
int main()
{
    /*
    int** chessboard = AI_start(BLACK, WHITE);

    //printf("%f",boardscore(chessboard,AIchess));

    printf("%f\n", search_DFS(search_generate(chessboard),1,chessboard,SCOREMAX,-SCOREMAX));
    printf("%d,%d",search_result.x,search_result.y);    //第一个是行数，第二个是列数
    /*
    for(int i = 1;i <= MAX; i++)
    {
        for(int j = 1;j<=MAX;j++)
        {
            printf("i%dj%d,%d ",i,j,chessboard[i][j]);
        }
        printf("\n");
    }
    */
    /*
    printf("%d",chessboard[4][7]);
    */
    initgraph(640, 480);
    circle(320, 240, 100);
    _getch();
    return 0;
}