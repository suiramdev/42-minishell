/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:51:43 by zdevove           #+#    #+#             */
/*   Updated: 2023/06/01 18:22:05 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

// GET NEXT LINE

size_t		ft_strlen(const char *s);

char		*ftt_strjoin(char const *s1, char const *s2);

char		*ftt_strchr(const char *str, int c);

char		*ft_substr(char const *s, unsigned int start, size_t len);

size_t		ftt_strlcpy(char *dst, const char *src, size_t size);

char		*get_rd_to_buffer(int fd, char *buffer);

char		*get_line(char *buffer);

char		*get_rest(char *buffer);

char		*get_next_line(int fd, char **line);

// LIBFT

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

int			ft_atoi(const char *str);

void		ft_bzero(void *s, size_t n);

void		*ft_calloc(size_t x, size_t y);

int			ft_isalnum(int c);

int			ft_isalpha(int c);

int			ft_isascii(int c);

int			ft_isdigit(int c);

int			ft_isprint(int c);

char		*ft_itoa(int n);

long long	ft_atoll(const char *str);

void		*ft_memchr(const void *str, int c, size_t n);

int			ft_memcmp(const void *s1, const void *s2, size_t n);

void		*ft_memcpy(void *dst, const void *src, size_t n);

void		*ft_memmove(void *str1, const void *str2, size_t n);

void		*ft_memset(void *str, int c, size_t n);

void		ft_putchar_fd(char c, int fd);

int			ft_putendl_fd(char *s, int fd);

void		ft_putnbr_fd(int n, int fd);

int			ft_putstr_fd(char *s, int fd);

char		**ft_split(char const *s, char c);

char		*ft_strchr(const char *str, int c);

char		*ft_strdup(const char *src);

void		ft_striteri(char *s, void (*f)(unsigned int, char *));

char		*ft_strjoin(char const *s1, char const *s2);

size_t		ft_strlcat(char *dst, const char *src, size_t size);

size_t		ft_strlcpy(char *dst, const char *src, size_t size);

size_t		ft_strlen(const char *s);

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			ft_strcmp(const char *s1, const char *s2);

char		*ft_strnstr(const char *s1, const char *s2, size_t n);

char		*ft_strrchr(const char *str, int c);

char		*ft_strtrim(char const *s1, char const *set);

char		*ft_substr(char const *s, unsigned int start, size_t len);

int			ft_tolower(int c);

int			ft_toupper(int c);

t_list		*ft_lstnew(void *content);

int			ft_lstsize(t_list *lst);

t_list		*ft_lstlast(t_list *lst);

void		ft_lstclear(t_list **lst, void (*del)(void *));

void		ft_lstdelone(t_list *lst, void (*del)(void *));

void		ft_lstiter(t_list *lst, void (*f)(void *));

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void		ft_lstadd_back(t_list **lst, t_list *new);

void		ft_lstadd_front(t_list **lst, t_list *new);

#endif
