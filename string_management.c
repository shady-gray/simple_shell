/*Author: Basil Bassey*/
#include "shell_main.h"

/**
 * _strlen - returns the length of a str.
 * @str: string pointer
 *
 * Return: length of str.
 */
int _strlen(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);
	while (str[len++] != '\0')
		;
	return (--len);
}

/**
 * _strdup - duplicates a str
 * @str: string
 *
 * Return: pointer to the array
 */
char *_strdup(char *str)
{
	char *res;
	int len, m;

	if (str == NULL)
		return (NULL);
	len = _strlen(str) + 1;
	res = malloc(len * sizeof(char));

	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (m = 0; m < len ; m++)
		res[m] = str[m];

	return (res);
}

/**
 * compare_str - Compares two strs
 * @str1: string 1
 * @str2: string 2
 * @num: number of characters
 *
 * Return: 1 for equal strings, 0 for unequal string
 */
int compare_str(char *str1, char *str2, int num)
{
	int itr;

	if (str1 == NULL && str2 == NULL)
		return (1);
	if (str1 == NULL || str2 == NULL)
		return (0);

	if (num == 0)
	{
		if (_strlen(str1) != _strlen(str2))
			return (0);
		itr = 0;
		while (str1[itr])
		{
			if (str1[itr] != str2[itr])
				return (0);
				itr++;
		}
		return (1);
	}
	else
	{
		for (itr = 0; itr < num ; itr++)
		{
			if (str1[itr] != str2[itr])
			return (0);
		}
		return (1);
	}
}

/**
 * _strconcate - concatenates 2 strings
 * @str1: string 1
 * @str2: string 2 (to dd to string 1)
 *
 * Return: concatenated string
 */
char *_strconcate(char *str1, char *str2)
{
	char *res;
	int len1 = 0, len2 = 0;

	if (str1 == NULL)
		str1 = "";
	len1 = _strlen(str1);

	if (str2 == NULL)
		str2 = "";
	len2 = _strlen(str2);

	res = malloc((len1 + len2 + 1) * sizeof(char));
	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (len1 = 0; str1[len1] != '\0'; len1++)
		res[len1] = str1[len1];
	free(str1);

	for (len2 = 0; str2[len2] != '\0'; len2++)
	{
		res[len1] = str2[len2];
		len1++;
	}
	res[len1] = '\0';

	return (res);
}


/**
 * _strrev - a function to reverses a string
 * @str: string
 *
 * Return: void
 */
void _strrev(char *str)
{

	int m = 0, len = _strlen(str) - 1;
	char hold;

	while (m < len)
	{
		hold = str[m];
		str[m++] = str[len];
		str[len--] = hold;
	}
}

