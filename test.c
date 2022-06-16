#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
/*
int main(void)
{
	char	*temp;

	temp = readline("minishell >>");
	printf ("%s", temp);
	free (temp);
	printf ("\n");
	//rl_on_new_line();
	//rl_replace_line ("", 0);
	rl_redisplay();
	return (0);
}
*/

int	main(void)
{
	DIR *a;

	a = opendir ("../minishell");
	printf("%p\n", a);
	printf("%d\n", a->__dd_fd);
	printf("%ld\n", a->__dd_loc);
	printf("%ld\n", a->__dd_size);
	printf("%d\n", a->__dd_len);
	return 0;
}