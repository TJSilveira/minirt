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

int	rt_importer_params(char **params, t_engine *e)
{
	if (ft_strncmp(params[0], "sp", 2) == 0 && ft_strlen(params[0]) == 2)
		return (rt_import_sphere(&params[1], e));
	if (ft_strncmp(params[0], "pl", 2) == 0 && ft_strlen(params[0]) == 2)
		return (rt_import_plane(&params[1], e));
	if (ft_strncmp(params[0], "L", 1) == 0 && ft_strlen(params[0]) == 1)
		return (rt_import_light(&params[1], e));
	if (ft_strncmp(params[0], "A", 1) == 0 && ft_strlen(params[0]) == 1)
		return (rt_import_ambient(&params[1], e));
	if (ft_strncmp(params[0], "C", 1) == 0 && ft_strlen(params[0]) == 1)
		return (rt_import_camera(&params[1], e));
	free_arrays(params);
	return (EXIT_FAILURE);
}

char	**rt_file_parser(char *buffer)
{
	char	**res;
	int		len;

	len = ft_strlen(buffer);
	if (len == 1 && buffer[0] == '\n')
		return (NULL);
	if (len > 0 && buffer[len - 1] == '\n')
		buffer[len - 1] = 0;
	res = ft_split(buffer, ' ');
	return (res);
}

void	rt_extension_check(char *argv[])
{
	const char	*ext;

	ext = ft_strrchr(argv[1], '.');
	if (!ext || ft_strncmp(ext, ".rt", 3) != 0)
	{
		ft_putstr_fd("The file used does not comply with the extension \
			requirements. You need to provide a .rt file\n",
			STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
