/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 12:53:00 by sbecker           #+#    #+#             */
/*   Updated: 2019/04/04 00:56:42 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int     keyboard_event(int keycode, t_all *all)
{
	double	tmp;

	if (all->control_flag == 1)
	{
		tmp = (all->right_b - all->left_b) / 20;
		if (keycode == 0)
		{
			all->right_b += tmp;
			all->left_b += tmp;
		}
		if (keycode == 2)
		{
			all->right_b -= tmp;
			all->left_b -= tmp;
		}
		if (keycode == 1)
		{
			all->top_b -= tmp;
			all->bot_b -= tmp;
		}
		if (keycode == 13)
		{
			all->bot_b += tmp;
			all->top_b += tmp;
		}
	}
	else
	{
		if (keycode == 0)
			all->center_x += 20;
		if (keycode == 2)
			all->center_x -= 20;
		if (keycode == 1)
			all->center_y -= 20;
		if (keycode == 13)
			all->center_y += 20;
	}
	if (keycode == 53)
		exit(0);
	if (keycode == 12)
		all->angle_z -= 0.05;
	if (keycode == 14)
		all->angle_z += 0.05;
	if (keycode == 8)
		all->color_mult = rand() % 99999999;
	if (keycode == 256)
		all->control_flag = 1;
	return (0);
}

int		key_release(int keycode, t_all *all)
{
	if (keycode == 256)
		all->control_flag = 0;
	return (0);
}

int		exit_event(void *param)
{
	param = 0;
	exit(0);
}
