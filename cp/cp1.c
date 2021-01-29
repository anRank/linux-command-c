#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char** argv,char** environ)
{
	if(NULL==argv[1])//argv[0]是运行的程序名 ，所以我们直接判断argv[1]是否为空就能知道参数是否足够。
	{
		puts("Args are needed!\n");
		return 0;
	}
	if(NULL!=argv[3])//如果argv[3]不为空，说明有第三个参数，而cp指令只需要有2个参数。
	{
		puts("Too many args\n");
		return 0;
	}
	int fd=open(argv[1],O_RDWR|O_CREAT,S_IRWXU);//打开要拷贝的文件
	if(fd<0)
	{
		puts("no permission");
		return 0;
	}
	int fd2=open(argv[2],O_RDWR|O_CREAT|O_EXCL,S_IRWXU);//建立一个新的空白文件
	if(fd2<0)
	{
		puts("file are exist,press y to recover");
		char ch;
		ch=getchar();
		if(ch == 'y')
		{
			fd2=open(argv[2],O_RDWR|O_CREAT,S_IRWXU);
			if(fd2<0)
			{
				puts("no permission");
				return 0;
			}
		}
		else
			return 0;
	}
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
