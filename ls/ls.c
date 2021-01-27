#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include <unistd.h>

int main()
{
    char path[128] = {0};
    // get the current path
    getcwd(path, 127);
    // open the directory and establish a directory stream
    DIR *dir = opendir(path);
    struct dirent * ptr;
    // readdir() returns the next directory entry point for the parameter 'dir' directory stream
    // dirent is a struct
    while((ptr=readdir(dir))!= NULL)
    {
        if(ptr->d_name[0]=='.' || (ptr->d_name[0]=='.'&&ptr->d_name[1]=='.')){
            continue;
        }else{
            printf("%s ", ptr->d_name);
        }
    }
    printf("\n");
    closedir(dir);
    return 0;
}