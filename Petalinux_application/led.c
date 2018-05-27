#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int valuefd, exportfd, directionfd;
    int valuefd2;

    printf("GPIO test running...\n");

    // The GPIO has to be exported to be able to see it
    // in sysfs

    exportfd = open("/sys/class/gpio/export", O_WRONLY);
    if (exportfd < 0)
    {
        printf("Cannot open GPIO to export it\n");
        exit(1);
    }

    write(exportfd, "504", 4);
    write(exportfd, "511", 4);
    close(exportfd);

    printf("GPIO exported successfully\n");

    // Update the direction of the GPIO to be an output

    directionfd = open("/sys/class/gpio/gpio504/direction", O_RDWR);
    if (directionfd < 0)
    {
        printf("Cannot open GPIO direction it\n");
        exit(1);
    }
    write(directionfd, "out", 4);

    directionfd = open("/sys/class/gpio/gpio511/direction", O_RDWR);
    if (directionfd < 0)
    {
	   printf("Cannot open GPIO direction it\n");
	   exit(1);
    }

    write(directionfd, "out", 4);

    close(directionfd);

    printf("GPIO direction set as output successfully\n");

    // Get the GPIO value ready to be toggled

    valuefd = open("/sys/class/gpio/gpio504/value", O_RDWR);
    if (valuefd < 0)
    {
        printf("Cannot open GPIO value\n");
        exit(1);
    }

    valuefd2 = open("/sys/class/gpio/gpio511/value", O_RDWR);
    if (valuefd2 < 0)
    {
        printf("Cannot open GPIO value\n");
        exit(1);
    }

    printf("GPIO value opened, now toggling...\n");

    // toggle the GPIO as fast a possible forever, a control c is needed
    // to stop it

    while (1)
    {
        write(valuefd, "1", 2);
        write(valuefd2,"1", 2);
        //printf("ON\n");
        sleep(1);
        write(valuefd,"0", 2);
        write(valuefd2,"0",2);
        //printf("off\n");
        sleep(1);
    }
}
