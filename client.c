/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chfederi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:24:18 by chfederi          #+#    #+#             */
/*   Updated: 2022/03/25 19:24:21 by chfederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_ac = 0;

static int	ft_atoi(const char *str)
{
	unsigned long	i;
	unsigned long	n;

	n = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (-1);
		}
		i++;
	}
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - 48;
		i++;
	}
	return (n);
}

static void	ft_acept(int sig)
{
	if (sig == SIGUSR1)
		write(1, "у аппарата\n", 22);
	g_ac = 1;
}

static void	ft_send(unsigned char c, pid_t p)
{
	int	a[8];
	int	i;

	i = 7;
	while (c > 0)
	{
		if (c % 2 == 1)
			a[i--] = 1;
		else
			a[i--] = 0;
		c = c / 2;
	}
	while (i >= 0)
		a[i--] = 0;
	while (++i < 8)
	{
		usleep(300);
		if (a[i] == 0)
			kill(p, SIGUSR1);
		else if (a[i] == 1)
			kill(p, SIGUSR2);
		while (g_ac != 1)
			usleep(1);
		g_ac = 0;
	}
}

int	main(int argc, char **argv)
{
	pid_t	p;
	int		i;

	i = 0;
	if (argc != 3)
	{
		write(1, "Error\n", 7);
		exit(EXIT_FAILURE);
	}
	p = ft_atoi(argv[1]);
	signal(SIGUSR1, ft_acept);
	if (p < 1)
	{
		write(1, "Wrong pid\n", 11);
		exit(EXIT_FAILURE);
	}
	while (argv[2][i])
	{
		ft_send(argv[2][i], p);
		i++;
	}
	ft_send('\n', p);
}
