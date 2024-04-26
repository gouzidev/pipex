/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:34 by sgouzi            #+#    #+#             */
/*   Updated: 2024/04/23 18:40:52 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = ((unsigned char *)s1);
	str2 = ((unsigned char *)s2);
	i = 0;
	if (n == 0)
		return (0);
	while (str2[i] != '\0' && str1[i] == str2[i] && n > 1)
	{
		i++;
		n--;
	}
	return (str1[i] - str2[i]);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = ((unsigned char *)s1);
	str2 = ((unsigned char *)s2);
	i = 0;
	while (str2[i] != '\0' && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

char	*ft_strdup(char *str, t_node **gc)
{
	char	*new_str;
	int		i;

	new_str = gc_malloc(gc, len(str) + 1);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strjoin(char *s1, char *s2, t_node **gc)
{
	char	*output;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	output = (char *)gc_malloc(gc, (len(s1) + len(s2) + 1) * sizeof(char));
	if (output == NULL)
		(gc_clear(gc), exit(1));
	i = 0;
	while (i < len(s1))
	{
		output[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len(s2))
		output[i++] = s2[j++];
	output[i] = '\0';
	return (output);
}

char	*ft_substr(char const *s, unsigned int start, size_t len, t_node **gc)
{
	char	*sub;
	size_t	i;
	size_t	j;
	size_t	output_len;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = 0;
	while (s[str_len])
		str_len++;
	i = 0;
	j = start;
	while (len - i > 0 && j <= str_len && s[j++])
		i++;
	output_len = i;
	sub = (char *)gc_malloc(gc, (output_len + 1) * sizeof(char));
	i = 0;
	j = start;
	while (i < output_len)
		sub[i++] = s[j++];
	sub[i] = '\0';
	return ((char *)sub);
}
