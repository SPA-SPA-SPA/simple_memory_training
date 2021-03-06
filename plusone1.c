/*加一训练（记忆多个数值并输入这些数值加1后的值）*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STAGE 10                    // 关卡数
#define LEVEL_MIN 2                     // 最低等级（数值个数）
#define LEVEL_MAX 6                    // 最高等级（数值个数）

/*---等待X秒---*/
int sleep (unsigned long x)
{
    clock_t c1 = clock();
    clock_t c2;
    do{
        if ((c2 = clock()) == (clock_t)(-1)) {
            return 0;
        }
    }while(1000.0 * (c2 - c1) / CLOCKS_PER_SEC < x);
    return 1;
}

int main(int argc, char const *argv[])
{
    int i, stage;
    int level;                              // 等级
    int success;                            // 答对数量
    int score[MAX_STAGE];                   // 所有关卡的答对数量
    clock_t start, end;                     // 开始时钟数，结束时钟数

    srand(time(NULL));                      // 设定随机的种子

    printf("加一训练开始！！\n");
    printf("来记忆2位的数值。\n");
    printf("请输入原数值加1后的值。\n");
    
    do
    {
        printf("要挑战的等级(%d~%d)：", LEVEL_MIN, LEVEL_MAX);
        scanf("%d", &level);
    } while (level < LEVEL_MIN || level > LEVEL_MAX);
    
    success = 0;
    start = clock();
    
    for( stage = 0; stage < MAX_STAGE; stage++)
    {
        int no[LEVEL_MAX];                         // 要记忆的数值
        int x[LEVEL_MAX];                          // 已读取的值
        int seikai = 0;                             // 本关卡的答对数量

        printf("\n第%d关卡开始！！\n", stage + 1);
        printf("Ready...");
        sleep(1000);                              // 给1秒时间让你准备一下
        printf("\r%*s\r", 10, " ");
        
        for( i = 0; i < level; i++)                 // 仅level个
        {
            no[i] = rand() % 90 + 10;               // 生成10~99的随机数
            printf("%d ", no[i]);                    // 显示
        }
        fflush(stdout);
        sleep(300 * level);                         // 等待一段时间
        printf("\r%*s\r", 3 * level, " ");          // 消除题目
        fflush(stdout);
        
        for( i = 0; i < level; i++)                 // 读取答案
        {
            printf("第%d个数：", i + 1);
            scanf("%d", &x[i]);
        }
        
        for( i = 0; i < level; i++)                 // 判断对错并显示
        {
            if(x[i] != no[i] + 1)
                printf("N ");                       // 错误
            else{
                printf("Y ");                       // 正确
                seikai++;
            }
        }
        putchar('\n');
        
        for(i = 0; i < level; i++)                  // 显示正确的答案
            printf("%2d ", no[i] + 1);
        
        printf("...答对了%d个。\n", seikai);
        score[stage] = seikai;                      // 记录关卡的答对数量
        success += seikai;                          // 更新整体的答对数量
    }
    end = clock();

    printf("%d个中答对了%d个。\n", level * MAX_STAGE, success);
    for(stage = 0; stage < MAX_STAGE; stage++)
        printf("第%2d关卡：答对了%d个\n", stage + 1, score[stage]);
    printf("用时%.1f秒。\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
