#ifndef TEST_H
#define TEST_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"

#define HIGHT 1080 
#define WIDTH 1920
#define BACKGROUND_COLOR 0x00ff0000

typedef struct	s_data {
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_data;

void ft_input(void);
int close_window(int keycode, void *param);

#endif 
