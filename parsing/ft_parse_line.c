/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 04:27:39 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/24 16:42:32 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

int	is_oper(char *str)
{
	return (!ft_strcmp(str, ">>") || !ft_strcmp(str, "<<")
		|| !ft_strcmp(str, "|") || !ft_strcmp(str, "<")
		|| !ft_strcmp(str, ">"));
}

static char	*get_error(char *s)
{
	char	*str;

	str = ft_strndup("minishell: syntax error near unexpected token : ", 48);
	str = ft_strjoin(str, s);
	return (str);
}

static char *check_line(char **matr, int *check)
{
	int		i;
	char	*str;

	if (!matr || !*matr)
		return (NULL);
	if (matr[0][0] == '|')
		return ((*check = 0), get_error("|"));
	i = 0;
	while (matr[++i])
	{
		if (is_oper(matr[i - 1]) && is_oper(matr[i]) && matr[i][0] == '|')
			return ((*check = i), get_error(matr[i]));
		if (is_oper(matr[i - 1]) && is_oper(matr[i]) && matr[i - 1][0] != '|')
			return ((*check = i), get_error(matr[i]));
	}
	if (is_oper(matr[get_size_mat(matr) - 1]))
	{
		str = ft_strndup("minishell: syntax error nearunexpected token `newline'", 54);
		*check = get_size_mat(matr);
		return (str);
	}
	return ((*check = -1), ft_strndup("", 1));
}

static void skip_hardoc(char **matr)
{
	int		i;
	int		index_error;
	char	*str_error;

	i = -1;
	str_error = check_line(matr, &index_error);
	if (!ft_strcmp(str_error, ""))
		index_error = get_size_mat(matr);
	while (matr[++i] && i < index_error)
	{
		if (!ft_strcmp(matr[i], "<<") && !is_oper(matr[i + 1]) && (i + 1) < get_size_mat(matr))
			ft_hardoc(matr[i + 1]);
	}
	free(str_error);
}

int	ft_parse_line(char **matr)
{
	int		index_error;
	char	*str_error;

	str_error = check_line(matr, &index_error);
	printf ("%p \n", str_error);
	if (!str_error)
		return (258);
	if (index_error != get_size_mat(matr) && ft_strcmp(str_error, ""))
	{
		write(2, str_error, ft_strlen(str_error));
		write(2, "\n", 1);
		skip_hardoc(matr);
		return (free(str_error), 258);
	}
	else
	{
		skip_hardoc(matr);
		if (!ft_strcmp(str_error, ""))
			return (free(str_error), 1);
		else
		{
			write(2, str_error, ft_strlen(str_error));
			write(2, "\n", 1);
			return (free(str_error), 258);
		}
	}
}
