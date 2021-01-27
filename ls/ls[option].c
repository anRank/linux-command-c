#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>   
#include <stdlib.h>

void mode_convert(mode_t st_mode)
{
    int n;
	for(n=8;n>=0;n--)
	{
		if(st_mode&(1<<n))
		{
			switch(n%3)
			{
			case 2:
				printf("r");
				break;
			case 1:
				printf("w");
				break;
			case 0:
				printf("x");
					break;
			default:
				break;
 
			}
		}
		else
		{
			printf("-");
		}
	}
}

void no_option(DIR *dir, struct dirent * ptr){
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
}
void a(DIR *dir, struct dirent * ptr){
    while((ptr=readdir(dir))!= NULL)
    {
        printf("%s ", ptr->d_name);
    }
    printf("\n");
    closedir(dir);
}
void l(DIR *dir, struct dirent * ptr){
    while((ptr=readdir(dir))!= NULL)
    {
        if(ptr->d_name[0]=='.' || (ptr->d_name[0]=='.'&&ptr->d_name[1]=='.')){
            continue;
        }else{
            struct stat buf;
            stat(ptr->d_name, &buf);
            mode_convert(buf.st_mode);
            printf("%d ", buf.st_nlink);
            struct passwd *user;
            struct group *gdata;
            user = getpwuid(buf.st_uid);
            gdata = getgrgid(buf.st_uid);
            printf("%s ", user->pw_name);
            printf("%s ", gdata->gr_name);
            printf("%d ", buf.st_size);
            struct tm *info = localtime(&buf.st_mtime);
            char buffer[80];
            strftime(buffer,80,"%a %e %R", info);
            printf("%s ", buffer);
            printf("%s\n", ptr->d_name);
        }
    }
    printf("\n");
    closedir(dir);
}
void r(DIR *dir, struct dirent * ptr){
    printf("r");
}
void t(DIR *dir, struct dirent * ptr){
    printf("t");
}
void A(DIR *dir, struct dirent * ptr){
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
}
void F(DIR *dir, struct dirent * ptr){
    while((ptr=readdir(dir))!= NULL)
    {
        if(ptr->d_name[0]=='.' || (ptr->d_name[0]=='.'&&ptr->d_name[1]=='.')){
            continue;
        }else{
            struct stat buf;
            stat(ptr->d_name, &buf);
            if(access(ptr->d_name,X_OK)==0){
                printf("%s* ", ptr->d_name);
            }else if(S_IFDIR & buf.st_mode){
                printf("%s/ ", ptr->d_name);
            }else{
                printf("%s ", ptr->d_name);
            }
        }
    }
    printf("\n");
    closedir(dir);
}
void R(DIR *dir, struct dirent * ptr){
    printf("R");
}

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

    char input[20] = {0};
    char order[4] = {0};
    char option[14] = {0};
    scanf("%[^\n]", input);
    int j=0;
    for(j=0;!isspace(input[j]);j++){
        order[j]=input[j];
    }
    for(int k=0,i=j+1;input[i]!=0;k++,i++){
        option[k]=input[i];
    }
    // printf(order);
    // printf(option);
    if(strcmp(order, "ls")==0)
    {
        if(option[1]=='a')
            a(dir, ptr);
        else if(option[1]=='l')
            l(dir, ptr);
        else if(option[1]=='r')
            r(dir, ptr);
        else if(option[1]=='t')
            t(dir, ptr);
        else if(option[1]=='A')
            A(dir, ptr);
        else if(option[1]=='F')
            F(dir, ptr);
        else if(option[1]=='R')
            R(dir, ptr);
        else
            no_option(dir, ptr);
    }
    // while((ptr=readdir(dir))!= NULL)
    // {
    //     if(ptr->d_name[0]=='.' || (ptr->d_name[0]=='.'&&ptr->d_name[1]=='.')){
    //         continue;
    //     }else{
    //         printf("%s ", ptr->d_name);
    //     }
    // }
    // printf("\n");
    // closedir(dir);
    return 0;
}