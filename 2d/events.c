/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 12:53:00 by sbecker           #+#    #+#             */
/*   Updated: 2019/04/02 01:32:43 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int     keyboard_event(int keycode, t_all *all)
{
	double	tmp;

	tmp = (all->right_b - all->left_b) / 4;
	if (keycode == 53)
		exit(0);
	if (keycode == 2)
	{
		all->right_b += tmp;
		all->left_b += tmp;
	}
	if (keycode == 0)
	{
		all->right_b -= tmp;
		all->left_b -= tmp;
	}
	if (keycode == 13)
	{
		all->top_b -= tmp;
		all->bot_b -= tmp;
	}
	if (keycode == 1)
	{
		all->bot_b += tmp;
		all->top_b += tmp;
	}
	if (keycode == 8)
		all->color_mult = rand() % 99999999;
	return (0);
}

int     mouse_event(int button, int x, int y, t_all *all)
{
	double	basis;
	double	comp_x;
	double	comp_y;
	double	section_a;
	double	section_b;

	if (button == 4)
	{
		double	dx = (all->right_b - all->left_b);
		double	dy = (all->bot_b - all->top_b);
		comp_x = dx / all->s_width * x;
		comp_y = dy / all->s_height * y;
/*		section_a = comp_x;
		section_b = dx - comp_x;
		section_b /= 1.5;
		section_a /= 1.5;*/
//		printf ("b: %f\n", dx - comp_x);
//		printf ("d: %f\n", (dx - comp_x) / 1.5);
//		printf ("a: %f\n", comp_x);
//		printf ("c: %f\n", comp_x / 1.5);
		all->left_b = all->left_b + comp_x /8;
		all->right_b = all->right_b - (dx - comp_x) / 8;
		all->top_b = all->top_b + comp_y / 8;
		all->bot_b = all->bot_b - (dy - comp_y) / 8;
	}
	else if (button == 5)
	{
		comp_x = (all->right_b - all->left_b) / 8;
		comp_y = (all->bot_b - all->top_b) / 8;
		all->left_b -= comp_x;
		all->right_b += comp_x;
		all->top_b -= comp_y;
		all->bot_b += comp_y;
	}
	return (0);
}
