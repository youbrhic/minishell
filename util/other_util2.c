/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:21:11 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/22 10:21:54 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_quotes(char *str)
{
	int		i;
	int		count;
	char	c;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (is_quot(str[i]))
		{
			count++;
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
		}
		if (str[i] == '\0')
			break ;
	}
	return (2 * count);
}

static char	*ft_add_skiper_str(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	char	c;

	new_str = malloc(ft_strlen(str) + count_quotes(str) + 1);
	if (!new_str)
		return (ft_perror("Error"), NULL);
	(1) && (i = -1, j = -1);
	while (str[++i])
	{
		if (is_quot(str[i]))
		{
			(1) && (new_str[++j] = '\\', c = str[i++], new_str[++j] = c);
			while (str[i] && str[i] != c)
				new_str[++j] = str[i++];
			new_str[++j] = '\\';
		}
		new_str[++j] = str[i];
	}
	return (new_str[++j] = '\0', new_str);
}

int	ft_add_skiper(char **token)
{
	int		i;
	char	*tmp;

	i = -1;
	while (token[++i])
	{
		if (count_quotes(token[i]))
		{
			tmp = ft_add_skiper_str(token[i]);
			if (!tmp)
				return (ft_perror("Error"), 0);
			free(token[i]);
			token[i] = tmp;
		}
	}
	return (1);
}

int	quotes_in_str(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (is_quot(str[i]))
			return (i);
		i++;
	}
	return (-1);
}

void	write_fd(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}
