/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 04:27:39 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/01 07:37:32 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_error(int flag)
{
	if (flag)
		write(2, "minishell : syntax error\n", 25);
}

static int	check_line(char **matr, int flag)
{
	int		i;

	if (matr[0][0] == '|')
		return (print_error(flag), 0);
	i = 0;
	while (matr[++i])
	{
		if (is_oper(matr[i - 1]) && is_oper(matr[i]) && matr[i][0] == '|')
			return (print_error(flag), i);
		if (is_oper(matr[i - 1]) && is_oper(matr[i]) && matr[i - 1][0] != '|')
			return (print_error(flag), i);
	}
	if (is_oper(matr[get_size_mat(matr) - 1]))
		return (print_error(flag), get_size_mat(matr));
	return (-1);
}

static void	skip_hardoc(char **matr)
{
	int		i;
	int		index_error;

	i = -1;
	index_error = check_line(matr, 0);
	if (index_error == -1)
		index_error = get_size_mat(matr);
	while (matr[++i] && i < index_error)
	{
		if (!ft_strcmp(matr[i], "<<") && !is_oper(matr[i + 1])
			&& (i + 1) < get_size_mat(matr))
			ft_hardoc(matr[i + 1]);
	}
}

int	ft_parse_line(char **matr)
{
	int		index_error;

	if (!matr || !*matr)
		return (258);
	index_error = check_line(matr, 0);
	if (index_error == -1)
		return (skip_hardoc(matr), 0);
	else
	{
		if (index_error != get_size_mat(matr))
			return (skip_hardoc(matr), check_line(matr, 1), 258);
		else
			return (check_line(matr, 1), skip_hardoc(matr), 258);
	}
}
