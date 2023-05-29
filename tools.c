#include "cub3d.h"

size_t	ft_strlen(char const *p)
{
	size_t	size;

	size = 0;
	while (*(p + size))
		size++;
	return (size);
}

int ft_strcmp(char *str1, char *str2)
{
    int i;

    i = 0;
    while((str1 || str2) && str1 == str2)
        i++;
    return(str1 - str2);
}


int	ft_strncmp( const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*str11 ;
	unsigned char	*str22 ;

	str11 = (unsigned char *)str1 ;
	str22 = (unsigned char *)str2 ;
	i = 0;
	if (n == 0)
		return (0);
	while ((*(str11 + i) || *(str22 + i))
		&& *(str11 + i) == *(str22 + i) && i < n - 1)
		i++;
	return (*(str11 + i) - *(str22 + i));
}

void	*ft_calloc(size_t nitems, size_t size)
{
	size_t	i;
	void	*p;

	i = 0;
	p = malloc(size * nitems);
	if (!p)
		exit (0);
	while (i < nitems * size)
	{
		*(char *)(p + i) = '\0';
		i++;
	}
	return (p);
}

int	ft_strlen2d(char **s1)
{
	int	i;

	i = 0;
	while (s1[i])
		i++;
	return (i);
}

char	**ft_join2d(char **env, char *var)
{
	char	**p;
	int		i;

	if (var == NULL)
		return (env);
	if (env == NULL)
	{
		p = ft_calloc(sizeof(char *), 2);
		*p = var;
		return (p);
	}
	p = ft_calloc(sizeof(char *), ft_strlen2d(env) + 2);
	i = 0;
	while (env[i])
	{
		p[i] = env[i];
		i++;
	}
	p[i] = var;
	return (p);
}