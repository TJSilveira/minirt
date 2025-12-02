/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42luxembourg.l  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:51:54 by tsilveir          #+#    #+#             */
/*   Updated: 2025/12/02 14:51:56 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	get_pixel_color_anti_alaising_rt(t_engine *e, t_pixel *p)
{
	t_ray		r;
	t_point3	curr_sample;
	int			i;
	int			j;

	p->top_left = calculate_pixel_top_left(e->cam, p->x, p->y);
	i = 0;
	while (i < RAY_SAMPLE_SIDE_SIZE)
	{
		j = 0;
		while (j < RAY_SAMPLE_SIDE_SIZE)
		{
			curr_sample = get_sample_location(e, p, i, j);
			init_ray(&r, e, &curr_sample);
			p->clr = vec3_add_2inst_copy(p->clr,
					vec3_div_const_copy(ray_tracer(&r, e), RAY_SAMPLE_SIDE_SIZE
						* RAY_SAMPLE_SIDE_SIZE));
			j++;
		}
		i++;
	}
}

t_point3	get_sample_location(t_engine *e, t_pixel *p, int i, int j)
{
	t_vec3		pixel_sample_delta_right;
	t_vec3		pixel_sample_delta_down;
	t_vec3		pixel_sample_delta;
	t_point3	curr_sample;

	pixel_sample_delta_right = vec3_mul_const_copy(e->cam->pixel_delta_right,
			RAY_SAMPLE_PADDING + i * (1.0 - 2.0 * RAY_SAMPLE_PADDING)
			/ (RAY_SAMPLE_SIDE_SIZE - 1.0));
	pixel_sample_delta_down = vec3_mul_const_copy(e->cam->pixel_delta_down,
			RAY_SAMPLE_PADDING + j * (1.0 - 2.0 * RAY_SAMPLE_PADDING)
			/ (RAY_SAMPLE_SIDE_SIZE - 1.0));
	pixel_sample_delta = vec3_add_2inst_copy(pixel_sample_delta_right,
			pixel_sample_delta_down);
	curr_sample = vec3_add_2inst_copy(p->top_left, pixel_sample_delta);
	return (curr_sample);
}

unsigned int	t_color3_to_uint(t_color3 c)
{
	unsigned int	color_final;

	c.e[X] = linear_to_gamma(c.e[X]);
	c.e[Y] = linear_to_gamma(c.e[Y]);
	c.e[Z] = linear_to_gamma(c.e[Z]);
	color_final = 0;
	color_final |= (unsigned int)(c.e[B] * 255);
	color_final |= (unsigned int)(c.e[G] * 255) << 8;
	color_final |= (unsigned int)(c.e[R] * 255) << 16;
	return (color_final);
}

float	linear_to_gamma(float num)
{
	if (num > 0)
		return (sqrt(num));
	return (0);
}
