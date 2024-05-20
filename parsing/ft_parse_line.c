/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 04:27:39 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/20 03:17:25 by youbrhic         ###   ########.fr       */
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

static int	skip_hardoc(char **matr, char **env, int exit_status)
{
	int		i;
	int		index_error;
	int		state;

	i = -1;
	index_error = check_line(matr, 0);
	if (index_error == -1)
		index_error = get_size_mat(matr);
	while (matr[++i] && i < index_error)
	{
		if (!ft_strcmp(matr[i], "<<") && !is_oper(matr[i + 1])
			&& (i + 1) < get_size_mat(matr))
			state = ft_hardoc(&matr[i + 1], env, exit_status);
		if (state == 1)
			break ;
	}
	return (state);
}

int	ft_parse_line(char **matr, char **env, int exit_status)
{
	int		index_error;
	int		state;

	if (!matr || !*matr)
		return (exit_status);
	(1) && (index_error = check_line(matr, 0), state = 0);
	if (index_error == -1)
		return (state = skip_hardoc(matr, env, exit_status), state);
	else
	{
		if (index_error != get_size_mat(matr))
		{
			check_line(matr, 1);
			state = skip_hardoc(matr, env, exit_status);
		}
		else
		{
			state = skip_hardoc(matr, env, exit_status);
			check_line(matr, 1);
		}
		if (!state)
			state = 258;
		return (state);
	}
}
