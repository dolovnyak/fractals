/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 08:36:32 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/16 18:31:36 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "config.h"
# include "fractal3d.h"

typedef struct	s_render
{
	int			lights_num;
	int			objects_num;
	t_object3d	*objects;
	t_canvas	canvas;
	t_lights	*lights;
	t_mlx		*mlx;
	t_cl		*cl;
	t_fractal3d	*fractal;
	void		(*get_fractal)(int*, t_object3d**, t_cl*, t_fractal3d*);
	cl_mem		mem_img;
	cl_mem		mem_objects;
	cl_mem		mem_lights;

}				t_render;

void			initialization_canvas(t_canvas *canvas, float relation);
void			initialization_scene(t_render *conf);
void			initialization_fractal3d_safety(t_fractal3d *fractal);
void			initialization_fractal3d_fast(t_fractal3d *fractal);
void			mandelbrot_3d(int *objects_num, t_object3d **objects, t_cl *cl,
		t_fractal3d *conf);
void			julia_3d(int *objects_num, t_object3d **objects, t_cl *cl,
		t_fractal3d *conf);
void			render_safety(t_cl *cl, t_render *conf);
void			render_fast(t_cl *cl, t_render *conf);
int				rt_key_press_safety(int key, t_render *conf);
int				rt_key_press_fast(int key, t_render *conf);
int				refresh_rt_safety(t_render *conf);
int				refresh_rt_fast(t_render *conf);
int				get_num_objects(t_fractal_point **all_points,
		int xy_len, int z_len);
t_object3d		*get_objects(int objects_num, t_fractal_point **all_points,
		int xy_len, int z_len);
void			get_mandel3d(int *objects_num, t_object3d *objects, t_cl *cl,
		t_fractal3d *conf);

#endif
