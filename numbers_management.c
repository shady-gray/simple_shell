/*Author: Basil Bassey*/
#include "shell_main.h"

/**
 * _atoi - convert a str to an integer.
 * @str: string origin
 *
 * Return: integer form of string
 */
int _atoi(char *str)
{
	int indicator = 1;
	unsigned int num = 0;

	while (!('0' <= *str && *str <= '9') && *str != '\0')
	{
		if (*str == '-')
			indicator *= -1;
		if (*str == '+')
			indicator *= +1;
		str++;
	}

	while ('0' <= *str && *str <= '9' && *str != '\0')
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (indicator * num);
}

/**
 * longint_to_str - converts a num to a str.
 * @num: number to be converted
 * @buff_str: buffer to hold the converted num in string format
 * @base: number conversion base
 *
 * Return: void
 */
void longint_to_str(long num, char *buff_str, int base)
{
	int neg_index = 0, i = 0;
	char letters[] = {"0123456789abcdef"};
	long convert = num;

	if (convert == 0)
		buff_str[i++] = '0';
	if (buff_str[0] == '-')
		neg_index = 1;

	while (convert)
	{
		if (convert < 0)
			buff_str[i++] = letters[-(convert % base)];
		else
			buff_str[i++] = letters[convert % base];
		convert /= base;
	}

	if (neg_index)
		buff_str[i++] = '-';
	buff_str[i] = '\0';

	_strrev(buff_str);
}

/**
 * char_count - count the coincidences of char in str.
 * @str: string origin
 * @chars: string to be counted
 *
 * Return: num of chars
 */
int char_count(char *str, char *chars)
{
	int m, count = 0;

	m = 0;
	while (str[m])
	{
		if (str[m] == chars[0])
			count++;
		m++;
	}
	return (count);
}

