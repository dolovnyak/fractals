/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:47:49 by sbecker           #+#    #+#             */
/*   Updated: 2019/04/16 10:41:56 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void    initialization_mlx(t_conf *conf)
{
	t_mlx		*mlx;

	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	mlx->width = 800;
	mlx->height = 800;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "fractol");
	mlx->img_ptr = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp, &mlx->size_line, &mlx->endian);
	conf->mlx = mlx;
}

void    initialization_fractol(t_conf *conf)
{
	t_fractol	fractol;
	
	fractol.x_len = 800;
	fractol.y_len = 800;
	fractol.z_len = 800;
	fractol.left_b = -2.0;
	fractol.right_b = 2.0;
	fractol.top_b = -2.0;
	fractol.bot_b = 2.0;
	fractol.back_b = -2.0;
	fractol.front_b = 2.0;
	fractol.depth = 100;
	conf->fractol = fractol;
}

void	initialization_canvas(t_conf *conf)
{
	t_canvas	*canvas;

	canvas = (t_canvas*)malloc(sizeof(t_canvas));
	canvas->width = 1;
	canvas->height = 1;
	canvas->nigh_distance = 1;
	canvas->far_distance = 9999999;
	canvas->camera = (mv_get_vector3d(0, 0, 0));
	conf->canvas = canvas;
}

t_lights	new_light_ambient(float intensity)
{
	t_lights light;

	light.type = 1;
	light.intensity = intensity;
	return (light);
}

t_lights	new_light_point(float intensity, t_vector3d position)
{
	t_lights light;

	light.type = 2;
	light.intensity = intensity;
	light.position = position;
	return (light);
}

t_lights	new_light_directional(float intensity, t_vector3d direction)
{
	t_lights light;

	light.type = 3;
	light.intensity = intensity;
	light.direction = direction;
	return (light);
}

void    initialization_scene(t_conf *conf)
{
	t_object3d	*objects;
	t_lights	*lights;

	conf->objects = 0;
	conf->objects_num = 0;
	conf->lights_num = 2;
	lights = (t_lights*)malloc(sizeof(t_lights) * conf->lights_num);
	lights[0] = new_light_ambient(0.2);
	lights[1] = new_light_point(0.4, mv_get_vector3d(2, 1, 0));
//	lights[2] = new_light_directional(0.4, mv_get_vector3d(1, 4, 4));
	conf->lights = lights;
}
