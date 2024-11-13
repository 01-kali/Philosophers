/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 02:16:50 by zelkalai          #+#    #+#             */
/*   Updated: 2024/11/13 02:24:03 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_check(long num, char *str, int len)
{
	int	i;

	i = 0;
	if (num == 0)
		str[0] = '0';
	else if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	i = len - 1;
	while (num != 0)
	{
		str[i] = (num % 10) + '0';
		i--;
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	long long	num;
	char		*str;
	int			len;
	long		temp;

	num = n;
	temp = num;
	if (num <= 0)
		len = 1;
	else
		len = 0;
	while (temp != 0)
	{
		len++;
		temp /= 10;
	}
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	ft_check(num, str, len);
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && n--)
	{
		if (s1[i] - s2[i] != 0)
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		r;
	int		s;
	char	*d;
	int		i;

	i = 0;
	r = 0;
	s = 1;
	if (str[i] == '\0')
		return (-1);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	d = ft_itoa(r * s);
	if (ft_strncmp(str, d, ft_strlen(str)))
		return (free(d), -1);
	return (free(d), r * s);
}
