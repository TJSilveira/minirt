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

t_vec3	vec3_mul_const_copy(t_vec3 v, float t)
{
	return ((t_vec3){{v.e[0] * t, v.e[1] * t, v.e[2] * t}});
}

void	vec3_mul_const(t_vec3 *v, float t)
{
	v->e[0] *= t;
	v->e[1] *= t;
	v->e[2] *= t;
}

t_vec3	vec3_mul_2inst_copy(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){{v1.e[0] * v2.e[0],
			v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]}});
}

void	vec3_mul_2inst(t_vec3 *v1, t_vec3 *v2)
{
	v1->e[0] *= v2->e[0];
	v1->e[1] *= v2->e[1];
	v1->e[2] *= v2->e[2];
}
