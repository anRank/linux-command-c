#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char buf[1024];
    char *cwd = getcwd(buf, 1024);

    if (cwd == NULL) {
        perror("Get current working directory fail.\n");
        exit(-1);
    } else {
        printf("%s\n", cwd);
    }
}