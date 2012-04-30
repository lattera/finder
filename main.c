#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define BUFSZ 512

#define ESCAPE " \\|#{}()&$"

void usage(char *name)
{
    fprintf(stderr, "USAGE: %s <cmd> <path1> .. <pathN>\n", name);
    exit(1);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    unsigned int i, j, k;
    char buf[BUFSZ+1];
    char *p;
    int skip;
    char *escape = ESCAPE;

    if (argc < 3)
        usage(argv[0]);

    fp = popen(argv[1], "r");
    if (!(fp)) {
        fprintf(stderr, "[-] popen failed!\n");
        exit(1);
    }

    while (!feof(fp)) {
        skip=0;
        memset(buf, 0x00, BUFSZ);

        fgets(buf, BUFSZ, fp);
        p = strchr(buf, '\n');
        if ((p))
            *p = 0x00;

        if (!strlen(buf))
            continue;

        for (j=2; argv[j]; j++)
            if (strstr(buf, argv[j]))
                skip = 1;

        if (skip)
            continue;

        printf("'%s'\n", buf);
    }

    return 0;
}
