#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define	SHOWHOST

void show_time(long timeval)
{
    char format_time[40];
    struct tm *cp;
    cp = localtime(&timeval);
    strftime(format_time,40,"%F %R",cp);
    printf("%s",format_time);
}

int show_info(struct utmp *utbufp)
{
    if(utbufp->ut_type == USER_PROCESS){
        printf("%-8.8s", utbufp->ut_name);
        printf(" ");
        printf("%-8.8s", utbufp->ut_line);
        printf("     ");
        show_time(utbufp->ut_time);
        printf(" ");
        printf("(%s)", utbufp->ut_host);
        printf("\n");
	}
	return 0;
}

int main()
{
    struct utmp current_record;
    int utmpfd;
    int	reclen = sizeof(current_record);

    if((utmpfd=open(UTMP_FILE, O_RDONLY))==-1){
        perror( UTMP_FILE );
		exit(1);
    }
    while(read(utmpfd, &current_record, reclen) == reclen)
    {
        show_info(&current_record);
    }
	close(utmpfd);
	return 0;
}