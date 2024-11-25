#include "test.h"

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
			printf("\tchar = %c, ", *((*file).str + i));
			++((*file).modelSize);
			printf("modelSize = %d\n", (*file).modelSize);
			++len;
			while (*((*file).str + i) >= '0' && *((*file).str + i) <= '9' || *((*file).str + i) == '-')
				++i;
		}
		while (*((*file).str + i) != ' ' && *((*file).str + i) != '\n' && *((*file).str + i))
				++i;
		while (*((*file).str + i) == ' ')
				++i;
	}
	printf("lines = %d, longestColumn = %d, modelSize = %d\n", (*file).lines, (*file).columns, (*file).modelSize);
}

char increaseVector(t_file *file)
{
	char *strTmp;

	(*file).strSize = ((*file).strSize + (*file).readSize) << 1;
	strTmp = malloc((*file).strSize * sizeof(char));
	if (strTmp == NULL)
		return 1;
	(*file).readSize <<= 1;
	for (int i = 0; i < (*file).strSize; ++i)
		*(strTmp + i) = 0;
	for (int i = 0; i < (*file).offset; ++i)
		*(strTmp + i) = *((*file).str + i);
	free((*file).str);
	(*file).str = strTmp;	
	return 0;
}

t_vec3* parsing(char *path)
{
	t_vec3* model = NULL;
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
		return (write(2, "NULL path.\n", 11), NULL);
	file.fd = open(path, O_RDONLY);
	if (file.fd == -1)
		return NULL;
	file.str = malloc(file.strSize * sizeof(char));
	if (file.str == NULL)
		return (write(2, "malloc failed.\n", 15), NULL);
	file.readBytes = read(file.fd, file.str, file.readSize);
	file.offset += file.readBytes; 
	while (file.readBytes > 0)
	{
		if (file.offset + file.readSize > file.strSize)
			if (increaseVector(&file))
				return (write(2, "malloc failed.\n", 15) , NULL);
		file.readBytes = read(file.fd, file.str + file.offset, file.readSize);
		file.offset += file.readBytes; 
	}
printf("%s\n", file.str);
	getModelSize(&file);
	//TODO: model = populate3dSpace(&file);
	free(file.str);
	return (model);
}
