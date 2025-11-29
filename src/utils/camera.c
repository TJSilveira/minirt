#include "../includes/minirt.h"

void init_camera_upper_left(t_camera *c)
{
	t_point3 vp_upper_left;
	t_point3 vec_right_half;
	t_point3 vec_down_half;

	vp_upper_left = vec3_sub_2inst_copy(c->camera_center, c->vec_focal);
	vec_right_half = vec3_div_const_copy(c->vec_right, 2);
	vec_down_half = vec3_div_const_copy(c->vec_down, 2);
	vp_upper_left = vec3_sub_2inst_copy(vp_upper_left, vec_right_half);
	vp_upper_left = vec3_sub_2inst_copy(vp_upper_left, vec_down_half);
	c->vp_upper_left = vp_upper_left;
}

void init_pixel00_center(t_camera *c)
{
	t_vec3	pixel_delta_dr;

	pixel_delta_dr = vec3_add_2inst_copy(c->pixel_delta_down, c->pixel_delta_right);
	pixel_delta_dr = vec3_div_const_copy(pixel_delta_dr, 2.0);
	c->pixel00_loc_center = vec3_add_2inst_copy(c->vp_upper_left, pixel_delta_dr);
}

void init_camera(t_engine *e)
{
	float	theta;
	float	h;

	theta = degrees_to_radians(e->cam->fov);
	h = tan(theta / 2);
	e->cam->focal_length = 1.0;
	e->cam->vp_height = 2 * h * e->cam->focal_length;
	e->cam->vp_width = e->cam->vp_height * (float)(e->win_w)/(float)e->win_h;
	e->cam->vec_right = init_vec3(e->cam->vp_width, 0.0, 0.0);
	e->cam->vec_down = init_vec3(0.0, -e->cam->vp_height, 0.0);
	e->cam->vec_focal = init_vec3(0.0, 0.0, e->cam->focal_length);
	e->cam->pixel_delta_right = vec3_div_const_copy(e->cam->vec_right, e->win_w);
	e->cam->pixel_delta_down = vec3_div_const_copy(e->cam->vec_down, e->win_h);
	init_camera_upper_left(e->cam);
	init_pixel00_center(e->cam);
}

t_point3 calculate_pixel_center(t_camera *c, int row, int col)
{
	t_point3	pixel_center;
	t_vec3	horizontal_shift;	
	t_vec3	vertical_shift;
	t_vec3	total_shift;

	horizontal_shift = vec3_mul_const_copy(c->pixel_delta_right, row);
	vertical_shift = vec3_mul_const_copy(c->pixel_delta_down, col);
	total_shift = vec3_add_2inst_copy(horizontal_shift,vertical_shift);
	pixel_center = vec3_add_2inst_copy(c->pixel00_loc_center, total_shift);

	return (pixel_center);
}

t_point3 calculate_pixel_top_left(t_camera *c, int row, int col)
{
	t_point3	pixel_top_left;
	t_vec3	horizontal_shift;	
	t_vec3	vertical_shift;
	t_vec3	total_shift;

	horizontal_shift = vec3_mul_const_copy(c->pixel_delta_right, row);
	vertical_shift = vec3_mul_const_copy(c->pixel_delta_down, col);
	total_shift = vec3_add_2inst_copy(horizontal_shift,vertical_shift);
	pixel_top_left = vec3_add_2inst_copy(c->vp_upper_left, total_shift);

	return (pixel_top_left);
}