#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

char *ft_strdup(char *str)
{
    char *aux;
    int i;
    
    aux = malloc(ft_strlen(str) * sizeof(char) + 1);
    i = 0;
    while (str[i] != '\0')
    {
        aux[i] = str[i];
        i++;
    }
    aux[i] = '\0';
    return (aux);
}

char *ft_strjoin(char *a, char *b)
{
    char *res;
    int i;
    int j;

    res = malloc((ft_strlen(a) + ft_strlen(b) + 1) * sizeof(char));
    i = 0;
    while (a[i] != '\0')
    {
        res[i] = a[i];
        i++;
    }
    j = 0;
    while (b[j] != '\0')
    {
        res[i] = b[j];
        j++;
        i++;
    }
    res[i] = '\0';
    return (res);
}

char *ft_substr(char *str, int start, int end)
{
    int len;
    int i;
    char *aux;

    len = end - start;
    aux = malloc((len + 1) * sizeof(char));
    i = 0;
    while (len > 0)
    {
        aux[i] = str[start];
        i++;
        start++;
        len--;
    }
    aux[i] = '\0';
    return (aux);
}

int ft_strchr(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}


char *ft_status(int resread, char **s)
{
    int i;
    char *line;
    char *aux;

    line = NULL;
    if (resread < 0)
    {
        free(*s);
        *s = NULL;
        return (0);
    }
    else if (!(*s) && resread == 0)
        return (0);
    else
    {
        i = 0;
        while ((*s)[i] != '\0' && (*s)[i] != '\n')
            i++;
        if ((*s)[i] == '\0')
        {
            line = ft_strdup(*s);
            free(*s);
            *s = NULL;
        }
        else if ((*s)[i] == '\n')
        {
            line = ft_substr(*s, 0, (i + 1));
            aux = ft_strdup(&(*s)[i + 1]);
            free(*s);
            *s = aux;
            if ((*s)[0] == 0)
			{
				free(*s);
				*s = NULL;
			}
            return (line);
        }
    }
    return (0);
}

char *ft_cut_lines(char *buffer, char **s)
{
    char *aux;

    if (!(*s))
        *s = ft_strdup(buffer);
    else
    {
        aux = ft_strjoin(*s, buffer);
        free(*s);
        *s = aux;
    }
    return (*s);
}

char *get_next_line(int fd)
{
    static char *s[4096];
    char buffer[BUFFER_SIZE + 1];
    int resread;

    if (BUFFER_SIZE < 1 || fd < 0)
        return (0);
    resread = 1;
    while (resread > 0)
    {
        resread = read(fd, buffer, BUFFER_SIZE);
        if (resread < 0)
            return (0);
        buffer[resread] = '\0';
        s[fd] = ft_cut_lines(buffer, &(s[fd]));
        if (ft_strchr(s[fd], '\n') != 0)
            break ;
    }
    return (ft_status(resread, &(s[fd])));
}

int main()
{
    int fd;

    fd = open("./file", O_RDONLY);
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    close(fd);
    return (0);
}