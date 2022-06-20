#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "libft/libft.h"

typedef struct node {
	char	*cmd;
	char	*arg;
	int		type;
	struct node	*left;
	struct node *right;
}		t_node;

void	change_input (char *s);


void	make_redirection(t_node *start)
{

}

void	make_node (char *split)
{
	t_node	*start;
	char	**cut;
	int		cmd = 0;

	start = (t_node *)malloc(sizeof(t_node));
	ft_memset (start, 0, sizeof(t_node));
	start->type = 0;
	cut = ft_split(split, (char)255);
	for (int k = 0; cut[k] != NULL; k++)
	{
		if (cut[k] == '>' || cut[k] == '>>' || cut[k] == '<' || cut[k] == '<<')
			make_redirection ();
		else if (check_cmd(cut[k] == 0 && cmd == 0))
		{
			make_cmd();
			cmd++;
		}
		else
			make_arg();
	}
}

int main(void)
{
	char	*temp;
	char	**split;

	while (1)
	{
	temp = readline("minishell >>");
	split = ft_split (temp, '|');
	for (int i = 0; split[i] != NULL; i++)
	{
		change_input(split[i]);
		make_node(split[i]);
	}
	// split = ft_split (temp, (char)255);
	for (int i = 0; split[i] != NULL; i++)
		printf ("%s\n", split[i]);
	}
	return (0);
}
