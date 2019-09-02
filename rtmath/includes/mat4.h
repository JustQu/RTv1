/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <dmelessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:25:03 by dmelessa          #+#    #+#             */
/*   Updated: 2019/09/02 19:52:00 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_H
# define MAT4_H

# include "rt_types.h"
# include "vec3.h"
# include "stddef.h"
# include "stdint.h" //size_t

#define MAT4_IDENTITY_INIT  {{1.0f, 0.0f, 0.0f, 0.0f},\
                            {0.0f, 1.0f, 0.0f, 0.0f},\
                            {0.0f, 0.0f, 1.0f, 0.0f},\
                            {0.0f, 0.0f, 0.0f, 1.0f}}

#define MAT4_ZERO_INIT      {{0.0f, 0.0f, 0.0f, 0.0f},\
                            {0.0f, 0.0f, 0.0f, 0.0f},\
                            {0.0f, 0.0f, 0.0f, 0.0f},\
                            {0.0f, 0.0f, 0.0f, 0.0f}}

#define MAT4_IDENTITY ((t_mat4)MAT4_IDENTITY_INIT)
#define MAT4_ZERO     ((t_mat4)MAT4_ZERO_INIT)

/*
** copy all members of [mat] to [dest]
*/
void	mat4_copy(t_mat4 mat, t_mat4 dest);

/*
** make given matrix identity. It is identical with below,
**      but it is more easy to do that with this func especially for members
**      e.g. mat4_identity(aStruct->aMatrix);
**
** mat4_copy(MAT4_IDENTITY, mat); // C only
** // or
** mat4 mat = MAT4_IDENTITY_INIT;
*/
void	mat4_identity(t_mat4 mat);

/*
**make given matrix array's each element identity matrix
*/
void	mat4_identity_array(t_mat4 *mat, size_t count);

/*
** make given matrix zero.
*/
void	mat4_zero(t_mat4 mat);

/*
**copy upper-left of mat4 to mat3
*/
void	mat4_pick3(t_mat4 mat, t_mat3 dest);

/*
** copy upper-left of mat4 to mat3 (transposed)
** the postfix t stands for transpose
*/
void	mat4_pick3t(t_mat4 mat, t_mat3 dest);

/*
** copy mat3 to mat4's upper-left
*/
void	mat4_ins3(t_mat3 mat, t_mat4 dest);

/*
** multiply m1 and m2 to dest
**
** m1, m2 and dest matrices can be same matrix, it is possible to write this:
**
** @code
** mat4 m = MAT4_IDENTITY_INIT;
** mat4_mul(m, m, m);
** @endcode
*/
void	mat4_mul(t_mat4 m1, t_mat4 m2, t_mat4 dest);

/*
** mupliply N mat4 matrices and store result in dest
**
** this function lets you multiply multiple (more than two or more...) matrices
** multiplication will be done in loop, this may reduce instructions
** size but if len is too small then compiler may unroll whole loop,
** usage:
** @code
** mat m1, m2, m3, m4, res;dest[2][3] = m[3][2];
**
** mat4_mulN((mat4 *[]){&m1, &m2, &m3, &m4}, 4, res);
** @endcode
**
** @warning matrices parameter is pointer array not mat4 array!
*/
void	mat4_mulN(t_mat4 *matrices[], uint32_t len, t_mat4 dest);

/*
** multiply mat4 with vec4 (column vector) and store in dest vector
*/
void	mat4_vec4_mul(t_mat4 m, t_vec4 v, t_vec4 dest);

/*
** trace of matrix
** sum of the elements on the main diagonal from upper left to the lower right
*/
float	mat4_trace(t_mat4 m);

/*
** trace of matrix (rotation part)
** sum of the elements on the main diagonal from upper left to the lower right
*/
float	mat4_trace3(t_mat4 m);

/*
** convert mat4's rotation part to quaternion
*/
void	mat4_quat(t_mat4 m, t_versor dest);

/*
**multiply vector with mat4
**
**m    mat4(affine transform)
**v    vec3
**last 4th item to make it vec4
**dest result vector (t_vec3)
*/
void	mat4_vec3_mul(t_mat4 m, t_vec3 v, float last, t_vec3 dest);

/*
** transpose mat4 and store in dest
** source matrix will not be transposed unless dest is m
** todo: error when dest and m is the same matrix
*/
void	mat4_transpose_to(t_mat4 m, t_mat4 dest);

/*
** tranpose mat4 and store result in same matrix
*/
void	mat4_transpose(t_mat4 m);

/*
** scale (multiply with scalar) matrix without
** multiply matrix with scalar
*/
void	mat4_scale(t_mat4 m, float s);

/*
** mat4 determinant
*/
float	mat4_det(t_mat4 mat);

/*
** inverse mat4 and store in dest
*/
void	mat4_inv(t_mat4 mat, t_mat4 dest);

/*
** swap two matrix columns
*/
void	mat4_swap_col(t_mat4 mat, int col1, int col2);

/*
** swap two matrix rows
*/
void	mat4_swap_row(t_mat4 mat, int row1, int row2);

/*
** helper for  R (row vector) * M (matrix) * C (column vector)
**
** rmc stands for Row * Matrix * Column
** the result is scalar because R * M = Matrix1x4 (row vector),
** then Matrix1x4 * Vec4 (column vector) = Matrix1x1 (Scalar)
*/
float	mat4_rmc(t_vec4 r, t_mat4 m, t_vec4 c);

#endif