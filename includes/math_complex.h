/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_complex.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 13:17:54 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/15 16:35:14 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_COMPLEX_H
# define MATH_COMPLEX_H

typedef struct	s_complex
{
	double	x;
	double	y;
}				t_complex;

t_complex		cx_pow(t_complex z, int pow);
t_complex		cx_dev(t_complex z1, t_complex z2);
t_complex		cx_mult(t_complex z1, t_complex z2);
t_complex		cx_mult_real(t_complex z, double num);
t_complex		cx_plus(t_complex z1, t_complex z2);
t_complex		cx_minus(t_complex z1, t_complex z2);
t_complex		cx_plus_real(t_complex z, double num);
t_complex		cx_minus_real(t_complex z, double num);

#endif
