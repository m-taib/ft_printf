/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:14:25 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/25 20:26:51 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_per_width(long long n, int *cn, t_list *pt)
{
	if (pt->pwd <= nlen(n, pt->placeholder))
	{
		if ((pt->plus && n >= 0) || n < 0)
			pt->wd--;
		handle_zero_spaces(pt->wd, nlen(n, pt->placeholder), ' ', cn);
		if (pt->plus && n >= 0)
			ft_putchar('+', cn);
		if (n < 0 && pt->placeholder != 'u')
			ft_putchar('-', cn);
	}
	if (pt->pwd > nlen(n, pt->placeholder))
	{
		if ((pt->plus && n >= 0) || n < 0)
			pt->wd--;
		handle_zero_spaces(pt->wd, pt->pwd, ' ', cn);
		if (pt->plus && n >= 0)
			ft_putchar('+', cn);
		if (n < 0 && pt->placeholder != 'u')
			ft_putchar('-', cn);
		handle_zero_spaces(pt->pwd, nlen(n, pt->placeholder), '0', cn);
	}
	if (n > 0 || (n < 0 && pt->placeholder != 'u'))
		ft_printnb(n, cn, pt->placeholder);
}
void	ft_plus_width(long long n, int *cn, t_list *pt)
{
	if (n >= 0)
		pt->wd--;
	handle_zero_spaces(pt->wd, nlen(n, pt->placeholder), ' ', cn);
	if (n >= 0)
		ft_putchar('+', cn);
	ft_printnb(n, cn, pt->placeholder);
}
void	ft_only_width(long long n, int *cn, t_list *pt)
{
	if (n < 0 && pt->placeholder != 'u')
		pt->wd--;
	if (pt->wd > 1 && n == 0)
		handle_zero_spaces(pt->wd, 1, ' ', cn);
	else if (pt->wd > 1)
		handle_zero_spaces(pt->wd, nlen(n, pt->placeholder), ' ', cn);
	if (n < 0 && pt->placeholder != 'u')
		ft_putchar('-', cn);
	ft_printnb(n, cn, pt->placeholder);
}
void	ft_width_combinations(long long n, int *cn, t_list *pt)
{
	if (pt->per || (pt->plus && n >= 0) || pt->zero || pt->hash)
	{
		if ((pt->zero && !pt->per) || pt->hash)
			ft_zero_width_hash(n, cn,  pt);
		if (!pt->hash)
		{
			if (pt->per)
				ft_per_width(n, cn, pt);
			if (!pt->per && pt->plus && !pt->zero)
				ft_plus_width(n, cn, pt);
		}
	}
	else
		ft_only_width(n, cn, pt);
}
void	ft_minus_combinations(long long n, int *cn, t_list *pt)
{
	if (pt->per || ((pt->space || pt->plus) && n >= 0))
		ft_per_space_plus(n, cn, pt);
	else
	{
		if (n < 0)
		{
			pt->wd--;
			ft_putchar('-', cn);
		}
		ft_minus_x(n, cn,  pt);
	}
}
