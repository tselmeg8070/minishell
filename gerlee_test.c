# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include <string.h>

int main()
{
    char    *str;

    str = NULL;
    printf("test |%s|\n", "test");
    printf("test |%s|\n", "");
    printf("test |%s|\n", "\0");
    printf("test |%s|\n\n", str);

    printf("test strdup |%s|\n", strdup("test"));
    printf("test strdup |%s|\n", strdup(""));
    printf("test strdup |%s|\n", strdup("\0"));
    printf("test strdup |%s|\n", strdup(str));

    return (0);
}
