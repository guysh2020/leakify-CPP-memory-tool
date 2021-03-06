
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>

#define FILE_NAME ".\\userData\\allocations.txt"

FILE* openFile()
{
    try {
        FILE* fp = fopen(FILE_NAME,"a");
        return fp;
    } catch(const std::exception& e) {
        std::cout << e.what();
    }
}

void *my_malloc(size_t size, const char *file, int line, const char *func)
{
    FILE *fp = openFile();
    void *p = malloc(size);
    if(p == NULL) {
        return NULL;
    }
    fprintf(fp, "0 Allocated =%s,%i,%s,#%p[%li]\n", file, line, func, p, size);
    fclose(fp);

    return p;
}

void *my_calloc(size_t count, size_t size, const char *file, int line, const char *func)
{
    FILE *fp = openFile();
    void *p = calloc(count, size);
    if(p == NULL) {
        return NULL;
    }
    fprintf(fp, "0 Allocated =%s,%i,%s,#%p[%li]\n", file, line, func, p, size);
    fclose(fp);

    return p;
}

void my_free(void *ptr, const char *file, int line, const char *func)
{
    FILE *fp = openFile();
    fprintf(fp, "1 freeing =%s,%i,%s,#%p\n", file, line, func, ptr);
    fclose(fp);

    free(ptr);
}

void *operator new(std::size_t sz, const char *file, int line, const char *func)
{
    FILE *fp = openFile();
    void *ptr = std::malloc(sz);
    if(ptr == NULL) {
        return NULL;
    }
    fprintf(fp, "0 Allocated =%s,%i,%s,#%p[%li]\n", file, line, func, ptr, sz);
    fclose(fp);

    return ptr;
}

void *operator new[](std::size_t sz,const char *file, int line, const char *func)
{
    FILE *fp = openFile();
    void *ptr = std::malloc(sz);
        if(ptr == NULL) {
        return NULL;
    }
    fprintf(fp, "0 Allocated =%s,%i,%s,#%p[%li]\n", file, line, func, ptr, sz);
    fclose(fp);

    return ptr;
}

void operator delete(void *ptr, std::size_t sz)
{
    FILE *fp = openFile();
    fprintf(fp, "1 freeing =#%p[%zu]\n", ptr, sz);
    fclose(fp);

    free(ptr);
}

void operator delete[](void *ptr, std::size_t sz)
{
    FILE *fp = openFile();
    fprintf(fp, "1 freeing =#%p[%zu]\n", ptr, sz);
    fclose(fp);
    
    free(ptr);
}

void operator delete[](void *ptr)
{
    FILE *fp = openFile();
    fprintf(fp, "1 freeing =#%p\n", ptr);
    fclose(fp);

    free(ptr);
}
