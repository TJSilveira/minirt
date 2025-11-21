#include "../includes/minirt.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->pix_bits / 8));
	*(unsigned int *)dst = color;
}

void	update_pixel(t_engine *e)
{
	t_pixel	p;
	int		w;

	p.x = 0;
	w = e->img.line_len / 4;
	while (p.x < w)
	{
		p.y = 0;
		while (p.y < (int)e->win_h)
		{
			p.center = calculate_pixel_center(&e->cam,p.x,p.y);
			t_vec3	ray_direction = vec3_sub_2inst_copy(p.center, e->cam.camera_center);
			ray		r;

			r.dir = &ray_direction;
			r.orig = &e->cam.camera_center;
			r.tmin = 0.0;
			r.tmax = 100.0;

            p.clr = ray_color(&r, e);
			my_mlx_pixel_put(&e->img, p.x, p.y, p.clr);
			p.y += 1;
		}
		p.x += 1;
	}
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
	printf("After creating scene\n");
	printf("Sphere 0:");
	print_vec3(&e->scene.objects[0]->sphere.center);
	printf(" %f ", e->scene.objects[0]->sphere.ray);
	print_vec3(&e->scene.objects[0]->sphere.color);
	printf("\n");
	printf("Sphere 1:");
	print_vec3(&e->scene.objects[1]->sphere.center);
	printf(" %f ", e->scene.objects[1]->sphere.ray);
	print_vec3(&e->scene.objects[1]->sphere.color);
	update_pixel(e);
}
