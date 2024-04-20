/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:20:36 by youbrhic          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/19 15:35:59 by aait-bab         ###   ########.fr       */
=======
/*   Updated: 2024/04/20 03:00:54 by youbrhic         ###   ########.fr       */
>>>>>>> 59802f23c1eec128652d13fd0305fde8ea55e5d8
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	affiche(t_node *head)
{
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		printf ("cmd : %s \n", tmp->cmd);
		printf ("rederiction : %s \n", tmp->redirections);
		tmp = tmp->next;
		printf("------------------------\n");
	}
}

// void f()
// {
// 	system ("leaks minishell");
// }

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**token;
	t_node	*head;

	(void)ac;
	(void)av;
	(void)env;
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
				printf("syntaxe error : quote not close \n");
			else
			{
				token = ft_split_cmd(input);
				if (!token)
					printf ("error");
				else
				{
					expand(token);
					if (parse_line(token) > 0)
					{
						head = get_nodes(token);
						if (!head)
						{
							printf ("it's her \n");
							exit(-1);
						}
<<<<<<< HEAD
						//affiche(head);
						// exec_bultin(head, env);
						exec_list(head, env);
=======
						affiche(head);
						//exec_list(head, env);
>>>>>>> 59802f23c1eec128652d13fd0305fde8ea55e5d8
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
