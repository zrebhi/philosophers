/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:04:30 by zrebhi            #+#    #+#             */
/*   Updated: 2023/04/20 19:24:22 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"

void			ft_putstr_fd(char *s, int fd);
void			*ft_calloc(unsigned long count, unsigned long size);
unsigned long	ft_atoi(const char *str);
unsigned long	get_time(void);

#endif