/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:53:29 by acesar-l          #+#    #+#             */
/*   Updated: 2021/03/06 10:00:42 by acesar-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	void		*content;
	struct s_list	*next;
}	t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

int	ft_isalpha(int argument);
int	ft_isdigit(int argument);
int	ft_isalnum(int argument);
int	ft_isascii(int argument);
int	ft_isprint(int argument);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *s, int argument, size_t length);
void	ft_bzero(void *s, size_t length);
void	*ft_memcpy(void *dest, const void *src, size_t length);
void	*ft_memmove(void *dest, const void *src, size_t length);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t dest_size);
int	ft_toupper(int argument);
int	ft_tolower(int argument);
char	*ft_strchr(const char *str, int argument);
char	*ft_strrchr(const char *str, int argument);
int	ft_strncmp(const char *s1, const char *s2, size_t size);
void	*ft_memchr(const void *str, int argument, size_t size);
int	ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *str, const char *to_find, size_t size);
int	ft_atoi(const char *str);
void	*ft_calloc(size_t nbr_elements, size_t element_size);
char	*ft_strdup(char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int	ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char	*get_next_line(int fd);
int	ft_printf(const char *str, ...);
int	ft_argument_c(char c);
int	ft_arguments_d_i(int c);
int	ft_argument_p(unsigned long nbr);
int	ft_argument_percent(void);
int	ft_argument_s(char *str);
int	ft_argument_u(unsigned int nbr);
int	ft_arguments_x(unsigned int nbr, char type);
int	ft_is_argument(char a);
int	ft_decimal_length(long int nbr);
void	ft_free_ptr(char **ptr);
char	ft_decimal_converter_to_hex(char digit, char type);
int	ft_hex_length(unsigned long nbr);
int	ft_print_reversed_str(char *str);

#endif
