/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclaw <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:13:30 by niclaw            #+#    #+#             */
/*   Updated: 2022/09/02 17:13:37 by niclaw           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

/*int main()
{
	printf("%u\n",ft_isascii(8));
	printf("%u",ft_isascii(132));	
}*/