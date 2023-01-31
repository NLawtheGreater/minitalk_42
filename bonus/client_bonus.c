#include "minitalk_bonus.h"

static void	client_action(int sig, siginfo_t *info, void *context)
{

	(void)info;
	(void)context;
	if (sig == SIGUSR1)
		ft_printf("server received SIGUSR1\n");	
	else if(sig == SIGUSR2)
		ft_printf("server received SIGUSR2\n");
	usleep(50);
}

void	send_character(unsigned char p_c, int p_pid)
{
	//ft_printf("%c\n", p_c);
	//ft_printf("%i\n", p_pid);
	unsigned char c;
	int	shift;

	shift = 7;
	while(shift >= 0)
	{
		c = p_c >> shift--;
		c <<= 7;
		if (c == 128)
			{
			kill(p_pid, SIGUSR1);
			//ft_printf("%i\n", c);
			}
		else
		{
			kill(p_pid, SIGUSR2);
			//ft_printf("%i\n", c);
		}
		usleep(500);
	}
}
void	send_string(char *p_str, int p_pid)
{
	int	cur;

	cur = 0;
	while (p_str[cur])
	{
		send_character(p_str[cur++], p_pid);
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	gg;

	if (argc != 3)
		return (1);
	/*if (argv[1][0] == '0')
	{
		ft_putendl_fd("Not support file descriptor 0.", 1);
		return (0);
	}*/
	sigemptyset(&gg.sa_mask);
		//ft_printf("yay\n");
	gg.sa_sigaction = client_action;
	gg.sa_flags = SA_SIGINFO | SA_NODEFER ;
	if (sigaction(SIGUSR1, &gg, 0) == -1)
		ft_printf("%s\n", errno);
	if (sigaction(SIGUSR2, &gg, 0) == -1)
		ft_printf("%s\n", errno);
	pid = ft_atoi(argv[1]);
	//ft_printf("%i", pid);
	send_string(argv[2], pid);
	return(0);
}