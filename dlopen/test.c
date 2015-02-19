
// http://lists.uclibc.org/pipermail/uclibc/2009-October/043115.html

#include <netdb.h>
#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>

typedef int (*func)(void);

int main(int argn, char* argv[])
{
    if(argn<2 || !argv[1])
    {
        printf("give a so name!\n", argv[1]);
        return -1;
    }

    void *lib = dlopen(argv[1], RTLD_NOW);
    if(!lib)
    {
        printf("file %s not found\n", argv[1]);
        return -1;
    }

    func f = dlsym(lib, "runthething");
    if(!f)
    {
        printf("function runthething not found\n", argv[1]);
        return -1;
    }

    f();

    printf("Bye !\n");
    return 0;
}

