/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_mandelbrot_2d.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 04:17:38 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/13 18:43:28 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal2d.h"

void	newton_initialization(t_fractal2d *conf)
{
	conf->left_b = -1000000.0 * conf->mlx->relation;
	conf->right_b = 1000000.0 * conf->mlx->relation;
	conf->top_b = -1000000.0;
	conf->bot_b = 1000000.0;
	conf->depth = 100;
	conf->color_mult = 1;
	conf->radius = 1;
}
