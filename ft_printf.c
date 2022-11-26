/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:37:09 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/26 19:33:22 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	placeholder2(char *st, int *ptr, va_list args, t_list *pt)
{
	if (pt->placeholder == 'c')
	{
		if (pt->status)
		{
			pt->st[0] = va_arg(args, int);
			pt->st[1] = 0;
			pt->str = pt->st;
			ft_putnbr(0, st, ptr, pt);
		}
		else
			ft_putchar(va_arg(args, int), ptr);
	}
	if (pt->placeholder == 's')
	{
		pt->str = va_arg(args, char *);
		if (!pt->str)
			pt->str = "(null)";
		if (pt->status)
			ft_putnbr(0, st, ptr, pt);
		else
			ft_putstr(pt->str, ptr);
	}
}

void	placeholder(char *st, int *ptr, va_list args, t_list *pt)
{
	if (pt->placeholder == 'd' || pt->placeholder == 'i')
		ft_putnbr(va_arg(args, int), st, ptr, pt);
	if (pt->placeholder == 'u')
		ft_putnbr(va_arg(args, unsigned int), st, ptr, pt);
	if (pt->placeholder == 'x' || pt->placeholder == 'X')
		ft_putnbr((long long)va_arg(args, unsigned int), st, ptr, pt);
	if (pt->placeholder == 'p')
	{
		if (pt->status)
			ft_putnbr((unsigned long)va_arg(args, void *), st, ptr, pt);
		else
			hexvalue(va_arg(args, void *), ptr);
	}
	if (pt->placeholder == '%')
	{
		if (!pt->status)
			ft_putchar('%', ptr);
		else
			ft_putnbr(0, st, ptr, pt);
	}
	placeholder2(st, ptr, args, pt);
	reset(pt);
}

int	scan_flags(char *str, int i, t_list *pt)
{
	while (str[i] && ft_check_ph(str[i]))
	{
		if (str[i] == '-')
			pt->minus = 1;
		if ((str[i] >= '0' && str[i] <= '9') && !pt->minus && str[i - 1] != '.')
			pt->width = 1;
		if (str[i] == '.')
			pt->per = 1;
		if (str[i] == '0' && (!pt->minus || !pt->per) && !(str[i - 1] >= '1'
				&& str[i - 1] <= '9'))
			pt->zero = 1;
		if (str[i] == ' ' && !pt->width)
			pt->space = 1;
		if (pt->width && pt->space)
			pt->space = 0;
		if (str[i] == '+' && !pt->space)
			pt->plus = 1;
		if (str[i] == '#')
			pt->hash = 1;
		i++;
	}
	if (str[i] && !ft_check_ph(str[i]))
		pt->placeholder = str[i];
	pt->status = check_status(pt);
	return (i);
}

