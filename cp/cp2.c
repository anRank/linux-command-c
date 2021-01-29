#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char** argv,char** environ)
{
    char *file = argv[1];
    char *dir = argv[2];

	if(NULL==argv[1])
	{
		puts("Args are needed!\n");
		return 0;
	}
	if(NULL!=argv[3])
	{
		puts("Too many args\n");
		return 0;
	}
	int fd=open(argv[1],O_RDWR|O_CREAT,S_IRWXU);
	if(fd<0)
	{
		puts("no permission");
		return 0;
	}

    chdir(dir);
    int fd2 = open(file, O_RDWR|O_CREAT|O_EXCL,S_IRWXU);
	
    

	int count=1;
	for(int i=0;count>0;i++)
	{
		char buf;
		count=read(fd,&buf,sizeof(buf));
		write(fd2,&buf,sizeof(buf));
	}//将被拷贝的文件的内容写入到空白文件中
	close(fd);//关闭被拷贝的文件
	close(fd2);//关闭新的文件
	return 0;
} 
