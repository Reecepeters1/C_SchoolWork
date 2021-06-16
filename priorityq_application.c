#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "priorityq.h"

#define MAX_ARGS 2
#define MAX_LINE_LENGTH 1002
#define BUFFER 2

/**
 * This application accepts a very specific output. A list of vals and priorities
 * seperated by a single space. It is not designed to handle exceptions to this
 * but the idea is that this application will only be used for processing files
 * in this format.
 * Ex:
 * Reece 20
 * */

int main(int argc, char *argv[])
{
    if (argc > MAX_ARGS)
    {
        printf("Please input less arguments.\n");
        return -1;
    }

    char *rdfile = NULL;

    if (argc > 1)
    {
        rdfile = argv[1];
    }

    FILE *fp;
    if (rdfile)
    {
        fp = fopen(rdfile, "r");
        if (!fp)
        {
            printf("Could not open file %s\n", rdfile);
            return -1;
        }
    }
    else
    {
        fp = stdin;
    }

    char currline[MAX_LINE_LENGTH];
    unsigned long gravity;
    unsigned long priority = 0;
    char val[MAX_LINE_LENGTH];

    printf("What POSITIVE gravity do you want for your priority queue?\n");
    printf("(Learn more in the priorityq.c documentation)\nGravity:");
    scanf("%lu", &gravity);
    getchar();
    struct PriorityQueue *use = make_priority_queue(gravity, NULL, 0);

    while (fgets(currline, MAX_LINE_LENGTH, fp))
    {
        if (strlen(currline) > MAX_LINE_LENGTH - BUFFER)
        {
            printf("\nSorry, priorityq_application doesn't accept line inputs greater than 1000 characters.\n");
            return -1;
        }
        int len = strlen(currline);
        if (currline[len - 1] == '\n')
        {
            currline[len - 1] = '\0';
        }
        sscanf(currline, "%s %lu", val, &priority);
        pq_add(use, val, priority);
    }
    printf("\nOutput order:\n");
    while (pq_size(use) > 0)
    {
        char *temp = pq_remove(use);
        printf("%s\n", temp);
        free(temp);
    }
    free_pq(use);
    return 0;
}