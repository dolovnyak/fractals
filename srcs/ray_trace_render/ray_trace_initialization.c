/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace_initialization.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 06:23:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/16 23:46:47 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	initialization_canvas(t_canvas *canvas, float relation)
{
	canvas->width = relation;
	canvas->height = 1;
	canvas->min_distance = 1;
	canvas->max_distance = 9999999;
	canvas->camera = (mv_get_vector3d(0, 0, 0));
	canvas->x_rotation = 0;
	canvas->y_rotation = 0;
	canvas->z_rotation = 0;
}

void	initialization_scene(t_render *conf)
{
	t_lights		*lights;

	conf->get_fractal(&conf->objects_num, &conf->objects,
			conf->cl, conf->fractal);
	ft_printf("getting lights...\n");
	conf->lights_num = 3;
	lights = (t_lights*)malloc(sizeof(t_lights) * conf->lights_num);
	lights[0] = new_light_ambient(0.2);
	lights[1] = new_light_point(0.6, mv_get_vector3d(0, 3, -5));
	lights[2] = new_light_directional(0.2, mv_get_vector3d(1, 4, 4));
	conf->lights = lights;
	ft_printf("lights obtained\n");
}

void	initialization_fractal3d_safety(t_fractal3d *fractal)
{
	fractal->x_len = 100;
	fractal->y_len = 100;
	fractal->z_len = 100;
	fractal->left_b = -3.0;
	fractal->right_b = 3.0;
	fractal->top_b = -3;
	fractal->bot_b = 3;
	fractal->back_b = -3;
	fractal->front_b = 3;
	fractal->depth = 10000;
	fractal->const_x = 0.38;
	fractal->const_iy = 0.2;
	fractal->const_jz = 0.2;
}

void	initialization_fractal3d_fast(t_fractal3d *fractal)
{
	fractal->x_len = 200;
	fractal->y_len = 200;
	fractal->z_len = 200;
	fractal->left_b = -3.0;
	fractal->right_b = 3.0;
	fractal->top_b = -3;
	fractal->bot_b = 3;
	fractal->back_b = -3;
	fractal->front_b = 3;
	fractal->depth = 10000;
	fractal->const_x = 0.38;
	fractal->const_iy = 0.2;
	fractal->const_jz = 0.2;
}
