#include "main.h"

void _printbuffer(char buffer[], int *buff_i);
int _printf(const char *format, ...);

/**
 * _printbuffer - Prints the contents of the buffer
 * @buffer: Array of chars
 * @buff_i: Index at which to add next char, represents the length
 */

void _printbuffer(char buffer[], int *buff_i)
{
	if (*buff_i > 0)
		write(1, &buffer[0], *buff_i);
	*buff_i = 0;
}

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, prints = 0, _printedchars = 0;
	int flags, wid, prec, size, buff_i = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_i++] = format[i];
			if (buff_i == BUFF_SIZE)
				_printbuffer(buffer, &buff_i);
			_printedchars++;
		}
		else
		{
			_printbuffer(buffer, &buff_i);
			flags = get_flags(format, &i);
			wid = get_width(format, &i, list);
			prec = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			prints = handle_print(format, &i, list, buffer,
				       flags, wid, prec, size);
			if (prints == -1)
				return (-1);
			_printedchars += prints;
		}
	}
	_printbuffer(buffer, &buff_i);
	va_end(list);
	return (_printedchars);
}

