/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:01:10 by bgresse           #+#    #+#             */
/*   Updated: 2023/04/19 19:38:24 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_bzero(void *s, int n)
{
	unsigned char	*tab;

	tab = s;
	while (n--)
		*(tab++) = 0;
}

void	*ft_calloc(unsigned long count, unsigned long size)
{
	void	*ptr;

	if (size && SIZE_MAX / size < count)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}
