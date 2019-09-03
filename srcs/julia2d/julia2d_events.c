/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel2d_keyboard_events.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 04:57:46 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/15 17:56:25 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal2d.h"

int	julia2d_key_press(int keycode, t_fractal2d *conf)
{
	if (keycode == 11 && conf->mouse_move_flag == 1)
		conf->mouse_move_flag = 0;
	else if (keycode == 11)
		conf->mouse_move_flag = 1;
	common2d_key_press(keycode, conf);
	return (0);
}

int	julia2d_mouse_move(int x, int y, t_fractal2d *conf)
{
	float	tmp_for_radius;

	if (conf->mouse_move_flag == 1)
	{
		tmp_for_radius = fabs(conf->const_real) + fabs(conf->const_imagin);
		conf->const_real = (x - conf->center_x / 2) * 0.001;
		conf->const_imagin = (y - conf->center_y / 2) * 0.001;
		if (tmp_for_radius > fabs(conf->const_real) + fabs(conf->const_imagin))
			conf->radius += 0.1;
		else if (conf->radius >= 1.5)
			conf->radius -= 0.1;
	}
	return (0);
}
