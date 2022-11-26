/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:13:56 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/25 20:24:09 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_precision(long long n, int *cn, int wd, t_list *pt)
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

void	hash_flag(long long n, int *cn, t_list *pt)
{
	if (pt->per && pt->hash && !pt->width && !pt->minus && !pt->zero)
	{
		pt->i[0] = nlen(n, pt->placeholder);
		if (n != 0)
			print_hex(pt, cn);
		handle_zero_spaces(pt->pwd, pt->i[0], '0', cn);
		hex(n, pt->placeholder, cn);
	}
	if (!pt->width && !pt->minus && !pt->zero && !pt->per)
	{
		if (n != 0)
			print_hex(pt, cn);
		hex(n, pt->placeholder, cn);
	}
}

void	ft_per_space_plus(long long n, int *cn, t_list *pt)
{
	pt->i[0] = nlen(n, pt->placeholder);
	pt->i[2] = pt->wd;
	if (pt->per)
	{
		if (pt->placeholder == 'd' || pt->placeholder == 'i')
		{
			if (pt->space)
				ft_putchar(' ', cn);
			if (pt->plus)
				ft_putchar('+', cn);
			if (n < 0 && pt->placeholder != 'u')
				ft_putchar('-', cn);
		}
		ft_per_minus(n, pt, cn);
	}
	if (!pt->per && !pt->space && pt->plus && pt->placeholder != 'u')
		ft_space_plus("+ ", n, cn, pt);
	if (!pt->per && pt->space && !pt->plus && pt->placeholder != 'u')
		ft_space_plus("  ", n, cn, pt);
}

void	ft_minus_x(long long n, int *cn, t_list *pt)
{
	if (pt->placeholder == 'x' || pt->placeholder == 'X')
		if (n != 0 && pt->hash)
			print_hex(pt, cn);
	ft_printnb(n, cn, pt->placeholder);
	if (pt->wd > 1)
	{
		if (n == 0)
			handle_zero_spaces(pt->wd, 1, ' ', cn);
		else
		{
			if (!(n < 0 && pt->placeholder == 'u'))
			{
				if (pt->placeholder == 'x' || pt->placeholder == 'X')
				{
					if (pt->hash)
						pt->i[0] = nlen(n, pt->placeholder) + 2;
					else
						pt->i[0] = nlen(n, pt->placeholder);
					handle_zero_spaces(pt->wd, pt->i[0], ' ', cn);
				}
			}
			if (!(pt->placeholder == 'x' || pt->placeholder == 'X'))
				handle_zero_spaces(pt->wd, nlen(n, pt->placeholder), ' ', cn);
		}
	}
}

void	ft_zero_pm(long long n, int *cn, t_list *pt)
{
	if (pt->plus && n >= 0)
	{
		ft_putchar('+', cn);
		pt->wd--;
	}
	if (n < 0 && pt->placeholder != 'u')
	{
		pt->wd--;
		ft_putchar('-', cn);
	}
	if (pt->wd >= 1)
	{
		if (n == 0)
			handle_zero_spaces(pt->wd, 1, '0', cn);
		else
			handle_zero_spaces(pt->wd, nlen(n, pt->placeholder), '0', cn);
	}
	ft_printnb(n, cn, pt->placeholder);
}

void	ft_zero_width_hash(long long n, int *cn, t_list *pt)
{
	if (!pt->hash)
		ft_zero_pm(n, cn, pt);
	else
	{
		if (pt->width || pt->zero)
		{
			pt->i[0] = nlen(n, pt->placeholder) + 2;
			if (!pt->zero)
				handle_zero_spaces(pt->wd, pt->i[0], ' ', cn);
			if (n != 0)
				print_hex(pt, cn);
			if (pt->zero)
				handle_zero_spaces(pt->wd, pt->i[0], '0', cn);
			ft_printnb(n, cn, pt->placeholder);
		}
	}
}
