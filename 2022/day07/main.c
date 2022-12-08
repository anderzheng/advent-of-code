#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct dir_node *DIRLIST;

typedef struct dirs{
    char name[100];
    int fSize;
    DIRLIST subDirs;
    //struct dirs* dList;
}DIRS;

typedef struct dir_node{
    DIRS dir;
    struct dir_node * next;
}NODE;


#define     LS_CMD  "$ ls"
#define     CD_CMD  "$ cd"
#define     DIR_INFO  "dir"
#define     DIR_PARENT  ".."



DIRS * findDir(DIRS *root, char* dName, int n){
    NODE * sub = NULL;
    if (NULL == root){
        return NULL;
    }
    sub = root->subDirs;
    while(sub != NULL){
        if (strncmp(sub->dir.name, dName, n) == 0){
            return &(sub->dir);
        }
        sub = sub->next;
    }
    return NULL;
}

void addDir(DIRS *root, NODE *dNode){
    NODE * sub = NULL;
    if (NULL == root){
        return;
    }
    if (root->subDirs == NULL){
        root->subDirs = dNode;
        return ;
    }

    sub = root->subDirs;
    while(sub->next != NULL){
        sub = sub->next;
    }
    sub->next = dNode;
    return;
}


int sumVal = 0;

void scanDirTree(DIRS *root){
    NODE *ptr = NULL;

    if (NULL == root){
        return;
    }

    ptr = root->subDirs;

    while(ptr){
        // recusively scan
        scanDirTree(&(ptr->dir));
        ptr = ptr->next;
    }
    if (root->fSize < 100000){
        sumVal += root->fSize;
    }
    printf("%s: %d\n", root->name, root->fSize);
}

int minVal = INT_MAX;
int found = 0;

void part2Scan(DIRS *root, int iSize){
    NODE *ptr = NULL;

    if (NULL == root || found == 1){
        return;
    }

    ptr = root->subDirs;

    while(ptr){
        // recusively scan
        part2Scan(&(ptr->dir), iSize);
        ptr = ptr->next;
    }
    if (root->fSize == iSize){
        minVal = iSize;
        found = 1;
    } else if(root->fSize > iSize) {
        minVal = root->fSize < minVal? root->fSize:minVal;
    }
    printf("%s: %d\n", root->name, root->fSize);
}

void main(int argc, char ** argv){
    FILE * fp = NULL;
    int i = 0;
    int res = 0;
    char buff[100] = {'\0'};

    int fSize=0;
    char fName[100] = {'\0'};

    DIRS root = {"/", 0, NULL};
    DIRS *pptr = NULL, *dptr = &root, *sdptr = NULL;
    NODE *node = NULL;

    DIRS * stack[100] = {0};
    int idx = 0;

    // open the file
    fp = fopen(argv[1], "r");
    if (NULL == fp){
        printf("Open failed.\n");
        return;
    }

    // read line
    while(fgets(buff, sizeof(buff)-1, fp) != NULL){
        if (strncmp(buff, CD_CMD, strlen(CD_CMD)) == 0){
            // command cd
            if (buff[strlen(CD_CMD)+1] == '/'){
                // root
                idx = 0;
                dptr = &root;
            } else if (strncmp(buff+strlen(CD_CMD)+1, DIR_PARENT, strlen(DIR_PARENT)) == 0){
                // parent dir, add the dir size to parent
                stack[idx-1]->fSize += dptr->fSize;
                // move to paretn dir
                dptr = stack[--idx];
            } else{
                // cd a dir, get dir name
                sscanf(buff, "$ cd %s\n", fName);
                sdptr = findDir(dptr, fName, strlen(fName));
                if (sdptr == NULL){
                    // create
                    node = (NODE*)malloc(sizeof(NODE));
                    node->next = NULL;
                    sdptr = &(node->dir);
                    strncpy(sdptr->name, fName, strlen(fName));
                    sdptr->fSize = 0;

                    // add to parent
                    addDir(dptr, node);
                }
                // push to stack
                stack[idx++] = dptr;
                // point to the dir
                dptr = sdptr;
            }
        } else if (strncmp(buff, LS_CMD, strlen(LS_CMD)) == 0){
            // cmd ls, get the file info next
            continue;
        } else {
            // file info
            if (strncmp(buff, DIR_INFO, strlen(DIR_INFO)) == 0){
                // sub dir, do nothing
            } else {
                // get file name and size
                sscanf(buff, "%d %s\n", &fSize, fName);
                dptr->fSize += fSize;
            }
        }
    }
    // if stack is not empty, pop
    while(idx>0){
        stack[--idx]->fSize += dptr->fSize;
        dptr= stack[idx];
    }

    // part1
    // scan the dir tree to find the size < 100000
    //scanDirTree(&root);

    //printf("result: %d\n", sumVal);

    // part2
    part2Scan(&root, root.fSize-40000000);
    printf("minVal: %d for: %d\n", minVal, root.fSize-40000000);


    return;
}
