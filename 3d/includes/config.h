/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 02:46:07 by sbecker           #+#    #+#             */
/*   Updated: 2019/04/16 11:03:07 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <OPENCL/opencl.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"
# include "utilits.h"
# include "fractol.h"
# include "RTv1.h"
# include <stdio.h>

typedef struct	s_CL
{
	cl_command_queue	queue;
	cl_context			context;
	cl_kernel			kernel;
}				t_CL;

typedef struct  s_mlx
{
	void    *img_ptr;
	void    *mlx;
	void    *win;
	char    *img_data;
	int     bpp;
	int     endian;
	int     size_line;
	int     width;
	int     height;
}               t_mlx;

typedef struct  s_canvas  //потом это будет камерой
{
	float       width;
	float       height;
	float       nigh_distance;
	float		far_distance;
	t_vector3d  camera;
}               t_canvas;

typedef struct  s_config
{
	int         lights_num;
	int         objects_num;
	t_object3d  *objects;
	t_canvas    *canvas;
	t_lights	*lights;
	t_mlx       *mlx;
	t_fractol	fractol;
	t_CL		CL;
}               t_conf;

void		initialization_mlx(t_conf *conf);
void		initialization_canvas(t_conf *conf);
void		initialization_scene(t_conf *conf);
int			keyboard_events(int keycode, t_conf *conf);
t_vector3d	get_cam_ray(int x, int y, t_conf *conf);
void		initialization_fractol(t_conf *conf);
void		initialization_CL(t_conf *conf);

#endif
