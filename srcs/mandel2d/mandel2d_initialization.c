/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_mandelbrot_2d.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 04:17:38 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/13 21:50:21 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal2d.h"

void	mandel2d_initialization(t_fractal2d *conf)
{
	conf->left_b = -3.0 * conf->mlx->relation;
	conf->right_b = 3.0 * conf->mlx->relation;
	conf->top_b = -3.0;
	conf->bot_b = 3.0;
	conf->depth = 255;
	conf->color_mult = 2000000;
	conf->radius = 4;
}
