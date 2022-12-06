#include <stdio.h>
#include <string.h>

int part1(char *str, int n, int maxLen){
    int flag[26] = {0};
    int i = 0, j=0, k=0, idx = 0;
    int len = 0;

    for(i=0; i<n && len < maxLen; i++){
        k = str[i] - 'a';
        len++;
        if(flag[k] != 0){
            // exist
            idx = flag[k]; // start from the idx
            // clear the chars before idx-1
            for (j=idx-2; j>=i-len+1; j--){
                flag[str[j] - 'a'] = 0;
            }
            len = i - idx + 1;
        }
        flag[k] = i+1;     // the index of next char
    }
    if (len >= maxLen){
        return i;
    }

    
    return -1;
}


void main(int argc, char ** argv){
    FILE * fp = NULL;
    int i = 0;
    int res = 0;
    char buff[4100] = {'\0'};

    // open the file
    fp = fopen(argv[1], "r");
    if (NULL == fp){
        printf("Open failed.\n");
        return;
    }
    // read line
    while(fgets(buff+strlen(buff), sizeof(buff)-1, fp) != NULL){
        if(buff[strlen(buff)-1] == '\n'){
            // part1
            res = part1(buff, strlen(buff)-1, 4);

            // part2
            //res = part1(buff, strlen(buff)-1, 14);

            printf("Result: %d\n", res);
            memset(buff, 0, strlen(buff));
        }
    }


    return;
}
