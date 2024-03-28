/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:03:06 by albokanc          #+#    #+#             */
/*   Updated: 2024/03/21 19:03:22 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **tab, int box)
{
	while (box >= 0)
	{
		free(tab[box]);
		box--;
	}
	free(tab);
}

int	create_tab(char **tab, const char *s, char sep)
{
	int	box;
	int	len;

	box = 0;
	len = 0;
	while (*s)
	{
		while (*s == sep && *s)
			s++;
		while (*s != sep && *s)
		{	
			len++;
			s++;
		}
		if (len > 0)
		{
			tab[box] = malloc(sizeof(char) * len + 1);
			if (!tab)
				return (ft_free(tab, box), 0);
			tab[box][len] = '\0';
		}
		box++;
		len = 0;
	}
	return (0);
}

void	fill_tab(char **tab, const char *s, char sep)
{
	int	i;
	int	box;

	i = 0;
	box = 0;
	while (*s)
	{
		while (*s == sep && *s)
			s++;
		while (*s != sep && *s)
		{	
			tab[box][i] = *s;
			s++;
			i++;
		}
		i = 0;
		box++;
	}
}

int	count_word(const char *s, char sep)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	len = 0;
	while (s[i])
	{	
		while (s[i] && s[i] == sep)
			i++;
		while (s[i] && s[i] != sep)
		{
			i++;
			len++;
		}
		if (len > 0)
			count++;
		len = 0;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		total_words;

	if (!s)
		return (NULL);
	total_words = count_word(s, c);
	tab = malloc(sizeof(char *) * (total_words + 1));
	if (!tab)
		return (NULL);
	tab[total_words] = 0;
	create_tab(tab, s, c);
	fill_tab(tab, s, c);
	return (tab);
}
