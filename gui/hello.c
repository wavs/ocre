#include <stdio.h>
#include <stdlib.h>

int main(int argv, char *argv[])
{
    int age = 0;
    (void)printf("Quel age avez vous ? ");
    (void)scanf("%d", &age);

    if (age < 18)
    {
        (void)puts("Vous etes mineur !");
    }
    else
    {
        (void)puts("Vous etes majeur !");
    }

    return EXIT_SUCCESS;
}
