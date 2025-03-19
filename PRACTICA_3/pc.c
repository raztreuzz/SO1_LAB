#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void crear_hijos(char padre, int cantidad, char hijos[]) {
    for (int i = 0; i < cantidad; i++) {
        pid_t pid = fork();
        if (pid == 0) {  // Proceso hijo
            printf("Soy %c PID#: %d, hijo de %c con #: %d\n", hijos[i], getpid(), padre, getppid());

            // Nivel 4: Crea hijos de C o E
            if (hijos[i] == 'C') {
                char sub_hijos[] = {'F', 'G', 'H'};
                crear_hijos('C', 3, sub_hijos);
            } else if (hijos[i] == 'E') {
                char hijo_e[] = {'I'};
                crear_hijos('E', 1, hijo_e);
            }

            // Nivel 5: I crea a J
            if (hijos[i] == 'I') {
                char hijo_i[] = {'J'};
                crear_hijos('I', 1, hijo_i);
            }

            return; // Termina el hijo para evitar ejecuciones no deseadas
        }
    }
    
    // Esperar a todos los hijos
    while (wait(NULL) > 0);
}

int main() {
    printf("Soy A PID#: %d\n", getpid());

    pid_t pid_b = fork();
    if (pid_b == 0) { // Proceso B
        printf("Soy B PID#: %d, hijo de A con #: %d\n", getpid(), getppid());
        
        // Nivel 3: C, D, E
        char hijos_b[] = {'C', 'D', 'E'};
        crear_hijos('B', 3, hijos_b);
        
        return 0;
    }

    wait(NULL); // Esperar a B
    return 0;
}
