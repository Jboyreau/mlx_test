#ifndef TEST_H
	#define TEST_H
	#include <sys/types.h> //man open.
	#include <sys/stat.h> //man open.
	#include <fcntl.h> //man open.
	#include <X11/keysym.h> //values of all available symboles.
	#include <unistd.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include "mlx.h"
//string
	#define STR_SIZE 1000
//cursor
	#define CURSOR_SPEED 0.4
	#define CURSOR_SIZE 10
//camera
	#define FOCAL_DISTANCE 5
//screenSpace
	#define HEIGHT 900
	#define WIDTH 1600
	#define SHEIGHT HEIGHT / 2
	#define SWIDTH WIDTH / 2
	#define BACKGROUND_COLOR 0x00ffffff //TRGB
	#define COLOR_BUFFER_SIZE WIDTH * HEIGHT
//input
	#define KEYSIZE 65536

/*Parsing*/
	typedef struct	s_file
	{
		int fd;
		int modelSize;
		int readBytes;
		int readSize;
		int strSize;
		int offset;
		int lines;
		int columns;
		char *str;
	}	t_file;

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
	typedef struct s_coordinate2
	{	
		int c;
		int l;
	} t_coord;
	typedef struct s_vec2
	{	
		float x;
		float y;
	} t_vec2;
	typedef struct s_vec3
	{
		char	isEmpty;
		float	x;
		float	y;
		float	z;
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
		char 			str[STR_SIZE];
		t_vec3			*model;
		float 			*zBuffer;
		t_vec2			mouse_coord;
		t_camera		*camera;
		t_screenSpace	*screenSpace;
		void 			*mlx;
		void 			*mlx_win;
		void			*img;

	} t_scene;

//0_parsing.c
	void parsing(char *path, t_scene *scene);
//0_house_keeping.c
	int houseKeeping(t_data *img);

//0_init.c
	void initCamera(t_camera *camera);
	void initScreenSpace(t_screenSpace *screenSpace, t_data *img);
	void initScene(t_scene *scene, t_data *img, t_camera *camera, t_screenSpace *screenSpace);

//1_input.c
	void ft_input(t_scene *scene);

//2_update_position.c
	void updateCursor(t_vec2 *vec, char *keysState, void *mlx);

//3_draw.c
	void clear(t_scene *scene);
	void drawSquare(t_scene *scene , int size, t_vec2 cursor);
#endif 
