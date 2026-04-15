#include "test.h"

typedef struct path_node
{
	char *dir;
	struct path_node *next;
} path_node;

int main(void)
{
	char *path = strdup(getenv("PATH"));
	char *token;
	path_node *new_node;
	path_node *local_head;
	path_node *head;

	token = strtok(path, ":");
	while (token != NULL)
	{
		new_node = malloc(sizeof(*new_node));
		new_node->dir = strdup(token);
		new_node->next = head;
		head = new_node;

		token = strtok(NULL, ":");
	}

	local_head = head;
	while (local_head != NULL)
	{
		printf("%s\n", local_head->dir);
		local_head = local_head->next;
	}

	free(path);
	return (0);
}
