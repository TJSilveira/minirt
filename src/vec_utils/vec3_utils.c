/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42luxembourg.l  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:53:04 by tsilveir          #+#    #+#             */
/*   Updated: 2025/12/02 14:53:05 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	print_vec3(t_vec3 *v)
{
	printf("%f; %f; %f;\n", v->e[0], v->e[1], v->e[2]);
}

t_vec3	init_vec3(float x, float y, float z)
{
	return ((t_vec3){{x, y, z}});
}

t_vec3	unit_vec3(t_vec3 *v)
{
	return (vec3_div_const_copy(*v, vec3_length(v)));
}

float	vec3_dot(t_vec3 *v1, t_vec3 *v2)
{
	return (v1->e[X] * v2->e[X] + v1->e[Y] * v2->e[Y] + v1->e[Z] * v2->e[Z]);
}

t_vec3	vec3_cross(t_vec3 *v1, t_vec3 *v2)
{
	return (init_vec3(v1->e[1] * v2->e[2] - v1->e[2] * v2->e[1], v1->e[2]
			* v2->e[0] - v1->e[0] * v2->e[2], v1->e[0] * v2->e[1] - v1->e[1]
			* v2->e[0]));
}
