/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 22:06:08 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/16 23:12:02 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void	get_buf_in_norm(char **program_buf, size_t *program_size)
{
	program_buf[6] = get_program_buf("srcs/ray_trace_render/sphere.cl",
			&program_size[6]);
	program_buf[7] = get_program_buf(
			"srcs/ray_trace_render/get_light_intensity.cl", &program_size[7]);
	program_buf[8] = get_program_buf("srcs/ray_trace_render/check_shadows.cl",
			&program_size[8]);
	program_buf[9] = get_program_buf("srcs/mandel2d/mandel2d.cl",
			&program_size[9]);
	program_buf[10] = get_program_buf("srcs/mandelfdf/mandelfdf.cl",
			&program_size[10]);
	program_buf[11] = get_program_buf("srcs/mandel3d/get_mandel3d.cl",
			&program_size[11]);
	program_buf[12] = get_program_buf("srcs/julia2d/julia2d.cl",
			&program_size[12]);
	program_buf[13] = get_program_buf("srcs/juliafdf/juliafdf.cl",
			&program_size[13]);
	program_buf[14] = get_program_buf("srcs/julia3d/get_julia3d.cl",
			&program_size[14]);
	program_buf[15] = get_program_buf("srcs/burning_ship2d/burning_ship2d.cl",
			&program_size[15]);
	program_buf[16] = get_program_buf("srcs/newton/newton.cl",
			&program_size[16]);
	program_buf[17] = get_program_buf("srcs/fractal_dick/fractal_dick.cl",
			&program_size[17]);
}

void	create_program(cl_context context, int err, cl_program *program)
{
	char		**program_buf;
	size_t		*program_size;
	int			files_num;

	files_num = 18;
	program_buf = (char**)malloc(sizeof(char*) * files_num);
	program_size = (size_t*)malloc(sizeof(size_t) * files_num);
	program_buf[0] = get_program_buf("srcs/utilits_cl/math_vec.cl",
			&program_size[0]);
	program_buf[1] = get_program_buf("srcs/utilits_cl/math_complex.cl",
			&program_size[1]);
	program_buf[2] = get_program_buf("srcs/utilits_cl/color.cl",
			&program_size[2]);
	program_buf[3] = get_program_buf("srcs/ray_trace_render/render.cl",
			&program_size[3]);
	program_buf[4] = get_program_buf("srcs/ray_trace_render/get_cam_ray.cl",
			&program_size[4]);
	program_buf[5] = get_program_buf("srcs/ray_trace_render/ray_trace.cl",
			&program_size[5]);
	get_buf_in_norm(program_buf, program_size);
	*program = clCreateProgramWithSource(context, files_num,
			(const char**)program_buf, (const size_t*)program_size, &err);
	if (err != 0)
		ft_printf("create program - error\n");
}

void	get_kernels(t_cl *cl, int err)
{
	cl->kernel_julia2d = clCreateKernel(cl->program, "julia_2d", &err);
	cl->kernel_julia2d_pow5 = clCreateKernel(cl->program,
			"julia_2d_pow5", &err);
	cl->kernel_juliafdf = clCreateKernel(cl->program, "julia_fdf", &err);
	cl->kernel_julia3d = clCreateKernel(cl->program, "julia_3d", &err);
	cl->kernel_burning_ship2d = clCreateKernel(cl->program,
			"burning_ship_2d", &err);
	cl->kernel_burning_ship2d_pow5 = clCreateKernel(cl->program,
			"burning_ship_2d_pow5", &err);
	cl->kernel_newton1 = clCreateKernel(cl->program, "newton1", &err);
	cl->kernel_newton2 = clCreateKernel(cl->program, "newton2", &err);
	cl->kernel_fractal_dick = clCreateKernel(cl->program, "fractal_dick", &err);
	cl->kernel_rt_safety = clCreateKernel(cl->program, "render_safety", &err);
	cl->kernel_rt_fast = clCreateKernel(cl->program, "render_fast", &err);
	cl->kernel_mandel2d = clCreateKernel(cl->program, "mandelbrot_2d", &err);
	cl->kernel_mandel2d_pow5 = clCreateKernel(cl->program,
			"mandelbrot_2d_pow5", &err);
	cl->kernel_mandelfdf = clCreateKernel(cl->program, "mandelbrot_fdf", &err);
	cl->kernel_mandel3d = clCreateKernel(cl->program, "mandelbrot_3d", &err);
	if (err != 0)
		ft_printf("create kernel - error\n");
}

void	create_porgram_and_get_kernels(cl_device_id *device, t_cl *cl)
{
	char	*log;
	int		err;
	size_t	log_size;

	create_program(cl->context, err = 0, &cl->program);
	err = clBuildProgram(cl->program, 1, device, "-I includes/", NULL, NULL);
	if (err != 0)
	{
		clGetProgramBuildInfo(cl->program, *device, CL_PROGRAM_BUILD_LOG,
				0, NULL, &log_size);
		log = (char*)malloc(log_size);
		clGetProgramBuildInfo(cl->program, *device, CL_PROGRAM_BUILD_LOG,
				log_size, log, NULL);
		ft_printf("build program - error (%d)\n", err);
		ft_printf("%s\n", log);
	}
	get_kernels(cl, err);
}

void	initialization_cl(t_cl *cl)
{
	cl_device_id	device;
	int				err;

	device = get_device_id();
	cl->context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
	if (err != 0)
		ft_printf("create context - error\n");
	cl->queue = clCreateCommandQueue(cl->context, device, 0, &err);
	if (err != 0)
		ft_printf("create command queue - error\n");
	create_porgram_and_get_kernels(&device, cl);
}
