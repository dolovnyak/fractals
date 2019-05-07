/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel2d_mouse_events.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 04:52:01 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/07 08:36:19 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandel2d.h"

int	mandel2d_mouse_press(int button, int x, int y, t_mandel2d *conf)
{
	double  comp_x;
	double  comp_y;
	double  dx;
	double  dy;

	if (button == 4)
	{
		dx = (conf->right_b - conf->left_b);
		dy = (conf->bot_b - conf->top_b);
		comp_x = dx / conf->mlx->width * x;
		comp_y = dy / conf->mlx->height * y;
		conf->left_b = conf->left_b + comp_x / 8;
		conf->right_b = conf->right_b - (dx - comp_x) / 8;
		conf->top_b = conf->top_b + comp_y / 8;
		conf->bot_b = conf->bot_b - (dy - comp_y) / 8;
	}
	else if (button == 5)
	{
		comp_x = (conf->right_b - conf->left_b) / 8;
		comp_y = (conf->bot_b - conf->top_b) / 8;
		conf->left_b -= comp_x;
		conf->right_b += comp_x;
		conf->top_b -= comp_y;
		conf->bot_b += comp_y;
	}
	return (0);
}

/*int	exit_event(t_cl *cl)
{
	ft_exit(cl);
}*/
