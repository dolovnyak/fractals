/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fractal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:24:19 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/16 22:58:36 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal3d.h"
#include "render.h"

static void				get_steps(t_fractal3d *conf)
{
	conf->step_x = (conf->right_b - conf->left_b) /
		conf->x_len;
	conf->step_y = (conf->bot_b - conf->top_b) /
		conf->y_len;
	conf->step_z = (conf->front_b - conf->back_b) /
		conf->z_len;
}

static t_fractal_point	*get_points_cl(t_fractal3d *conf, t_cl *cl,
		int *z, size_t global_size)
{
	int				err;
	t_fractal_point	*xy_points;
	cl_mem			mem_arr_structs;

	xy_points = (t_fractal_point*)malloc(sizeof(t_fractal_point)
			* global_size);
	mem_arr_structs = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			global_size * sizeof(t_fractal_point), NULL, &err);
	err = clSetKernelArg(cl->kernel_mandel3d, 0, sizeof(cl_mem),
			&mem_arr_structs);
	err = clSetKernelArg(cl->kernel_mandel3d, 1, sizeof(int), z);
	err = clSetKernelArg(cl->kernel_mandel3d, 2, sizeof(t_fractal3d), conf);
	if (err != 0)
		ft_printf("set kernel args - error\n");
	err = clEnqueueNDRangeKernel(cl->queue, cl->kernel_mandel3d,
			1, NULL, &global_size, NULL, 0, NULL, NULL);
	err = clEnqueueReadBuffer(cl->queue, mem_arr_structs, CL_TRUE, 0,
			global_size * sizeof(t_fractal_point), xy_points, 0, NULL, NULL);
	if (err != 0)
		ft_printf("create buf or run kernels or read buf - error\n");
	clReleaseMemObject(mem_arr_structs);
	return (xy_points);
}

static t_fractal_point	**get_points(t_fractal3d *conf,
		size_t global_size, t_cl *cl)
{
	int				i;
	t_fractal_point	**all_points;

	get_steps(conf);
	all_points = (t_fractal_point**)malloc(sizeof(t_fractal_point*) *
			conf->z_len);
	i = -1;
	while (++i < conf->z_len)
		all_points[i] = get_points_cl(conf, cl, &i, global_size);
	return (all_points);
}

void					mandelbrot_3d(int *objects_num, t_object3d **objects,
		t_cl *cl, t_fractal3d *conf)
{
	size_t			xy_size;
	t_fractal_point	**all_points;

	xy_size = conf->x_len * conf->y_len;
	all_points = get_points(conf, xy_size, cl);
	*objects_num = get_num_objects(all_points, xy_size, conf->z_len);
	*objects = get_objects(*objects_num, all_points, xy_size, conf->z_len);
}
