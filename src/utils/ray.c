#include "../includes/minirt.h"

t_point3 point_at_ray(t_ray *r, float t)
{
	t_point3 result;

	result = vec3_mul_const_copy(r->dir, t);
	vec3_add_2inst(&result, &r->orig);

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

t_color3	ray_color(t_ray *r, t_engine *e)
{
	t_hit	hit;

	hit = (t_hit){0};
	t_color3 blue = {{0.5,0.7,1.0}};
	t_color3 black = {{1.0,1.0,1.0}};
	if (hit_object(e,r,&hit) == TRUE)
	{
		return (hit.color);
	}
	t_vec3 unit_direction = unit_vec3(&r->dir);
	float a = 0.5 * (unit_direction.e[1] + 1.0);
	black = vec3_mul_const_copy(black, 1.0 - a); 
	blue = vec3_mul_const_copy(blue, a); 
	return (vec3_add_2inst_copy(black, blue));
}

void set_face_normal(t_ray *r, t_hit *rec)
{
	if (vec3_dot(&r->dir, &rec->normal) > 0.0)
	{
		rec->inside_face = TRUE;
		vec3_mul_const(&rec->normal, -1.0);
	}
	rec->inside_face = FALSE;
}

t_bool	hit_sphere(t_sphere *s, t_ray *r, t_hit *rec)
{
	t_vec3	oc;
	t_vec3	normal;
	t_quadratic quad;
	float	root;

	oc = vec3_sub_2inst_copy(s->center, r->orig);
	quad.a = vec3_dot(&r->dir, &r->dir);
	quad.h = vec3_dot(&oc, &r->dir);
	quad.c = vec3_dot(&oc, &oc) - (s->ray * s->ray);
	solve_quadratic(&quad);
	if(quad.has_solutions == FALSE)
		return (FALSE);
	root = quad.t_minus;
	if (root <= r->itv.min || root >= r->itv.max)
	{
		root = quad.t_plus;
		if (root <= r->itv.min || root >= r->itv.max)
			return (FALSE);
	}
	rec->p = point_at_ray(r, root);
	normal = vec3_sub_2inst_copy(rec->p, s->center);
	normal = unit_vec3(&normal);
	record_hit(r, rec, &normal, root);
	set_face_normal(r, rec);
	rec->color = s->color;
	return (TRUE);
}

/* Plane Intersection : https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection */
t_bool	hit_plane (t_plane *p, t_ray *r, t_hit *rec)
{
	float	denominator;
	float	t;
	t_vec3	p0_minus_l0;

	denominator = vec3_dot(&p->normal, &r->dir);
	if (ft_fabs(denominator) < EPSILON)
		return (FALSE);
	p0_minus_l0 = vec3_sub_2inst_copy(p->point, r->orig);
	t = vec3_dot(&p0_minus_l0, &p->normal) / denominator;
	if (t <= r->itv.min || t >= r->itv.max)
		return (FALSE);
	record_hit(r, rec, &p->normal, t);
	rec->color = p->color;
	return (TRUE);
}

void	record_hit (t_ray *r, t_hit *rec, t_vec3 *normal, float t)
{
	rec->t = t;
	r->itv.max = t;
	rec->p = point_at_ray(r, rec->t);
	rec->normal = unit_vec3(normal);
}

t_bool hit_object(t_engine *e, t_ray *r, t_hit *hit)
{
	int		i;
	t_bool	hit_anything;

	i = -1;
	hit_anything = FALSE;
	while (e->scene.objects[++i])
	{
		if (hit_object_function_selecter(e->scene.objects[i], r, hit) == TRUE)
		{
			hit_anything = TRUE;
			hit->hit_obj = e->scene.objects[i];
		}
	}
	return (hit_anything);
}

t_bool hit_object_function_selecter(t_object *obj, t_ray *r, t_hit *hit)
{
	if (obj->id == id_sphere)
		return (hit_sphere(&obj->sphere, r, hit));
	else if (obj->id == id_plane)
		return (hit_plane(&obj->plane, r, hit));
	return (FALSE);
}
