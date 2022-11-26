/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils000.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:47:36 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/25 19:35:59 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	hexvalue(void *pt, int *ptr)
{
	ft_putchar('0', ptr);
	ft_putchar('x', ptr);
	hexlong((unsigned long)pt, ptr);
}

int	ft_check_ph(char c)
{
	if (c == 'd' || c == 'i' || c == 'c' || c == 's' || c == 'x'
		|| c == 'X' || c == 'p' || c == '%' || c == 'u')
		return (0);
	return (1);
}

void	reset(t_list *pt)
{
	pt->status = 0;
	pt->minus = 0;
	pt->zero = 0;
	pt->per = 0;
	pt->dec = 0;
	pt->width = 0;
	pt->space = 0;
	pt->plus = 0;
	pt->placeholder = '\0';
	pt->pwd = 0;
	pt->wd = 0;
	pt->hash = 0;
}
