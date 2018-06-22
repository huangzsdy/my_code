#include <stdio.h>
#include <stdlib.h>
#define SIZE_view 50
struct view_info
{
    int id;
    char name[20];
    int code;
    char shortname[20];
    char LName[100];
}views[SIZE_view];
FILE *f;
char buf[256];
char *p;
int i, n;
int main(void)
{
    if (NULL == (f = fopen("1.txt", "r")))
    {
        fprintf(stderr, "Can not open file : 1.txt");
        return 1;
    }
    i = n = 0;
    while (1)
    {
        if (n == SIZE_view) break;
        if (NULL == fgets(buf, 256, f)) break;
        if ('\n' == buf[0]) continue;     //空行继续
        p = buf;
        sscanf(p, "%d%s%d%s%s", &views[n].id, views[n].name, &views[n].code, views[n].shortname, views[n].LName);
        n++;
    }
    do
    {
        printf("%d %s %d %s %s\n", views[i].id, views[i].name, views[i].code, views[i].shortname, views[i].LName);
        i++;
    } while (i < n);
    fclose(f);
    return 0;
}