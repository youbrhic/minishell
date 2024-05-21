/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libtf_util4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 06:30:14 by youbrhic          #+#    #+#             */
/*   Updated: 2024/05/21 09:32:51 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	len(long n)
{
	if (n == 0)
		return (0);
	else if (n < 0)
		return (1 + len(n * -1));
	return (1 + len(n / 10));
}

static char	*get_str(long l, int s)
{
	char	*str;

	if (l == 0)
		s++;
	str = (char *)malloc((s + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (l == 0)
		*str = '0';
	else if (l < 0)
	{
		*str = '-';
		l *= -1;
	}
	*(str + s--) = '\0';
	while (l > 0)
	{
		*(str + s--) = l % 10 + 48;
		l /= 10;
	}
	return (str);
}

int	ft_atoi(char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;
	long long			max;

	i = 0;
	sign = 1;
	res = 0;
	max = 9223372036854775807;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		if (res > (unsigned long long)max)
			return (ft_putstr_fd("minishell:exit:", 2), ft_putstr_fd(str, 2)
				, ft_putstr_fd(":numeric argument required", 2), 2);
		i++;
	}
	return (res * sign);
}

char	*ft_itoa(int n)
{
	long	l;

	l = n;
	return (get_str(l, len(l)));
}
