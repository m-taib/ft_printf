/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percentage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:51:27 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/26 19:42:28 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_percentage(t_list *pt,int *cn)
{
	if (pt->width)
	{
		if (pt->wd > 1)
		{
			if (pt->zero)
				handle_zero_spaces(pt->wd, 1, '0', cn);
			else
				handle_zero_spaces(pt->wd, 1, ' ', cn);
		}
		ft_putchar('%',cn);
	}
	if (pt->minus)
	{
		ft_putchar('%',cn);
		if (pt->wd > 1)
			handle_zero_spaces(pt->wd, 1, ' ', cn);
	}
}
