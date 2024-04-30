/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:58:11 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/30 22:24:14 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int 	check_fd(int fd1, int fd2)
{
	if (fd1 != fd2 && (close(fd1) < 0))
		return (perror("Erorr close"), 0);
	return (1);
}

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

static int	ft_open_file_help(char *redirection, int *input, int *output)
{
	int		i;
	char	**matr;

	i = -1;
	matr = ft_split_cmd(redirection);
	ft_remove_quotes(matr);
	ft_expand(matr, 1, i);
	while (matr[++i])
	{
		if (!ft_strcmp(matr[i], ">") && check_fd(*output, 1))
			*output = open(matr[++i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (!ft_strcmp(matr[i], "<") && check_fd(*input, 0))
			*input = open(matr[++i], O_RDONLY);
		else if (!ft_strcmp(matr[i], ">>") && check_fd(*output, 1))
			*output = open(matr[++i], O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (!ft_strcmp(matr[i], "<<") && check_fd(*input, 0))
			(1) && (*input = open("/tmp/hardoc", O_RDONLY), ++i);
		if (*input < 0 || *output < 0)
			return (perror(matr[i]), free_mat(matr), 1);
	}
	return (free_mat(matr), 0);
}

int	ft_open_file(char *redirection, int *input, int *output, int flag)
{
	int	state;

	state = ft_open_file_help(redirection, input, output);
	if (state || (flag && (dup_io(*input, *output) < 0 || close_fd(*input, *output) < 0)))
	{
		if (state)
			return (state);
		return (-1);
	}
	return (0);
}
