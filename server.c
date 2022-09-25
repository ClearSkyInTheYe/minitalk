/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chfederi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:24:29 by chfederi          #+#    #+#             */
/*   Updated: 2022/03/27 21:11:14 by chfederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n = -n;
		}
		if (n > 9)
			ft_putnbr_fd((n / 10), fd);
		ft_putchar_fd((n % 10) + 48, fd);
	}
}

static void	sig_hand(int sig, siginfo_t *inf, void *text)
{
	static int			a[8];
	static int			i;
	int					c;
	static int			pid;

	(void)text;
	if (pid != inf->si_pid)
		i = 0;
	if (sig == SIGUSR1)
		a[i++] = 0;
	else
		a[i++] = 1;
	if (i == 8)
	{
		c = ft_dec(a);
		ft_putchar_fd(c, 1);
		while (i != 0)
			a[i--] = 0;
			i = 0;
	}
	pid = inf->si_pid;
	kill(inf->si_pid, SIGUSR1);
}

int	ft_dec(int a[8])
{
	int	x;
	int	i;
	int	z;

	x = 0;
	i = 0;
	z = 128;
	while (i < 8)
	{
		x += a[i] * z;
		z = z / 2;
		i++;
	}
	return (x);
}

int	main(int argc, char **argv)
{
	pid_t				p;
	struct sigaction	sig;

	(void)argv;
	if (argc != 1)
	{
		write(1, "Error\n", 7);
		exit(EXIT_FAILURE);
	}
	p = getpid();
	write(1, "PID:", 4);
	ft_putnbr_fd(p, 1);
	ft_putchar_fd('\n', 1);
	sig.sa_sigaction = sig_hand;
	while (1)
	{
		sigaction(SIGUSR1, &sig, 0);
		sigaction(SIGUSR2, &sig, 0);
		pause();
	}
}