void	ft_scan(char *str, t_list *data, int *i, int *f)
{
	*f = scan_flags(str, *i, data);
	if (check_status(data))
	{
		while (!(str[*i] >= '0' && str[*i] <= '9') && str[*i] && str[*i] != '.'
			&& ft_check_ph(str[*i]) == 1)
		{
			skip(str, i, str[*i]);
			*i = *i + 1;
		}
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_list	*data;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	data = libft_calloc(1, sizeof(t_list));
	va_start(args, str);
	while (str[i[0]])
	{
		if (str[i[0]] != '%')
			ft_putchar(str[i[0]], &i[2]);
		else
		{
			i[0]++;
			ft_scan((char *)str, data, &i[0], &i[1]);
			data->placeholder = str[i[1]];
			placeholder((char *)(str + i[0]), &i[2], args, data);
			i[0] = i[1];
		}
		i[0]++;
	}
	free(data);
	return (va_end(args), i[2]);
}
/*int main()
{
	int b;
	//b = -10;
	//ft_printf("%+30.20d||\n",b);
	//b = -4200;
	//printf(" % s ", "-");
	//ft_printf("% s\n", "hello");
	//printf("% s", "hello");
	ft_printf("We %-s what we %8s||\n", "do", "must");
	//ft_printf("%-3c||\n", '\0');
	//ft_printf("%9x||\n", (unsigned int)3735929054);
	//printf("%9x||", (unsigned int)3735929054);
	//printf("%-3c||", '\0');
}*/
/*#include <stdio.h>
int	main(void):se
{
	ft_printf("This %p is even stranger", (void *)-1);
	printf("This %p is even stranger", (void *)-1);
}*/
/*int main()
{
	char c = 'a';
	char *s = "string";
	int i = -132454845;
	int x = 1213432;
	int x2 = 0;
	unsigned int u = 2147483649;
	int amp = 12;
	int n;
	char *sc = "";
	int	*ptr;

	int ret = 0;
	int ret2 = 0;


	write(1,"\n|____MANDATORY____|\n",21);

	//char test
	write(1,"\n|%c basic test|\n",17);

	ret = printf("printf c:%cl\n", c);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf c:%cl\n", c);
	ft_printf("ft_printf num:%i\n", ret2);

	ret = printf("printf 2 c:%c, %cl\n", c, c);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 c:%c, %cl\n", c, c);
	ft_printf("ft_printf num:%i\n", ret2);

	write(1,"\n|%% basic test|\n",17);

	ret = printf("printf %%:%%l\n");
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf %%:%%l\n");
	ft_printf("ft_printf num:%i\n", ret2);

	ret = printf("printf 2 %%:%%, \n");
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 %%:%%, \n");
	ft_printf("ft_printf num:%i\n", ret2);

	//integer test
	write(1,"\n|%i basic test|\n",17);

	ret = printf("printf i:%il\n", i);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf i:%il\n", i);
	ft_printf("ft_printf num:%i\n", ret2);

	ret = printf("printf 2 i:%i, %il\n", i, i);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 i:%i, %il\n", i, i);
	ft_printf("ft_printf num:%i\n", ret2);

	write(1,"\n|%d basic test|\n",17);

	ret = printf("printf d:%dl\n", i);
	printf("printf num:%d\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf d:%dl\n", i);
	ft_printf("ft_printf num:%d\n", ret2);

	ret = printf("printf 2 d:%d, %dl\n", i, i);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 d:%d, %dl\n", i, i);
	ft_printf("ft_printf num:%i\n", ret2);

	write(1,"\n|%u basic test|\n",17);

	ret = printf("printf u:%ul\n", u);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf u:%ul\n", u);
	ft_printf("ft_printf num:%i\n", ret2);

	ret = printf("printf 2 u:%u, %ul\n", u, u);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 u:%u, %ul\n", u, u);
	ft_printf("ft_printf num:%i\n", ret2);

	//str test
	write(1,"\n|%s basic test|\n",17);

	ret = printf("printf s:%sl\n", s);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf s:%sl\n", s);
	ft_printf("ft_printf num:%i\n", ret2);

	ret = printf("printf 2 s:%s, %sl\n", s, s);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 s:%s, %sl\n", s, s);
	ft_printf("ft_printf num:%i\n", ret2);

	write(1,"\n|%p basic test|\n",17);

	ret = printf("printf p:%pl\n", s);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf p:%pl\n", s);
	ft_printf("ft_printf num:%i\n", ret2);

	ret = printf("printf 2 p:%p, %pl\n", s, s);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 p:%p, %pl\n", s, s);
	ft_printf("ft_printf num:%i\n", ret2);

	//hexadecimal test
	write(1,"\n|%x basic test|\n",17);

	ret = printf("printf x:%xl\n", x);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf x:%xl\n", x);
	ft_printf("ft_printf num:%i\n", ret2);

	ret = printf("printf 2 x:%x, %xl\n", x, x);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 x:%x, %xl\n", x, x);
	ft_printf("ft_printf num:%i\n", ret2);

	write(1,"\n|%X basic test|\n",17);

	ret = printf("printf X:%Xl\n", x);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf X:%Xl\n", x);
	ft_printf("ft_printf num:%i\n", ret2);

	ret = printf("printf 2 X:%X, %Xl\n", x, x);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf 2 X:%X, %Xl\n", x, x);
	ft_printf("ft_printf num:%i\n", ret2);

	write(1,"\n|Multiple specifiers test|\n",28);

	ret = printf("printf c, %%, d, i, u, s, p, x, X:%c, %%, %d, %i, %u, %s, %p,
			%x, %Xl\n", c, i, i, u, s, s, x, x);
	printf("printf num:%i\n", ret);
	write(1, "ft_", 3);
	ret2 = ft_printf("printf c, %%, d, i, u, s, p, x, X:%c, %%, %d, %i, %u, %s,
			%p, %x, %Xl\n", c, i, i, u, s, s, x, x);
	ft_printf("ft_printf num:%i\n\n\n", ret2);


	x = 0;
	ptr = &x;

	printf("ft_printf: \n");
	i = ft_printf("Hello My Name is: %c%c%c%c%c %s and Im %d years and
			%X years in hex, My adress is %p, print %% with no argument\n",
			'A','y','m','a','n',"Bouabra",18,18,ptr);
	printf("%d\n\n", i);
	printf("printf: \n");
	i = printf("Hello My Name is: %c%c%c%c%c %s and Im %d years and
			%X years in hex, My adress is %p, print %% with no argument\n",
			'A','y','m','a','n',"Bouabra",18,18,ptr);
	printf("%d\n", i);

	return (0);
}*/
