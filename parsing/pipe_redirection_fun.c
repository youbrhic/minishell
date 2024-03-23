/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirection_fun.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:29:41 by youbrhic          #+#    #+#             */
/*   Updated: 2024/03/22 11:01:04 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(char *file, char *redirection)
{
	int		fd;

	fd = -1;
	if (!ft_strcmp(redirection, ">"))
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	else if (!ft_strcmp(redirection, "<"))
		fd = open(file, O_RDWR | O_TRUNC, 0777);
	else if (!ft_strcmp(redirection, ">>"))
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (!ft_strcmp(redirection, "<<"))
		fd = dup(1);
	return (fd);
}

void	check_fd(t_node *node, char *redirection)
{
	if (((!ft_strcmp(redirection, "<") || !ft_strcmp(redirection, "<<")))
		&& node->input != 0)
		close(node->input);
	else if (((!ft_strcmp(redirection, ">") || !ft_strcmp(redirection, ">>")))
		&& node->output != 1)
		close(node->output);
}

int	check_cmd_line(char **matr, int start, int end)
{
	int		i;

	i = start;
	while (i < get_size_mat(matr) && matr[i] && i < end)
	{
		if (is_redirection(matr[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	is_redirection(char	*str)
{
	return (!ft_strcmp(str, ">>") || !ft_strcmp(str, "<<")
		 || !ft_strcmp(str, "<") || !ft_strcmp(str, ">"));
}
