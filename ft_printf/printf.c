/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:46:17 by vifernan          #+#    #+#             */
/*   Updated: 2021/09/29 16:55:57 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

void ft_putchar(char c)
{
	write(1, &c, 1);

}

int ft_character(char c)
{
	int x;
	
	x = 0;
	x += write(1, &c, 1);
	return (x);
}

int ft_str_put(char *aux)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (aux[i] != '\0')
	{
		x += write(1, &aux[i], 1);
		i++;
	}

	return (x);
}

int ft_number(int n)
{
	int x;

	x = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
		x++;
	}
	if (n > 9)
	{
		x += ft_number(n / 10);
	}
	if (n || (n == 0 && x == 0))
		x++;
	ft_putchar((n % 10) + 48);
	return (x);
}

int ft_hexadecimal(unsigned int n)
{
	char *hexa = "0123456789abcdef";
	int x;

	x = 0;
	if (n > 16)
	{
		x += ft_hexadecimal(n / 16);
	}
	if (n || (n == 0 && x == 0))
		x++;
	ft_putchar(hexa[n % 16]);
	return (x);
}

int ft_count(va_list arg, const char *str)
{
	int x;
	int i;

	i = 0;
	x = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] == 'c')
		{
			x += ft_character(va_arg(arg, int));
			i++;
		}
		else if (str[i] == '%' && str[i + 1] == 's')
		{
			x += ft_str_put(va_arg(arg, char *));
			i++;	
		}
		else if (str[i] == '%' && str[i + 1] == 'd')
		{
			x += ft_number(va_arg(arg, int));
			i++;
		}
		else if (str[i] == '%' && str[i + 1] == 'x')
		{
			x += ft_hexadecimal((unsigned int)va_arg(arg, int));
			i++;	
		}
		else
			x += write(1, &str[i], 1);
		i++;
	}
	return (x);
}

int ft_printf(const char *str, ... )
{
	int count;
	va_list arg;
	
	count = 0;
	va_start(arg, str);
	count += ft_count(arg, str);
	va_end(arg);

	return (count);
}

int main()
{
	int x;
	int i;

	x = ft_printf("M:%x %d %s %c \n", -90, 9, "Hola",'a');
	i = printf("O:%x %d %s %c \n", -90,  9, "Hola",'a');

	printf("M: %d | O: %d\n", x, i);
}

