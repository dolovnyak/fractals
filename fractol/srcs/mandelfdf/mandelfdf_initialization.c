/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelfdf_initialization.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:08:28 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/07 11:02:27 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelfdf.h"

void	mandelfdf_initialization(t_mandelfdf *conf)
{
	conf->center_x = 0;
	conf->center_y = 0;
	conf->zoom = 1;
	conf->left_b = -2.0 * conf->mlx->relation;
	conf->right_b = 1.0 * conf->mlx->relation;
	conf->top_b = -1.5;
	conf->bot_b = 1.5;
	conf->depth = 255;
	conf->angle_z = 0.5;
	conf->angle_x = 2.1;
	conf->center_x = conf->mlx->width / 2;
	conf->center_y = conf->mlx->height / 2;
	conf->control_flag = 0;
}
