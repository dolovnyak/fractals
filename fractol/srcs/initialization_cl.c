/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 22:06:08 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/07 10:08:00 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

cl_device_id	get_device_id(void)
{
	cl_platform_id	platform;
	cl_device_id	device;
	int				err;

	err = clGetPlatformIDs(1, &platform, NULL);
	if (err != 0)
		printf("Get platform - error\n");
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
	if (err != 0)
		printf("Get device id - error\n");
	return (device);
}

char			*get_program_buf(const char *name, size_t *program_size)
{
	size_t	file_size;
	FILE	*fd;
	char	*buf;

	fd = fopen(name, "r");
	if (!fd)
		printf("Open kernel file '%s' - error\n", name);
	fseek(fd, 0, SEEK_END);
	file_size = ftell(fd);
	rewind(fd);
	buf = (char*)malloc(file_size + 1);
	fread(buf, sizeof(char), file_size, fd);
	buf[file_size] = '\0';
	fclose(fd);
	*program_size = file_size;
	return (buf);
}

cl_program		create_program(cl_context context)
{
	cl_program	program;
	char		**program_buf;
	size_t		*program_size;
	int			files_num;
	int			err;

	files_num = 4;
	program_buf = (char**)malloc(sizeof(char*) * files_num);
	program_size = (size_t*)malloc(sizeof(size_t) * files_num);
	program_buf[0] = get_program_buf("srcs/utilits_cl/math_vec.cl",
			&program_size[0]);
	program_buf[1] = get_program_buf("srcs/utilits_cl/color.cl", &program_size[1]);
	program_buf[2] = get_program_buf("srcs/mandel2d/mandel2d.cl", &program_size[2]);
	program_buf[3] = get_program_buf("srcs/mandelfdf/mandelfdf.cl", &program_size[3]);

/*	program_buf[2] = get_program_buf("srcs/render.cl", &program_size[2]);
	program_buf[3] = get_program_buf("srcs/get_cam_ray.cl", &program_size[3]);
	program_buf[4] = get_program_buf("srcs/ray-trace.cl", &program_size[4]);
	program_buf[5] = get_program_buf("srcs/sphere.cl", &program_size[5]);
	program_buf[6] = get_program_buf("srcs/get_light_intensity.cl",
			&program_size[6]);
	program_buf[7] = get_program_buf("srcs/check_shadows.cl", &program_size[7]);
	program_buf[8] = get_program_buf("srcs/get_fractal.cl", &program_size[8]);*/
	program = clCreateProgramWithSource(context, files_num,
			(const char**)program_buf, (const size_t*)program_size, &err);
	if (err != 0)
		printf("create program - error\n");
	return (program);
}

void			get_kernels(cl_device_id *device, t_cl *cl)
{
	char	*log;
	int		err;
	size_t	log_size;

	cl->program = create_program(cl->context);
	err = clBuildProgram(cl->program, 1, device, "-I includes/", NULL, NULL);
	if (err != 0)
	{
		clGetProgramBuildInfo(cl->program, *device, CL_PROGRAM_BUILD_LOG,
				0, NULL, &log_size);
		log = (char*)malloc(log_size);
		clGetProgramBuildInfo(cl->program, *device, CL_PROGRAM_BUILD_LOG,
				log_size, log, NULL);
		printf("build program - error (%d)\n", err);
		printf("%s\n", log);
	}
	cl->kernel_mandel2d = clCreateKernel(cl->program, "mandelbrot_2d", &err);
	cl->kernel_mandelfdf = clCreateKernel(cl->program, "mandelbrot_fdf", &err);
//	cl->kernel_rt = clCreateKernel(cl->program, "render", &err);
	if (err != 0)
		printf("create kernel - error\n");
}

void			initialization_cl(t_cl *cl)
{
	cl_device_id	device;
	int				err;

	device = get_device_id();
	cl->context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
	if (err != 0)
		printf("create context - error\n");
	cl->queue = clCreateCommandQueue(cl->context, device, 0, &err);
	if (err != 0)
		printf("create command queue - error\n");
	get_kernels(&device, cl);
}
