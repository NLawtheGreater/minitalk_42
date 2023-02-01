#include "minitalk_bonus.h"


static void	server_action(int sig, siginfo_t *info, void *context)
{
	static int				i = 0;
	static unsigned char	c = 0;

	(void)context;
	if (i >= 8)
		i = 0;
	if (sig == SIGUSR1)
	{
		//ft_printf("SIGUSR1 received\n");	
		kill(info->si_pid, SIGUSR1);
		c <<= 1;
		c += 1;
		i++;
	}
	else if(sig == SIGUSR2)
	{
		//ft_printf("SIGUSR2 received\n");	
		kill(info->si_pid, SIGUSR1);
		c <<= 1;
		i++;
	}
	if (i == 8 && c)
		kill(info->si_pid, SIGUSR2);
		ft_putchar_fd(c, 1);
		//ft_printf("%d\n", c);
}

int	main(void)
{
	struct sigaction	gg;

	ft_printf("SERVER pid is: %i\n", getpid());
	//struct sigaction
	//signal(SIGUSR1, handle_sigusr1);
	sigemptyset(&gg.sa_mask);
		//ft_printf("yay\n");
	gg.sa_sigaction = server_action;
	gg.sa_flags = SA_SIGINFO | SA_NODEFER | SA_RESTART;
	if (sigaction(SIGUSR1, &gg, 0) == -1)
		ft_printf("%s\n", errno);
	if (sigaction(SIGUSR2, &gg, 0) == -1)
		ft_printf("%s\n", errno);
	while (1)
		pause();
	//sigaction(SIGUSR1, );
	return (0);
}
