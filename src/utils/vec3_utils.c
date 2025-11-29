#include "../includes/minirt.h"

void	print_vec3(t_vec3 *v)
{
    printf("%f.%f.%f\n", v->e[0], v->e[1], v->e[2]);
}

t_vec3	init_vec3(float x, float y, float z)
{
	return ((t_vec3){{x,y,z}});
}

t_vec3	unit_vec3(t_vec3 *v)
{
	return (vec3_div_const_copy(*v, length(v)));
}

float	length_squared(t_vec3 *v)
{
	return (v->e[0]*v->e[0] + v->e[1] * v->e[1] + v->e[2] * v->e[2]);
}

float	length(t_vec3 *v)
{
	return (sqrt(length_squared(v)));
}

t_vec3	vec3_mul_const_copy(t_vec3 v, float t)
{
	return (t_vec3){{
		v.e[0] * t,
		v.e[1] * t,
		v.e[2] * t
	}};
}

void	vec3_mul_const(t_vec3 *v, float t)
{
	v->e[0] *= t;
	v->e[1] *= t;
	v->e[2] *= t;
}

t_vec3	vec3_mul_2inst_copy(t_vec3 v1, t_vec3 v2)
{
	return (t_vec3){{
		v1.e[0] * v2.e[0],
		v1.e[1] * v2.e[1],
		v1.e[2] * v2.e[2]
	}};
}

void	vec3_mul_2inst(t_vec3 *v1, t_vec3 *v2)
{
	v1->e[0] *= v2->e[0];
	v1->e[1] *= v2->e[1];
	v1->e[2] *= v2->e[2];
}

t_vec3	vec3_div_const_copy(t_vec3 v, float t)
{
	return (t_vec3){{
		v.e[0] / t,
		v.e[1] / t,
		v.e[2] / t
	}};
}

void	vec3_div_const(t_vec3 *v, float t)
{
	v->e[0] /= t;
	v->e[1] /= t;
	v->e[2] /= t;
}

t_vec3	vec3_add_2inst_copy(t_vec3 v1, t_vec3 v2)
{
	return (t_vec3){{
		v1.e[0] + v2.e[0],
		v1.e[1] + v2.e[1],
		v1.e[2] + v2.e[2]
	}};
}

void	vec3_add_2inst(t_vec3 *v1, t_vec3 *v2)
{
	v1->e[0] += v2->e[0];
	v1->e[1] += v2->e[1];
	v1->e[2] += v2->e[2];
}

t_vec3	vec3_add_cont_copy(t_vec3 v1, float t)
{
	return (t_vec3){{
		v1.e[0] + t,
		v1.e[1] + t,
		v1.e[2] + t
	}};
}

void	vec3_add_cont(t_vec3 *v1, float t)
{
	v1->e[0] += t;
	v1->e[1] += t;
	v1->e[2] += t;
}

t_vec3	vec3_sub_2inst_copy(t_vec3 v1, t_vec3 v2)
{
	return (t_vec3){{
		v1.e[0] - v2.e[0],
		v1.e[1] - v2.e[1],
		v1.e[2] - v2.e[2]
	}};
}

void	vec3_sub_2inst(t_vec3 *v1, t_vec3 *v2)
{
	v1->e[0] -= v2->e[0];
	v1->e[1] -= v2->e[1];
	v1->e[2] -= v2->e[2];
}

float	vec3_dot(t_vec3 *v1, t_vec3 *v2)
{
	return (v1->e[X] * v2->e[X]
			+ v1->e[Y] * v2->e[Y]
			+ v1->e[Z] * v2->e[Z]);
}

t_vec3	vec3_cross(t_vec3 *v1, t_vec3 *v2)
{
	return (init_vec3(
		v1->e[1] * v2->e[2] - v1->e[2] * v2->e[1],
		v1->e[0] * v2->e[2] - v1->e[2] * v2->e[0],
		v1->e[0] * v2->e[1] - v1->e[1] * v2->e[0]
		)
	);
}

float	vec3_get_x(t_vec3 *v)
{
	return (v->e[X]);
}

float	vec3_get_y(t_vec3 *v)
{
	return (v->e[Y]);
}

float	vec3_get_z(t_vec3 *v)
{
	return (v->e[Z]);
}
