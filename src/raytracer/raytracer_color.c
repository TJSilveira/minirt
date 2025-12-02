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

t_color3	ray_color(t_ray *r, t_engine *e, t_hit *hit)
{
	int			i;
	t_color3	phong_color;
	t_color3	diffuse_color;
	t_color3	specular_color;

	phong_color = ray_color_ambient_light(e, hit);
	i = -1;
	while (e->scene.lights[++i])
	{
		if (in_shadow(e, e->scene.lights[i], hit) == FALSE)
		{
			diffuse_color = ray_color_diffuse_light(e->scene.lights[i], hit);
			vec3_add_2inst(&phong_color, &diffuse_color);
			specular_color
				= ray_color_specular_light(e->scene.lights[i], hit, r);
			vec3_add_2inst(&phong_color, &specular_color);
		}
	}
	vec3_max_normalization(&phong_color);
	return (phong_color);
}

t_color3	ray_color_ambient_light(t_engine *e, t_hit *hit)
{
	t_color3	ambient_color;

	ambient_color = vec3_mul_const_copy(e->scene.amb->color,
			e->scene.amb->intensity);
	vec3_mul_2inst(&ambient_color, &hit->color);
	return (ambient_color);
}

t_color3	ray_color_diffuse_light(t_light *l, t_hit *hit)
{
	t_ray		light_ray;
	t_color3	diffuse_color;
	float		intensity;

	light_ray.dir = vec3_sub_2inst_copy(l->center, hit->p);
	light_ray.dir = unit_vec3(&light_ray.dir);
	intensity = vec3_dot(&light_ray.dir, &hit->normal);
	if (intensity < 0)
		return ((t_color3){{0, 0, 0}});
	intensity *= l->brightness;
	diffuse_color = vec3_mul_const_copy(l->color, intensity);
	vec3_mul_2inst(&diffuse_color, &hit->color);
	return (diffuse_color);
}

/* www.fabrizioduroni.it/blog/post/2017/08/25
	/how-to-calculate-reflection-vector */
t_color3	ray_color_specular_light(t_light *l, t_hit *hit, t_ray *r)
{
	t_ray		reflected_ray;
	t_ray		light_ray;
	t_color3	specular_color;
	float		intensity;
	float		n_dot_l;

	light_ray.dir = vec3_sub_2inst_copy(l->center, hit->p);
	light_ray.dir = unit_vec3(&light_ray.dir);
	reflected_ray.dir = hit->normal;
	n_dot_l = vec3_dot(&hit->normal, &light_ray.dir);
	vec3_mul_const(&reflected_ray.dir, 2.0 * n_dot_l);
	vec3_sub_2inst(&reflected_ray.dir, &light_ray.dir);
	reflected_ray.dir = unit_vec3(&reflected_ray.dir);
	vec3_mul_const(&reflected_ray.dir, -1.0);
	r->dir = unit_vec3(&r->dir);
	intensity = vec3_dot(&reflected_ray.dir, &r->dir);
	if (intensity < 0)
		return ((t_color3){{0, 0, 0}});
	intensity = pow(fmax(0.0, intensity), SPECULAR_PARAM);
	intensity *= l->brightness;
	specular_color = vec3_mul_const_copy(l->color, intensity);
	vec3_mul_2inst(&specular_color, &hit->color);
	return (specular_color);
}

void	vec3_max_normalization(t_vec3 *v)
{
	float	max_component;

	max_component = v->e[X];
	if (v->e[Y] > max_component)
		max_component = v->e[Y];
	if (v->e[Z] > max_component)
		max_component = v->e[Z];
	vec3_div_const(v, (1 + max_component));
}
