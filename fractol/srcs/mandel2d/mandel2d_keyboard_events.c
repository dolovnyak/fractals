/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel2d_keyboard_events.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 04:57:46 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/07 08:34:24 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandel2d.h"

int     mandel2d_keyboard_event(int keycode, t_mandel2d *conf)
{
	double  tmp;

	tmp = (conf->right_b - conf->left_b) / 4;
	if (keycode == 53)
		exit(0);
	if (keycode == 2)
	{
		conf->right_b += tmp / conf->mlx->relation;
		conf->left_b += tmp / conf->mlx->relation;
	}
	if (keycode == 0)
	{
		conf->right_b -= tmp / conf->mlx->relation;
		conf->left_b -= tmp / conf->mlx->relation;
	}
	if (keycode == 13)
	{
		conf->top_b -= tmp;
		conf->bot_b -= tmp;
	}
	if (keycode == 1)
	{
		conf->bot_b += tmp;
		conf->top_b += tmp;
	}
	if (keycode == 8)
		conf->color_mult = rand() % 99999999; //TODO
	return (0);
}
