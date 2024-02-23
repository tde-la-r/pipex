/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:50:42 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/02/21 16:25:22 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*area1;
	unsigned char	*area2;
	size_t			i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	area1 = (void *)s1;
	area2 = (void *)s2;
	while ((area1[i] || area2[i]) && i < n)
	{
		if (area1[i] != area2[i])
			return (area1[i] - area2[i]);
		i++;
	}
	return (0);
}
