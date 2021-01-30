#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include <libgen.h> 

#define MAXPATH  1024

void cpFile(char *file, char *dir)
{
    char buffer[MAXPATH];
    getcwd(buffer, MAXPATH);
    int fd=open(file,O_RDWR|O_CREAT,S_IRWXU);
    if(fd<0)
	{
		puts("no permission");
		return;
	}
    chdir(dir);
    int fd2 = open(file, O_RDWR|O_CREAT|O_EXCL,S_IRWXU);
    int count=1;
	for(int i=0;count>0;i++)
	{
		char buf;
		count=read(fd,&buf,sizeof(buf));
		write(fd2,&buf,sizeof(buf));
	}
	close(fd);
	close(fd2);
    chdir(buffer);
}

void cpDir(char *source_dir, char *target_dir)
{
    struct dirent *entry; 
    DIR *dir = NULL;  
    if((dir = opendir(source_dir))==NULL)
    {
        printf("opendir failed!");  
      	exit(0);
    }
    else
    {
        while(entry=readdir(dir)) 
        {
            if(entry->d_name[0]!='.')
            {
                char cwd_buf[MAXPATH];
                getcwd(cwd_buf, MAXPATH);
                char ch_buf[MAXPATH];
                char src_buf[1024] = {0};
                // printf("%s-", source_dir);
                // printf("%s-", entry->d_name);
                // printf("%s\n", target_dir);
                sprintf(ch_buf, "%s/%s", target_dir, source_dir);
                // printf("%s\n", ch_buf);
                if(entry->d_type==4)
                {
                    chdir(ch_buf);
                    mkdir(entry->d_name, 0777);
                    chdir(cwd_buf);
                    sprintf(src_buf, "%s/%s", source_dir, entry->d_name);                    
                    cpDir(src_buf, target_dir);
                }
                else if(entry->d_type==8)
                {
                    int fd=open(entry->d_name,O_RDWR|O_CREAT,S_IRWXU);
                    chdir(ch_buf);
                    int fd2 = open(entry->d_name, O_RDWR|O_CREAT|O_EXCL,S_IRWXU);
                    printf("%s\n", ch_buf);
                    int count=1;
                    for(int i=0;count>0;i++)
                    {
                        char buf;
                        count=read(fd,&buf,sizeof(buf));
                        write(fd2,&buf,sizeof(buf));
                    }
                    close(fd);
                    close(fd2);
                    chdir(cwd_buf);
                }
            }
        }
        closedir(dir);   
    }
    
}

int main(int argc,char** argv)
{
    // two situations: argv[1] is a file, or it's a dir   
    struct stat buf;
    stat(argv[1], &buf);
    if(S_IFDIR & buf.st_mode){
        char buffer[MAXPATH];
        getcwd(buffer, MAXPATH);
        chdir(argv[2]);
        mkdir(argv[1], 0777);
        chdir(buffer);
        sprintf(buffer, "%s/%s", argv[2], argv[1]);
        cpDir(argv[1], argv[2]);
    }else if(S_IFREG & buf.st_mode){
        cpFile(argv[1], argv[2]);
    }

    return 0;
}