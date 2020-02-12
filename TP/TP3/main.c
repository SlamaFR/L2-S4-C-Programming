#include <sys/time.h>

typedef struct timeval Time;

long int intervalle_ms(Time debut, Time fin) {
    return (fin.tv_sec - debut.tv_sec) * 1000 + (fin.tv_usec - debut.tv_usec) / 1000;
}
