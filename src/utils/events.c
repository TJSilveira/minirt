/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42luxembourg.l  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:52:02 by tsilveir          #+#    #+#             */
/*   Updated: 2025/12/02 14:52:05 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	close_win(t_engine *engine)
{
	cleanup_engine(engine);
	exit(EXIT_SUCCESS);
}

int	key_fig(int key, t_engine *e)
{
	if (key == KEY_ESC)
		close_win(e);
	else if (key == KEY_W)
		move_translation(e, 0.0, 0.3, 0.0);
	else if (key == KEY_S)
		move_translation(e, 0.0, -0.3, 0.0);
	else if (key == KEY_A)
		move_translation(e, -0.3, 0.0, 0.0);
	else if (key == KEY_D)
		move_translation(e, 0.3, 0.0, 0.0);
	else if (key == KEY_R)
		move_translation(e, 0.0, 0.0, 1.0);
	else if (key == KEY_F)
		move_translation(e, 0.0, 0.0, -1.0);
	else if (key == KEY_I)
		move_rotation(e, 0.0, 0.2);
	else if (key == KEY_J)
		move_rotation(e, -0.2, 0.0);
	else if (key == KEY_K)
		move_rotation(e, 0.0, -0.2);
	else if (key == KEY_L)
		move_rotation(e, 0.2, 0.0);
	return (0);
}

void	move_translation(t_engine *e, float x_move, float y_move, float z_move)
{
	t_vec3	x_vec3;
	t_vec3	y_vec3;
	t_vec3	z_vec3;

	x_vec3 = vec3_mul_const_copy(e->cam->vec_right, x_move);
	y_vec3 = vec3_mul_const_copy(e->cam->vec_down, -y_move);
	z_vec3 = vec3_mul_const_copy(e->cam->vec_focal, z_move);
	vec3_add_2inst(&e->cam->camera_center, &x_vec3);
	vec3_add_2inst(&e->cam->camera_center, &y_vec3);
	vec3_add_2inst(&e->cam->camera_center, &z_vec3);
	update_camera_location(e);
	render(e);
	mlx_put_image_to_window(e->mlx, e->window, e->img.img, 0, 0);
}

void	move_rotation(t_engine *e, float side_rot, float front_rot)
{
	t_point3	new_focal_point;
	t_vec3		side_tilt;
	t_vec3		front_tilt;
	t_vec3		new_dir;

	new_focal_point = vec3_add_2inst_copy(e->cam->camera_center,
			e->cam->vec_focal);
	side_tilt = vec3_mul_const_copy(e->cam->vec_right, side_rot);
	front_tilt = vec3_mul_const_copy(e->cam->vec_down, -front_rot);
	vec3_add_2inst(&new_focal_point, &side_tilt);
	vec3_add_2inst(&new_focal_point, &front_tilt);
	new_dir = vec3_sub_2inst_copy(new_focal_point, e->cam->camera_center);
	new_dir = unit_vec3(&new_dir);
	e->cam->direction = new_dir;
	update_camera_location(e);
	render(e);
	mlx_put_image_to_window(e->mlx, e->window, e->img.img, 0, 0);
}

int	handle_key(int keycode, void *param)
{
	printf("keycode: %d\n", keycode);
	(void)param;
	return (0);
}
