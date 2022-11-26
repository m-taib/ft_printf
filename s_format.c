/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_format.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:29:32 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/26 19:08:31 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_substr(char const *s, unsigned int start, size_t len, int *cn)
{
	while (s[start] && start < len)
	{
		ft_putchar(s[start], cn);
		start++;
	}
}
void	ft_putstrb(char *str, t_list *pt, int *cn)
{

	if (pt->placeholder == 's' || pt->placeholder == 'c')
	{
		if (pt->per && !pt->minus && !pt->width && pt->placeholder == 's')
		{
			if (pt->pwd >= ft_strlen(str, pt))
				ft_putstr(str, cn);
			else
			{
				ft_substr(str, 0, pt->pwd, cn);
			}
		}
		if (pt->per && !pt->minus && !pt->width && pt->placeholder == 'c')
		{
			if (!pt->pwd)
				ft_putchar(str[0], cn);
		}
		if (pt->minus)
		{
			if (pt->per && pt->placeholder == 's')
			{
				if (pt->pwd >= ft_strlen(str, pt))
				{
					ft_putstr(str, cn);
					handle_zero_spaces(pt->wd, ft_strlen(str, pt), ' ', cn);
				}
				else
				{
					ft_substr(str, 0, pt->pwd, cn);
					handle_zero_spaces(pt->wd, pt->pwd, ' ', cn);
				}
			}
			else
			{
				if (pt->placeholder == 's')
					ft_putstr(str, cn);
				else
					ft_putchar(str[0], cn);
				handle_zero_spaces(pt->wd, ft_strlen(str, pt), ' ', cn);
			}
		}
		if (pt->width)
		{
			if (pt->per && pt->placeholder == 's')
			{
				if (pt->pwd >= ft_strlen(str, pt))
				{
					handle_zero_spaces(pt->wd, ft_strlen(str, pt), ' ', cn);
					ft_putstr(str, cn);
				}
				else
				{
					handle_zero_spaces(pt->wd, pt->pwd, ' ', cn);
					ft_substr(str, 0, pt->pwd, cn);
				}
			}
			else
			{
				handle_zero_spaces(pt->wd, ft_strlen(str, pt), ' ', cn);
				if (pt->placeholder == 's')
					ft_putstr(str, cn);
				else
					ft_putchar(str[0], cn);
			}
		}
	}
}
