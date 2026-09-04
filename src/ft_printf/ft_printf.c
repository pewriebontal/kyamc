/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikhaing <0x@bontal.net>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:53:36 by mikhaing          #+#    #+#             */
/*   Updated: 2025/08/30 14:36:47 by mikhaing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <kyamc/ft_printf.h>

static int	do_print(int fd, char fmt, va_list *args)
{
	if (fmt == 'c')
		return (handle_char(va_arg(*args, int), fd));
	else if (fmt == 's')
		return (handle_string(va_arg(*args, char *), fd));
	else if (fmt == 'p')
		return (handle_ptr(va_arg(*args, unsigned long long), fd));
	else if (fmt == 'd' || fmt == 'i')
		return (handle_int(va_arg(*args, int), fd));
	else if (fmt == 'u')
		return (handle_unsigned(va_arg(*args, unsigned int), fd));
	else if (fmt == 'x' || fmt == 'X')
		return (handle_hex(va_arg(*args, unsigned int), fmt, fd));
	else if (fmt == '%')
		return (handle_percent(fd));
	return (0);
}

int	ft_vdprintf(int fd, const char *fmt, va_list args)
{
	va_list	ap;
	int		num_char_printed;
	int		i;

	va_copy(ap, args);
	num_char_printed = 0;
	i = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			num_char_printed += do_print(fd, fmt[i + 1], &ap);
			i++;
		}
		else
			num_char_printed += handle_char(fmt[i], fd);
		i++;
	}
	va_end(ap);
	return (num_char_printed);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		char_count;

	va_start(args, fmt);
	char_count = ft_vdprintf(1, fmt, args);
	va_end(args);
	return (char_count);
}

int	ft_dprintf(int fd, const char *fmt, ...)
{
	va_list	args;
	int		char_count;

	va_start(args, fmt);
	char_count = ft_vdprintf(fd, fmt, args);
	va_end(args);
	return (char_count);
}
