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
# define MAX_INT_COLOR 255
# define TMAX 5000
# define RAY_SAMPLE_SIDE_SIZE 2.0
# define RAY_SAMPLE_PADDING 0.2
# define EPSILON 0.00001

# define PI 3.14159265

# define NUM_PARAM_SPHERE 3
# define NUM_PARAM_PLANE 3
# define NUM_PARAM_LIGHT 3
# define NUM_PARAM_AMBIENT 2


#include <stdio.h>

typedef enum e_bool {FALSE, TRUE}	t_bool;

typedef union u_object t_object;

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
	t_object	*hit_obj;
	t_color3	color;
}t_hit;

typedef struct s_interval
{
	float	min;
	float	max;
} t_interval;


typedef struct s_ray
{
	t_vec3 		dir;
	t_point3 	orig;
	t_interval	itv;
} t_ray;

typedef struct s_sphere
{
	t_point3	center;
	t_color3	color;
	float 	ray;
}t_sphere;

typedef struct s_plane
{
	t_point3	point;
	t_vec3		normal;
	t_color3	color;
}t_plane;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		normal;
	float		diam;
	float		h;
	t_color3	color;
} t_cylinder;

typedef struct s_light
{
	t_point3	center;
	float		brightness;
	t_color3	color;
} t_light;

typedef struct s_image
{
	void			*img;
	char			*addr;
	int				pix_bits;
	int				line_len;
	int				endian;
	int				iter;
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
	t_point3	pixel00_loc_center;
}t_camera;

typedef enum e_object_id
{
	id_sphere,
	id_plane,
	id_cylinder
} t_object_id;

typedef union u_object
{
	t_object_id	id;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
} t_object;

typedef	struct s_ambient
{
	int			has_ambient;
	float		intensity;
	t_color3	color;
}t_ambient;

typedef struct s_scene
{
	t_object	**objects;
	t_light		**lights;
	size_t		obj_count;
	size_t		obj_capacity;
	size_t		l_count;
	size_t		l_capacity;
	t_ambient	amb;
} t_scene;

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
	t_point3		top_left;
	t_point3		start_sample;
	t_color3		clr;
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
t_vec3		vec3_mul_2inst_copy(t_vec3 v1, t_vec3 v2);
void		vec3_mul_2inst(t_vec3 *v1, t_vec3 *v2);

t_vec3		vec3_div_const_copy(t_vec3 v, float t);
void		vec3_div_const(t_vec3 *v, float t);

t_vec3		vec3_add_2inst_copy(t_vec3 v1, t_vec3 v2);
void		vec3_add_2inst(t_vec3 *v1, t_vec3 *v2);
t_vec3		vec3_add_cont_copy(t_vec3 v1, float t);
void		vec3_add_cont(t_vec3 *v1, float t);

t_vec3		vec3_sub_2inst_copy(t_vec3 v1, t_vec3 v2);
void		vec3_sub_2inst(t_vec3 *v1, t_vec3 *v2);

float	vec3_get_x(t_vec3 *v);
float	vec3_get_y(t_vec3 *v);
float	vec3_get_z(t_vec3 *v);

// colors.c
void write_color(t_color3 *c);

// t_camera.c
void init_camera_upper_left(t_camera *c);
void init_pixel00_center(t_camera *c);
void init_camera(t_engine *e);
t_point3 calculate_pixel_center(t_camera *c, int row, int col);
t_point3 calculate_pixel_top_left(t_camera *c, int row, int col);

// ray.c
t_color3	ray_tracer(t_ray *r, t_engine *e);
t_point3 point_at_ray(t_ray *r, float t);
t_bool	hit_sphere(t_sphere *s, t_ray *r, t_hit *rec);
t_bool hit_object(t_engine *e, t_ray *r, t_hit *hit);
t_bool hit_occluded(t_engine *e, t_ray *r, t_hit *hit);
unsigned int t_color3_to_uint(t_color3 c);
void	record_hit (t_ray *r, t_hit *rec, t_vec3 *normal, float t);
t_bool hit_object_function_selecter(t_object *obj, t_ray *r, t_hit *hit);

t_color3	ray_color(t_ray *r, t_engine *e, t_hit *hit);
t_color3	ray_color_ambient_light(t_engine *e, t_hit *hit);
t_color3	ray_color_diffuse_light(t_light *l, t_hit *hit);
t_color3	ray_color_specular_light(t_light *l, t_hit *hit, t_ray *r);


// mlx_utils.c
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
void	render(t_engine *e);
void	init_img(t_engine *e);
void	init_engine(char *argv[], t_engine *e);
void	get_pixel_color_anti_alaising_rt(t_engine *e, t_pixel *p);
t_point3	get_sample_location(t_engine *e, t_pixel *p, int i, int j);
void 	init_ray(t_ray *ray, t_engine *e, t_point3 *dir_point);
void	print_scene(t_engine *e);
void	print_scene_ambient(t_engine *e);
void	print_scene_lights(t_engine *e);
void	print_scene_objects(t_engine *e);
void	print_scene_sphere(t_object *obj);
void	print_scene_plane(t_object *obj);

// math_utils.c
void	solve_quadratic(t_quadratic *q);
float	ft_fabs(float num);

// scene.c
void create_scene(char *argv[], t_engine *e);
void add_object_to_scene(t_scene *s, t_object *o);
void add_light_to_scene(t_scene *s, t_light *light);

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

// light.c
t_bool in_shadow(t_engine *e, t_light *l, t_hit *hit);

#endif