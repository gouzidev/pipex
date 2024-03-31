#include <stdio.h>

struct car
{
    char *name;
    void (*start)();
};

void start_car()
{
    printf("started ... \n");
}

int main()
{    
    struct car c;
    c.start = start_car;
    c.start();
}
