/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   juliafdf_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 16:26:06 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/15 19:57:09 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractalfdf.h"

int		juliafdf_key_press(int keycode, t_fractalfdf *conf)
{
	if (keycode == 11 && conf->fractal.mouse_move_flag == 1)
		conf->fractal.mouse_move_flag = 0;
	else if (keycode == 11)
		conf->fractal.mouse_move_flag = 1;
	else
		commonfdf_keyboard_press(keycode, conf);
	return (0);
}

int		juliafdf_mouse_move(int x, int y, t_fractalfdf *conf)
{
	float	tmp_for_radius;

	if (conf->fractal.mouse_move_flag == 1)
	{
		tmp_for_radius = fabs(conf->fractal.const_real)
			+ fabs(conf->fractal.const_imagin);
		conf->fractal.const_real = (x - conf->center_x / 2) * 0.001;
		conf->fractal.const_imagin = (y - conf->center_y / 2) * 0.001;
		if (tmp_for_radius > fabs(conf->fractal.const_real)
				+ fabs(conf->fractal.const_imagin))
			conf->fractal.radius += 0.1;
		else if (conf->fractal.radius >= 1.5)
			conf->fractal.radius -= 0.1;
	}
	else
		commonfdf_mouse_move(x, y, conf);
	return (0);
}
