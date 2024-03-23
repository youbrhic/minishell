/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 04:27:39 by youbrhic          #+#    #+#             */
/*   Updated: 2024/03/22 06:36:36 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_oper(char *str)
{
	return (!ft_strcmp(str, ">>") || !ft_strcmp(str, "<<")
		|| !ft_strcmp(str, "|") || !ft_strcmp(str, "<")
		|| !ft_strcmp(str, ">"));
}

static void	print_error(char *s)
{
	char	*str;

	str = ft_strndup("minishell: syntax error near unexpected token : ", 51);
	str = ft_strjoin(str, s);
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		free(str);
	}
}

int	parse_line(char **matr)
{
	int		i;
	char	*str;

	if (!matr || !*matr)
		return (-1);
	if (matr[0][0] == '|')
		return (print_error("|"), -1);
	i = 0;
	while (matr[++i])
	{
		if (is_oper(matr[i - 1]) && is_oper(matr[i]) && matr[i][0] == '|')
			return (print_error(matr[i]), -1);
		if (is_oper(matr[i - 1]) && is_oper(matr[i]) && matr[i - 1][0] != '|')
			return (print_error(matr[i]), -1);
	}
	if (is_oper(matr[get_size_mat(matr) - 1]))
	{
		str = ft_strndup("bash: syntax error nearunexpected token `newline'", 50);
		write(2, str, ft_strlen(str));
		write(1, "\n", 1);
		return (-1);
	}
	return (1);
}
