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

int	rt_import_color(char *param, t_vec3 *vec)
{
	char	**nums;
	int		i;

	if (ft_strchr(param, '.') != NULL)
		return (EXIT_FAILURE);
	nums = ft_split(param, ',');
	if (!(nums && nums[0] && nums[1] && nums[2] && !nums[3]))
		return (return_and_free_array(EXIT_FAILURE, nums));
	i = -1;
	while (++i < 3)
	{
		if (is_int_color(nums[i]) == FALSE)
			return (return_and_free_array(EXIT_FAILURE, nums));
	}
	i = -1;
	while (nums[++i])
		ft_str_to_float(nums[i], &vec->e[i]);
	vec3_div_const(vec, MAX_INT_COLOR);
	return (return_and_free_array(EXIT_SUCCESS, nums));
}

int	rt_import_float_non_negative(char *param, float *result)
{
	if (is_float(param) == FALSE)
		return (EXIT_FAILURE);
	ft_str_to_float(param, result);
	if (*result <= 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	rt_import_float_between_01(char *param, float *result)
{
	if (is_float(param) == FALSE)
		return (EXIT_FAILURE);
	ft_str_to_float(param, result);
	if (*result < 0 || *result > 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	rt_import_fov(char *param, float *result)
{
	if (is_float(param) == FALSE)
		return (EXIT_FAILURE);
	ft_str_to_float(param, result);
	if (*result <= 0.0 || *result >= 180.0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	rt_import_vec3(char *param, t_vec3 *vec)
{
	char	**nums;
	int		i;

	nums = ft_split(param, ',');
	if (!(nums && nums[0] && nums[1] && nums[2] && !nums[3]))
		return (return_and_free_array(EXIT_FAILURE, nums));
	i = -1;
	while (++i < 3)
	{
		if (is_float(nums[i]) == FALSE)
			return (return_and_free_array(EXIT_FAILURE, nums));
	}
	i = -1;
	while (nums[++i])
		ft_str_to_float(nums[i], &vec->e[i]);
	return (return_and_free_array(EXIT_SUCCESS, nums));
}

int	rt_import_vec3_normalized(char *param, t_vec3 *vec)
{
	char	**nums;
	int		i;

	nums = ft_split(param, ',');
	if (!(nums && nums[0] && nums[1] && nums[2] && !nums[3]))
		return (return_and_free_array(EXIT_FAILURE, nums));
	i = -1;
	while (++i < 3)
	{
		if (is_float(nums[i]) == FALSE)
			return (return_and_free_array(EXIT_FAILURE, nums));
	}
	i = -1;
	while (nums[++i])
		ft_str_to_float(nums[i], &vec->e[i]);
	if (fabs(vec3_length(vec) - 1.0f) < EPSILON)
		return (return_and_free_array(EXIT_SUCCESS, nums));
	return (return_and_free_array(EXIT_FAILURE, nums));
}
