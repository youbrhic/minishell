/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bab <aait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:20:22 by aait-bab          #+#    #+#             */
/*   Updated: 2024/04/24 08:23:55 by aait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export_env(char **env)
{
	char *v_qts;
	int	f_occu;
	int	i;
	int	j;
	int	k;

	i = -1;
	while (env[++i])
	{
		j = 0;
		k = 0;
		f_occu = 0;
		v_qts = malloc(ft_strlen(env[i]) + 3);
		while (env[i][k])
		{
			v_qts[j] = env[i][k];
			if (v_qts[j] == '=' && f_occu == 0)
			{
				v_qts[j + 1] = '\"';
				f_occu = 1;
				j += 2;
			}
			else
				j++;
			k++;
		}
		v_qts[k] = '\"';
		v_qts[k + 1] = '\0';
		printf("declare -x %s\n", v_qts);
	}
}

void	ft_export(char **args, char **env)
{
	int	i;

	i = 1;
	if (!args[1])
		print_export_env(env);
	// else
	// {
	// 	while (args[i])
	// 	{
	// 		if (ft_strchr(args[i], '+='))
	// 			update_env(args[i], env);
	// 		else if (ft_strchr(args[i], '='))
	// 			add_env_kv(args[i], env);
	// 		else
	// 			add_env_k(args[i], env);
	// 		i++;
	// 	}
	// }
}