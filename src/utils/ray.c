#include "../includes/minirt.h"

t_point3 point_at_ray(ray *r, float t)
{
	t_point3 result;

	result = vec3_mul_const_copy(*r->dir, t);
	vec3_add_2inst(&result, r->orig);

	return (result);
}

unsigned int t_color3_to_uint(t_color3 c)
{
	unsigned int color_final;
	
	color_final = 0;
    color_final |= (unsigned int)(c.e[B] * 255);
    color_final |= (unsigned int)(c.e[G] * 255) << 8;
    color_final |= (unsigned int)(c.e[R] * 255) << 16;
    return (color_final);
}

unsigned int ray_color(ray *r, t_engine *e)
{
	t_vec3		n;
	t_hit		hit;

	if (hit_sphere(&e->scene.objects[0]->sphere, r, &hit) == TRUE)
	{
		n = vec3_sub_2inst_copy(point_at_ray(r, hit.t), e->scene.objects[0]->sphere.center);
		n = unit_vec3(&n);
		vec3_add_cont(&n, 1);
		vec3_mul_const(&n, 0.5);
		return (t_color3_to_uint(n));
	}

	t_vec3 unit_direction = unit_vec3(r->dir);
	float a = 0.5 * (unit_direction.e[1] + 1.0);
	t_color3 black = {{1.0,1.0,1.0}};
	t_color3 blue = {{0.5,0.7,1.0}};
	black = vec3_mul_const_copy(black, 1.0 - a); 
	blue = vec3_mul_const_copy(blue, a); 
	return t_color3_to_uint(vec3_add_2inst_copy(black, blue));
}

void set_face_normal(ray *r, t_hit *rec)
{
	if (vec3_dot(r->dir, &rec->normal) > 0.0)
	{
		rec->inside_face = TRUE;
		vec3_mul_const(&rec->normal, -1.0);
	}
	rec->inside_face = FALSE;
}

t_bool	hit_sphere(t_sphere *s, ray *r, t_hit *rec)
{
	t_vec3	oc;
	t_quadratic quad;
	float	root;

	oc = vec3_sub_2inst_copy(*r->orig, s->center);
	quad.a = vec3_dot(r->dir, r->dir);
	quad.h = vec3_dot(&oc, r->dir);
	quad.c = vec3_dot(&oc, &oc) - (s->ray * s->ray);
	solve_quadratic(&quad);
	if(quad.has_solutions == FALSE)
		return (FALSE);
	root = quad.t_minus;
	if (root <= r->tmin || root >= r->tmax)
	{
		root = quad.t_plus;
		if (root <= r->tmin || root >= r->tmax)
			return (FALSE);
	}
	rec->t = root;
	rec->p = point_at_ray(r, root);
	rec->normal = unit_vec3(&oc);
	set_face_normal(r, rec);
	return (TRUE);
}
