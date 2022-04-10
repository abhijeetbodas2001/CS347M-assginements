#include <pthread.h>

typedef struct zemaphore {
    int n;
    pthread_cond_t cv;
    pthread_mutex_t m;
} zem_t;

void zem_init(zem_t *, int);
void zem_up(zem_t *);
void zem_down(zem_t *);
