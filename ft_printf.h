#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
typedef struct t_list
{
	int		status;
	int		minus;
	int		zero;
	int		per;
	int		dec;
	int		width;
	int		space;
	int		plus;
	int		hash;
	char	placeholder;
	int		pwd;
	int		wd;
	int		i[3];
	char	*str;
	char	st[2];
}	t_list;
void    ft_percentage(t_list *pt,int *cn);
int ft_printf(const char *str, ...);
void	ft_substr(char const *s, unsigned int start, size_t len, int *cn);
void    ft_putstrb(char *str, t_list *pt, int *cn);
void    placeholder2(char *st, int *ptr, va_list args, t_list *pt);
void    placeholder(char *st, int *ptr, va_list args, t_list *pt);
int scan_flags(char *str, int i, t_list *pt);
void    ft_scan(char *str, t_list *data, int *i, int *f);
void    *ft_memset(void *b, int c, size_t len);
void    ft_bzero(void *s, size_t n);
void    *libft_calloc(size_t count, size_t size);
int ft_strlen(const char *str, t_list *pt);
void    ft_putchar(char c, int *ptr);
void    ft_putstr(char *str, int *ptr);
void    hex(unsigned int nb, char c, int *ptr);
void    skip(char *str, int *i, char c);
int check_status(t_list *pt);
void    hexlong(unsigned long nb, int *ptr);
void    hexvalue(void *pt, int *ptr);
int ft_check_ph(char c);
void    reset(t_list *pt);
//printf op
int ft_atoi(const char *str);
int decimal_len(long long n, char c, int base);
int nlen(long long n, char c);
void    ft_printnb(int n, int *cn, char c);
int handle_zero_spaces(int a, int b, char c, int *cn);
void    ft_space_plus(char *c, int n, int *cn, t_list *pt);
void    single_flag(int n, int *cn, t_list *pt);
void    single_flag_per(long long n, int pwd, int *cn, t_list *pt);
void    ft_per_minus(long long n, t_list *pt, int *cn);
void    print_hex(t_list *pt, int *cn);
void    ft_handle_precision(long long  n, int *cn, int wd, t_list *pt);
void    hash_flag(long long  n, int *cn, t_list *pt);
void    ft_per_space_plus(long long  n, int *cn, t_list *pt);
void    ft_minus_x(long long  n, int *cn, t_list *pt);
void    ft_zero_pm(long long  n, int *cn, t_list *pt);
void    ft_zero_width_hash(long long  n, int *cn, t_list *pt);
void    ft_per_width(long long  n, int *cn, t_list *pt);
void    ft_plus_width(long long  n, int *cn, t_list *pt);
void    ft_only_width(long long  n, int *cn, t_list *pt);
void    ft_width_combinations(long long  n, int *cn,  t_list *pt);
void    ft_minus_combinations(long long  n, int *cn, t_list *pt);
void    ft_putnbr_original(long long  n, int *cn, t_list *pt);
void    minus_value(t_list *pt, char *str, int n);
void    get_values(long long n, char *str, t_list *pt);
void    ft_putnbr(long long n, char *str, int *cn, t_list *pt);

//
#endif
