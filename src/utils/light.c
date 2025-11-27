#include "../includes/minirt.h"

t_bool in_shadow(t_engine *e, t_light *l, t_hit *hit)
{
	t_ray	shadow_ray;

	shadow_ray.dir = vec3_sub_2inst_copy(l->center, hit->p);
	shadow_ray.orig = hit->p;
	shadow_ray.itv.min = EPSILON;
	shadow_ray.itv.max = TMAX;
	return (hit_occluded(e, &shadow_ray));
}