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
		printf("Problem in the import of the sphere\n");
		return (EXIT_FAILURE);		
	}
	add_object_to_scene(s, sp);
	return(EXIT_SUCCESS);
}

int rt_import_color(char *param, t_vec3 *vec)
{
	char	**nums;
	int		i;

	if (ft_strchr(param, '.') != NULL)
		return (EXIT_FAILURE);
	nums = ft_split(param, ',');
	
	for (size_t i = 0; nums[i]; i++)
	{
		printf("This is inside import_color: %s\n", nums[i]);
	}
	
	
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
	printf("In rt_import_float %s\n", param);
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
	{
		ft_str_to_float(nums[i], &vec->e[i]);
		printf("Inside the import_vec3 function: [%i] %f\n", i, vec->e[i]);
	}
	return(return_and_free_array(EXIT_SUCCESS, nums));
}

int rt_importer_params(char **params, t_scene *s)
{
	if (ft_strncmp(params[0], "sp", 2) == 0)
		return(rt_import_sphere(&params[1], s));
	return (EXIT_FAILURE);
}

void rt_extension_check(char *argv[])
{
	const char *ext;

	ext = ft_strrchr(argv[1],'.');
	if (!ext || ft_strncmp(ext, ".rt",3) != 0)
		exit (EXIT_FAILURE); // TODO: Error Handler
}
