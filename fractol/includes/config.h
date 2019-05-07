/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 04:06:38 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/07 10:11:49 by sbecker          ###   ########.fr       */
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
# include "RTv1.h"
# include <stdio.h> //TODO

typedef struct  s_mlx
{
	void	*img_ptr;
	void	*mlx;
	void	*win;
	char	*img_data;
	int 	bpp;
	int 	endian;
	int 	size_line;
	int 	width;
	int 	height;
	float	relation;
}               t_mlx;

typedef struct  s_cl
{
	cl_command_queue    queue;
	cl_context          context;
	cl_program          program;
	cl_kernel			kernel_mandel2d;
	cl_kernel			kernel_mandelfdf;
}               t_cl;

void	initialization_cl(t_cl *cl);
void	initialization_mlx(t_mlx *mlx);
void    mandelbrot_2d(t_cl *cl, t_mlx *mlx);
void    mandelbrot_fdf(t_cl *cl, t_mlx *mlx);

#endif
