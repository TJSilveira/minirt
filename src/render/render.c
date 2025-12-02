/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42luxembourg.l  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:52:28 by tsilveir          #+#    #+#             */
/*   Updated: 2025/12/02 14:52:30 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->pix_bits / 8));
	*(unsigned int *)dst = color;
}

void	init_img(t_engine *e)
{
	e->img.img = mlx_new_image(e->mlx, e->win_w, e->win_h);
	if (!e->img.img)
		error_handler("Failed to create mlx image\n", e);
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
	e->win_h = (int)(e->win_w / aspect_ratio);
	e->window = mlx_new_window(e->mlx, e->win_w, e->win_h, header);
	init_img(e);
	import_rt_file_definitions(argv, e);
	update_camera_location(e);
	print_scene_elements(e);
	render(e);
}
