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

t_color3	ray_tracer(t_ray *r, t_engine *e)
{
	t_hit	hit;

	hit = (t_hit){0};

	if (hit_object(e,r,&hit) == TRUE)
	{
		return (ray_color(r, e, &hit));
	}
	t_color3 blue = {{0.5,0.7,1.0}};
	t_color3 black = {{1.0,1.0,1.0}};
	t_vec3 unit_direction = unit_vec3(&r->dir);
	float a = 0.5 * (unit_direction.e[1] + 1.0);
	black = vec3_mul_const_copy(black, 1.0 - a); 
	blue = vec3_mul_const_copy(blue, a); 
	return (vec3_add_2inst_copy(black, blue));
}

t_color3	ray_color(t_ray *r, t_engine *e, t_hit *hit)
{
	int			i;
	t_color3	phong_color;
	t_color3	diffuse_color;
	t_color3	specular_color;

	phong_color = ray_color_ambient_light(e, hit);
	i = -1;
	while (e->scene.lights[++i])
	{
		if (in_shadow(e, e->scene.lights[i], hit) == FALSE)
		{
			diffuse_color = ray_color_diffuse_light(e->scene.lights[i], hit);
			vec3_add_2inst(&phong_color, &diffuse_color);
			specular_color = ray_color_specular_light(e->scene.lights[i], hit, r);
			vec3_add_2inst(&phong_color, &specular_color);
		}
	}
	return (phong_color);
}

t_color3	ray_color_ambient_light(t_engine *e, t_hit *hit)
{
	t_color3	ambient_color;

	ambient_color = vec3_mul_const_copy(e->scene.amb.color, e->scene.amb.intensity);
	unit_vec3(&ambient_color);
	vec3_mul_2inst_copy(ambient_color, hit->color);
	// printf("Ambient color\n");
	// print_vec3(&hit->color);
	// print_vec3(&ambient_color);
	return (ambient_color);
}

t_color3	ray_color_diffuse_light(t_light *l, t_hit *hit)
{
	t_ray		light_ray;
	t_color3	diffuse_color;
	float		intensity;

	light_ray.dir = vec3_sub_2inst_copy(l->center, hit->p);
	unit_vec3(&light_ray.dir);
	intensity = vec3_dot(&light_ray.dir, &hit->normal);
	if (intensity < 0)
		return ((t_color3){{0,0,0}});
	intensity *= l->brightness;
	diffuse_color = vec3_mul_const_copy(l->color, intensity);
	vec3_mul_2inst(&diffuse_color, &hit->color);
	return (diffuse_color);
}

/* https://www.fabrizioduroni.it/blog/post/2017/08/25/how-to-calculate-reflection-vector */
t_color3	ray_color_specular_light(t_light *l, t_hit *hit, t_ray *r)
{
	t_ray		reflected_ray;
	t_ray		light_ray;
	t_color3	specular_color;
	float		intensity;
	float		n_dot_l;

	light_ray.dir = vec3_sub_2inst_copy(l->center, hit->p);
	unit_vec3(&light_ray.dir);
	reflected_ray.dir = hit->normal;
	n_dot_l = vec3_dot(&hit->normal, &light_ray.dir);
	vec3_mul_const(&reflected_ray.dir, 2.0 * n_dot_l);
	vec3_sub_2inst(&reflected_ray.dir, &light_ray.dir);
	intensity = vec3_dot(&reflected_ray.dir, &r->dir);
	if (intensity < 0)
		return ((t_color3){{0,0,0}});
	intensity *= l->brightness;
	specular_color = vec3_mul_const_copy(l->color, intensity);
	vec3_mul_2inst(&specular_color, &hit->color);
	return (specular_color);
}

void set_face_normal(t_ray *r, t_hit *hit)
{
	if (vec3_dot(&r->dir, &hit->normal) > 0.0)
	{
		hit->inside_face = TRUE;
		vec3_mul_const(&hit->normal, -1.0);
	}
	hit->inside_face = FALSE;
}

t_bool	hit_sphere(t_sphere *s, t_ray *r, t_hit *hit)
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
	hit->p = point_at_ray(r, root);
	normal = vec3_sub_2inst_copy(hit->p, s->center);
	normal = unit_vec3(&normal);
	record_hit(r, hit, &normal, root);
	set_face_normal(r, hit);
	hit->color = s->color;
	return (TRUE);
}

/* Plane Intersection : https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection */
t_bool	hit_plane (t_plane *p, t_ray *r, t_hit *hit)
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
	record_hit(r, hit, &p->normal, t);
	hit->color = p->color;
	return (TRUE);
}

void	record_hit (t_ray *r, t_hit *hit, t_vec3 *normal, float t)
{
	hit->t = t;
	r->itv.max = t;
	hit->p = point_at_ray(r, hit->t);
	hit->normal = unit_vec3(normal);
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

t_bool hit_occluded(t_engine *e, t_ray *r, t_hit *hit)
{
	int		i;

	i = -1;
	while (e->scene.objects[++i])
	{
		if (hit_object_function_selecter(e->scene.objects[i], r, hit) == TRUE)
			return (TRUE);
	}
	return (FALSE);
}


t_bool hit_object_function_selecter(t_object *obj, t_ray *r, t_hit *hit)
{
	if (obj->id == id_sphere)
		return (hit_sphere(&obj->sphere, r, hit));
	else if (obj->id == id_plane)
		return (hit_plane(&obj->plane, r, hit));
	return (FALSE);
}
