#ifndef CUB3D_H
# define  CUB3D_H


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

size_t	ft_strlen(char const *p);
char	**ft_join2d(char **env, char *var);
void	*ft_calloc(size_t nitems, size_t size);
void	*ft_callocs(size_t nitems, size_t size);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlens(char *p, char a);
char	*ft_substr(char *s, size_t start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *str, int c);
char	*get_next_line(int fd);
int     ft_strcmp(char *str1, char *str2);
int	ft_strncmp( const char *str1, const char *str2, size_t n);
int	ft_strlen2d(char **s1);
#endif 
