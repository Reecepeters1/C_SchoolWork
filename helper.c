#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    (void)argc;
    char currline[1000];
    char *rdfile = argv[1];
    FILE *fp = fopen(rdfile, "r");
    int in_bracket = 0;
    int go_now = 1;

    while (fgets(currline, 1000, fp))
    {
        if (!strcmp(currline, "{\n"))
        {
            in_bracket = 1;
        }
        else if (!strcmp(currline, "}\n"))
        {
            go_now = 0;
            in_bracket = 0;
        }
        else if (!strcmp(currline, "\n"))
        {
            go_now = 0;
        }
        if (!in_bracket && go_now)
        {
            printf("%s", currline);
        }
        go_now = 1;
    }
}