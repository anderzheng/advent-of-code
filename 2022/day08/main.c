#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


#define M_SIZE    99
int map[M_SIZE][M_SIZE] = {0};
int flag[M_SIZE][M_SIZE] = {0};

int dirct[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

int sumVal = 0;

void part1(){
    int i=0, j=0;
    int prevHeight = 0;

    sumVal = (M_SIZE-1) * 4;
    // look from top
    for(i=1; i<M_SIZE-1; i++){
        prevHeight = map[0][i];
        for(j=1; j<M_SIZE-1; j++){
            if (map[j][i] > prevHeight){

                prevHeight = map[j][i];     // set the height
                if (flag[j][i] == 0 ){
                    sumVal ++;
                    flag[j][i] = 1;         // set as visited
                }
                // if height is 9, skip the rest
                if (prevHeight == 9){
                    break;
                }
            }
        }
    }
    // look from bottom
    for(i=1; i<M_SIZE-1; i++){
        prevHeight = map[M_SIZE-1][i];

        for(j=M_SIZE-2; j>0; j--){
            if (map[j][i] > prevHeight){

                prevHeight = map[j][i];     // set the height
                if (flag[j][i] == 0 ){
                    sumVal ++;
                    flag[j][i] = 1;         // set as visited
                }
                // if height is 9, skip the rest
                if (prevHeight == 9){
                    break;
                }
            }
        }
    }
    // look from left
    for(i=1; i<M_SIZE-1; i++){
        prevHeight = map[i][0];

        for(j=1; j<M_SIZE-1; j++){
            if (map[i][j] > prevHeight){
                
                prevHeight = map[i][j];     // set the height
                if (flag[i][j] == 0 ){
                    sumVal ++;
                    flag[i][j] = 1;         // set as visited
                }
                // if height is 9, skip the rest
                if (prevHeight == 9){
                    break;
                }
            }
        }
    }
    // look from right
    for(i=1; i<M_SIZE-1; i++){
        prevHeight = map[i][M_SIZE-1];

        for(j=M_SIZE-2; j>0; j--){
            if (map[i][j] > prevHeight){

                prevHeight = map[i][j];     // set the height
                if (flag[i][j] == 0 ){
                    sumVal ++;
                    flag[i][j] = 1;         // set as visited
                }
                // if height is 9, skip the rest
                if (prevHeight == 9){
                    break;
                }
            }
        }
    }
}


void part2(){
    int i=0, j=0;
    int x=0, y=0;
    int k = 0;
    int cnt = 0;
    int score = 0;

    for(i=1; i<M_SIZE-1; i++){
        for(j=1; j<M_SIZE-1; j++){
            score = 1;
            // calc top
            for(k=0; k<4; k++){
                x = i;
                y = j;
                cnt = 0;
                do{
                    cnt ++;     // visible
                    x += dirct[k][0];
                    y += dirct[k][1];
                }while((x>0 && x<M_SIZE-1 && y>0 && y<M_SIZE-1 ) && map[x][y] < map[i][j]);
                score *= cnt;
            }
            if (score > sumVal){
                sumVal = score;
                //printf("%d, %d : %d\n", i, j, sumVal);
            }
        }
    }
}


void main(int argc, char ** argv){
    FILE * fp = NULL;
    int i = 0, j = 0;
    char buff[104] = {'\0'};

    // open the file
    fp = fopen(argv[1], "r");
    if (NULL == fp){
        printf("Open failed.\n");
        return;
    }

    // read line
    while(fgets(buff, sizeof(buff)-1, fp) != NULL){
        for(j=0; j<M_SIZE; j++){
            map[i][j] = buff[j]-'0';
        }
        i++;
    }

    // part1();
    
    part2();

    printf("result: %d\n", sumVal);

    return;
}
