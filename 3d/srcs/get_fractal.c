/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fractal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:24:19 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/04 07:28:03 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void			get_steps(t_conf *conf)
{
	conf->fractal.step_x = (conf->fractal.right_b - conf->fractal.left_b) /
		conf->fractal.x_len;
	conf->fractal.step_y = (conf->fractal.bot_b - conf->fractal.top_b) /
		conf->fractal.y_len;
	conf->fractal.step_z = (conf->fractal.front_b - conf->fractal.back_b) /
		conf->fractal.z_len;
}

void			set_args_and_run(t_conf *conf, cl_mem *mem_arr_structs,
		int *z, size_t global_size)
{
	int	err;

	err = clSetKernelArg(conf->cl.kernel_mandel, 0, sizeof(cl_mem),
			mem_arr_structs);
	err = clSetKernelArg(conf->cl.kernel_mandel, 1, sizeof(int), z);
	err = clSetKernelArg(conf->cl.kernel_mandel, 2, sizeof(t_fractal),
			&conf->fractal);
	if (err != 0)
		printf("set kernel args - error\n");
	err = clEnqueueNDRangeKernel(conf->cl.queue, conf->cl.kernel_mandel,
			1, NULL, &global_size, NULL, 0, NULL, NULL);
}

t_fractal_point	**get_fractal(t_conf *conf, size_t global_size)
{
	cl_mem			mem_arr_structs;
	t_fractal_point	*xy_points;
	int				i;
	t_fractal_point	**all_points;
	int				err;

	get_steps(conf);
	all_points = (t_fractal_point**)malloc(sizeof(t_fractal_point*) *
			conf->fractal.z_len);
	i = -1;
	while (++i < conf->fractal.z_len)
	{
		xy_points = (t_fractal_point*)malloc(sizeof(t_fractal_point)
				* global_size);
		mem_arr_structs = clCreateBuffer(conf->cl.context, CL_MEM_READ_WRITE,
				global_size * sizeof(t_fractal_point), NULL, &err);
		set_args_and_run(conf, &mem_arr_structs, &i, global_size);
		err = clEnqueueReadBuffer(conf->cl.queue, mem_arr_structs, CL_TRUE, 0,
			global_size * sizeof(t_fractal_point), xy_points, 0, NULL, NULL);
		if (err != 0)
			printf("create buf or run kernels or read buf - error\n");
		all_points[i] = xy_points;
	}
	clReleaseMemObject(mem_arr_structs);
	return (all_points);
}
