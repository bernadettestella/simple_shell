#include "main.h"

/**
 * _upstr - function that returns pointer to allocated copy of string
 * @trs: the string to e copied to the space being returned as a pointer
 * Return: the pointer to allocated space
 */

char *_upstr(char *trs)
{
	int x, leng = 0;
	char *thread;

	if (trs == NULL)
		return (NULL);
	while (*(trs + x) != '\0')
	{
		leng++;
		x++;
	}
	x = 0;
	thread = malloc(sizeof(char) * leng + 1);
	if (thread == NULL)
		return (NULL);
	while (*(trs + x) != '\0')
	{
		*(thread + x) = *(trs + x);
		x++;
	}
	*(thread + x) = '\0';
	return (thread);
}

/**
 * _conc - function that concatenates two string
 * @concat: allocated memory spcae to concatenate the strings
 * @s1: first string
 * @s2: second string
 * Return: a pointer to the memory space thats been concatenated
 */

char *_conc(char *concat, char *s1, char *s2)
{
	int numbconcat = 0, numbstring = 0;

	while (*(s1 + numbstring) != '\0')
	{
		*(concat + numbconcat) = *(s1 + numbstring);
		numbconcat++;
		numbstring++;
	}
	numbstring = 0;
	while (*(s2 + numbstring) != '\0')
	{
		*(concat + numbconcat) = *(s1 + numbstring);
		numbconcat++;
		numbstring++;
	}
	*(concat + numbconcat) = '\0';
	return (concat);
}

/**
 * _strlen - function that returns the length of a string
 * @st: the string parameter
 * Return: length of the string
 */

int _strlen(char *st)
{
	int leng = 0, x = 0;

	if (st == NULL)
		return (-1);
	while (st[x] != '\0')
	{
		leng = leng + 1;
		x++;
	}
	return (leng);
}

/**
 * str_conc - function that attaches a string to its destination string
 * @s1: first string
 * @s2: destination string
 * Return: the concatenated string
 */

char *str_conc(char *s1, char *s2)
{
	int leng1;
	int leng2;
	char *concat;

	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char));
		if (s1 == NULL)
			return (NULL);
		*s1 = '\0';
	}
	if (s2 == NULL)
	{
		s2 = malloc(sizeof(char));
		if  (s2 == NULL)
			return (NULL);
		*s2 = '\0';
	}
	leng1 = _strlen(s1);
	leng2 = _strlen(s2);
	concat = malloc(sizeof(char) * (leng1 + leng2 + 1));
	if (concat == NULL)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	return (_conc(concat, s1, s2));
}

/**
 * str_cmp - a function that compares pointers to two strings
 * @s1: a pointer to the first string to be compared
 * @s2: a pointer to the second string to be compared with s1
 * Return: the negative or positive difference between the two compared strings
 */

int str_cmp(char *s1, char *s2)
{
	while ((*s1 == *s2) && *s1 != '\0' && *s2 != '\0')
	{
		s1++;
		s2++;
	}
	if ((*s1 == '\0') && (*s2 == '\0'))
		return (0);
	else if (*s1 > *s2)
		return ((int)(*s1 - *s2));
	else
		return ((int)(*s1 - *s2));
}
