#include "../includes/minirt.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->pix_bits / 8));
	*(unsigned int *)dst = color;
}

void	render(t_engine *e)
{
	t_pixel			p;
	unsigned int	clr_uint;
	int				w;

	p.x = 0;
	w = e->img.line_len / 4;
	while (p.x < w)
	{
		p.y = 0;
		while (p.y < (int)e->win_h)
		{
			p.clr = init_vec3(0, 0, 0);
			get_pixel_color_anti_alaising_rt(e, &p);
			clr_uint = t_color3_to_uint(p.clr);
			my_mlx_pixel_put(&e->img, p.x, p.y, clr_uint);
			p.y += 1;
		}
		p.x += 1;
	}
}

void	get_pixel_color_anti_alaising_rt(t_engine *e, t_pixel *p)
{
	t_ray		r;
	t_point3	curr_sample;
	int			i;
	int			j;

	p->top_left = calculate_pixel_top_left(&e->cam, p->x, p->y);
	i = 0;
	while (i < RAY_SAMPLE_SIDE_SIZE)
	{
		j = 0;
		while (j < RAY_SAMPLE_SIDE_SIZE)
		{
			curr_sample = get_sample_location(e, p, i, j);
			init_ray(&r, e, &curr_sample);
            p->clr = vec3_add_2inst_copy(p->clr, vec3_div_const_copy(ray_tracer(&r, e), RAY_SAMPLE_SIDE_SIZE * RAY_SAMPLE_SIDE_SIZE));
			j++;
		}
		i++;
	}
}

t_point3	get_sample_location(t_engine *e, t_pixel *p, int i, int j)
{
	t_point3	pixel_sample_delta;
	t_point3	curr_sample;
	float		x;
	float		y;

	x = (RAY_SAMPLE_PADDING + i * (1.0 - 2.0 * RAY_SAMPLE_PADDING) / (RAY_SAMPLE_SIDE_SIZE - 1.0)) * vec3_get_x(&e->cam.pixel_delta_right);
	y = (RAY_SAMPLE_PADDING + j * (1.0 - 2.0 * RAY_SAMPLE_PADDING) / (RAY_SAMPLE_SIDE_SIZE - 1.0)) * vec3_get_y(&e->cam.pixel_delta_down);
	pixel_sample_delta = init_vec3(x, y, 0.0);
	curr_sample = vec3_add_2inst_copy(p->top_left, pixel_sample_delta);
	return (curr_sample);
}

void init_ray(t_ray *ray, t_engine *e, t_point3 *dir_point)
{
	t_vec3		ray_direction;

	ray_direction = vec3_sub_2inst_copy(*dir_point, e->cam.camera_center);
	ray->dir = ray_direction;
	ray->orig = e->cam.camera_center;
	ray->itv.min = 0.0;
	ray->itv.max = TMAX;
}

void	init_img(t_engine *e)
{
	e->img.img = mlx_new_image(e->mlx, e->win_w, e->win_h);
	if (!e->img.img)
	{
		ft_putstr_fd("Error: Failed to create image\n", 2);
		// TODO cleanup_engine(e);
		exit(EXIT_FAILURE);
	}
	e->img.addr = mlx_get_data_addr(e->img.img, &e->img.pix_bits,
			&e->img.line_len, &e->img.endian);
}

void	init_engine(char *argv[], t_engine *e)
{
	char	*header;
    float	aspect_ratio;

	header = "\"E foi o Eder que os comeu\" - Luis Vaz de Camoes, 1986";
	e->mlx = mlx_init();
	e->win_w = IMAGE_WIDTH;
	aspect_ratio = 16.0 / 9.0;
	e->win_h = (int)(e->win_w/aspect_ratio);
	e->window = mlx_new_window(e->mlx, e->win_w, e->win_h, header);
	init_img(e);
	init_camera(e);
	create_scene(argv, e);
	print_scene(e);
	render(e);
}

void	print_scene(t_engine *e)
{
	print_scene_ambient(e);
	print_scene_lights(e);
	print_scene_objects(e);
}

void	print_scene_ambient(t_engine *e)
{
	if (e->scene.amb.has_ambient)
	{
		printf("[Ambient Color]\n");
		printf("Ambient Color:");
		print_vec3(&e->scene.amb.color);
		printf("Ambient Intensity: %f\n",e->scene.amb.intensity);
	}
	else
		printf("No Ambient light loaded\n");
}

void	print_scene_lights(t_engine *e)
{
	int	i;

	i = -1;
	if (e->scene.l_count == 0)
		printf("No Lights loaded\n");
	else
		printf("[%li Lights loaded]\n", e->scene.l_count);
	while (e->scene.lights[++i])
	{
		printf("[%i] Brightness: %f\n", i, e->scene.lights[i]->brightness);
		printf("[%i] Color:\n", i);
		print_vec3(&e->scene.lights[i]->color);
		printf("[%i] Center:\n", i);
		print_vec3(&e->scene.lights[i]->center);
		printf("\n");
	}
}

void	print_scene_objects(t_engine *e)
{
	int	i;

	i = -1;
	printf("[Objects]\n");
	while (e->scene.objects[++i])
	{
		print_scene_sphere(e->scene.objects[i]);
		print_scene_plane(e->scene.objects[i]);
	}
}

void	print_scene_sphere(t_object *obj)
{
	if (obj->id == id_sphere)
	{
		printf("[SPHERE]\n");
		printf("Color:\n");
		print_vec3(&obj->sphere.color);
		printf("Center:\n");
		print_vec3(&obj->sphere.center);
		printf("Ray: %f\n", obj->sphere.ray);
		printf("\n");
	}
}

void	print_scene_plane(t_object *obj)
{
	if (obj->id == id_plane)
	{
		printf("[PLANE]\n");
		printf("Color:\n");
		print_vec3(&obj->plane.color);
		printf("Normal:\n");
		print_vec3(&obj->plane.normal);
		printf("Point:\n");
		print_vec3(&obj->plane.point);
		printf("\n");
	}
}
