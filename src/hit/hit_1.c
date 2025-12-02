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

t_bool	hit_object(t_engine *e, t_ray *r, t_hit *hit)
{
	int		i;
	t_bool	hit_anything;

	i = -1;
	hit_anything = FALSE;
	while (e->scene.objects[++i])
	{
		if (hit_object_function_selecter(e->scene.objects[i], r, hit) == TRUE)
		{
			hit_anything = TRUE;
			hit->hit_obj = e->scene.objects[i];
		}
	}
	return (hit_anything);
}

t_bool	hit_object_function_selecter(t_object *obj, t_ray *r, t_hit *hit)
{
	if (obj->id == id_sphere)
		return (hit_sphere(&obj->obj_union.sphere, r, hit));
	else if (obj->id == id_plane)
		return (hit_plane(&obj->obj_union.plane, r, hit));
	return (FALSE);
}

t_bool	hit_sphere(t_sphere *s, t_ray *r, t_hit *hit)
{
	t_vec3		normal;
	t_quadratic	quad;
	float		root;

	quad = solve_quadratic(s, r);
	if (quad.has_solutions == FALSE)
		return (FALSE);
	root = quad.t_minus;
	if (root <= r->itv.min || root >= r->itv.max)
	{
		root = quad.t_plus;
		if (root <= r->itv.min || root >= r->itv.max)
			return (FALSE);
	}
	hit->p = point_at_ray(r, root);
	normal = vec3_sub_2inst_copy(hit->p, s->center);
	normal = unit_vec3(&normal);
	record_hit(r, hit, &normal, root);
	set_face_normal(r, hit);
	hit->color = s->color;
	return (TRUE);
}

/*	Plane Intersection :
	https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection */
t_bool	hit_plane(t_plane *p, t_ray *r, t_hit *hit)
{
	float	denominator;
	float	t;
	t_vec3	p0_minus_l0;

	denominator = vec3_dot(&p->normal, &r->dir);
	if (fabs(denominator) < EPSILON)
		return (FALSE);
	p0_minus_l0 = vec3_sub_2inst_copy(p->point, r->orig);
	t = vec3_dot(&p0_minus_l0, &p->normal) / denominator;
	if (t <= r->itv.min || t >= r->itv.max)
		return (FALSE);
	record_hit(r, hit, &p->normal, t);
	if (vec3_dot(&hit->normal, &r->dir) > 0)
		vec3_mul_const(&hit->normal, -1.0);
	hit->color = p->color;
	return (TRUE);
}
