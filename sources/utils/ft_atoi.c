/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:22:23 by zrebhi            #+#    #+#             */
/*   Updated: 2023/04/20 19:08:04 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	atoi;

	i = 0;
	sign = 1;
	atoi = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (atoi + str[i] - '0' != (atoi + str[i] - '0') * 10 / 10)
			return ((sign + 1) / 2 * -1);
		atoi = atoi * 10 + str[i] - '0';
		i++;
	}
	if (str[i])
		return (-1);
	return ((int)atoi * sign);
}
