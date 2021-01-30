#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

/*根据文件名获取文件inode-number*/
ino_t get_ino_byname(char *filename)
{
    struct stat file_stat;
    if(stat(filename, &file_stat)!=0)
    {
        perror("stat");
        exit(-1);
    }
    return file_stat.st_ino;
}

/*根据inode-number ，在当前目录中查找对应的文件名*/
char *find_name_byino(ino_t ino)
{
    DIR *dp = NULL;
    struct dirent *dptr = NULL;
    char *filename = NULL;
    dp = opendir(".");
    if(dp == NULL)
    {
        fprintf(stderr, "Can not open Current Directory\n");
        exit(-1);
    }
    else
    {
        while (NULL != (dptr = readdir(dp))) {
            if (dptr->d_ino == ino) {
                filename = strdup(dptr->d_name);
                break;
            }
        }
        closedir(dp);
    }
    
    return filename;
}

/*限制最大的目录深度*/
#define MAX_DIR_DEPTH (256)

int main(int argc, char *argv[])
{
    /*记录目录名的栈*/
    char *dir_stack[MAX_DIR_DEPTH];
    unsigned current_depth = 0;

    for(;;) {
        /*1.通过特殊的文件名“.”获取当前目录的inode-number*/
        ino_t current_ino = get_ino_byname(".");
        /*2.通过特殊的文件名“..”获取当前目录的父级目录的inode-number*/
        ino_t parent_ino = get_ino_byname("..");

        /*3.判断当前目录和上级目录的inode-number是否一样*/
        if (current_ino == parent_ino)
            break; /*4.如果两个inode-number一样说明到达根目录*/

        /*5.如果两个inode-number不一样*/
        /*切换至父级目录，根据步骤1获取的inode-number，在父级目录中搜索对应的文件名并记录下来, 重新回到步骤1*/
        chdir("..");
        dir_stack[current_depth++] = find_name_byino(current_ino);
        if (current_depth>=MAX_DIR_DEPTH) { /*路径名太深*/
             fprintf(stderr, "Directory tree is too deep.\n");
             exit(-1);
        }
    }
    /*输出完整路径名*/
    int i = current_depth-1;
    for (i = current_depth-1; i>=0; i--) {
       fprintf(stdout, "/%s", dir_stack[i]);
    }
    fprintf(stdout, "%s\n", current_depth==0?"/":"");

    return 0;
    
}