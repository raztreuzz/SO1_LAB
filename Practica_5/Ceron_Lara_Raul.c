#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TAM 1000
#define NUM_THREADS 4

int primos[TAM] = {0};
pthread_mutex_t lock;

// Función para verificar si un número es primo
int es_primo(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

// Estructura para manejar la información de cada hilo
typedef struct {
    int inicio;
    int fin;
    int cont;
} Hilo_Info;

// Función que ejecutará cada hilo
void *buscar_primos(void *arg) {
    Hilo_Info *info = (Hilo_Info *)arg;
    info->cont = 0;

    for (int i = info->inicio; i < info->fin; i++) {
        if (es_primo(i + 1)) { // Se evalúa el número real (i+1)
            pthread_mutex_lock(&lock);
            primos[i] = 1; // Se marca como primo
            pthread_mutex_unlock(&lock);
            info->cont++;
        }
    }
    pthread_exit((void *)(intptr_t)info->cont);
}

int main() {
    pthread_t threads[NUM_THREADS];
    Hilo_Info datos_info[NUM_THREADS];
    int segmento = TAM / NUM_THREADS;
    int total_primos = 0;

    pthread_mutex_init(&lock, NULL);

    // Creación de hilos
    for (int i = 0; i < NUM_THREADS; i++) {
        datos_info[i].inicio = i * segmento;
        datos_info[i].fin = (i == NUM_THREADS - 1) ? TAM : (i + 1) * segmento;
        pthread_create(&threads[i], NULL, buscar_primos, &datos_info[i]);
    }

    // Esperar a que terminen los hilos y sumar resultados
    for (int i = 0; i < NUM_THREADS; i++) {
        void *count;
        pthread_join(threads[i], &count);
        total_primos += (intptr_t)count;
    }

    pthread_mutex_destroy(&lock);

    // Imprimir los primos encontrados
    printf("Total de primos: %d\n", total_primos);
    for (int i = 0; i < TAM; i++) {
        if (primos[i]) printf("%d ", i + 1);
    }
    printf("\n");

    return 0;
}
