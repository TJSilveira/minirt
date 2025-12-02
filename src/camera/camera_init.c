/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42luxembourg.l  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:51:36 by tsilveir          #+#    #+#             */
/*   Updated: 2025/12/02 14:51:39 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/*	The point that corresponds to the top left of the screen upon which
	all the calculations on pixel location will depend on */
void	init_camera_upper_left(t_camera *c)
{
	t_point3	vp_upper_left;
	t_point3	vec_right_half;
	t_point3	vec_down_half;

	vp_upper_left = vec3_add_2inst_copy(c->camera_center, c->vec_focal);
	vec_right_half = vec3_div_const_copy(c->vec_right, 2);
	vec_down_half = vec3_div_const_copy(c->vec_down, 2);
	vp_upper_left = vec3_sub_2inst_copy(vp_upper_left, vec_right_half);
	vp_upper_left = vec3_sub_2inst_copy(vp_upper_left, vec_down_half);
	c->vp_upper_left = vp_upper_left;
}

/*	The location of the top left pixel. Note that the pixel location is set
	to the middle of the pixel */
void	init_pixel00_center(t_engine *e)
{
	t_vec3	pixel_delta_dr;

	e->cam->pixel_delta_right = vec3_div_const_copy
		(e->cam->vec_right, e->win_w);
	e->cam->pixel_delta_down = vec3_div_const_copy(e->cam->vec_down, e->win_h);
	pixel_delta_dr = vec3_add_2inst_copy
		(e->cam->pixel_delta_down, e->cam->pixel_delta_right);
	pixel_delta_dr = vec3_div_const_copy(pixel_delta_dr, 2.0);
	e->cam->pixel00_loc_center = vec3_add_2inst_copy
		(e->cam->vp_upper_left, pixel_delta_dr);
}

void	init_camera_orthogonal_vectors(t_engine *e, t_vec3 *up)
{
	if (fabs(e->cam->direction.e[Y]) < 0.9)
		*up = init_vec3(0, 1, 0);
	else
		*up = init_vec3(0, 0, 1);
	e->cam->vec_right = vec3_cross(&e->cam->direction, up);
	e->cam->vec_right = unit_vec3(&e->cam->vec_right);
	*up = vec3_cross(&e->cam->vec_right, &e->cam->direction);
	*up = unit_vec3(up);
}

void	resize_camera_orthogonal_vectors(t_engine *e, t_vec3 *up)
{
	e->cam->vec_right = vec3_mul_const_copy(e->cam->vec_right,
			e->cam->vp_width);
	e->cam->vec_down = vec3_mul_const_copy(*up, -e->cam->vp_height);
	e->cam->vec_focal = vec3_mul_const_copy(e->cam->direction,
			e->cam->focal_length);
}
