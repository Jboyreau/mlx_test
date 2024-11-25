SRC_DIR=./src/
NAME=mlx_test
OBJ=$(SRC_DIR)0_main.o $(SRC_DIR)0_parsing.c $(SRC_DIR)0_house_keeping.o $(SRC_DIR)0_init.o $(SRC_DIR)1_input.o $(SRC_DIR)2_update_position.o $(SRC_DIR)3_draw.o
MLX=libmlx_Linux.a 
CFLAGS=-lXext -lX11 -lm -lz -L. libmlx_Linux.a
CPPFLAGS=-Wall -Wextra -Werror -g3 

all: $(NAME)
$(NAME) :$(MLX) $(OBJ)
	cc $(OBJ) $(CFLAGS) -o $(NAME)
clean:	
	rm -f $(SRC_DIR)*.o
	rm $(NAME)
re : clean all

$(MLX):
	git clone https://github.com/42Paris/minilibx-linux.git mlx_temp
	cp -r mlx_temp/* .
	rm -rf mlx_temp
	cp ./mlx.h ./src/mlx.h
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
