#include "../includes/minirt.h"

void	free_arrays(char **arrays)
{
	int	i;

	i = 0;
	while (arrays != NULL && arrays[i])
	{
		free(arrays[i]);
		i++;
	}
	free(arrays);
}

int	return_and_free_array(int exit_value, char **arrays)
{
	free_arrays(arrays);
	return (exit_value);
}

void	ft_str_to_float(char *str, float *result)
{
	int		i;
	float	div;
	float	prec;
	float	sign;

	i = -1;
	div = 1.0;
	sign = 1.0;
	prec = 0.0;
	*result = 0.0;
	if (str && str[0] == '-')
		sign = -1.0;	
	*result = (float)ft_atoi(str);
	while (str[++i] && str[i] != '.');
	if (str[i] == '.')
	{
		while (str[++i] >= '0' && str[i] <= '9')
		{
			div *= 10.0;
			prec += (str[i] - '0') / div;
		}
		*result += sign * prec;
	}
}

t_bool is_digit(char c)
{
	if ((c >= '0' && c <= '9'))
		return (TRUE);
	else
		return (FALSE);
}

t_bool is_float(char *num)
{
	int i;
	
	i = -1;
	if (num[0] == '-')
		i = 0;
	while (num[++i] && num[i] != '.')
	{
		if (is_digit(num[i]) == FALSE)
			return (FALSE);
	}
	if (num[i] == '.')
	{
		while (num[++i])
		{
			if (is_digit(num[i]) == FALSE)
				return (FALSE);
		}
	}
	return (TRUE);	
}

t_bool is_int_color(char *num)
{
	int i;
	int	result;
	
	i = -1;
	result = 0;
	if (num[0] == '-' || ft_strlen(num) == 0)
		return (FALSE);
	while (num[++i])
	{
		if (is_digit(num[i]) == FALSE)
			return (FALSE);
		result *= 10;
		result += num[i] - '0';
		if (result > MAX_INT_COLOR)
			return (FALSE);		
	}
	return (TRUE);	
}