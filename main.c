/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:20:36 by youbrhic          #+#    #+#             */
/*   Updated: 2024/04/26 20:46:56 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	affiche(t_node *head)
// {
// 	t_node	*tmp;

// 	tmp = head;
// 	while (tmp)
// 	{
// 		printf ("cmd : %s \n", tmp->cmd);
// 		printf ("rederiction : %s \n", tmp->redirections);
// 		tmp = tmp->next;
// 		printf("------------------------\n");
// 	}
// }
/*PATH=/Users/aait-bab/.docker/bin:/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.
PWD=/Users/aait-bab/Desktop/minishell
SHLVL=1
_=/usr/bin/env*/

char	**copy_env(char **env)
{
	int		i;
	char	**nenv;

	i = 0;
	while (env[i])
		i++;
	nenv = (char **)malloc(sizeof(char *) * (i + 1));
	if (!nenv)
		return (NULL);
	i = -1;
	while (env[++i])
		nenv[i] = ft_strndup(env[i], ft_strlen(env[i]));
	nenv[i] = NULL;
	return (nenv);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**token;
	t_node	*head;
	char	**nenv;
	int		i;

	(void)ac;
	(void)av;
	nenv = copy_env(env);
	while (1)
	{
		input = readline("minibash$ ");
		if (!input)
			exit(1);
		else
		{
			if (*input)
            	add_history(input);
			input = add_space(input);
			if (!input)
				printf("syntax error \n");
			else
			{
				token = ft_split_cmd(input);
				if (!token)
					printf ("error");
				else
				{
					expand(token, 1);
					// remove_quotes(token);
					if (parse_line(token) != 258)
					{
						head = get_nodes(token);
						if (!head)
							continue;
						//affiche(head);
						exec_list(head, &nenv);
						// affiche(head);
						//exec_list(head, env);
						ft_lstclear(&head);
					}
					free_mat(&token);
				}
			}
			free(input);
		}
	}
	clear_history();
}
