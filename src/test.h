#ifndef TEST_H
	#define TEST_H
	#include <math.h> //cos(); sin().
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
	#define ZMIN 2
	#define ZMAX 1000
	#define REF_MODEF_DEPTH 100
	#define X 0
	#define Y 0
	#define FOCAL_DISTANCE 5
	#define STEP 0.4
	#define ROTATION_MODEL_STEP 0.01
	#define ROTATION_CAMERA_STEP 0.01
//screenSpace
	#define HEIGHT 900
	#define WIDTH 1600
	#define SHEIGHT HEIGHT / 2
	#define SWIDTH WIDTH / 2
	#define ZOOM 800
	#define ZOOM_STEP 10
	#define DEFAULT_VECTOR_COLOR 0x00000000
	#define BACKGROUND_COLOR 0x00ffffff //TRGB
	#define COLOR_BUFFER_SIZE WIDTH * HEIGHT
//input
	#define KEYSIZE 65537

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
	
	typedef struct s_vec2Int
	{	
		int x;
		int y;
	} t_vec2Int;
	typedef struct s_vec2
	{	
		float x;
		float y;
	} t_vec2;
	typedef struct s_vec3
	{
		char	isEmpty;
		int		color;
		float	x;
		float	y;
		float	z;
	} t_vec3;
	typedef struct s_biVec3
	{
		t_vec3	a;
		t_vec3	b;
	} t_biVec3;
	typedef struct s_camera
	{
		int		biVecSize;
		int		modelSize;
		int		modelWidth;
		int		modelHeight;
		float	step;
		float	zoom;
		t_vec2	rotations;
		t_vec3	translations;
		t_vec3	modelRotations;
		float	focalDistance;
		t_vec3	*model;
		t_biVec3	*modelT;//buffer which contains the model with all the linear translations applied.
	} t_camera;

/*Screen Space*/
	typedef struct s_screenSpace
	{
		int		xOffset;
		int		yOffset;
		int		*colorBuffer;
		float	*zBuffer;//Depth Buffer.
		t_vec2	cursor;
	} t_screenSpace;

/*Scene*/
	typedef struct s_scene
	{
		char			keysState[KEYSIZE];
		char 			str[STR_SIZE];
		t_vec2Int		mouse_coord;
		t_camera		*camera;
		t_screenSpace	*screenSpace;
		void 			*mlx;
		void 			*mlx_win;
		void			*img;
	} t_scene;

//0_parsing.c
	void parsing(char *path, t_camera *camera, t_screenSpace *screenSpace);
//0_house_keeping.c
	int houseKeeping(t_data *img);

//0_init.c
	void initCamera(t_camera *camera);
	void initScreenSpace(t_screenSpace *screenSpace, t_data *img);
	void initScene(t_scene *scene, t_data *img, t_camera *camera, t_screenSpace *screenSpace);

//1_input.c
	void ft_input(t_scene *scene);

//2_update_position.c
	void updateCursor(t_vec2 *vec, char *keysState);
	void translateScaleModel(t_vec3 *translations, char *keysState, float *zoom, float step);
	void updateModelRotations(t_vec3 *angles, char *keysState);

//3_draw.c
	void clear(t_scene *scene);
	void drawSquare(t_scene *scene , int size, t_vec2 cursor);
	void project(t_camera *camera, t_screenSpace *screenSpace, t_scene *scene, int i);
	void projectIso(t_camera *camera, t_screenSpace *screenSpace, t_scene *scene, int i);
#endif 
