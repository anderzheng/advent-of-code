#include <stdio.h>

int part1(char a, char b){
    int score = 0;
    int valA = a - 'A';
    int valB = b - 'X';

    if (valA == valB){
        score = 3 + valB + 1;
    } else if((valA + 1)%3 == valB){
        // B win
        score = 6 + valB + 1;
    } else {
        // B loss
        score = valB + 1;
    }

    return score;
}

int part2(char a, char b){
    int score = 0;
    int val = a-'A';
    if (b == 'X'){
        // loss, B should be (a+2)%3
        score = (val+2)%3 +1;
    } else if(b == 'Y') {
        // draw
        score = val +1 +3;
    } else {
        // win
        score = (val+1)%3 +1 + 6;
    }

    return score;
}


void main(int argc, char ** argv){
    FILE * fp = NULL;
    int i = 0;
    char chA, chB;
    int sumVal = 0, score = 0;
    char buff[10] = {'\0'};

    // open the file
    fp = fopen(argv[1], "r");
    if (NULL == fp){
        printf("Open failed.\n");
        return;
    }
    // read line
    while(fgets(buff, sizeof(buff)-1, fp) != NULL){
        sscanf(buff, "%c %c\n", &chA, &chB);
        // part1
        score = part1(chA, chB);
        // part2
        //score = part2(chA, chB);
        printf("score %d: %d\n", i++, score);
        sumVal += score;
        
        memset(buff, 0, sizeof(buff));
    }

    printf("Sum of score: %d\n", sumVal);

    return;
}
