/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42luxembourg.l  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:52:58 by tsilveir          #+#    #+#             */
/*   Updated: 2025/12/02 14:53:00 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	free_arrays(char **arrays)
{
	int	i;

	i = 0;
	while (arrays != NULL && arrays[i])
	{
		free(arrays[i]);
		arrays[i] = NULL;
		i++;
	}
	free(arrays);
	arrays = NULL;
}

int	return_and_free_array(int exit_value, char **arrays)
{
	free_arrays(arrays);
	return (exit_value);
}

void	error_handler(char *msg, t_engine *e)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	cleanup_engine(e);
	exit(EXIT_FAILURE);
}
