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
		printf(" %d ------------------------\n", i);
		i++;
	}
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

int	ft_execute_lst(char **av, int *p_1, int *p_2, char **env)
{
	int			i;
	int			pid;
	t_node		*lst;
	char		**matr;

	i = 1;
	matr = add_pipes(&av[1]);
	lst = get_nodes(matr);
	while (lst)
	{
		if ((ft_pipe(p_1, p_2, lst, i) < 0))
			return (-1);
		pid = fork();
		if (pid == 0)
		{
			if (0 <= ft_dup(p_1, p_2, lst, i))
			{
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


int main(int ac, char **av, char **env)
{
	int		pipes1[2];
	int		pipes2[2];
	t_node  *node;
	char	**matr;
	t_node	*head;

	//node = get_nodes(matr);
	//affiche(node);
	ft_execute_lst(av, pipes1, pipes2, env);
}
