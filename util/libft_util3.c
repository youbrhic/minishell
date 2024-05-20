/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_util3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 02:26:56 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/20 02:28:19 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

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

int	is_alphanum(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'));
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*new;

	i = 0;
	new = (char *)malloc(ft_strlen((char *)s1) + 1);
	if (new == NULL)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
