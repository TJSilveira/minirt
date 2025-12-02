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

void	update_camera_location(t_engine *e)
{
	t_vec3	up;

	if (!e->cam)
		error_handler("Camera configuration not provided\n", e);
	up = init_vec3(0, 0, 0);
	calculate_viewport_size(e);
	init_camera_orthogonal_vectors(e, &up);
	resize_camera_orthogonal_vectors(e, &up);
	init_camera_upper_left(e->cam);
	init_pixel00_center(e);
}

void	calculate_viewport_size(t_engine *e)
{
	float	theta;
	float	h;

	theta = degrees_to_radians(e->cam->fov);
	h = tan(theta / 2);
	e->cam->focal_length = 1.0;
	e->cam->vp_height = 2 * h * e->cam->focal_length;
	e->cam->vp_width = e->cam->vp_height * (float)(e->win_w) / (float)e->win_h;
}

t_point3	calculate_pixel_center(t_camera *c, int row, int col)
{
	t_point3	pixel_center;
	t_vec3		horizontal_shift;
	t_vec3		vertical_shift;
	t_vec3		total_shift;

	horizontal_shift = vec3_mul_const_copy(c->pixel_delta_right, row);
	vertical_shift = vec3_mul_const_copy(c->pixel_delta_down, col);
	total_shift = vec3_add_2inst_copy(horizontal_shift, vertical_shift);
	pixel_center = vec3_add_2inst_copy(c->pixel00_loc_center, total_shift);
	return (pixel_center);
}

t_point3	calculate_pixel_top_left(t_camera *c, int row, int col)
{
	t_point3	pixel_top_left;
	t_vec3		horizontal_shift;
	t_vec3		vertical_shift;
	t_vec3		total_shift;

	horizontal_shift = vec3_mul_const_copy(c->pixel_delta_right, row);
	vertical_shift = vec3_mul_const_copy(c->pixel_delta_down, col);
	total_shift = vec3_add_2inst_copy(horizontal_shift, vertical_shift);
	pixel_top_left = vec3_add_2inst_copy(c->vp_upper_left, total_shift);
	return (pixel_top_left);
}
