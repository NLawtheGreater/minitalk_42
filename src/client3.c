#include "minitalk.h"
#include <signal.h>

int	send_character(int p_pid, char p_c)
{
	static int		shift = -1;
	static char		c;
	static int		pid;


	if (p_pid)
	{
		c = p_c;
		pid = p_pid;
	}
	if (pid <= 0 || kill(pid, 0) < 0)
	{
		ft_putendl_fd("Invalid Process ID.", 1);
		exit(1);
	}
	if (shift < 0)
		shift = 7;
	if (c & (1 << shift))
		{
		kill(pid, SIGUSR1);
		//ft_printf("%i\n", c);
		}
	else
		kill(pid, SIGUSR2);
	shift--;
	return (shift);
}

void	send_string(int pid, char *p_string)
{
	static int		char_count = 0;
	static char		*str;
	static int		serv_pid = 0;
	static int		shift = -1;

	
	if (pid)
	{
		str = p_string;
		serv_pid = pid;
	}
	if (shift < 0)
	{
		if (str[char_count])
		{
			shift = send_character(serv_pid, str[char_count++]);
		}
		else
			shift = send_character(serv_pid, 0);
	}
	else
		shift = send_character(0, 0);
}

static void	client_action(int sig, siginfo_t *info, void *context)
{
	
	(void)context;
	if(sig == SIGUSR1 && info->si_pid)
	{	
		send_string(0, "");
	}
	else if (sig == SIGUSR2)
	{
		ft_printf("Server received all messages.\n");
		exit (0);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	cl;
	int					serv_pid;

	if (argc != 3)
	{
		ft_putstr_fd("parameters incorrect", 1);
		return (1);
	}
	ft_memset(&cl, 0, sizeof(cl));
	sigemptyset(&cl.sa_mask);
	cl.sa_sigaction = client_action;	
	cl.sa_flags = SA_SIGINFO | SA_NODEFER;
	if (sigaction(SIGUSR1, &cl, 0) == -1)
		ft_printf("%s\n", errno);
	if (sigaction(SIGUSR2, &cl, 0) == -1)
		ft_printf("%s\n", errno);	
	if (argv[1][0] == '0')
	{
		ft_putendl_fd("Not support file descriptor 0.", 1);
		return (0);
	}

	serv_pid = ft_atoi(argv[1]);
	send_string(serv_pid, argv[2]);
	while(1)
		pause();
	return(0);
}