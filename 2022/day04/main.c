#include <stdio.h>
#include <string.h>

int part1(char *str, int n){
    int a1, a2, b1, b2;

    if (n < 7){
        return 0;
    }

    sscanf(str, "%d-%d,%d-%d\n", &a1, &a2, &b1, &b2);

    //printf("%d:%d, %d:%d\n", a1,a2, b1,b2);
    if ((b1 >= a1 && b2 <= a2) ||
        (a1 >= b1 && a1 <= b2)){
        printf("%d:%d, %d:%d\n", a1,a2, b1,b2);
        return 1;
    }
    
    return 0;
}

int part2(char *str, int n){
    int a1, a2, b1, b2;

    if (n < 7){
        return 0;
    }

    sscanf(str, "%d-%d,%d-%d\n", &a1, &a2, &b1, &b2);

    //printf("%d:%d, %d:%d\n", a1,a2, b1,b2);
    if ((b1 >= a1 && b1 <= a2) ||
        (a1 >= b1 && a1 <= b2)){
        printf("%d:%d, %d:%d\n", a1,a2, b1,b2);
        return 1;
    }
    
    return 0;
}


void main(int argc, char ** argv){
    FILE * fp = NULL;
    int i = 0;
    int sumVal = 0, score = 0;
    char buff[100] = {'\0'};

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
        score = part2(buff, strlen(buff)-1);

        sumVal += score;
        
        memset(buff, 0, sizeof(buff));
    }

    printf("Sum of score: %d\n", sumVal);

    return;
}
