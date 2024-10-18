NAME=mlx_test
OBJ=0_main.o 1_input.o 
CFLAGS=-lXext -lX11 -lm -lz -L. libmlx_Linux.a
CPPFLAGS=-Wall -Wextra -Werror 

all: $(NAME)
$(NAME) : $(OBJ)
	cc $(OBJ) $(CFLAGS) -o mlx_test
clean:
	rm -f *.o
	rm $(NAME)
fclean: clean
	rm -f fdf
re : fclean all

#############
## PATERNS ##
#############
#$@: Nom de la regle
#$<: Nom de la premiere dépendance
#$^: Nom de la toute les dependances
%.o: %.c
	cc $(CPPFLAGS) -c $< -o $@
.PHONY: all clean fclean re
