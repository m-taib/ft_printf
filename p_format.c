/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_format.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:26:26 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/19 16:55:00 by mtaib            ###   ########.fr       */
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
	if (n < 0)
	{
		nb = n;
		while (nb)
		{
			nb = nb / base;
			cn++;
		}
		if (c == 'p')
			cn += 2;
		return (cn);
	}
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
	if (c == 'p')
		cn += 2;
	return (cn);
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
			{
				nb = n * -1;
			}
		}
		if (nb / 10)
			ft_printnb(nb / 10, cn, c);
		ft_putchar((nb % 10) + 48, cn);
	}
}
int	handle_zero_spaces(int a, int b, char c, int *cn)
{
	int	i;

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

void	ft_space_plus(char *c, int n, int *cn, t_list *pt)
{
	if (n >= 0)
		ft_putchar(c[0], cn);
	ft_printnb(n, cn, pt->placeholder);
	handle_zero_spaces(pt->i[2], pt->i[0], c[1], cn);
}

void	single_flag(int n, int *cn, t_list *pt)
{
	if (pt->space && !pt->width && !pt->per && !pt->minus && !pt->plus
		&& n >= 0)
	{
		ft_putchar(' ', cn);
		ft_printnb(n, cn, pt->placeholder);
	}
	if (pt->plus && !pt->width && !pt->per && !pt->minus && !pt->space
		&& n >= 0)
	{
		ft_putchar('+', cn);
		ft_printnb(n, cn, pt->placeholder);
	}
	if ((pt->space || pt->plus) && !pt->width && !pt->per && !pt->minus
		&& n < 0)
	{
		ft_putchar('-', cn);
		ft_printnb(n, cn, pt->placeholder);
	}
}
void	single_flag_per(long long n, int pwd, int *cn, t_list *pt)
{
	if (pwd > nlen(n, pt->placeholder))
	{
		if (n < 0 && pt->placeholder != 'u')
			ft_putchar('-', cn);
		if (n > 0 || (n < 0 && pt->placeholder != 'u'))
			handle_zero_spaces(pwd, nlen(n, pt->placeholder), '0', cn);
		if (n == 0 && pwd > 1)
			handle_zero_spaces(pwd, 1, '0', cn);
		ft_printnb(n, cn, pt->placeholder);
	}
	else if (pwd <= nlen(n, pt->placeholder))
	{
		if (n < 0 && pt->placeholder != 'u')
		{
			ft_putchar('-', cn);
			ft_printnb(n, cn, pt->placeholder);
		}
		if (n > 0)
			ft_printnb(n, cn, pt->placeholder);
	}
}
void	ft_per_minus(long long n, t_list *pt, int *cn)
{
	int	i[3];

	i[0] = nlen(n, pt->placeholder);
	if (pt->placeholder == 'x' || pt->placeholder == 'X')
		print_hex(pt, cn);
	;
	if (pt->pwd > i[0])
	{
		i[1] = pt->pwd;
		i[1] = handle_zero_spaces(pt->pwd, i[0], '0', cn);
		if (n > 0 || n < 0)
			ft_printnb(n, cn, pt->placeholder);
		if (n < 0 && pt->placeholder != 'u')
			i[1]++;
		i[2] = pt->wd;
		if (pt->placeholder == 'x' || pt->placeholder == 'X')
			i[1] = i[1] + 2;
		handle_zero_spaces(i[2], i[1], ' ', cn);
	}
	else if (pt->pwd <= nlen(n, pt->placeholder))
	{
		if (n < 0)
			i[0]++;
		i[2] = pt->wd;
		if (n > 0 || (n < 0 && pt->placeholder != 'u'))
			ft_printnb(n, cn, pt->placeholder);
		if (pt->placeholder == 'x' || pt->placeholder == 'X')
			i[0] = i[0] + 2;
		handle_zero_spaces(i[2], i[0], ' ', cn);
	}
}

void	print_hex(t_list *pt, int *cn)
{
	if (pt->placeholder == 'x')
		ft_putstr("0x", cn);
	else
		ft_putstr("0X", cn);
	//hex(n, pt->placeholder, cn);
}
void	ft_putnbr_original(long long n, int pwd, int *cn, int wd, t_list *pt)
{
	pwd = 0;
	if (pt->placeholder == 'p')
	{
		if (pt->width)
		{
			handle_zero_spaces(wd, nlen(n, pt->placeholder), ' ', cn);
			ft_putstr("0x", cn);
			hexlong(n, cn);
		}
		if (pt->minus)
		{
			ft_putstr("0x", cn);
			hexlong(n, cn);
			handle_zero_spaces(wd, nlen(n, pt->placeholder), ' ', cn);
		}
	}
}

void	minus_value(t_list *pt, char *str, int n)
{
	int	i;

	i = 0;
	if ((pt->space || pt->plus) && pt->placeholder != 'u')
	{
		if (n >= 0)
			pt->wd = ft_atoi(&str[i]) - 1;
		else if (n < 0 && pt->placeholder != 'u')
			pt->wd = ft_atoi(&str[i]);
	}
	else
		pt->wd = ft_atoi(&str[i]);
}

void	ft_putnbr(unsigned long long n, char *str, int *cn, t_list *pt)
{
	int	i;

	i = 0;
	if (pt->status)
	{
		if (pt->width || pt->zero)
		{
			if (!pt->hash || str[i + 1] != '#')
				pt->wd = ft_atoi(&str[i]);
			else
			{
				if (str[i + 1] == '#')
				{
					i++;
					while (str[i] == '#' && str[i])
						i++;
					pt->wd = ft_atoi(&str[i]);
				}
			}
		}
		if (pt->minus)
			/*pt->wd==*/minus_value(pt, str, n);
		if (pt->per)
		{
			while (str[i] && str[i] != '.')
				i++;
			if (str[i])
				pt->pwd = ft_atoi(&str[i + 1]);
		}
		ft_putnbr_original(n, pt->pwd, cn, pt->wd, pt);
	}
	else
	{
		if (pt->placeholder != 'p')
		{
			if (n < 0 && pt->placeholder != 'u')
				ft_putchar('-', cn);
			ft_printnb(n, cn, pt->placeholder);
		}
		else
		{
			ft_putstr("0x", cn);
			hexlong(n, cn);
		}
	}
}
