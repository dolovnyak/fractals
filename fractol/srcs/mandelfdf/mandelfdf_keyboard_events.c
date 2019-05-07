/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelfdf_keyboard_events.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:09:00 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/07 10:52:27 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelfdf.h"

int		mandelfdf_keyboard_press(int keycode, t_mandelfdf *conf)
{
	double	tmp;

	if (conf->control_flag == 1)
	{
		tmp = (conf->right_b - conf->left_b) / 20;
		if (keycode == 0)
		{
			conf->right_b += tmp;
			conf->left_b += tmp;
		}
		if (keycode == 2)
		{
			conf->right_b -= tmp;
			conf->left_b -= tmp;
		}
		if (keycode == 1)
		{
			conf->top_b -= tmp;
			conf->bot_b -= tmp;
		}
		if (keycode == 13)
		{
			conf->bot_b += tmp;
			conf->top_b += tmp;
		}
	}
	else
	{
		if (keycode == 0)
			conf->center_x += 20;
		if (keycode == 2)
			conf->center_x -= 20;
		if (keycode == 1)
			conf->center_y -= 20;
		if (keycode == 13)
			conf->center_y += 20;
	}
	if (keycode == 53)
		exit(0);
	if (keycode == 12)
		conf->angle_z -= 0.05;
	if (keycode == 14)
		conf->angle_z += 0.05;
	if (keycode == 8)
		conf->color_mult = rand() % 99999999;
	if (keycode == 256)
		conf->control_flag = 1;
	return (0);
}

int		mandelfdf_key_release(int keycode, t_mandelfdf *conf)
{
	if (keycode == 256)
		conf->control_flag = 0;
	return (0);
}

/*int		exit_event(void *param)
{
	param = 0;
	exit(0);
}*/
