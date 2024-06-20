/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenev <spenev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:36:47 by spenev            #+#    #+#             */
/*   Updated: 2024/06/20 11:37:27 by spenev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H
# ifdef __linux__
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_PLUS 61
#  define KEY_MINUS 45
#  define KEY_SPACE 32
#  define KEY_C 99
#  define KEY_X 120
#  define KEY_M 109
# else
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_PLUS 24
#  define KEY_MINUS 27
#  define KEY_SPACE 49
#  define KEY_C 8
#  define KEY_X 7
#  define KEY_M 46
# endif
#endif