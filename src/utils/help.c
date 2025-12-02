/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42luxembourg.l  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:52:28 by tsilveir          #+#    #+#             */
/*   Updated: 2025/12/02 14:52:30 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	show_controls1(void)
{
	printf("\n");
	printf("╔════════════════════════════════════════════════════════════╗\n");
	printf("║                     MINIRT CONTROLS                        ║\n");
	printf("╚════════════════════════════════════════════════════════════╝\n");
	printf("\n");
	printf("┌─ MOVEMENT / TRANSLATION ───────────────────────────────────┐\n");
	printf("│                                                            │\n");
	printf("│                           W (UP)                           │\n");
	printf("│                             ▲                              │\n");
	printf("│              A (LEFT) ◄─────┼─────► D (RIGHT)              │\n");
	printf("│                             ▼                              │\n");
	printf("│                          S (DOWN)                          │\n");
	printf("│                                                            │\n");
	printf("│                R (FORWARD)  /  F (BACKWARD)                │\n");
	printf("│                                                            │\n");
	printf("└────────────────────────────────────────────────────────────┘\n");
	printf("\n");
}

void	show_controls2(void)
{
	printf("┌─ ROTATION ─────────────────────────────────────────────────┐\n");
	printf("│                                                            │\n");
	printf("│                           I (UP)                           │\n");
	printf("│                            ▲                               │\n");
	printf("│             J (LEFT) ◄─────┼─────► L (RIGHT)               │\n");
	printf("│                            ▼                               │\n");
	printf("│                        K (DOWN)                            │\n");
	printf("│                                                            │\n");
	printf("└────────────────────────────────────────────────────────────┘\n");
	printf("\n");
	printf("┌─ OTHER ────────────────────────────────────────────────────┐\n");
	printf("│                                                            │\n");
	printf("│           ESC - Close Application                          │\n");
	printf("│                                                            │\n");
	printf("└────────────────────────────────────────────────────────────┘\n");
	printf("\n");
}

void	show_help(void)
{
	printf("\n");
	printf(" +--------------- Let me help you! --------------+\n");
	printf(" |                                               |\n");
	printf(" | Usage: ./bin/minirt [file.rt]                 |\n");
	printf(" |                                               |\n");
	printf(" | e.g: ./bin/minirt test1.rt                    |\n");
	printf(" |                                               |\n");
	printf(" +-----------------------------------------------+\n");
	show_controls1();
	show_controls2();
	exit(EXIT_SUCCESS);
}
