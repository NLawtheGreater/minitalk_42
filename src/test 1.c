#include "minitalk.h"

int	send_character(char p_c, int p_pid)
{
	static int		i = -1;
	static char		c;
	static int		pid;

	if (p_pid)
	{
		c = p_c;
		pid = p_pid;
	}
	if (i < 0)
		i = 7;
	if (pid <= 0 || kill(pid, 0) < 0)
	{
		ft_putendl_fd("Invalid Process ID.", 1);
		exit(0);
	}
	if (c & (1 << i))
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	i--;
	return (i);
}

void	send_string(char *p_str, int p_pid)
{
	static int		cur = 0;
	static char		*str;
	static int		pid;
	static int		i = -1;

	if (p_pid)
	{
		str = p_str;
		pid = p_pid;
	}
	if (i < 0)
	{
		if (str[cur])
		{
			i = send_character(str[cur], pid);
			cur++;
		}
		else
			i = send_character(0, pid);
	}
	else
		i = send_character(0, 0);
}

void	client_action(int sig)
{
	if (sig == SIGUSR1)
		send_string("", 0);
	else if (sig == SIGUSR2)
		exit(0);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_putendl_fd("Using with:", 1);
		ft_putendl_fd("./client <process_id> <message>", 1);
		return (1);
	}
	signal(SIGUSR1, &client_action);
	signal(SIGUSR2, &client_action);
	if (argv[1][0] == '0')
	{
		ft_putendl_fd("Not support file descriptor 0.", 1);
		return (0);
	}
	pid = ft_atoi(argv[1]);
	send_string(argv[2], pid);
	while (1)
		pause();
	return (0);
}