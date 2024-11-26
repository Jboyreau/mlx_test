#include "test.h"

int ft_atoiAlt(char *str, int *i)
{
	int alt = 0;
	int sign;

	sign = 1;
	if (*(str + *i) == '-')
	{
		sign *= -1;
		(*i)++;
	}
	while (*(str + *i) >= '0' && *(str + *i) <= '9')
	{
		alt = alt * 10 + *(str + *i) - '0';
		(*i)++;
	}
	return (alt * sign);
}


void populate3dSpace(t_file *file, t_scene *scene)
{
	t_coord	sqr;
	int		i;
	int		z;
	int		x;

	(*scene).model = NULL;
	(*scene).model = malloc((*file).lines * (*file).columns * sizeof(t_vec3) + COLOR_BUFFER_SIZE * sizeof(float));
	if ((*scene).model == NULL)
		return ;
	(*scene).zBuffer = (float*)((*scene).model + (*file).lines * (*file).columns);
	z = (*file).lines / 2;
	i = 0;
	sqr.l = 0;
	sqr.c = 0;
	x = -((*file).columns / 2);
	while (i < (*file).offset)
	{
		if (*((*file).str + i) == '\n')
		{
			while (sqr.c < (*file).columns)
			{
				(*((*scene).model + sqr.l * (*file).columns + sqr.c)).isEmpty = 1;
				++(sqr.c);
			}
			--z;
			++(sqr.l);
			x = -((*file).columns / 2);
			++i;
			sqr.c = 0;
		}
		if (*((*file).str + i) >= '0' && *((*file).str + i) <= '9' || *((*file).str + i) == '-')
		{
			(*((*scene).model + sqr.l * (*file).columns + sqr.c)).y = ft_atoiAlt((*file).str, &i);
			(*((*scene).model + sqr.l * (*file).columns + sqr.c)).x = x;
			(*((*scene).model + sqr.l * (*file).columns + sqr.c)).z = z;
			(*((*scene).model + sqr.l * (*file).columns + sqr.c)).isEmpty = 0;
//Debug
printf("x = %f, y = %f, z = %f\n"
	, (*((*scene).model + sqr.l * (*file).columns + sqr.c)).x
	, (*((*scene).model + sqr.l * (*file).columns + sqr.c)).y
	, (*((*scene).model + sqr.l * (*file).columns + sqr.c)).z
);
			++x;
			++(sqr.c);
		}
		while (*((*file).str + i) != ' ' && *((*file).str + i) != '\n' && *((*file).str + i))
				++i;
		while (*((*file).str + i) == ' ')
				++i;
	}
}

void getModelSize(t_file *file)
{
	int i = 0;
	int len = 0;

	while (i < (*file).offset)
	{
		if (*((*file).str + i) == '\n')
		{
			++((*file).lines);
			++i;
			if (len > (*file).columns)
				(*file).columns = len;
			len = 0;
		}
		if (*((*file).str + i) >= '0' && *((*file).str + i) <= '9' || *((*file).str + i) == '-')
		{	
			++((*file).modelSize);
			++len;
			while (*((*file).str + i) >= '0' && *((*file).str + i) <= '9' || *((*file).str + i) == '-')
				++i;
		}
		while (*((*file).str + i) != ' ' && *((*file).str + i) != '\n' && *((*file).str + i))
				++i;
		while (*((*file).str + i) == ' ')
				++i;
	}
//DEBUG
printf("lines = %d, longestColumn = %d, modelSize = %d\n", (*file).lines, (*file).columns, (*file).modelSize);
}

char increaseVector(t_file *file)
{
	char *strTmp;

	(*file).strSize = ((*file).strSize + (*file).readSize) << 1;
	strTmp = malloc((*file).strSize * sizeof(char));
	if (strTmp == NULL)
		return (free((*file).str), 1);
	(*file).readSize <<= 1;
	for (int i = 0; i < (*file).strSize; ++i)
		*(strTmp + i) = 0;
	for (int i = 0; i < (*file).offset; ++i)
		*(strTmp + i) = *((*file).str + i);
	free((*file).str);
	(*file).str = strTmp;
	return 0;
}

void parsing(char *path, t_scene *scene)
{
	t_file file = {
		.fd = -1,
		.modelSize = 0,
		.readBytes = 0,
		.readSize = 9,
		.strSize = 10,
		.offset = 0,
		.lines = 0,
		.columns = 0,
		.str = NULL
	};
	if (path == NULL)
		return (write(2, "NULL path.\n", 11), (void)0);
	file.fd = open(path, O_RDONLY);
	if (file.fd == -1)
		return (void)0;
	file.str = malloc(file.strSize * sizeof(char));
	if (file.str == NULL)
		return (write(2, "malloc failed.\n", 15), (void)0);
	file.readBytes = read(file.fd, file.str, file.readSize);
	file.offset += file.readBytes; 
	while (file.readBytes > 0)
	{
		if (file.offset + file.readSize > file.strSize)
			if (increaseVector(&file))
				return (write(2, "malloc failed.\n", 15), (void)0);
		file.readBytes = read(file.fd, file.str + file.offset, file.readSize);
		file.offset += file.readBytes * (file.readBytes > 0); 
	}
//DEBUG
printf("%s\n", file.str);
	getModelSize(&file);
	populate3dSpace(&file, scene);
	if ((*scene).model == NULL)
		return (write(2, "malloc failed.\n", 15), free(file.str), (void)0);
	free(file.str);
}
