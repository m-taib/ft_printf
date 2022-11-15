/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_format.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:26:26 by mtaib             #+#    #+#             */
/*   Updated: 2022/11/10 15:29:28 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		arb;
	int		res;
	arb = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
				|| str[i] == '\t' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			arb *= -1;
	res = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * arb);
}

int		nlen(long int n)
{
	int		c;
	if (n == 0)
		return (0);
	c = 0;
	if (n < 0)
	{
		n *= -1;
		//c++;
	}
	if (n ==0)
		c++;
	while(n)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

void ft_printnb(int n,int *cn)
{
	unsigned int 	nb;
	nb = n;
	//if(c!='u')
	//{
		if (n < 0)
		{
			nb = n * -1;
		}
	//}
	if (nb / 10)
		ft_printnb(nb/10,cn);
	ft_putchar((nb % 10) + 48,cn);

}
int handle_zero_spaces(int a,int b,char c,int *cn)
{
	int	i;
	i = 0;
	while (a > b)
	{
		i++;
		ft_putchar(c,cn);
        	a--;
	}
	i = i + b;
	return (i);
}

void ft_space_plus(char *c,int n,int *cn,int *i)
{
	if (n >= 0)
       		ft_putchar(c[0],cn);
        ft_printnb(n,cn);
        handle_zero_spaces(i[2],i[0],c[1],cn);
}

void single_flag(int n, int *cn, t_list *pt)
{
	if (pt->space && !pt->width && !pt->per && !pt->minus && !pt->plus && n >= 0)
        {
                ft_putchar(' ',cn);
                ft_printnb(n,cn);
        }
	if (pt->plus && !pt->width && !pt->per && !pt->minus && !pt->space && n >= 0)
        {
                ft_putchar('+',cn);
                ft_printnb(n,cn);
        }
	if ((pt->space || pt->plus) && !pt->width && !pt->per && !pt->minus && n < 0)
	{
		ft_putchar('-',cn);
		ft_printnb(n,cn);
	}
}
void ft_putnbr_original(int n,int pwd,int *cn,int wd,t_list *pt)
{
	int		i[3];
	single_flag(n, cn, pt);
	
	if (pt->per && !pt->minus && !pt->width)
	{
                 if (pwd > nlen(n))
                         {
			      if (n < 0)
				      ft_putchar('-',cn);
			      if (n == 0 && pwd > 1)
				      handle_zero_spaces(pwd,1,'0',cn);
			      if (n > 0 || n < 0)
			      		handle_zero_spaces(pwd,nlen(n),'0',cn);
                              ft_printnb(n,cn);
                         }
                  else if (pwd <= nlen(n))
                   {

                                        if (n < 0)
					{
						ft_putchar('-',cn);
						ft_printnb(n,cn);
					}
                                        if (n > 0)
						ft_printnb(n,cn);
                   }


	}
	if (pt->minus)
	{
		if (pt->per || ((pt->space || pt->plus) && n >= 0))
		{
			i[0] = nlen(n);
			i[2] = wd;
			if (pt->per)
			{
				if (pt->space && n >= 0)
					ft_putchar(' ',cn);
				if (pt->plus && n >= 0)
					ft_putchar('+',cn);
				if (n < 0)
					ft_putchar('-',cn);
				if (pwd > nlen(n))
				{
					i[1] = pwd;
					i[1] = handle_zero_spaces(pwd,nlen(n),'0',cn);
                       			if (n > 0 || n < 0)
						ft_printnb(n,cn);
					if (n < 0)
						i[1]++;
					i[2] = wd;
					handle_zero_spaces(i[2],i[1],' ',cn);
				}
				else if (pwd <= nlen(n))
				{
					if (n < 0)
                                                i[0]++;
                                        i[2] = wd;
                       			if (n > 0 || n < 0)
						ft_printnb(n,cn);
                                        handle_zero_spaces(i[2],i[0],' ',cn);
				}
			}
			if (!pt->per && !pt->space && pt->plus)
				ft_space_plus("+ ",n,cn,i);
			if (!pt->per && pt->space && !pt->plus)
				ft_space_plus("  ",n,cn,i);
		}
		else
		{
			if (n < 0)
			{
				wd--;
				ft_putchar('-',cn);
			}
                        ft_printnb(n,cn);
			if (wd > 1)
			{
				if (n == 0)
					handle_zero_spaces(wd,1,' ',cn);
				else
					handle_zero_spaces(wd,nlen(n),' ',cn);
			}
		}

	}
	if (pt->width)
	{
		if (pt->per || (pt->plus && n >= 0) || pt->zero)
		{
			if (pt->zero && !pt->per)
                	{
                        	if (pt->plus && n >=0)
                        	{
                                	ft_putchar('+',cn);
                                	wd--;
                       		 }
                        	if (n < 0)
				{
					wd--;
					ft_putchar('-',cn);
				}
				if (wd >= 1)
                        	{
                                	if (n == 0)
                                        	handle_zero_spaces(wd,1,'0',cn);
                                	else
                                        	handle_zero_spaces(wd,nlen(n),'0',cn);
                        	}

                        	ft_printnb(n,cn);
                	}

			i[0] = nlen(n);
                        i[2] = wd;
			if (pt->per)
                        {
				if (pwd <= nlen(n))
				{
					i[2] = wd;
					if ((pt->plus && n >= 0) || n < 0)
						i[2]--;
					handle_zero_spaces(i[2],nlen(n),' ',cn);
                                	if (pt->plus && n >= 0)
						ft_putchar('+',cn);
					if (n < 0)
						ft_putchar('-',cn);
                                        if (n > 0 || n < 0)
						ft_printnb(n,cn);
				}
                                if (pwd > nlen(n))
                                {
                                        i[1] = pwd;
					i[2] = nlen(n);
					if ((pt->plus && n >= 0) || n < 0)
                                                wd--;
					handle_zero_spaces(wd,i[1],' ',cn);
					if (pt->plus && n >= 0)
                                                ft_putchar('+',cn);
					if (n < 0)
						ft_putchar('-',cn);
                                        handle_zero_spaces(pwd, i[2],'0',cn);
                                        if (n > 0 || n < 0)
						ft_printnb(n,cn);
                                }
			}
			if (!pt->per && pt->plus && !pt->zero)
			{
				if (n >= 0)
					wd--;
       				handle_zero_spaces(wd,i[0],' ',cn);
				if (n >= 0)
        			        ft_putchar('+',cn);
     			  	ft_printnb(n,cn);

			}
		}
	else
                {
                        if (n < 0)
                                wd--;
			if (wd > 1)
                        	handle_zero_spaces(wd,nlen(n),' ',cn);
			if (n < 0)
				ft_putchar('-',cn);
                        ft_printnb(n,cn);
                }



	}
}

int 	minus_value(t_list *pt,char *str,int n)
{
	int	mwd;
	int	i;
	i = 0;
	mwd = 0;
         if (pt->space || pt->plus)
             {
                         if (n >= 0)
                                 mwd = ft_atoi(&str[i]) - 1;
                         else
                                 mwd = ft_atoi(&str[i]);
            }
         else
              mwd = ft_atoi(&str[i]);
	return (mwd);

}

void	ft_putnbr(int n,char *str,int *cn,t_list *pt)
{
	int		pwd;
	int		wd;
	int		i;
	i = 0;
	pwd = 0;
	wd = 0;
	if (pt->status)
	{
		if (pt->width || pt->zero)
			wd = ft_atoi(&str[i]);
		if (pt->minus)
			wd = minus_value(pt,str,n);
		
		if (pt->per)
		{
			while(str[i] && str[i] != '.')
				i++;
			if (str[i])
				pwd = ft_atoi(&str[i+1]);
		}
		ft_putnbr_original(n,pwd,cn,wd,pt);
	}
	else
	{
		if (n < 0)
			ft_putchar('-',cn);
		ft_printnb(n,cn);
	}
}
