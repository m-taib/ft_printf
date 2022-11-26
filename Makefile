SRC = ft_printf.c  printf_op.c ft_printf_utils0.c s_format.c \
	  percentage.c ft_printf_utils.c ft_printf_utils00.c ft_printf_utils000.c ft_printf_utils2.c ft_printf_utils3.c \
	  ft_printf_utils4.c

OBJ = $(SRC:.c=.o)

BOBJ = $(BSRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a

AR = ar -rcs

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $@ $^

bonus : fclean all

%.o:%.c
	cc -c $(CFLAGS)  $< 

clean :
	@rm -f *.o
fclean :  
	@rm -f *.o  $(NAME)
re :fclean all

.PHONY : all clean fclean re bonus
