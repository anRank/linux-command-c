#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>


struct mode_s
{
    int f;
    int m;
    int g;
    int o;
    char mode[10];
};


void mode_convert(mode_t st_mode, char mode[10])
{
    int k=0;
    int n;
	for(n=8;n>=0;n--)
	{
		if(st_mode&(1<<n))
		{
			switch(n%3)
			{
			case 2:
                mode[k++]='r';
				break;
			case 1:
                mode[k++]='w';
				break;
			case 0:
                mode[k++]='x';
				break;
			default:
				break;
 
			}
		}
		else
		{
            mode[k++]='-';
		}
	}
}

int main(int argc,char* argv[])
{
    int f=0;    int m=0;    int g=0;    int o=0;
    char mode[10];
    struct stat buf;    
    stat(argv[1], &buf);

    mode_convert(buf.st_mode, mode);
    for(int i=0;i<=2;i++){
        if(mode[i]=='r'){
            m+=4;
        }else if(mode[i]=='w')
        {
            m+=2;
        }else if (mode[i]=='x')
        {
            m+=1;
        }  
    }
    for(int i=3;i<=5;i++){
        if(mode[i]=='r'){
            g+=4;
        }else if(mode[i]=='w')
        {
            g+=2;
        }else if (mode[i]=='x')
        {
            g+=1;
        }  
    }
    for(int i=6;i<=8;i++){
        if(mode[i]=='r'){
            o+=4;
        }else if(mode[i]=='w')
        {
            o+=2;
        }else if (mode[i]=='x')
        {
            o+=1;
        }  
    }
    
    struct passwd *p;
    struct  group  *grp;
    p = getpwuid(buf.st_uid);
    grp = getgrgid(buf.st_gid);

    char atime[80], mtime[80], ctime[80];
    struct tm *ainfo, *minfo, *cinfo;
    ainfo = localtime(&buf.st_atime);
    minfo = localtime(&buf.st_mtime);
    cinfo = localtime(&buf.st_ctime);
    strftime(atime, 80, "%Y-%m-%e %X",ainfo);
    strftime(mtime, 80, "%Y-%m-%e %X",minfo);
    strftime(ctime, 80, "%Y-%m-%e %X",cinfo);

    printf("  File: %s\n", argv[1]);
    printf("  Size: %-15d Blocks: %-10d IO Block: %-6d\n", buf.st_size, buf.st_blocks, buf.st_blksize);
    printf("Device: %-15d Inode: %-11d Links: %d\n", buf.st_dev, buf.st_ino, buf.st_nlink);
    printf("Access: (%d%d%d%d/-%s)  ", f, m, g, o , mode);
    printf("Uid: (%5d/%8s)   Gid: (%4d/%8s)\n", buf.st_uid, p->pw_name, buf.st_gid, grp->gr_name);
    printf("Access: %s\n", atime);  //st_atime
    printf("Modify: %s\n", mtime);  //st_mtime
    printf("Change: %s\n", ctime);  //st_ctime
    printf(" Birth: -\n");
    return 0;
}