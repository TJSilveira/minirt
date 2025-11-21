/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42luxembourg.l  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:16:39 by tsilveir          #+#    #+#             */
/*   Updated: 2025/08/18 18:16:40 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "../libft/libft.h"
# include <math.h>
# include "../minilibx-linux/mlx.h"
# define X 0
# define Y 1
# define Z 2
# define R 0
# define G 1
# define B 2
# define MAX_OBJECTS 100
# define IMAGE_WIDTH 1200
# define PI 3.14159265
# define MAX_INT_COLOR 255
# define NUM_PARAM_SPHERE 3


#include <stdio.h>

typedef enum e_bool {FALSE, TRUE}	t_bool;

typedef struct s_vec3 
{
	float e[3];
} t_vec3, t_color3, t_point3;

typedef struct s_hit
{
	t_point3	p;
	t_vec3		normal;
	float		t;
	t_bool		inside_face;
}t_hit;

typedef struct ray
{
	t_vec3 		*dir;
	t_point3 	*orig;
	float		tmin;
	float		tmax;
} ray;

typedef struct s_sphere
{
	t_point3	center;
	t_color3	color;
	float 	ray;
}t_sphere;

typedef struct s_image
{
	void			*img;
	char			*addr;
	int				pix_bits;
	int				line_len;
	int				endian;
	int				iter;
	// int				fractal_type;
	// unsigned int	main_color;
	// unsigned int	secundary_color;
}	t_image;

typedef struct s_camera
{
	float	focal_length;
    float	vp_height;
    float	vp_width;
	t_vec3	vec_right;
    t_vec3	vec_down;
    t_vec3	vec_focal;
	t_vec3	pixel_delta_right;
	t_vec3	pixel_delta_down;
	t_point3	camera_center;
	t_point3	vp_upper_left;
	t_point3	pixel00_loc;
}t_camera;

typedef enum e_object_id
{
	id_sphere
} t_object_id;

typedef union u_object
{
	t_sphere	sphere;
} t_object;

typedef struct s_scene
{
	t_object	**objects;
	size_t		count;
	size_t		capacity;
}t_scene;

typedef struct s_engine
{
	void			*mlx;
	void			*window;
	unsigned int	win_w;
	unsigned int	win_h;
	float			aspect_ratio;
	t_image			img;
	t_camera		cam;
	t_scene			scene;
}	t_engine;


typedef struct s_pixel
{
	int	x;
	int	y;
	t_point3		center;
	unsigned int	clr;
}	t_pixel;

typedef struct s_quadartic
{
	float	a;
	float	h;
	float	c;
	float	discriminate;
	t_bool	has_solutions;
	float	t_minus;
	float	t_plus;
} t_quadratic;

// vec3_utils.c function prototypes
void print_vec3(t_vec3 *v);
t_vec3 init_vec3(float x, float y, float z);
t_vec3 unit_vec3(t_vec3 *v);
float vec3_dot(t_vec3 *v1, t_vec3 *v2);

float		length_squared(t_vec3 *v);
float		length(t_vec3 *v);

t_vec3		vec3_mul_const_copy(t_vec3 v, float t);
void		vec3_mul_const(t_vec3 *v, float t);

t_vec3		vec3_div_const_copy(t_vec3 v, float t);
void		vec3_div_const(t_vec3 *v, float t);

t_vec3		vec3_add_2inst_copy(t_vec3 v1, t_vec3 v2);
void		vec3_add_2inst(t_vec3 *v1, t_vec3 *v2);
t_vec3		vec3_add_cont_copy(t_vec3 v1, float t);
void		vec3_add_cont(t_vec3 *v1, float t);

t_vec3		vec3_sub_2inst_copy(t_vec3 v1, t_vec3 v2);
void		vec3_sub_2inst(t_vec3 *v1, t_vec3 *v2);

// colors.c
void write_color(t_color3 *c);

// t_camera.c
void init_camera_upper_left(t_camera *c);
void init_pixel00(t_camera *c);
void init_camera(t_engine *e);
t_point3 calculate_pixel_center(t_camera *c, int row, int col);

// ray.c
unsigned int ray_color(ray *r, t_engine *e);
t_point3 point_at_ray(ray *r, float t);
t_bool	hit_sphere(t_sphere *s, ray *r, t_hit *rec);

// mlx_utils.c
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
void	update_pixel(t_engine *e);
void	init_img(t_engine *e);
void	init_engine(char *argv[], t_engine *e);

// math_utils.c
void	solve_quadratic(t_quadratic *q);

// scene.c
void create_scene(char *argv[], t_engine *e);
void add_object_to_scene(t_scene *s, t_object *o);

// import.c
char **rt_file_parser(char* buffer);
int rt_import_sphere(char **params, t_scene *s);
int rt_import_color(char *param, t_vec3 *vec);
int	rt_import_float(char *param, float *result);
int rt_import_vec3 (char *param, t_vec3 *vec);
int rt_importer_params(char **params, t_scene *s);
void rt_extension_check(char *argv[]);


// utils.c
void	free_arrays(char **arrays);
int	return_and_free_array(int exit_value, char **arrays);
void	ft_str_to_float(char *str, float *result);
t_bool is_digit(char c);
t_bool is_float(char *num);
t_bool is_int_color(char *num);

#endif