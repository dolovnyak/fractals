/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:47:49 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/02 06:06:58 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void    initialization_fractal(t_fractal *fractal)
{
	fractal->x_len = 800;
	fractal->y_len = 800;
	fractal->z_len = 800;
	fractal->left_b = -2.0;
	fractal->right_b = 2.0;
	fractal->top_b = -2.0;
	fractal->bot_b = 2.0;
	fractal->back_b = -2.0;
	fractal->front_b = 2.0;
	fractal->depth = 10000;
}

void    initialization_mlx(t_mlx *mlx)
{
	mlx->width = 800;
	mlx->height = 800;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "mandelbrot");
	mlx->img_ptr = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp, &mlx->size_line, &mlx->endian);
}

void	initialization_canvas(t_canvas *canvas)
{
	canvas->width = 1;
	canvas->height = 1;
	canvas->min_distance = 1;
	canvas->max_distance = 9999999;
//	canvas->x_rotation = 0;
//	canvas->y_rotation = 0;
//	canvas->z_rotation = 0;
	canvas->camera = (mv_get_vector3d(0, 0, 0));
}

void    initialization_scene(t_conf *conf)
{
	size_t			xy_size;
	t_object3d		*objects;
	t_lights		*lights;
	t_fractal_point	**all_points;

	xy_size = conf->fractal.x_len * conf->fractal.y_len;
	all_points = get_fractal(conf, xy_size);
	conf->objects_num = get_num_objects(all_points, xy_size, conf->fractal.z_len);
	get_objects(conf, all_points, xy_size, conf->fractal.z_len);
	conf->lights_num = 1;
	lights = (t_lights*)malloc(sizeof(t_lights) * conf->lights_num);
	lights[0] = new_light_ambient(0.8);
//	lights[1] = new_light_point(0.6, mv_get_vector3d(0, 3, -5));
//	lights[2] = new_light_directional(0.3, mv_get_vector3d(1, 4, 4));
	conf->lights = lights;
}
