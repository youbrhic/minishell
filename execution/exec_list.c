/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:01:51 by youbrhic          #+#    #+#             */
/*   Updated: 2024/03/25 07:24:57 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_fd(int input, int output)
{
	if (input != 0)
		close(input);
	if (output != 1)
		close(output);
}

void	open_file(char *redirection, int *input, int *output)
{
	int		i;
	char	**matr;

	if (!redirection)
		return ;
	i = -1;
	matr = ft_split(redirection, ' ');
	while (matr[++i])
	{
		check_fd(*input, *output);
		if (!ft_strcmp(matr[i], ">"))
		{
			*output = open(matr[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			i++;
		}
		else if (!ft_strcmp(matr[i], "<"))
		{
			*input = open(matr[i + 1], O_RDONLY , 0644);
			if (*input < 0)
				perror(matr[i + 1]);
			i++;
		}
		else if (!ft_strcmp(matr[i], ">>"))
		{
			*output = open(matr[i + 1], O_CREAT | O_WRONLY  | O_APPEND, 0644);
			i++;
		}
	}
	free_mat(&matr);
}

static void dup_io(int	input, int output)
{
	if (input != 0)
	{
		if (dup2(input, 0) < 0)
			exit(1);
	}
	if (output != 1)
	{
		if (dup2(output, 1) < 0)
			exit(1);
	}
}

static void close_fd(int input, int output)
{
	if (input != 0)
		close(input);
	if (output != 1)
		close(output);
}

void	exec_list(t_node *node, char **env)
{
	pid_t	pid;
	int		input;
	int		output;

	input = 0;
	output = 1;
	if (ft_lstsize(node) == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			open_file(node->redirections, &input, &output);
			dup_io(input, output);
			close_fd(input, output);
			if (exec_cmd(node->cmd, env) < 0)
			{
				perror(node->cmd);
				exit(1);
			}
		}
		else if (pid == -1)
			perror("fork error");
		else
			wait(&pid);
	}
}
