#include <stdio.h>

int part1(char *str, int n){
    int score = 0, i = 0;
    int priority = 0;
    int hSet[53] = {0};

    for (i=0; i<n/2; i++){
        priority = str[i] - 'a' < 0? str[i] - 'A' + 27: str[i] - 'a' + 1;
        hSet[priority] = 1;
    }

    // scan the part 2
    for(; i<n; i++){
        priority = str[i] - 'a' < 0? str[i] - 'A' + 27: str[i] - 'a' + 1;
        if (hSet[priority] != 0){
            score += priority;
            break;
        }
    }
    
    return score;
}

int part2(char (*str)[100], int *len, int n){
    int score = 0, i = 0, j = 0;
    int priority = 0;
    int hSet[53] = {0};


    for(i=0; i<n; i++){
        for (j=0; j<len[i]; j++){
            priority = str[i][j] - 'a' < 0? str[i][j] - 'A' + 27: str[i][j] - 'a' + 1;
            if(hSet[priority] == i){
                // add 1 to flag
                hSet[priority]++;
                if (hSet[priority] == n){
                    // find the letter
                    return priority;
                }
            }
        }
    }    
    return 0;
}


void main(int argc, char ** argv){
    FILE * fp = NULL;
    int i = 0;
    char chA, chB;
    int sumVal = 0, score = 0;
    char buff[100] = {'\0'};
    char grp[3][100] = {'\0'};
    int lens[3] = {0};

    // open the file
    fp = fopen(argv[1], "r");
    if (NULL == fp){
        printf("Open failed.\n");
        return;
    }
    // read line
    while(fgets(buff, sizeof(buff)-1, fp) != NULL){
        // part1
        // score = part1(buff, strlen(buff)-1);

        // part2
        strncpy(grp[i], buff, strlen(buff));
        lens[i] = strlen(buff)-1;
        i = (i+1)%3;
        if (i==0){
            score = part2(grp, lens, 3);
            memset(grp, 0, sizeof(grp));

            printf("score : %d\n", score);
            sumVal += score;
        }
        
        memset(buff, 0, sizeof(buff));
    }

    printf("Sum of score: %d\n", sumVal);

    return;
}
