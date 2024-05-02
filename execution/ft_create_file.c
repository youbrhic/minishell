/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 03:02:51 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/02 09:35:50 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int check_spacestr(char *str)
{
    int     i;

    i = -1;
    while (str[++i])
    {
        if (is_space(str[i]))
            return (1);
    }
	return (0);
}

static void print_error(char *str)
{
	write(2, "minishell :", 11);
	write(2, str, ft_strlen(str));
	write(2, ":ambiguous redirect\n", 20);	
}

static int 	check_fd(int fd1, int fd2)
{
	if (fd1 != fd2 && (close(fd1) < 0))
		return (perror("Erorr close"), 0);
	return (1);
}

static int check_ambiguous(char **matr, int exit_status, char **env)
{
    char    **copy;
    int     i;

    copy = get_matr_copy(matr);
    if (!copy)
        return (1);
    if (!ft_expand(copy, 1, exit_status, env))
        return (free_mat(copy), 1);
    i = -1;
    while (copy[++i])
    {
        if (is_redirection(copy[i]) && ft_strcmp(copy[i], "<<"))
        {
            if (matr[i + 1][0] == '$' && (check_spacestr(copy[i + 1]) || !*copy[i + 1]))
				return (free_mat(copy), print_error(matr[i + 1]), 1);
        }
    }
	if (!ft_remove_quotes(matr) || !ft_expand(matr, 1, exit_status, env))
		return (free_mat(copy), 1);
	return (free_mat(copy), 0);
}

int	ft_create_file(char *redirection, int *input, int *output, int exit_status, char **env)
{
	int		i;
	char	**matr;

	i = -1;
	matr = ft_split_cmd(redirection);
	if (check_ambiguous(matr, exit_status, env))
		return (free_mat(matr), 1);
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
			return (write(2, "minishell :", 12), perror(matr[i]), free_mat(matr), 1);
	}
	return (free_mat(matr), 0);
}
