/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 07:09:25 by sbecker           #+#    #+#             */
/*   Updated: 2019/04/11 05:32:39 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

int		keyboard_events(int keycode, t_conf *conf)
{
	if (keycode == 0)
		conf->canvas->camera.x -= 1;
	if (keycode == 2)
		conf->canvas->camera.x += 1;
	return (0);
}
