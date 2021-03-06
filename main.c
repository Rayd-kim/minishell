#include "minishell.h"

void	free_left (t_node *top) // redirection, 명령어 입력된 node들 비워주는 함수
{
	t_node	*node;
	t_node	*free_node;

	node = top;
	if (node->right != NULL)
	{
		free (node->right->cmd);
		free (node->right->arg);
		free (node->right);
	}
	free_node = node;
	node = node->left;
	free (free_node);
	while (node != NULL)
	{
		free (node->cmd);
		free (node->arg);
		free_node = node;
		node = node->left;
		free (free_node);
	}
}

void	reset_root (t_root *start) //root기준으로 돌면서 start이외에 다 리셋해주는 함수
{
	t_root	*root;
	t_root	*free_root;

	root = start;
	while (root != NULL)
	{
		if (root->left != NULL)
			free_left (root->left);
		free_root = root;
		root = root->right;
		if (free_root != start)
			free (free_root);
	}
	start->left = NULL;
	start->right = NULL;
}

void	show_prompt (t_root *start) //함수가 길어서 자름. readline으로 prompt처럼 보이게 하는용도 이전이랑 비슷.
{
	char	*temp;
	char	**split;
	int		i;

	temp = readline("minishell >>");
	split = ft_split (temp, '|');
	if (split == NULL)
		exit (1);
	i = 0;
	while (split[i] != NULL)
	{
		change_input(split[i]);
		make_node(split[i], make_cmd_node(start));
		free (split[i]);
		i++;
	}
	free (split);
	free (temp);
}

int main(int arg, char *argv[], char **envp)
{
	t_root	*start;
	t_list	*env;

	if (arg > 1 || ft_strncmp (argv[0], "./minishell", ft_strlen(argv[0])) != 0)
		exit (1);
	start = make_root (0, 1);
	env = make_env (envp); // 환경변수 받아와서 리스트로 저장. 중간에 export나 unset으로 처리하기 편하기위해서.
	while (1)
	{
		reset_root(start);
		show_prompt (start);
		//exe_cmd (start, env); //이제 위에서 만든 트리구조를 가지고 순서대로 순환하면서 명령어, redirection등을 실행.

		//입력이 잘 되고, reset잘 되는지 확인하는용도. 
		/*
		t_root	*root;
		t_node	*node;
		
		root = start;
		while (root != NULL)
		{
			node = root->left;
			while (node != NULL)
			{
				if (node->right != NULL)
					printf ("\ncommand cmd %s arg %s\n", node->right->cmd, node->right->arg);
				node = node->left;
				if (node != NULL)
					printf ("redirection cmd %s arg %s\n\n", node->cmd, node->arg);
			}
			root = root->right;
		}
		*/
	}
	return (0);
}