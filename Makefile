NAME = lem-in

FLAGS =  -Wall -Wextra -Werror -o

SRCS =	src/main.c src/links.c src/read_ants.c src/freeing.c\
		src/rooms.c src/reading.c src/special.c src/clearing_map.c\
		src/algo.c src/going.c src/creating_queue.c src/bonus.c 

OBJ=$(SRCS:.c=.o)

all: $(NAME)
	
$(NAME) : $(OBJ)
	make -C libft/
	make -C ft_printf/libft/
	make -C ft_printf/
	gcc $(FLAGS) $(NAME) $(SRCS) -I /bin/ -L./libft -lft -L./ft_printf -lftprintf
clean:
	make -C libft/ fclean
	make -C ft_printf/ fclean
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re norm
.NOTPARALLEL: all clean fclean re norm

norm:
	norminette *.c *.h
