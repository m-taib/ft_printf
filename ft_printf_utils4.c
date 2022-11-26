/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:15:45 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/26 16:33:03 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

/*void	ft_width_combinations(long long n, int *cn, t_list *pt)
{
	if (pt->per || (pt->plus && n >= 0) || pt->zero || pt->hash)
	{
		if ((pt->zero && !pt->per) || pt->hash)
			ft_zero_width_hash(n, cn, pt);
		if (!pt->hash)
		{
			if (pt->per)
				ft_per_width(n, cn, pt);
			if (!pt->per && pt->plus && !pt->zero)
				ft_plus_width(n, cn, pt);
		}
	}
	else
		ft_only_width(n, cn,  pt);
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
		ft_minus_x(n, cn, pt);
	}
}
*/
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

void	get_values(long long n, char *str, t_list *pt)
{
	int	i;

	i = 0;
	if (pt->width || pt->zero)
	{
		if (!pt->hash || str[i + 1] != '#')
			pt->wd = ft_atoi(&str[i]);
		else
		{
			if (str[(i++) + 1] == '#')
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
