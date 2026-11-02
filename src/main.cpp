#include <cstdio>
#include <orbis/libkernel.h>

int main()
{
    setvbuf(stdout, nullptr, _IONBF, 0);

    printf("================================\n");
    printf("       SAMIX GAMES PS4\n");
    printf("================================\n");
    printf("Native PS4 Homebrew\n");
    printf("Version: 1.0\n");
    printf("Status: Started\n");

    while (true)
    {
        sceKernelUsleep(1000000);
    }

    return 0;
}