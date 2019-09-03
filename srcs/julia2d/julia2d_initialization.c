/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_mandelbrot_2d.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 04:17:38 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/12 10:38:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal2d.h"

void	julia2d_initialization(t_fractal2d *conf)
{
	conf->left_b = -3.0 * conf->mlx->relation;
	conf->right_b = 3.0 * conf->mlx->relation;
	conf->top_b = -3.0;
	conf->bot_b = 3.0;
	conf->depth = 255;
	conf->color_mult = 1000000;
	conf->mouse_move_flag = 1;
	conf->center_x = conf->mlx->width / 2;
	conf->center_y = conf->mlx->height / 2;
	conf->const_real = 0.0;
	conf->const_imagin = 0.0;
	conf->radius = 4;
}
