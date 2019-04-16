/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:00:42 by sbecker           #+#    #+#             */
/*   Updated: 2019/04/16 11:02:49 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <OPENCL/opencl.h>

typedef struct  s_fractol
{
	int         x_len;
	int         y_len;
	int         z_len;
	double      left_b;
	double      right_b;
	double      top_b;
	double      bot_b;
	double      front_b;
	double      back_b;
	int         depth;
}               t_fractol;

typedef struct  s_cl_sphera
{
	cl_float   x;
	cl_float   y;
	cl_float   z;
	cl_int     r;
	cl_int     g;
	cl_int     b;
	cl_int     flag;
}               t_cl_sphera;

#endif
