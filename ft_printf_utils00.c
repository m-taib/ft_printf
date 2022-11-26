/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils00.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:46:41 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/25 17:47:12 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *str, int *ptr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i], ptr);
		i++;
	}
}

void	hex(unsigned int nb, char c, int *ptr)
{
	char	*arr;

	arr = "0123456789abcdef";
	if (nb / 16)
		hex(nb / 16, c, ptr);
	if (c == 'x')
		ft_putchar(arr[nb % 16], ptr);
	else
	{
		if (arr[nb % 16] >= '0' && arr[nb % 16] <= '9')
			ft_putchar(arr[nb % 16], ptr);
		else
			ft_putchar(arr[nb % 16] - 32, ptr);
	}
}

void	skip(char *str, int *i, char c)
{
	while (!(str[*i + 1] >= '0' && str[*i + 1] <= '9') && str[*i + 1] == c)
		*i = *i + 1;
}

int	check_status(t_list *pt)
{
	if (pt->minus || pt->zero || pt->per || pt->dec || pt->width || pt->space
		|| pt->plus || pt->hash)
		return (1);
	return (0);
}

void	hexlong(unsigned long nb, int *ptr)
{
	char	*arr;

	arr = "0123456789abcdef";
	if (nb / 16)
		hexlong(nb / 16, ptr);
	ft_putchar(arr[nb % 16], ptr);
}
