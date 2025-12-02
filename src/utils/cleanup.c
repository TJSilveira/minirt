/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42luxembourg.l  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:51:45 by tsilveir          #+#    #+#             */
/*   Updated: 2025/12/02 14:51:47 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	cleanup_engine(t_engine *e)
{
	cleanup_scene(e);
	cleanup_image(e);
	if (e->window)
	{
		mlx_destroy_window(e->mlx, e->window);
		e->window = NULL;
	}
	if (e->mlx)
	{
		mlx_destroy_display(e->mlx);
		free(e->mlx);
		e->mlx = NULL;
	}
}

void	cleanup_scene(t_engine *e)
{
	size_t	i;

	i = 0;
	while (e->scene.lights && i < e->scene.l_count)
		free(e->scene.lights[i++]);
	if (e->scene.lights)
		free(e->scene.lights);
	e->scene.lights = NULL;
	i = 0;
	while (e->scene.objects && i < e->scene.obj_count)
		free(e->scene.objects[i++]);
	if (e->scene.objects)
		free(e->scene.objects);
	e->scene.objects = NULL;
	if (e->scene.amb)
		free(e->scene.amb);
	e->scene.amb = NULL;
	if (e->cam)
		free(e->cam);
	e->cam = NULL;
}

void	cleanup_image(t_engine *e)
{
	if (!e)
		return ;
	if (e->img.img && e->mlx)
	{
		mlx_destroy_image(e->mlx, e->img.img);
		e->img.img = NULL;
	}
}
