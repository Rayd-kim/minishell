#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "libft/libft.h"

char	**minishell_split(char const *s);


int main(void)
{
	char	*temp;
	char	**split;

	while (1)
	{
	temp = readline("minishell >>");
	split = minishell_split (temp);
	if (split == NULL)
	{
		printf("ERROR\n");
		return (1);
	}
	// for (int i = 0; split[i] != NULL; i++)
	// 	printf ("%d번째 %s\n",i, split[i]);
	// for (int i = 0; split[i] != NULL; i++)
	// 	free(split[i]);
	free (split);
	}
	return (0);
}
