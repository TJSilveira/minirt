#include "../includes/minirt.h"

void add_object_to_scene(t_scene *s, t_object *obj)
{
	if (s->count > s->capacity)
		exit(1); // TODO: Add error handling function
	printf("Count of the object: %li\n", s->count);
	s->objects[s->count] = obj;
	s->count += 1;
}

void create_scene(char *argv[], t_engine *e)
{
	int		fd;
	char	*buffer;
	char	**params;
	
	e->scene.objects = malloc(sizeof(t_object*) * MAX_OBJECTS);
	e->scene.capacity = MAX_OBJECTS;
	e->scene.count = 0;

	fd = open(argv[1], O_RDONLY);
	buffer = get_next_line(fd, TO_USE);
	while (buffer)
	{
		params = rt_file_parser(buffer);
		rt_importer_params(params,&e->scene);
		free(buffer);
		buffer = NULL;
		buffer = get_next_line(fd, TO_USE);
	}
}
