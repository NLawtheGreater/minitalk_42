#include "minitalk.h"
#include <signal.h>

char	*globe_argv[2];

void	send_character(unsigned char p_c, int p_pid)
{
	//ft_printf("%c\n", p_c);
	//ft_printf("%i\n", p_pid);
	unsigned int c;
	int shift;

	shift = 7;
	while (shift >= 0)
	{
	c = p_c >> shift--;
	if (c == 1)
		{
		kill(p_pid, SIGUSR1);
		//ft_printf("%i\n", c);
		}
	else
	{
		kill(p_pid, SIGUSR2);
		//ft_printf("%i\n", c);
	}
	}
}
void	send_string()
{
	static int		char_count = 0;
	static int		str_num = 0;
	static int		serv_pid = 0;
	//static int		shift = 7;

	/*if (shift == -1)
		char_count++;
	if (shift < 0)
		shift = 7;
	*/
	if (serv_pid == 0)
		serv_pid = ft_atoi(globe_argv[0]);
	if (str_num == 0)
		str_num = (int) ft_strlen(globe_argv[1]);
	if (char_count > str_num)
		exit (0);
	send_character(globe_argv[1][char_count], serv_pid);
	char_count++;
	//shift--;
}

static void	client_action(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if(sig == SIGUSR1)
	{	
		send_string();
		usleep(1);
	}
	else
	{
		ft_printf("Server received all messages.\n");
		exit (0);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	cl;

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
	send_string();
	while(1)
		pause();
	return(0);
}