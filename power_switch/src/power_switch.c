#include <fcntl.h>
#include <signal.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include "linux/autoconf.h"
#include "ralink_gpio.h"
#define CONTROLPOWER 7 /*gpio#7*/

int gFd;
static void ResetSigHandler(int signum)
{
	if (signum != SIGUSR2)
		return;
    
    //set gpio output high
    if(ioctl(gFd,RALINK_GPIO_WRITE_DATA1,CONTROLPOWER) < 0 ){
        printf("Time Out:set gpio#%d Output high error\n",CONTROLPOWER);
        return;
    }
}

static void CutOffPowerHandler(int signum)
{
	if (signum != SIGUSR1)
		return;
    system("/usr/bin/switch.sh");
    sleep(1);
    //set gpio output low
    if(ioctl(gFd,RALINK_GPIO_WRITE_DATA0,CONTROLPOWER) < 0 ){
        printf("CutOffPowerHandler:set gpio#%d Output low error\n",CONTROLPOWER);
        return;
    }
}

static void InitGpio()
{
	ralink_gpio_reg_info info;
	system("mknod /dev/gpio c 252 0");
	gFd = open("/dev/gpio", O_RDONLY);
	if (gFd < 0) {
		perror("/dev/gpio");
		return;
	}
	//set gpio direction to out
	if (ioctl(gFd, RALINK_GPIO_SET_DIR_OUT, RALINK_GPIO(CONTROLPOWER)) < 0)
		goto ioctl_err;

    //set gpio output high
    if(ioctl(gFd,RALINK_GPIO_WRITE_DATA1,CONTROLPOWER) < 0 ){
        printf("InitGpio:set gpio#%d Output high error\n",CONTROLPOWER);
        goto ioctl_err;
    }
	//enable gpio interrupt
	if (ioctl(gFd, RALINK_GPIO_ENABLE_INTP) < 0)
		goto ioctl_err;
	//register my information
	info.pid = getpid();
	info.irq = 18;/*gpio#7 Interrupt number*/
	if (ioctl(gFd, RALINK_GPIO_REG_IRQ, &info) < 0)
		goto ioctl_err;

	signal(SIGUSR1, CutOffPowerHandler);
	signal(SIGUSR2, ResetSigHandler);
	return;

ioctl_err:
	perror("ioctl");
	close(gFd);
	return;
}


int main(int argc, char** argv)
{
	pid_t pid;
	if((pid = fork()) < 0)
	{
		printf("fork error\n");
	}
	else if (pid == 0)
	{
        InitGpio();
		while(1)
       	{
			sleep(100);
		}
	}
	else
	{
		exit(0);
	}
}


