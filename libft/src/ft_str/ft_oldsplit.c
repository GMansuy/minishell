/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_oldsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmansuy <gmansuy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:07:10 by gmansuy           #+#    #+#             */
/*   Updated: 2022/11/02 18:17:18 by gmansuy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

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
		tab[k] = malloc(sizeof(char) * (j + 1));
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

char	**ft_oldsplit(const char *s, char c)
{
	int			size;
	int			ret;
	char		**tab;

	if (!s)
	{
		tab = malloc (sizeof(char *));
		tab[0] = NULL;
		return (tab);
	}
	size = ft_size((char *)s, c);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	tab[size] = NULL;
	ret = ft_splitter(size, tab, (char *)s, c);
	if (!ret)
	{
		free_split(tab);
		return (NULL);
	}
	return (tab);
}
