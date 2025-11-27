#include "../includes/minirt.h"

char **rt_file_parser(char* buffer)
{
	char	**res;
	int		len;

	len = ft_strlen(buffer);
	if (len == 1 && buffer[0] == '\n')
		return (NULL);
	if (len > 0 && buffer[len - 1] == '\n')
		buffer[len - 1] = 0;
	res = ft_split(buffer, ' ');
	return(res);
}

int rt_import_sphere(char **params, t_scene *s)
{
	int			i;
	t_object	*sp;
	
	i = -1;
	sp = malloc(sizeof(t_object));
	while (params[++i]);
	if (i != NUM_PARAM_SPHERE)
		return (EXIT_FAILURE);
	if (rt_import_vec3(params[0], &sp->sphere.center) == EXIT_FAILURE ||
		rt_import_float(params[1], &sp->sphere.ray) == EXIT_FAILURE ||
		rt_import_color(params[2], &sp->sphere.color) == EXIT_FAILURE)
	{
		free(sp);
		return (EXIT_FAILURE);		
	}
	sp->id = id_sphere;
	add_object_to_scene(s, sp);
	return(EXIT_SUCCESS);
}

int rt_import_plane(char **params, t_scene *s)
{
	int			i;
	t_object	*pl;
	
	i = -1;
	pl = malloc(sizeof(t_object));
	while (params[++i]);
	if (i != NUM_PARAM_PLANE)
		return (EXIT_FAILURE);
	if (rt_import_vec3(params[0], &pl->plane.point) == EXIT_FAILURE ||
		rt_import_vec3(params[1], &pl->plane.normal) == EXIT_FAILURE ||
		rt_import_color(params[2], &pl->plane.color) == EXIT_FAILURE)
	{
		free(pl);
		return (EXIT_FAILURE);		
	}
	pl->id = id_plane;
	unit_vec3(&pl->plane.normal);
	add_object_to_scene(s, pl);
	return(EXIT_SUCCESS);
}

int rt_import_light(char **params, t_scene *s)
{
	int		i;
	t_light	*l;
	
	i = -1;
	l = malloc(sizeof(t_light));
	while (params[++i]);
	if (i != NUM_PARAM_LIGHT)
		return (EXIT_FAILURE);
	if (rt_import_vec3(params[0], &l->center) == EXIT_FAILURE ||
		rt_import_float(params[1], &l->brightness) == EXIT_FAILURE ||
		rt_import_color(params[2], &l->color) == EXIT_FAILURE)
	{
		free(l);
		return (EXIT_FAILURE);
	}
	add_light_to_scene(s, l);
	return(EXIT_SUCCESS);
}

int rt_import_ambient(char **params, t_scene *s)
{
	int		i;
	
	if (s->amb.has_ambient == 1)
		return (EXIT_FAILURE);
	i = -1;
	while (params[++i]);
	if (i != NUM_PARAM_AMBIENT)
		return (EXIT_FAILURE);
	if (rt_import_float(params[0], &s->amb.intensity) == EXIT_FAILURE ||
		rt_import_color(params[1], &s->amb.color) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	s->amb.has_ambient = 1;
	return(EXIT_SUCCESS);
}

int rt_import_color(char *param, t_vec3 *vec)
{
	char	**nums;
	int		i;

	if (ft_strchr(param, '.') != NULL)
		return (EXIT_FAILURE);
	nums = ft_split(param, ',');
	if (!(nums && nums[0] && nums[1] && nums [2] && !nums[3]))
		return(return_and_free_array(EXIT_FAILURE, nums));
	i = -1;
	while (++i < 3)
	{
		if(is_int_color(nums[i]) == FALSE)
			return(return_and_free_array(EXIT_FAILURE, nums));
	}	
	i = -1;
	while (nums[++i])
		ft_str_to_float(nums[i], &vec->e[i]);
	vec3_div_const(vec, MAX_INT_COLOR);
	return(return_and_free_array(EXIT_SUCCESS, nums));
}

int	rt_import_float(char *param, float *result)
{
	if (is_float(param) == FALSE)
		return (EXIT_FAILURE);
	ft_str_to_float(param, result);
	return (EXIT_SUCCESS);
}

int rt_import_vec3 (char *param, t_vec3 *vec)
{
	char	**nums;
	int		i;

	nums = ft_split(param, ',');
	if (!(nums && nums[0] && nums[1] && nums [2] && !nums[3]))
		return(return_and_free_array(EXIT_FAILURE, nums));
	i = -1;
	while (++i < 3)
	{
		if(is_float(nums[i]) == FALSE)
			return(return_and_free_array(EXIT_FAILURE, nums));
	}	
	i = -1;
	while (nums[++i])
		ft_str_to_float(nums[i], &vec->e[i]);
	return(return_and_free_array(EXIT_SUCCESS, nums));
}

int rt_importer_params(char **params, t_scene *s)
{
	if (ft_strncmp(params[0], "sp", 2) == 0 && ft_strlen(params[0]) == 2)
		return(rt_import_sphere(&params[1], s));
	if (ft_strncmp(params[0], "pl", 2) == 0 && ft_strlen(params[0]) == 2)
		return(rt_import_plane(&params[1], s));
	if (ft_strncmp(params[0], "L", 1) == 0 && ft_strlen(params[0]) == 1)
		return(rt_import_light(&params[1], s));
	if (ft_strncmp(params[0], "A", 1) == 0 && ft_strlen(params[0]) == 1)
		return(rt_import_ambient(&params[1], s));
	return (EXIT_FAILURE);
}

void rt_extension_check(char *argv[])
{
	const char *ext;

	ext = ft_strrchr(argv[1],'.');
	if (!ext || ft_strncmp(ext, ".rt",3) != 0)
		exit (EXIT_FAILURE); // TODO: Error Handler
}
