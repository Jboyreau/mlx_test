NAME=fdf
OBJ=0_main.o 
CFLAGS=-lmlx -lXext -lX11 -lm -L. libmlx.a
CPPFLAGS=-march=native -O3 -g3 -Wall -Wextra -Werror 

all: $(NAME)
$(NAME) : $(OBJ)
