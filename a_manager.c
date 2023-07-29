#include "shell.h"
#include <unistd.h>

/**
 * print_alias - prints an alias string
 * @alias: the alias string
 *
 * Return: The number of characters written.
 */
int print_alias(char *alias)
{
	int i = 0;
	char *p = NULL;

	if (alias)
	{
		p = _strchr(alias, '=');
		for (i = 0; alias[i] && alias + i <= p; i++)
			;
		write(STDOUT_FILENO, alias, i);
		write(STDOUT_FILENO, "\'", 1);
		write(STDOUT_FILENO, p + 1, _strlen(p + 1));
		write(STDOUT_FILENO, "\'\n", 2);
		return (i + 3 + _strlen(p + 1));
	}
	return (-1);
}

/**
 * print_all_aliases - prints all alias strings
 * @alias_list: the alias list
 *
 * Return: The number of characters written.
 */
int print_all_aliases(list_t *alias_list)
{
	int total_chars = 0;
	char *alias = NULL;

	while (alias_list)
	{
		alias = alias_list->str;
		total_chars += print_alias(alias);
		alias_list = alias_list->next;
	}
	return (total_chars);
}

/**
 * set_alias - sets an alias string
 * @info: parameter struct
 * @alias: the alias string
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *alias)
{
	char *p;

	p = _strchr(alias, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, alias));
	unset_alias(info, alias);
	return (add_node_end(&(info->alias), alias, 0) == NULL);
}

/**
 * unset_alias - unsets an alias string
 * @info: parameter struct
 * @alias: the alias string
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *alias)
{
	char *p, c;
	int ret;

	p = _strchr(alias, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, alias, -1)));
	*p = c;
	return (ret);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		return (print_all_aliases(info->alias));
	}

	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
		{
			node = node_starts_with(info->alias, info->argv[i], '=');
			if (node)
				print_alias(node->str);
		}
	}

	return (0);
}
