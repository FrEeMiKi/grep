#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
int MAX_LINES = 1024;
int LINE_LENGTH = 1024;
int IGNORE_CASE = 0;
int COUNT = 0;
int WORD_REGEXP = 0;
int PREFIX = 0;

void grep(FILE *file, char *argv[], int argc);

int main(int argc, char *argv[])
{

    FILE *file;
    if (argc < 3)
    {
        printf("Usage: %s (flags) \"text\" <file>\n", argv[0]);
        return 1;
    }
    else
    {
        file = fopen(argv[argc - 1], "r");
    }
    for (int i = 1; i < argc - 2; i++)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            IGNORE_CASE = 1;
        }
        else if (strcmp(argv[i], "-c") == 0)
        {
            COUNT = 1;
        }
        else if (strcmp(argv[i], "-w") == 0)
        {
            WORD_REGEXP = 1;
        }
        else if (strcmp(argv[i], "-n") == 0)
        {
            PREFIX = 1;
        }
    }
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }
    else
    {
        grep(file, argv, argc);
    }
}

void grep(FILE *file, char *argv[], int argc)
{
    int count_lines = 0;
    int count = 0;
    char lines[MAX_LINES][LINE_LENGTH];

    while (fgets(lines[count_lines % MAX_LINES], LINE_LENGTH, file) != NULL)
    {
        count_lines++;
    }

    for (int i = 0; i < count_lines; i++)
    {
        int match_found = 0;

        if (IGNORE_CASE)
        {
            if (WORD_REGEXP)
            {
                if (strcasestr(lines[i], argv[argc - 2]) != NULL)
                {
                    match_found = 1;
                }
            }
            else
            {
                if (strcasestr(lines[i], argv[argc - 2]) != NULL)
                {
                    match_found = 1;
                }
            }
        }
        else
        {
            if (WORD_REGEXP)
            {
                if (strstr(lines[i], argv[argc - 2]) != NULL)
                {
                    match_found = 1;
                }
            }
            else
            {
                if (strstr(lines[i], argv[argc - 2]) != NULL)
                {
                    match_found = 1;
                }
            }
        }

        if (match_found)
        {
            if (COUNT)
            {
                count ++;
            }
            else
            {
                if (PREFIX)
                {
                    printf("%d: %s", i + 1, lines[i]);
                }
                else
                {
                    printf("%s", lines[i]);
                }
            }
        }
    }
    if (COUNT)
    {
        printf("%d\n", count);
    }
}
