/*ejemplo de mutex*/
#include <pthread.h>

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;
pthread_mutex_t resource_mutex = PTHREAD_MUTEX_INITIALIZER;

/* decrease available resources by count resources */
/* return 0 if sufficient resources available, */
/* otherwise return -1 */
int decrease_count(int count) {
  pthread_mutex_lock(&resource_mutex);
  if (available_resources < count) {
    pthread_mutex_unlock(&resource_mutex);
    return -1;
  } else {
    available_resources -= count;
    pthread_mutex_unlock(&resource_mutex);
    return 0;
  }
}

/* increase available resources by count */
int increase_count(int count) {
  pthread_mutex_lock(&resource_mutex);
  available_resources += count;
  pthread_mutex_unlock(&resource_mutex);
  return 0;
}

