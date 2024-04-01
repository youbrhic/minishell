#include <libc.h>

int main(int ac, char **av, char **env)
{
    char    *ch;

    env[0] = strdup("YASSINE=33");
    ch = getenv("YASSINE");
    printf ("%s \n", ch);
}
