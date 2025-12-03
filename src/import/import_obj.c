/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42luxembourg.l  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:51:19 by tsilveir          #+#    #+#             */
/*   Updated: 2025/12/02 14:51:22 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	rt_import_sphere(char **params, t_engine *e)
{
	int			i;
	t_object	*sp;

	sp = malloc(sizeof(t_object));
	if (!sp)
		error_handler("Malloc was not successful.\n", e);
	i = 0;
	while (params[i])
		i++;
	if (i != NUM_PARAM_SPHERE)
		return (EXIT_FAILURE);
	if (rt_import_vec3(params[0], &sp->obj_union.sphere.center) == EXIT_FAILURE
		|| rt_import_float_non_negative(params[1], &sp->obj_union.sphere.ray) == EXIT_FAILURE
		|| rt_import_color(params[2],
			&sp->obj_union.sphere.color) == EXIT_FAILURE)
	{
		free(sp);
		return (EXIT_FAILURE);
	}
	sp->id = id_sphere;
	add_object_to_scene(e, sp);
	return (EXIT_SUCCESS);
}

int	rt_import_plane(char **params, t_engine *e)
{
	int			i;
	t_object	*pl;

	i = -1;
	pl = malloc(sizeof(t_object));
	if (!pl)
		error_handler("Malloc was not successful.\n", e);
	while (params[++i])
		;
	if (i != NUM_PARAM_PLANE)
		return (EXIT_FAILURE);
	if (rt_import_vec3(params[0], &pl->obj_union.plane.point) == EXIT_FAILURE
		|| rt_import_vec3_normalized(params[1],
			&pl->obj_union.plane.normal) == EXIT_FAILURE
		|| rt_import_color(params[2],
			&pl->obj_union.plane.color) == EXIT_FAILURE)
	{
		free(pl);
		return (EXIT_FAILURE);
	}
	pl->id = id_plane;
	pl->obj_union.plane.normal = unit_vec3(&pl->obj_union.plane.normal);
	add_object_to_scene(e, pl);
	return (EXIT_SUCCESS);
}

int	rt_import_light(char **params, t_engine *e)
{
	int		i;
	t_light	*l;

	i = -1;
	l = malloc(sizeof(t_light));
	if (!l)
		error_handler("Malloc was not successful.\n", e);
	while (params[++i])
		;
	if (i != NUM_PARAM_LIGHT)
		return (EXIT_FAILURE);
	if (rt_import_vec3(params[0], &l->center) == EXIT_FAILURE
		|| rt_import_float_between_01(params[1], &l->brightness) == EXIT_FAILURE
		|| rt_import_color(params[2], &l->color) == EXIT_FAILURE)
	{
		free(l);
		return (EXIT_FAILURE);
	}
	add_light_to_scene(e, l);
	return (EXIT_SUCCESS);
}

int	rt_import_ambient(char **params, t_engine *e)
{
	int	i;

	if (e->scene.amb)
		return (EXIT_FAILURE);
	e->scene.amb = malloc(sizeof(t_ambient));
	if (!e->scene.amb)
		error_handler("Malloc was not successful.\n", e);
	i = -1;
	while (params[++i])
		;
	if (i != NUM_PARAM_AMBIENT)
		return (EXIT_FAILURE);
	if (rt_import_float_between_01(params[0], &e->scene.amb->intensity) == EXIT_FAILURE
		|| rt_import_color(params[1], &e->scene.amb->color) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	e->scene.amb->has_ambient = 1;
	return (EXIT_SUCCESS);
}

int	rt_import_camera(char **params, t_engine *e)
{
	int	i;

	if (e->cam)
		return (EXIT_FAILURE);
	e->cam = malloc(sizeof(t_camera));
	if (!e->cam)
		error_handler("Malloc was not successful.\n", e);
	i = -1;
	while (params[++i])
		;
	if (i != NUM_PARAM_CAMERA)
		return (EXIT_FAILURE);
	if (rt_import_vec3(params[0], &e->cam->camera_center) == EXIT_FAILURE
		|| rt_import_vec3_normalized(params[1],
			&e->cam->direction) == EXIT_FAILURE || rt_import_fov(params[2],
			&e->cam->fov) == EXIT_FAILURE)
		error_handler("Camera inputs not provided correctly\n", e);
	return (EXIT_SUCCESS);
}
