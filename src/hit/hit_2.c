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

void	set_face_normal(t_ray *r, t_hit *hit)
{
	if (vec3_dot(&r->dir, &hit->normal) > 0.0)
	{
		hit->inside_face = TRUE;
		vec3_mul_const(&hit->normal, -1.0);
	}
	else
		hit->inside_face = FALSE;
}

void	record_hit(t_ray *r, t_hit *hit, t_vec3 *normal, float t)
{
	hit->t = t;
	r->itv.max = t;
	hit->p = point_at_ray(r, hit->t);
	hit->normal = unit_vec3(normal);
}

t_bool	hit_occluded(t_engine *e, t_ray *r)
{
	t_hit	shadow_hit;
	int		i;

	shadow_hit = (t_hit){0};
	i = -1;
	while (e->scene.objects[++i])
	{
		if (hit_object_function_selecter(e->scene.objects[i], r,
				&shadow_hit) == TRUE)
			return (TRUE);
	}
	return (FALSE);
}
