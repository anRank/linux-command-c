#include<stdio.h>
#include<pwd.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    uid_t uid;
    struct passwd *p;
    uid = geteuid();
    p = getpwuid(uid);
    printf("%s\n",p->pw_name);
	return 0;
}