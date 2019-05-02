/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:00:42 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/02 04:24:55 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

typedef struct  s_fractal
{
	int			x_len;
	int			y_len;
	int			z_len;
	float		left_b;
	float		right_b;
	float		top_b;
	float		bot_b;
	float		front_b;
	float		back_b;
	float		step_x;
	float		step_y;
	float		step_z;
	int			depth;
}               t_fractal;

typedef struct  s_fractal_point
{
	float   x;
	float   y;
	float   z;
	int     r;
	int     g;
	int     b;
	int     flag;
}               t_fractal_point;

#endif
