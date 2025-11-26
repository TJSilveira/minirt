#include "../includes/minirt.h"

void add_object_to_scene(t_scene *s, t_object *obj)
{
	if (s->obj_count > s->obj_capacity)
		exit(1); // TODO: Add error handling function
	s->objects[s->obj_count] = obj;
	s->obj_count += 1;
}

void add_light_to_scene(t_scene *s, t_light *light)
{
	if (s->l_count > s->l_capacity)
		exit(1); // TODO: Add error handling function
	s->lights[s->l_count] = light;
	s->l_capacity += 1;
}

void create_scene(char *argv[], t_engine *e)
{
	int		fd;
	char	*buffer;
	char	**params;
	
	e->scene.objects = ft_calloc(sizeof(t_object*), MAX_OBJECTS);
	e->scene.lights = ft_calloc(sizeof(t_light*), MAX_OBJECTS);
	e->scene.obj_capacity = MAX_OBJECTS;
	e->scene.obj_count = 0;
	e->scene.l_capacity = MAX_OBJECTS;
	e->scene.l_count = 0;

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
