#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <libc.h>
#include "minishell.h"

static void	affiche(t_node *head)
{
	t_node	*tmp;
	int		i;

	tmp = head;
	i = 1;
	while (tmp)
	{
		printf ("cmd : %s \n", tmp->cmd);
		printf ("rederiction : %s \n", tmp->redirections);
		tmp = tmp->next;
		printf(" ------------------------\n");
		i++;
	}
}

void	check_fd2(int input, int output)
{
	if (input != 0)
		close(input);
	if (output != 1)
		close(output);
}

void	open_file2(char *redirection, int *input, int *output)
{
	int		i;
	char	**matr;

	if (!redirection)
		return ;
	i = -1;
	matr = ft_split(redirection, ' ');
	while (matr[++i])
	{
		check_fd2(*input, *output);
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

static char	**add_pipes(char **av)
{
	char	**matr;
	int		i;
	int		j;

	matr = malloc(sizeof(char *) * (2 * get_size_mat(av) + 1) - 1);
	i = -1;
	j = -1;
	while (av[++i])
	{
		matr[++j] = av[i];
		matr[++j] = ft_strndup("|", 1);
	}
	return (matr);
}

static int	ft_close_fd(int	*p_1, int *p_2, int i)
{
	if (i % 2 == 0)
	{
		if (close(p_1[0]) < 0)
			return (perror("Error"), -1);
	} 
	if ((1 < i) && (i % 2 != 0))
	{
		if (close(p_2[0]) < 0)
			return (perror("Error"), -1);
	}
	return (0);
}

static int	ft_pipe(int	*p_1, int *p_2, t_node*node, int i)
{
	if ((i == 1) && node->next && ((pipe(p_1) < 0)))
		return (perror("Error"), -1);
	else if (1 < i)
	{
		if (!node->next)
		{
			if ((i % 2 == 0) && ((close(p_1[1]) < 0)))
				return (perror("Error"), -1);
			else if (i % 2 != 0 && ((close(p_2[1]) < 0)))
				return (perror("Error"), -1);
		}
		else if ((i % 2 == 0) && \
			((close(p_1[1]) < 0) || (pipe(p_2) < 0)))
			return (perror("Error"), -1);
		else if ((i % 2 != 0) && \
			((close(p_2[1]) < 0) || (pipe(p_1) < 0)))
			return (perror("Error"), -1);
	}
	return (0); 
}

static int	ft_dup(int	*p_1, int *p_2, t_node*node, int i)
{
	if ((i == 1) && node->next && ((dup2(p_1[1], 1) < 0)))
		return (perror("Error"), -1);
	else if (1 < i)
	{
		if (!node->next)
		{
			if ((i % 2 == 0) && ((dup2(p_1[0], 0) < 0)))
				return (perror("Error"), -1);
			else if (i % 2 != 0 && ((dup2(p_2[0], 0) < 0)))
				return (perror("Error"), -1);
		}
		else if ((i % 2 == 0) && ((dup2(p_1[0], 0) < 0) || \
			(dup2(p_2[1], 1) < 0)))
			return (perror("Error"), -1);
		else if ((i % 2 != 0) && ((dup2(p_2[0], 0) < 0) ||
			(dup2(p_1[1], 1) < 0)))
			return (perror("Error"), -1);
	}
	return (0); 
}

int	ft_execute_lst(char *av, int *p_1, int *p_2, char **env)
{
	int			i;
	int			pid;
	t_node		*lst;
	char		**matr;
	char 		*word;
	int			input;
	int			output;

	i = 1;
	word = ft_strndup(av, ft_strlen(av));
	matr = ft_split_cmd(word);
	lst = get_nodes(matr);
	input = 0;
	output = 1;
	while (lst)
	{
		if ((ft_pipe(p_1, p_2, lst, i) < 0))
			return (-1);
		pid = fork();
		if (pid == 0)
		{
			if (0 <= ft_dup(p_1, p_2, lst, i))
			{
				if (lst->redirections)
				{
					open_file2(lst->redirections, &input, &output);
					dup_io(input, output);
				}
				exec_cmd(lst->cmd, env);
			}
			exit(1);
		}
		ft_close_fd(p_1, p_2, i);
		lst = lst->next;
		i++;
	}
	while (0 < wait(NULL))
		;
	return (0);
}

// int main(int ac, char **av, char **env)
// {
// 	int		pipes1[2];
// 	int		pipes2[2];
// 	t_node  *node;
// 	char	**matr;
// 	t_node	*head;

// 	//node = get_nodes(&av[1]);
// 	//affiche(node);
// 	// matr = add_pipes(&av[1]);
// 	// node = get_nodes(matr);
// 	if (ac == 2)
// 		ft_execute_lst(av[1], pipes1, pipes2, env);
// }