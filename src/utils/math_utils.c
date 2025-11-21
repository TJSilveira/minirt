#include "../includes/minirt.h"

void	solve_quadratic(t_quadratic *q)
{
	q->discriminate = (q->h * q->h - q->a * q->c);

	if (q->discriminate < 0 )
		q->has_solutions = FALSE;
	else
	{
		q->has_solutions = TRUE;
		q->t_minus = (q->h - sqrt(q->discriminate)) / q->a;
		q->t_plus = (q->h + sqrt(q->discriminate)) / q->a;
	}
}