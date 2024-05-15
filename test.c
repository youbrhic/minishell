#include <libc.h>
#include <readline/readline.h>

int	ft_strexsit(char *s, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		j = 0;
		if (s[i] == str[j])
		{
			while (s[i] == str[j] && str[j])
			{
				i++;
				j++;
			}
			if (!str[j])
			{
				if (s[i - 3] == '=')
					return (0);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
	printf("ft_strexist: %d\n", ft_strexsit("a+=22222222=+=0", "+="));
}

