/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 04:06:38 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/16 23:13:20 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <OPENCL/opencl.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"
# include "utilits.h"
# include "math_vec.h"
# include "math_complex.h"
# include "ray_trace.h"
# include <stdio.h>

typedef struct			s_mlx
{
	void	*img_ptr;
	void	*mlx;
	void	*win;
	char	*img_data;
	int		bpp;
	int		endian;
	int		size_line;
	int		width;
	int		height;
	float	relation;
}						t_mlx;

typedef struct			s_cl
{
	cl_command_queue	queue;
	cl_context			context;
	cl_program			program;
	cl_kernel			kernel_mandel2d;
	cl_kernel			kernel_mandel2d_pow5;
	cl_kernel			kernel_mandelfdf;
	cl_kernel			kernel_mandel3d;
	cl_kernel			kernel_julia2d;
	cl_kernel			kernel_juliafdf;
	cl_kernel			kernel_julia2d_pow5;
	cl_kernel			kernel_julia3d;
	cl_kernel			kernel_burning_ship2d;
	cl_kernel			kernel_burning_ship2d_pow5;
	cl_kernel			kernel_newton1;
	cl_kernel			kernel_newton2;
	cl_kernel			kernel_fractal_dick;
	cl_kernel			kernel_rt_safety;
	cl_kernel			kernel_rt_fast;
}						t_cl;

void					initialization_cl(t_cl *cl);
cl_device_id			get_device_id(void);
char					*get_program_buf(const char *name,
		size_t *program_size);
void					initialization_mlx2d(t_mlx *mlx);
void					initialization_mlx3d(t_mlx *mlx);
void					initialization_mlx_fdf(t_mlx *mlx);
void					mandelbrot_2d(t_cl *cl);
void					mandelbrot_2d_pow5(t_cl *cl);
void					mandelbrot_fdf(t_cl *cl);
void					julia_2d(t_cl *cl);
void					julia_2d_pow5(t_cl *cl);
void					julia_fdf(t_cl *cl);
void					burning_ship_2d(t_cl *cl);
void					burning_ship_2d_pow5(t_cl *cl);
void					newton1(t_cl *cl);
void					newton2(t_cl *cl);
void					fractal_dick(t_cl *cl);
int						exit_event(t_cl *cl);

#endif
