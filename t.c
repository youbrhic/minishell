#include "minishell.h"
#include <stdbool.h>

int main()
{
    char    *str;

    str = getenv("PATH");
    printf ("%s \n", str);
}
