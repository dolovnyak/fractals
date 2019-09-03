/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   juliafdf_initialization.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 09:36:52 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/12 09:43:53 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractalfdf.h"

void	juliafdf_initialization(t_fractalfdf *conf)
{
	conf->fractal.left_b = -3.0 * conf->fractal.mlx->relation;
	conf->fractal.right_b = 3.0 * conf->fractal.mlx->relation;
	conf->fractal.top_b = -3.0;
	conf->fractal.bot_b = 3.0;
	conf->fractal.depth = 500;
	conf->fractal.color_mult = 100000;
	conf->fractal.mouse_move_flag = 1;
	conf->fractal.const_real = 0.0;
	conf->fractal.const_imagin = 0.0;
	conf->fractal.radius = 4;
	conf->center_x = conf->fractal.mlx->width / 2;
	conf->center_y = conf->fractal.mlx->height / 2;
	conf->zoom = 1;
	conf->angle_z = 0;
	conf->angle_x = 1.57;
	conf->shift_flag = 0;
	conf->button_flag = 0;
}
