#include "minitalk.h"
#include <signal.h>


void	send_character(int p_pid, unsigned char p_c, int shift)
{

	if (p_pid <= 0 || kill(p_pid, 0) < 0)
	{
		ft_putendl_fd("Invalid Process ID.", 1);
		exit(0);
	}
	p_c = p_c >> shift;
	p_c = p_c << 7;
	if (p_c == 128)
		{
		kill(p_pid, SIGUSR1);
		//ft_printf("%i\n", c);
		}
	else
	{
		kill(p_pid, SIGUSR2);
		//ft_printf("%i\n", c);
	}
	usleep(1);
}

void	send_string(int pid, char *p_string)
{
	static int		char_count = 0;
	static int		str_num = 0;
	static char		*str;
	static int		serv_pid = 0;
	static int		shift = 7;

	if (shift < 0)
	{
		shift = 7;
		char_count++;
	}
	if (pid)
	{
		str = p_string;
		serv_pid = pid;
	}
	if (str_num == 0)
		str_num = (int) ft_strlen(globe_argv[1]);
	if (char_count > str_num)
		exit (0);
	send_character(serv_pid, globe_argv[1][char_count], shift--);
	//char_count++;
}

static void	client_action(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if(sig == SIGUSR1 && info->si_pid == ft_atoi(globe_argv[0]))
	{	
		send_string("", 0);
		usleep(1);
	}
	else if (sig == SIGUSR2)
	{
		ft_printf("Server received all messages.\n");
		exit (1);
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
	sigemptyset(&cl.sa_mask);
	cl.sa_sigaction = client_action;	
	cl.sa_flags = SA_SIGINFO | SA_NODEFER;
	if (sigaction(SIGUSR1, &cl, 0) == -1)
		ft_printf("%s\n", errno);
	if (sigaction(SIGUSR2, &cl, 0) == -1)
		ft_printf("%s\n", errno);	
	/*if (argv[1][0] == '0')
	{
		ft_putendl_fd("Not support file descriptor 0.", 1);
		return (0);
	}*/
	globe_argv[0] = argv[1];
	globe_argv[1] = argv[2];
	//ft_printf("%i", pid);

	serv_pid = ft_atoi(globe_argv[0]);
	send_string(argv[2], serv_pid);
	while(1)
		pause();
	return(0);
}