#include "minishell.h"

int	open_redirection(char *file_name, int check)
{
	int	fd;

	if (check == 1) // > 일 때는 무조건 지우고 새로 파일을 만들어야함
	{
		if (access (file_name, F_OK) == 0) //해당이름의 파일이 존재하는지 확인하는 함수. access함수 인자에 대해 확인해보시면 될듯.
			unlink (file_name); //file_name의 파일을 삭제하는 함수
		fd = open (file_name, O_WRONLY | O_CREAT, 0644);
		return (fd);
	}
	else // >>일 때는 파일이 존재하는 지 확인하고 존재하면 APPEND옵션으로 파일 열고, 없으면 creat로 파일열어야함.
	{
		if (access (file_name, F_OK) == 0) 
			fd = open (file_name, O_WRONLY | O_APPEND);
		else
			fd = open (file_name, O_WRONLY | O_CREAT, 0644);
		return (fd);
	}
}

int	check_heredoc(char *name) //here_doc 구현하는 함수. readline으로 shell상에서 받아오면서 체크.
{
	int		fd[2];
	char	*temp;

	pipe (fd);
	temp = readline (">");
	while (ft_strncmp (name, temp, ft_strlen (temp)) != 0)
	{
		write (fd[1], temp, ft_strlen(temp));
		write (fd[1], "\n", 1);
		free (temp);
		temp = readline (">");
	}
	free (temp);
	close (fd[1]);
	return (fd[0]);
	//우선 pipex에서 한거처럼 비슷하게 구현했는데, 아직 좀더 수정필요할듯.
}

void	do_redirection(t_root *top)
{
	t_node	*temp;

	temp = top->left;
	while (temp != NULL)
	{
		if (ft_strncmp (temp->cmd, ">" , 1) == 0)
			top->out_fd = open_redirection(temp->arg, 1);
		else if (ft_strncmp (temp->cmd, ">>", 2) == 0)
			top->out_fd = open_redirection(temp->arg, 2);
		else if (ft_strncmp (temp->cmd, "<", 1) == 0)
			top->in_fd = open (temp->arg, O_RDONLY);
		else
			top->in_fd = check_heredoc (temp->arg);
	}
}

void	exe_cmd(t_root *start, t_list *env)
{
	t_node	*node_temp;
	t_root	*root_temp;

	root_temp = start;
	while (root_temp != NULL)
	{
		node_temp = root_temp->left;
		while (node_temp != NULL) //어차피 redirection이 모든 명령어보다 우선시 되야하니깐 이것먼저 실행하기.
		{
			//do_redirection(node_temp);
			node_temp = node_temp->left;
		}
		//이 밑으로는 아직 구현중.

		//do_command(root->temp->left->right);
		root_temp = root_temp->right;
		//fd값 조정해주기
		//root_temp의 fd_out을 root_temp->right의 fd_in으로 (오류날때는?)
	}
}