/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:20:36 by youbrhic          #+#    #+#             */
/*   Updated: 2024/03/29 13:36:13 by youbrhic         ###   ########.fr       */
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

void f()
{
	system ("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**matrice;
	t_node	*head;
	int		input_fd;
	int		output;

	(void)ac;
	(void)av;
	(void)env;
	input_fd = dup(0);
	output = dup(1);
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
				printf("syntaxe error : quote not close (\" or \')\n");
			else
			{
				matrice = ft_split_cmd(input);
				if (!matrice)
					printf ("error");
				else
				{
					if (parse_line(matrice) > 0)
					{
						head = get_nodes(matrice);
						if (!head)
						{
							printf ("it's her \n");
							exit(-1);
						}
						affiche(head);
						//exec_list(head, env);
						ft_lstclear(&head);
					}
					free_mat(&matrice);
					dup2(0, input_fd);
					dup2(1, output);
				}
			}
			free(input);
		}
	}
	clear_history();
}
