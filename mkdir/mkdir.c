#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libgen.h>
#include <string.h>

#define MAXSIZE 100	

void createdir(char *path)
{
	if(access(path,F_OK) == 0)
	{
		chdir(path);
		return;
	}
	else
	{
		char *p = basename(path);
		path = dirname(path);
		createdir(path);
		// printf(p);
		mkdir(p, 0777);
		chdir(p);
		// printf("\n");
	}
		
}

int main(int argc, char *argv[])
{
	// printf("argc is %d\n",argc);
	// for(int i=0;i<argc;i++)
	// {
	// 	printf("argv[%d] is: %s\n",i,argv[i]);	
	// }
	if(argc <= 1){
        printf("mkdir:Usage:dirstr\n");
        exit(1);
    }
	//mkdir(argv[1], 0777);
	createdir(argv[1]);
	return 0;
}