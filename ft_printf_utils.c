/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:27:42 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/26 16:31:43 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hex(t_list *pt, int *cn)
{
	if (pt->placeholder == 'x')
		ft_putstr("0x", cn);
	else
		ft_putstr("0X", cn);
	//hex(n, pt->placeholder, cn);
}

void	ft_space_plus(char *c, int n, int *cn, t_list *pt)
{
	if (n >= 0)
		ft_putchar(c[0], cn);
	ft_printnb(n, cn, pt->placeholder);
	handle_zero_spaces(pt->i[2], pt->i[0], c[1], cn);
}

void	ft_per_minus(long long n, t_list *pt, int *cn)
{
	int	i[3];

	i[0] = nlen(n, pt->placeholder);
	if ((pt->placeholder == 'x' || pt->placeholder == 'X') && pt->hash)
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
		if ((pt->placeholder == 'x' || pt->placeholder == 'X') && pt->hash)
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
		if ((pt->placeholder == 'x' || pt->placeholder == 'X') && pt->hash)
			i[0] = i[0] + 2;
		handle_zero_spaces(i[2], i[0], ' ', cn);
	}
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
