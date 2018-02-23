/*
** EPITECH PROJECT, 2018
** nm
** File description:
** sort
*/

#include "my_nm.h"
#include <ctype.h>
#include <stdlib.h>

int alphanum_index(char *str)
{
	size_t i = 0;

	while (str && str[i] && isalnum(str[i]) == 0)
		i++;
	return (i);
}

bool alphanum_comp(char *str_1, char *str_2)
{
	size_t i = alphanum_index(str_1);
	size_t j = alphanum_index(str_2);
	int cmp_result;

	if (str_1 && str_2) {
		cmp_result = strcasecmp(&str_1[i], &str_2[j]);
		if (cmp_result == 0)
			return (strlen(str_1) < strlen(str_2) ? true : false);
		return (cmp_result > 0 ? true : false);
	}
	return (false);
}

t_symbol *alphanum_sort(t_symbol *array)
{
	t_symbol tmp;

	for (size_t i = 0 ; array[i].name ; i++) {
		for (size_t f = 0 ; array[f].name ; f++) {
			if (array[f + 1].name &&
				alphanum_comp(array[f].name,
					array[f + 1].name) == true) {
				tmp = array[f];
				array[f] = array[f + 1];
				array[f + 1] = tmp;
			}
		}
	}
	return (array);
}
