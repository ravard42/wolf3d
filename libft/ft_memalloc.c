/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/16 23:56:54 by ravard            #+#    #+#             */
/*   Updated: 2016/01/16 23:56:55 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*memalloc;

	memalloc = malloc(size);
	if (memalloc == NULL)
		return (NULL);
	ft_memset(memalloc, 0, size);
	return (memalloc);
}
