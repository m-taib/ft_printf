/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:02:44 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/22 15:05:57 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return ((void *)(str));
}
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*libft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
int	ft_strlenr(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putcharr(char c, int *ptr)
{
	write(1, &c, 1);
	*ptr = *ptr + 1;
	;
}
void	ft_putstrr(char *str, int *ptr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putcharr(str[i], ptr);
		i++;
	}
}

void	ft_putnbrr(int n, char c, int *ptr)
{
	unsigned int	nb;

	nb = n;
	if (c != 'u')
	{
		if (n < 0)
		{
			ft_putcharr('-', ptr);
			nb = n * -1;
		}
	}
	if (nb / 10)
		ft_putnbrr(nb / 10, c, ptr);
	ft_putcharr((nb % 10) + 48, ptr);
}
void	hexr(unsigned int nb, char c, int *ptr)
{
	char	arr[16];

	arr[16] = "0123456789abcdef";
	if (nb / 16)
		hexr(nb / 16, c, ptr);
	if (c == 'x')
		ft_putcharr(arr[nb % 16], ptr);
	else
	{
		if (arr[nb % 16] >= '0' && arr[nb % 16] <= '9')
			ft_putcharr(arr[nb % 16], ptr);
		else
			ft_putcharr(arr[nb % 16] - 32, ptr);
	}
}
void	hexlongr(unsigned long nb, int *ptr)
{
	char	arr[16];

	arr[16] = "0123456789abcdef";
	if (nb / 16)
		hexlongr(nb / 16, ptr);
	ft_putcharr(arr[nb % 16], ptr);
}

void	hexvaluer(void *pt, int *ptr)
{
	ft_putcharr('0', ptr);
	ft_putcharr('x', ptr);
	hexlongr((unsigned long)pt, ptr);
}

void	placeholderr(char c, int *ptr, va_list args)
{
	char	*str;

	if (c == 'c')
		ft_putcharr(va_arg(args, int), ptr);
	if (c == 's')
	{
		str = va_arg(args, char *);
		if (!str)
			str = "(null)";
		ft_putstrr(str, ptr);
	}
	if (c == 'd' || c == 'i')
		ft_putnbrr(va_arg(args, int), c, ptr);
	if (c == 'u')
		ft_putnbrr(va_arg(args, unsigned int), c, ptr);
	if (c == 'x' || c == 'X')
		hexr(va_arg(args, int), c, ptr);
	if (c == 'p')
		hexvaluer(va_arg(args, void *), ptr);
	if (c == '%')
		ft_putcharr('%', ptr);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		cn;

	//t_list	*data;
	//data = libft_calloc(1, sizeof(t_list));
	va_start(args, str);
	cn = 0;
	i = 0;
	while (i < ft_strlenr(str))
	{
		if (str[i] != '%')
			ft_putcharr(str[i], &cn);
		else
		{
			i++;
			placeholderr(str[i], &cn, args);
		}
		i++;
	}
	va_end(args);
	return (cn);
}
