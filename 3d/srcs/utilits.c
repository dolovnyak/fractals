/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/04/12 03:20:19 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

t_color     get_rgb(int r, int g, int b)
{
	t_color color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color		rgb_mult_num(t_color rgb, float num)
{
	rgb.r *= num;
	rgb.g *= num;
	rgb.b *= num;

	rgb.r = rgb.r > 255 ? 255 : rgb.r;
	rgb.g = rgb.g > 255 ? 255 : rgb.g;
	rgb.b = rgb.b > 255 ? 255 : rgb.b;
	return (rgb);
}

t_vector3d  get_cam_ray(int x, int y, t_conf *conf)
{
	t_vector3d  canvas_cell;
	t_vector3d	cam_ray;

	x -= (float)conf->mlx->width / 2;
	y -= (float)conf->mlx->height / 2;
	canvas_cell.x = (float)x * conf->canvas->width / (float)conf->mlx->width;
	canvas_cell.y = (float)y * conf->canvas->height / (float)conf->mlx->height;
	canvas_cell.z = 1;
	cam_ray = mv_minus(canvas_cell, conf->canvas->camera);
	return (cam_ray);
}
