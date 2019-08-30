/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:21:16 by dmelessa          #+#    #+#             */
/*   Updated: 2019/08/30 22:21:16 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "rt_types.h"

/*
**multiply given parameter with itself = x * x or powf(x, 2)
*/
float	pow2(float x);

/*
**find minimum of given two values
*/
float	min(float a, float b);

/*
**find maximum of given two values
*/
float	max(float a, float b);

/*
**clamp a number between min and max
*/
float	clamp(float val, float min_val, float max_val);

/*
**clamp a number to zero and one
*/
float	clamp_zo(float val);

/*
** convert degree to radians
*/
float	deg_to_rad(float deg);

/*
** convert radians to degree
*/
float	rad_to_deg(float rad);

#endif