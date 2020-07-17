#include <stdio.h>
#include <dlfcn.h>

int mallocTotal = 0;
int freeTotal = 0;

void *malloc(size_t size) {
    static void *(*mallocp)(size_t size);
    char *error;
    void *ptr;

    /* get address of libc malloc */
    if (!mallocp) {
	mallocp = dlsym(RTLD_NEXT, "malloc");
	if ((error = dlerror()) != NULL) {
	    fputs(error, stderr);
	    exit(1);
	}
    }
    ptr = mallocp(size);
    printf("malloc(%d) = %p\n", size, ptr); 
	mallocTotal++;
	printf("\nmalloc: %d", mallocTotal); 
    return ptr;
}

void free(void *ptr) {
    static void (*freep)(void *);
    char *error;

    /* get address of libc free */
    if (!freep) {
	freep = dlsym(RTLD_NEXT, "free");
	if ((error = dlerror()) != NULL) {
	    fputs(error, stderr);
	    exit(1);
	}
    }
    printf("free(%p)\n", ptr);     
    freep(ptr);
}
#endif
	
