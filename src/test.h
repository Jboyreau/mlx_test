#ifndef TEST_H
	#define TEST_H
	#include <X11/keysym.h> //values of all available symboles.
	#include <unistd.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include "mlx.h"

	#define CURSOR_SPEED 0.4
	#define CURSOR_SIZE 10
	#define HEIGHT 900
	#define WIDTH 1600
	#define SHEIGHT HEIGHT / 2
	#define SWIDTH WIDTH / 2
	#define BACKGROUND_COLOR 0x00ffffff //ARGB
	#define KEYSIZE 65536

	/*House Keeping*/
	typedef struct	s_data
	{
		void	*mlx;
		void	*mlx_win;
		void	*img;
		int		*addr;
		int		bits_per_pixel;
		int		line_length;
		int		endian;
	} t_data;

	/*Camera/Model Space*/
	typedef struct s_vec2
	{	
		float x;
		float y;
	} t_vec2;

	typedef struct s_vec3
	{
		float x;
		float y;
		float z;
	} t_vec3;

	typedef struct s_camera
	{
		t_vec2 rotations;
		t_vec3 translations;
		float focalDistance;
	} t_camera;

	/*Screen Space*/
	typedef struct s_screenSpace
	{
		t_vec2 cursor;
		int	*colorBuffer;
		int xOffset;
		int yOffset;
	} t_screenSpace;

	/*Scene*/
	typedef struct s_scene
	{
		char			keysState[KEYSIZE];
		char 			str[1000];
		int				x;
		int				y;
		t_camera		*camera;
		t_screenSpace	*screenSpace;
		void 			*mlx;
		void 			*mlx_win;
		void			*img;

	} t_scene;

	//0_house_keeping.c
	int houseKeeping(t_data *img);

	//1_input.c
	void ft_input(t_scene *scene);

	//2_update_position.c
	void updateCursor(t_vec2 *vec, char *keysState);

	//3_draw.c
	void clear(t_scene *scene);
	void drawSquare(t_scene *scene , int size, t_vec2 cursor);
#endif 
