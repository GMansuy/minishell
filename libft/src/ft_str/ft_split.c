/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:07:10 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/02 18:15:31 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!(str[i] == c) && (str[i + 1] == c || str[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

static int	ft_splitter(int size, char **tab, char *str, char c)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = 0;
	k = 0;
	while (k < size)
	{
		while (str[i] == c)
			i++;
		j = 0;
		while (!(str[i + j] == c) && str[i + j])
			j++;
		tab[k] = magic_malloc(sizeof(char) * (j + 1));
		if (!(tab[k]))
			return (0);
		l = 0;
		while (l < j)
			tab[k][l++] = str[i++];
		tab[k][l] = '\0';
		k++;
	}
	return (1);
}

char	**ft_split(const char *s, char c)
{
	int			size;
	int			ret;
	char		**tab;

	if (!s)
	{
		tab = magic_malloc (sizeof(char *));
		tab[0] = NULL;
		return (tab);
	}
	size = ft_size((char *)s, c);
	tab = magic_malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	tab[size] = NULL;
	ret = ft_splitter(size, tab, (char *)s, c);
	if (!ret)
	{
		magic_free();
		return (NULL);
	}
	return (tab);
}
