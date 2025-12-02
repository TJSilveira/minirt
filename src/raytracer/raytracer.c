/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42luxembourg.l  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:52:42 by tsilveir          #+#    #+#             */
/*   Updated: 2025/12/02 14:52:44 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color3	ray_tracer(t_ray *r, t_engine *e)
{
	t_hit		hit;
	t_color3	black;

	hit = (t_hit){0};
	black = (t_color3){{0.0, 0.0, 0.0}};
	if (hit_object(e, r, &hit) == TRUE)
		return (ray_color(r, e, &hit));
	return (black);
}

void	init_ray(t_ray *ray, t_engine *e, t_point3 *dir_point)
{
	t_vec3	ray_direction;

	ray_direction = vec3_sub_2inst_copy(*dir_point, e->cam->camera_center);
	ray->dir = ray_direction;
	ray->orig = e->cam->camera_center;
	ray->itv.min = 0.0;
	ray->itv.max = TMAX;
}

t_point3	point_at_ray(t_ray *r, float t)
{
	t_point3	result;

	result = vec3_mul_const_copy(r->dir, t);
	vec3_add_2inst(&result, &r->orig);
	return (result);
}
