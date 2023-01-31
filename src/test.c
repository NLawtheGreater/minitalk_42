#include "minitalk.h"
#include "libft.h"

void	handleSIG1(int signo)
{
	if (signo == SIGUSR1)
		ft_printf("SIGUSR1 received\n");
}
void	handleSIG2(int signo)
{
	if (signo == SIGUSR2)
		ft_printf("SIGUSR2 received\n");
}

int	main(void)
{
	ft_printf("SERVER pid is: %i\n", getpid());
	signal(SIGUSR1, handleSIG1);
	signal(SIGUSR2, handleSIG2);
	while (1)
		pause();
	return (0);
}