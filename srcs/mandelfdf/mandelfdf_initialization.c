/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelfdf_initialization.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:08:28 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/12 09:36:26 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractalfdf.h"

void	mandelfdf_initialization(t_fractalfdf *conf)
{
	conf->fractal.left_b = -2.0 * conf->fractal.mlx->relation;
	conf->fractal.right_b = 1.0 * conf->fractal.mlx->relation;
	conf->fractal.top_b = -1.5;
	conf->fractal.bot_b = 1.5;
	conf->fractal.depth = 500;
	conf->fractal.color_mult = 2000000;
	conf->zoom = 1;
	conf->angle_z = 0;
	conf->angle_x = 1.57;
	conf->center_x = conf->fractal.mlx->width / 2;
	conf->center_y = conf->fractal.mlx->height / 2;
	conf->shift_flag = 0;
	conf->fractal.radius = 4;
	conf->button_flag = 0;
}
