#include <stdio.h>

#define TOP_NUM 3

/*
* function : compare the top 3
* val:  new number
* *top: array with desc order
* *topIdx: idx of top value
* n: size of top array
*/ 
void compareTop(int val, int idx, int *top, int *topIdx, int n){
    int tmp = 0;
    int i = 0;
    if (NULL == top){
        return;
    }
    for (i=0; i<n; i++){
        if (val > top[i]){
            // swap value
            tmp = top[i];
            top[i] = val;
            val = tmp;
            // swap idx
            tmp = topIdx[i];
            topIdx[i] = idx;
            idx = tmp;
        }
    }

    return;
}

void main(void){
    FILE * fp = NULL;
    int i = 0;
    //int maxVal = 0, maxIdx = 0;
    int topVal[TOP_NUM] = {0}, topIdx[TOP_NUM] = {0};   // for part 2
    int sumVal = 0, idx = 0;
    char buff[100] = {'\0'};

    // open the file
    fp = fopen("./input.txt", "r");
    if (NULL == fp){
        printf("Open failed.\n");
        return;
    }
    // read line
    while(fgets(buff, sizeof(buff)-1, fp) != NULL){
        if (buff[0] == '\n'){
            // printf("idx: %d, val: %d\n", idx, sumVal);
            /*
            // finish a elf, compare the value
            if (sumVal > maxVal){
                maxVal = sumVal;
                maxIdx = idx;
            }
            */

            // part2
            compareTop(sumVal, idx, topVal, topIdx, TOP_NUM);

            // reset the var for next elf
            sumVal = 0;
            idx++;
        } else {
            sumVal += atoi(buff);
        }
        memset(buff, 0, sizeof(buff));
    }
    /*
    if (sumVal > maxVal){
        maxVal = sumVal;
        maxIdx = idx;
    }
    */
    // part2
    compareTop(sumVal, idx, topVal, topIdx, sizeof(topVal));

    sumVal=0;
    for(i=0; i<TOP_NUM; i++){
       printf("Top%d: %d, idx: %d\n", i, topVal[i], topIdx[i]); 
       sumVal += topVal[i];
    }
    printf("Sum of Top %d: %d\n",TOP_NUM, sumVal);

    return;
}
