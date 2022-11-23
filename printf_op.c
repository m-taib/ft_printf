/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:26:26 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/23 13:22:38 by mtaib            ###   ########.fr       */
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

int	nlen(long long n,char c)
{
	int	cn;
	int base;
	unsigned long long nb;
	nb = 0;
	base = 10;
	cn = 0;
	if (c == 'x' || c == 'X' || c == 'p')
		base = 16;
	if (c == 'p')
	{
		nb  = n;
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

void	ft_printnb(int n, int *cn,char c)
{
	unsigned int	nb;

	nb = n;
	if (c == 'x' || c == 'X')
		hex(nb, c, cn);
	else
	{

		if(c !='u')
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
	ft_printnb(n, cn,pt->placeholder);
	handle_zero_spaces(pt->i[2], pt->i[0], c[1], cn);
}

void	single_flag(int n, int *cn, t_list *pt)
{
	if (pt->space && !pt->width && !pt->per && !pt->minus && !pt->plus
		&& n >= 0)
	{
		ft_putchar(' ', cn);
		ft_printnb(n, cn,pt->placeholder);
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
void	single_flag_per(long long n, int pwd, int *cn,t_list *pt)
{
	if (pwd > nlen(n,pt->placeholder))
	{
		if (n < 0 && pt->placeholder != 'u')
			ft_putchar('-', cn);
		if (n > 0 || (n < 0 && pt->placeholder != 'u'))
			handle_zero_spaces(pwd, nlen(n,pt->placeholder), '0', cn);
		if (n == 0 && pwd > 1)
			handle_zero_spaces(pwd, 1, '0', cn);
		ft_printnb(n, cn, pt->placeholder);
	}
	else if (pwd <= nlen(n,pt->placeholder))
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

	i[0] = nlen(n,pt->placeholder);
	if ((pt->placeholder == 'x' || pt->placeholder == 'X') && pt->hash)
		print_hex(pt,cn);;
	if (pt->pwd > i[0])
	{
		i[1] = pt->pwd;
		i[1] = handle_zero_spaces(pt->pwd, i[0], '0', cn);
		if (n > 0 || n < 0)
			ft_printnb(n, cn, pt->placeholder);
		if (n < 0 && pt->placeholder != 'u')
			i[1]++;
		i[2] = pt->wd;
		if ((pt->placeholder == 'x' || pt->placeholder == 'X') && pt->hash)
			i[1] = i[1] + 2; 
		handle_zero_spaces(i[2], i[1], ' ', cn);
	}
	else if (pt->pwd <= nlen(n,pt->placeholder))
	{
		if (n < 0)
			i[0]++;
		i[2] = pt->wd;
		if (n > 0 || (n < 0 && pt->placeholder != 'u'))
			ft_printnb(n, cn, pt->placeholder);
		if ((pt->placeholder == 'x' || pt->placeholder == 'X') && pt->hash)
			i[0] = i[0] + 2;
		handle_zero_spaces(i[2], i[0], ' ', cn);
	}
}

void 	print_hex(t_list *pt,int *cn)
{
	if (pt->placeholder == 'x')
		ft_putstr("0x",cn);
	else
		ft_putstr("0X",cn);
	//hex(n, pt->placeholder, cn);
}
void	ft_handle_precision(long long  n, int *cn, int wd, t_list *pt)
{
		if (pt->width)
		{
			handle_zero_spaces(wd, nlen(n,pt->placeholder), ' ', cn);
			ft_putstr("0x",cn);
			hexlong(n, cn);
		}
		if (pt->minus)
		{
			ft_putstr("0x",cn);
			hexlong(n, cn);
			handle_zero_spaces(wd, nlen(n,pt->placeholder), ' ', cn);
		}
}
void	hash_flag(long long  n, int *cn, t_list *pt)
{
		if (pt->per && pt->hash && !pt->width && !pt->minus && !pt->zero)
		{
			pt->i[0] = nlen(n,pt->placeholder);
			if (n != 0)
				print_hex(pt,cn);
			handle_zero_spaces(pt->pwd, pt->i[0], '0', cn);
			hex(n, pt->placeholder, cn);
		}
		if (!pt->width && !pt->minus && !pt->zero && !pt->per)
		{
			if (n != 0)
				print_hex(pt,cn);
			hex(n, pt->placeholder, cn);
		}	
}
void	ft_per_space_plus(long long  n, int *cn, int wd, t_list *pt)
{
			pt->i[0] = nlen(n,pt->placeholder);
			pt->i[2] = wd;
			if (pt->per)
			{
				if (pt->placeholder == 'd' || pt->placeholder == 'i')
				{
					if (pt->space)
						ft_putchar(' ', cn);
					if (pt->plus)
						ft_putchar('+', cn);
					if (n < 0  && pt->placeholder != 'u')
						ft_putchar('-', cn);
				}
				ft_per_minus(n, pt, cn);
			}
			if (!pt->per && !pt->space && pt->plus  && pt->placeholder != 'u')
				ft_space_plus("+ ", n, cn, pt);
			if (!pt->per && pt->space && !pt->plus  && pt->placeholder != 'u')
				ft_space_plus("  ", n, cn, pt);	
}
void	ft_minus_x(long long  n, int *cn, int wd, t_list *pt)
{
			if (pt->placeholder == 'x' || pt->placeholder == 'X')
				if (n != 0 && pt->hash)
					print_hex(pt,cn);
			ft_printnb(n, cn, pt->placeholder);
			if (wd > 1)
			{
				if (n == 0)
					handle_zero_spaces(wd, 1, ' ', cn);
				else
				{
					if ((!(n < 0 && pt->placeholder == 'u')) || (pt->placeholder == 'x' || pt->placeholder == 'X'))
					{
						if (pt->hash)
							pt->i[0] = nlen(n,pt->placeholder) + 2;
						else
							pt->i[0] = nlen(n,pt->placeholder);
						handle_zero_spaces(wd, pt->i[0], ' ', cn);
					}
					if (!(pt->placeholder == 'x' || pt->placeholder == 'X'))
						handle_zero_spaces(wd, nlen(n,pt->placeholder), ' ', cn);
				}
			}
}
void	ft_putnbr_original(long long  n, int pwd, int *cn, int wd, t_list *pt)
{
	if (pt->placeholder == 'p')
		ft_handle_precision(n, cn, wd, pt);
	if (pt->placeholder != 'p')
	{
		if (pt->hash && (pt->placeholder == 'x' || pt->placeholder == 'X'))
			hash_flag(n, cn, pt);
		if (pt->placeholder != 'u' || pt->placeholder != 'x' || pt->placeholder != 'X')
			single_flag(n, cn, pt);
		if (pt->per && !pt->minus && !pt->width && !pt->hash)
			single_flag_per(n, pwd, cn,pt);
	if (pt->minus)
	{
		if (pt->per || ((pt->space || pt->plus) && n >= 0))
			ft_per_space_plus(n, cn, wd, pt);
		else
		{
			if (n < 0)
			{
				wd--;
				ft_putchar('-', cn);
			}
			//ft_minus_x(n, cn, wd, pt);
			if (pt->placeholder == 'x' || pt->placeholder == 'X')
			{
				if (n != 0 && pt->hash)
					print_hex(pt,cn);
			}
			ft_printnb(n, cn, pt->placeholder);
			if (wd > 1)
			{
				if (n == 0)
					handle_zero_spaces(wd, 1, ' ', cn);
				else 
				{
					if (!(n < 0 && pt->placeholder == 'u'))
					{
						if (pt->placeholder == 'x' || pt->placeholder == 'X')
						{
							if (pt->hash)
								pt->i[0] = nlen(n,pt->placeholder) + 2;
							else
								pt->i[0] = nlen(n,pt->placeholder);
							handle_zero_spaces(wd, pt->i[0], ' ', cn);
						}
					}
					if (!(pt->placeholder == 'x' || pt->placeholder == 'X'))
					{
						pt->i[0] = nlen(n,pt->placeholder);
						handle_zero_spaces(wd, pt->i[0], ' ', cn);
					}
				}
			}
		}
	}
	if (pt->width)
	{
		if (pt->per || (pt->plus && n >= 0) || pt->zero || pt->hash)
		{
			if ((pt->zero && !pt->per) || pt->hash)
			{
				if (!pt->hash)
				{
					if (pt->plus && n >= 0)
					{
						ft_putchar('+', cn);
						wd--;
					}
					if (n < 0  && pt->placeholder != 'u')
					{
						wd--;
						ft_putchar('-', cn);
					}
					if (wd >= 1)
					{
						if (n == 0)
							handle_zero_spaces(wd, 1, '0', cn);
						else
							handle_zero_spaces(wd, nlen(n,pt->placeholder), '0', cn);
					}
					ft_printnb(n, cn,pt->placeholder);
				}
				else 
				{
					if ((pt->width || pt->zero) && !pt->per)
					{
						pt->i[0] = nlen(n,pt->placeholder) + 2;
						if (!pt->zero)
							handle_zero_spaces(wd, pt->i[0], ' ', cn);
						if (n != 0)
							print_hex(pt,cn);
						if (pt->zero)
							handle_zero_spaces(wd, pt->i[0], '0', cn);
						ft_printnb(n, cn,pt->placeholder);
					}
					if (pt->width && pt->per)
					{
						if (pt->pwd > nlen(n,pt->placeholder))
						{
							pt->i[0] = nlen(n,pt->placeholder) + 2 + (pwd - nlen(n,pt->placeholder));
							handle_zero_spaces(wd, pt->i[0], ' ', cn);
							pt->i[0] = nlen(n,pt->placeholder) + 2;
						}
						else
						{
							pt->i[0] = nlen(n,pt->placeholder) + 2;
							handle_zero_spaces(wd, pt->i[0], ' ', cn);

						}
						if (n != 0)
							print_hex(pt,cn);
						handle_zero_spaces(pt->pwd, nlen(n,pt->placeholder), '0', cn);
						ft_printnb(n, cn,pt->placeholder);
						
					}
				}
			}
			if (!pt->hash)
			{
			pt->i[0] = nlen(n,pt->placeholder);
			pt->i[2] = wd;
			if (pt->per)
			{
				if (pwd <= nlen(n,pt->placeholder))
				{
					pt->i[2] = wd;
					if ((pt->plus && n >= 0) || n < 0)
						pt->i[2]--;
					handle_zero_spaces(pt->i[2], nlen(n,pt->placeholder), ' ', cn);
					if (pt->plus && n >= 0)
						ft_putchar('+', cn);
					if (n < 0  && pt->placeholder != 'u')
						ft_putchar('-', cn);
					if (n > 0 || (n < 0  && pt->placeholder != 'u'))
						ft_printnb(n, cn,pt->placeholder);
				}
				if (pwd > nlen(n,pt->placeholder))
				{
					pt->i[1] = pwd;
					pt->i[2] = nlen(n,pt->placeholder);
					if ((pt->plus && n >= 0) || n < 0)
						wd--;
					handle_zero_spaces(wd, pt->i[1], ' ', cn);
					if (pt->plus && n >= 0)
						ft_putchar('+', cn);
					if (n < 0  && pt->placeholder != 'u')
						ft_putchar('-', cn);
					handle_zero_spaces(pwd, pt->i[2], '0', cn);
					if (n > 0 || (n < 0  && pt->placeholder != 'u'))
						ft_printnb(n, cn,pt->placeholder);
				}
			}
			
			if (!pt->per && pt->plus && !pt->zero)
			{
				if (n >= 0)
					wd--;
				handle_zero_spaces(wd, pt->i[0], ' ', cn);
				if (n >= 0)
					ft_putchar('+', cn);
				ft_printnb(n, cn,pt->placeholder);
			}
			}
		}
		else
		{
			if (n < 0  && pt->placeholder != 'u')
				wd--;
			if (wd > 1 && n == 0)
			{
				//if (n == 0)
					handle_zero_spaces(wd, 1, ' ', cn);
			}
			
			else if (wd > 1)
					handle_zero_spaces(wd, nlen(n,pt->placeholder), ' ', cn);
			if (n < 0  && pt->placeholder != 'u')
					ft_putchar('-', cn);
			ft_printnb(n, cn,pt->placeholder);
		}
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
		else if ( n < 0 && pt->placeholder != 'u')
			pt->wd = ft_atoi(&str[i]);
	}
	else
		pt->wd = ft_atoi(&str[i]);
}

void	get_values(long long n, char *str, t_list *pt)
{
	int		i;

	i = 0;
	if (pt->width || pt->zero)
	{
		if (!pt->hash || str[i+1] != '#')
			pt->wd = ft_atoi(&str[i]);
		else
		{
			if (str[(i++)+1] == '#')
				while (str[i] == '#' && str[i])
					i++;
			pt->wd = ft_atoi(&str[i]);
		}
	}
	if (pt->minus)
		minus_value(pt, str, n);
	if (pt->per)
	{
			while (str[i] && str[i] != '.')
				i++;
			pt->pwd = ft_atoi(&str[i + 1]);
	}
}
void	ft_putnbr(long long n, char *str, int *cn, t_list *pt)
{
	if (pt->status || pt->placeholder == 's' || pt->placeholder == 'c')
	{
		get_values(n, str, pt);
		if (pt->placeholder != 's' && pt->placeholder != 'c')
			ft_putnbr_original(n, pt->pwd, cn, pt->wd, pt);
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
