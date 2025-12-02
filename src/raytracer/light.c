/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42luxembourg.l  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:52:11 by tsilveir          #+#    #+#             */
/*   Updated: 2025/12/02 14:52:13 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_bool	in_shadow(t_engine *e, t_light *l, t_hit *hit)
{
	t_ray	shadow_ray;
	t_vec3	offset;
	float	distance_to_light;
	t_bool	occluded;

	shadow_ray.dir = vec3_sub_2inst_copy(l->center, hit->p);
	distance_to_light = vec3_length(&shadow_ray.dir);
	shadow_ray.dir = unit_vec3(&shadow_ray.dir);
	offset = vec3_mul_const_copy(hit->normal, 1e-4);
	shadow_ray.orig = vec3_add_2inst_copy(hit->p, offset);
	shadow_ray.itv.min = EPSILON;
	shadow_ray.itv.max = distance_to_light;
	occluded = hit_occluded(e, &shadow_ray);
	shadow_ray.itv.max = distance_to_light;
	return (occluded);
}
