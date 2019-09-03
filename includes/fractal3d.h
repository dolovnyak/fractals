/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal3d.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 07:23:37 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/15 16:44:39 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL3D_H
# define FRACTAL3D_H

typedef struct	s_fractal3d
{
	int		x_len;
	int		y_len;
	int		z_len;
	float	left_b;
	float	right_b;
	float	top_b;
	float	bot_b;
	float	front_b;
	float	back_b;
	float	step_x;
	float	step_y;
	float	step_z;
	float	const_x;
	float	const_iy;
	float	const_jz;
	int		depth;
}				t_fractal3d;

typedef struct	s_fractal_point
{
	float	x;
	float	y;
	float	z;
	int		r;
	int		g;
	int		b;
	int		flag;
}				t_fractal_point;

#endif
