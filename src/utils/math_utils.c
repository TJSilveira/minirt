/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42luxembourg.l  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:52:18 by tsilveir          #+#    #+#             */
/*   Updated: 2025/12/02 14:52:22 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_quadratic	solve_quadratic(t_sphere *s, t_ray *r)
{
	t_vec3		oc;
	t_quadratic	q;

	oc = vec3_sub_2inst_copy(s->center, r->orig);
	q.a = vec3_dot(&r->dir, &r->dir);
	q.h = vec3_dot(&oc, &r->dir);
	q.c = vec3_dot(&oc, &oc) - (s->ray * s->ray);
	q.discriminate = (q.h * q.h - q.a * q.c);
	if (q.discriminate < 0)
		q.has_solutions = FALSE;
	else
	{
		q.has_solutions = TRUE;
		q.t_minus = (q.h - sqrt(q.discriminate)) / q.a;
		q.t_plus = (q.h + sqrt(q.discriminate)) / q.a;
	}
	return (q);
}

float	degrees_to_radians(float degrees)
{
	return (degrees * PI / 180.0);
}
