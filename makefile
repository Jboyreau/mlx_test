NAME=mlx_test
OBJ=0_main.o 0_house_keeping.o 1_input.o 2_update_position.o 3_draw.o
MLX=libmlx_Linux.a 
CFLAGS=-lXext -lX11 -lm -lz -L. libmlx_Linux.a
CPPFLAGS=-Wall -Wextra -Werror -g3 

all: $(NAME)
$(NAME) :$(MLX) $(OBJ)
	cc $(OBJ) $(CFLAGS) -o mlx_test
clean:
	rm -f *.o
	rm $(NAME)
fclean: clean
	rm -f fdf
re : fclean all
$(MLX):
	./configure
#############
## PATERNS ##
#############
#$@: Nom de la regle
#$<: Nom de la premiere dépendance
#$^: Nom de la toute les dependances
%.o: %.c
	cc $(CPPFLAGS) -c $< -o $@
.PHONY: all clean fclean re
