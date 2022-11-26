/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:26:26 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/26 19:38:14 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	arb;
	int	res;

	arb = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\t' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			arb *= -1;
	res = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * arb);
}

int	decimal_len(long long n, char c, int base)
{
	int	cn;

	cn = 0;
	if (n == 0 && c != 'p')
		return (0);
	if (n < 0)
		n *= -1;
	if (n == 0)
		cn++;
	while (n)
	{
		n = n / base;
		cn++;
	}
	return (cn);
}

int	nlen(long long n, char c)
{
	int					cn;
	int					base;
	unsigned long long	nb;

	nb = 0;
	base = 10;
	cn = 0;
	if (c == 'x' || c == 'X' || c == 'p')
		base = 16;
	if (c == 'p')
	{
		nb = n;
		while (nb)
		{
			nb = nb / base;
			cn++;
		}
		if (n == 0)
			cn++;
		if (c == 'p')
			cn += 2;
		return (cn);
	}
	return (decimal_len(n, c, base));
}

void	ft_printnb(int n, int *cn, char c)
{
	unsigned int	nb;

	nb = n;
	if (c == 'x' || c == 'X')
		hex(nb, c, cn);
	else
	{
		if (c != 'u')
		{
			if (n < 0)
				nb = n * -1;
		}
		if (nb / 10)
			ft_printnb(nb / 10, cn, c);
		ft_putchar((nb % 10) + 48, cn);
	}
}

int	handle_zero_spaces(int a, int b, char c, int *cn)
{
	int		i;

	i = 0;
	while (a > b)
	{
		i++;
		ft_putchar(c, cn);
		a--;
	}
	i = i + b;
	return (i);
}

void	ft_putnbr_original(long long  n, int *cn, t_list *pt)
{
	if (pt->placeholder == 'p')
		ft_handle_precision(n, cn, pt->wd, pt);
	if (pt->placeholder != 'p')
	{
		if (pt->hash && (pt->placeholder == 'x' || pt->placeholder == 'X'))
			hash_flag(n, cn, pt);
		if (pt->placeholder != 'u' || pt->placeholder != 'x' || pt->placeholder != 'X')
			single_flag(n, cn, pt);
		if (pt->per && !pt->minus && !pt->width && !pt->hash)
			single_flag_per(n, pt->pwd, cn,pt);
	if (pt->minus)
		ft_minus_combinations(n, cn, pt);
	if (pt->width)
		ft_width_combinations(n, cn, pt);
	}
}

void	ft_putnbr(long long n, char *str, int *cn, t_list *pt)
{
	if (pt->status || pt->placeholder == 's' || pt->placeholder == 'c' || pt->placeholder == '%')
	{
		get_values(n, str, pt);
		if (pt->placeholder == '%')
			ft_percentage(pt,cn);
		if (pt->placeholder != 's' && pt->placeholder != 'c' && pt->placeholder != '%')
			ft_putnbr_original(n, cn, pt);
		else if (pt->placeholder == 's' || pt->placeholder == 'c')
			ft_putstrb(pt->str,pt,cn);
	}
	else
	{
			if ((n < 0 && pt->placeholder != 'u')) 
					ft_putchar('-', cn);
			ft_printnb(n, cn,pt->placeholder);
	}
}
