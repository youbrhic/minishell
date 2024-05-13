/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:58:11 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/13 01:36:58 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	close_fd(int input, int output)
{
	if (input != 0 && (close(input) < 0))
		return (perror("Erorr input"), -1);
	if (output != 1 && (close(output) < 0))
		return (perror("Erorr output"), -1);
	return (1);
}

static int	dup_io(int input, int output)
{
	if (input != 0)
	{
		if (dup2(input, 0) < 0)
			return (perror("Erorr dup2"), -1);
	}
	if (output != 1)
	{
		if (dup2(output, 1) < 0)
			return (perror("Erorr dup2"), -1);
	}
	return (1);
}

int	ft_open_file(char *redirection, t_argument arg, int exit_status, char **env)
{
	int	state;

	state = ft_create_file(redirection, &arg, exit_status, env);
	if (state || (dup_io(arg.input, arg.output) < 0
			|| close_fd(arg.input, arg.output) < 0))
	{
		if (state)
			return (state);
		return (-1);
	}
	return (0);
}
