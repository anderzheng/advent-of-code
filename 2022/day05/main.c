#include <stdio.h>
#include <string.h>

#define NUM_STACKS 9

char stacks[NUM_STACKS][72] = {"QFMRLWCV",
                      "DQL",
                      "PSRGWCNB",
                      "LCDHBQG",
                      "VGLFZS",
                      "DGNP",
                      "DZPVFCW",
                      "CPDMS",
                      "ZNWTVMPC"};
/*
char stacks[NUM_STACKS][9] = {{'Z', 'N'},
                     {'M', 'C', 'D'},
                     {'P'}};
*/

void printStack(){
    int i=0;

    for(i=0; i<NUM_STACKS; i++){
        printf("%s\n", stacks[i]);
    }
    printf("----------------\n");
}

void part1(int nums, int from, int to){
    int i =0;
    int idxFrom = strlen(stacks[from])-1;
    int idxTo = strlen(stacks[to]);

    for(i=0; i<nums; i++){
        stacks[to][idxTo++]= stacks[from][idxFrom];
        // set zero
        stacks[from][idxFrom] = '\0';
        idxFrom--;
    }

    // printStack();
    
    return ;
}

void part2(int nums, int from, int to){
    int i =0;
    int idxFrom = strlen(stacks[from])-nums;

    strncat(stacks[to], stacks[from]+idxFrom, nums);
    // set zero
    stacks[from][idxFrom] = '\0';

    printStack();
    
    return ;
}


void main(int argc, char ** argv){
    FILE * fp = NULL;
    int i = 0;
    //int sumVal = 0, score = 0;
    int nums = 0, from = 0, to = 0;
    char buff[100] = {'\0'};

    // open the file
    fp = fopen(argv[1], "r");
    if (NULL == fp){
        printf("Open failed.\n");
        return;
    }
    // read line
    while(fgets(buff, sizeof(buff)-1, fp) != NULL){

        sscanf(buff, "move %d from %d to %d\n", &nums, &from, &to);
        
        // part1
        //part1(nums, from-1, to-1);

        // part2
        part2(nums, from-1, to-1);
        //sumVal += score;
        
        memset(buff, 0, sizeof(buff));
    }

    printf("resutl:");
    // print the top
    for(i=0; i<NUM_STACKS; i++){
        printf("%c", stacks[i][strlen(stacks[i])-1]);
    }

    printf("\n");

    //printf("Sum of score: %d\n", sumVal);

    return;
}
