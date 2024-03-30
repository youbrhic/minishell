/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:09:12 by youbrhic          #+#    #+#             */
/*   Updated: 2024/03/30 13:22:48 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_fd(int input, int output)
{
	if (input != 0)
		close(input);
	if (output != 1)
		close(output);
}

static int close_fd(int input, int output)
{
	if (input != 0 && (close(input) < 0))
		return (perror("Errro input"), -1);
	if (output != 1 && (close(output) < 0))
		return (perror("Errro output"), -1);
	return (1);
}

static int dup_io(int	input, int output)
{
	if (input != 0)
	{
		if (dup2(input, 0) < 0)
			return (perror("Errro dup2"), -1);
	}
	if (output != 1)
	{
		if (dup2(output, 1) < 0)
			return (perror("Errro dup2"), -1);
	}
	return (1);
}

static int 	open_file_help(char *redirection, int *input, int *output)
{
	int		i;
	char	**matr;

	i = -1;
	matr = ft_split(redirection, ' ');
	while (matr[++i])
	{
		check_fd(*input, *output);
		if (!ft_strcmp(matr[i], ">"))
			*output = open(matr[++i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (!ft_strcmp(matr[i], "<"))
			*input = open(matr[++i], O_RDONLY , 0644);
		else if (!ft_strcmp(matr[i], ">>"))
			*output = open(matr[++i], O_CREAT | O_WRONLY  | O_APPEND, 0644);
		if (*input < 0 || *output < 0)
			break ;
	}
	if (i != get_size_mat(matr))
		return (perror(matr[i]),free_mat(&matr), -1);
	return (free_mat(&matr), 1);
}

int	open_file(char *redirection, int *input, int *output)
{
	if (open_file_help(redirection, input, output) < 0
			|| dup_io(*input, *output) < 0 || close_fd(*input, *output) < 0)
		return (-1);
	return (1);
}
