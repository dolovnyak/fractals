/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_mandelbrot_2d.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 04:17:38 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/07 09:59:30 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandel2d.h"

void	mandel2d_initialization(t_mandel2d *conf)
{
	conf->left_b = -3.0 * conf->mlx->relation;
	conf->right_b = 3.0 * conf->mlx->relation;
	conf->top_b = -3.0;
	conf->bot_b = 3.0;
	conf->depth = 255;
}
