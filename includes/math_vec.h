/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 02:26:36 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/15 16:39:06 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_VEC_H
# define MATH_VEC_H

typedef struct	s_vector3d
{
	float	x;
	float	y;
	float	z;
}				t_vector3d;

float			mv_scalar_mult(const t_vector3d a, const t_vector3d b);
t_vector3d		mv_get_vector3d(float x, float y, float z);
t_vector3d		mv_minus(const t_vector3d a, const t_vector3d b);
t_vector3d		mv_plus(const t_vector3d a, const t_vector3d b);
t_vector3d		mv_mult_num(const t_vector3d a, float num);
t_vector3d		mv_dev_num(const t_vector3d a, float num);
float			mv_length(const t_vector3d a);

#endif
