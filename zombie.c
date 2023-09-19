#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Proceso hijo
        printf("Soy el proceso hijo\n");
	sleep(100);
    } else if (pid > 0) {
        // Proceso padre
         // Espera para dar tiempo al proceso hijo a completarse
    }
    
    // El proceso padre no recopila el estado de salida del proceso hijo
    return 0;
}
