#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Definición de la estructura del proceso
typedef struct {
    int id;
    int tiempo_llegada;
    int duracion;
    int tiempo_espera;
    int prioridad;
}Proceso;

// Declaraciones de funciones para cada algoritmo de planificación
void fcfs(Proceso procesos[], int num_procesos);
void sjf(Proceso procesos[], int num_procesos);
void round_robin(Proceso procesos[], int num_procesos, int quantum);
void planificacion_por_prioridad(Proceso procesos[], int num_procesos);
void srtf(Proceso procesos[], int num_procesos);

// Función para calcular estadísticas
void calcular_estadisticas(Proceso procesos[], int num_procesos);

int main(){
    int opcion;
    int quantum;
    int num_procesos;
    
    do {
        printf("---> Ingrese el numero de procesos (debe ser mayor que 0): ");
        if(scanf("%d", &num_procesos) != 1 || num_procesos <= 0) {
            printf("-X- Ingrese un numero valido de procesos -X-\n");
            while(getchar() != '\n'); // Limpiar el buffer de entrada
        }
    } while (num_procesos <= 0);

    Proceso procesos[num_procesos];

    for(int i=0;i<num_procesos;i++){
        
        printf("- Proceso %d\n", i + 1);
        procesos[i].id = i + 1;
        printf("- Tiempo de llegada: ");
        scanf("%d", &procesos[i].tiempo_llegada);
        printf("- Tiempo de ejecucion: ");
        scanf("%d", &procesos[i].duracion);
        procesos[i].tiempo_espera = 0;

        if (procesos[i].duracion <= 0 || procesos[i].duracion > 1000) { 
            printf("\n-X- El tiempo de ejecucion debe ser mayor que 0 y menor que 1000. -X-\n");
            i--;
        }

    }

    do{
        printf("\n--- Simulador de Planificacion de Procesos ---\n");
        printf("1) Ejecutar algoritmo first come first served (FCFS)\n");
        printf("2) Ejecutar algoritmo shorted job first (SJF)\n");
        printf("3) Ejecutar algoritmo Round Robin (RR)\n");
        printf("4) Ejecutar algoritmo Planificador por prioridad (PP)\n");
        printf("5) Ejecutar algoritmo shorted remaining time next (SRTN)\n");
        printf("6) Calcular estadisticas \n");
        printf("0) Salir\n");
        printf("- Seleccione una opcion: \n");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                fcfs(procesos, num_procesos);
                break;
            case 2:
                sjf(procesos, num_procesos);
                break;
            case 3:
                do{
                    printf("Ingrese el quantum para Round Robin (debe ser mayor que 0): ");
                    if(scanf("%d", &quantum) != 1 || quantum <= 0){
                        printf("\n-X-Ingrese un valor valido para quantum-X-\n");
                        while(getchar() != '\n'); // Limpiar el buffer de entrada
                    }
                }while (quantum <= 0);
                round_robin(procesos, num_procesos, quantum);
                break;
            case 4:
                planificacion_por_prioridad(procesos, num_procesos);
                break;
            case 5:
                srtf(procesos, num_procesos);
                break;
            case 6:
                calcular_estadisticas(procesos, num_procesos);
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("-X- Opcion no valida. Por favor, ingrese una opcion valida. -X-\n");
                break;
        }
    } while (opcion != 0);

    return 0;
}

// Implementación de algoritmos de planificación

//Algoritmo first come first served
void fcfs(Proceso procesos[], int num_procesos){
    int tiempo_actual = 0;
    float tiempo_espera_total = 0;

    for (int i=0; i<num_procesos; i++) {
        if (tiempo_actual < procesos[i].tiempo_llegada) {
            tiempo_actual = procesos[i].tiempo_llegada;
        }

        procesos[i].tiempo_espera = tiempo_actual - procesos[i].tiempo_llegada;
        tiempo_espera_total += procesos[i].tiempo_espera;
        tiempo_actual += procesos[i].duracion;
    }

    float tiempo_espera_promedio = tiempo_espera_total/num_procesos;
    printf("FCFS - Tiempo de espera promedio: %.2f \n", tiempo_espera_promedio);
}
//Algoritmo shorted job first
void sjf(Proceso procesos[], int num_procesos){
    int tiempo_actual = 0;
    int procesos_restantes = num_procesos;
    float tiempo_espera_total = 0;

    while (procesos_restantes > 0) {
        int proceso_mas_corto = -1;
        int duracion_mas_corta = INT_MAX;

        for (int i = 0; i < num_procesos; i++) {
            if (procesos[i].tiempo_llegada <= tiempo_actual && procesos[i].duracion < duracion_mas_corta && procesos[i].duracion > 0) {
                if (procesos[i].duracion == duracion_mas_corta) {
                    if (procesos[i].tiempo_llegada < procesos[proceso_mas_corto].tiempo_llegada) {
                        proceso_mas_corto = i;
                        duracion_mas_corta = procesos[i].duracion;
                    }
                } else {
                    proceso_mas_corto = i;
                    duracion_mas_corta = procesos[i].duracion;
                }
            }
        }

        if (proceso_mas_corto == -1) {
            tiempo_actual++;
        }

        procesos[proceso_mas_corto].tiempo_espera += tiempo_actual - procesos[proceso_mas_corto].tiempo_llegada + 1;
        tiempo_espera_total += procesos[proceso_mas_corto].tiempo_espera;
        tiempo_actual += procesos[proceso_mas_corto].duracion;
        procesos[proceso_mas_corto].duracion = 0;
        procesos_restantes--;
    }

    float tiempo_espera_promedio = tiempo_espera_total / num_procesos;
    printf("SJF - Tiempo de espera promedio: %.2f\n", tiempo_espera_promedio);
}
//Agoritmo round robin 
void round_robin(Proceso procesos[], int num_procesos, int quantum){
    int tiempo_actual = 0;
    int procesos_restantes = num_procesos;
    float tiempo_espera_total = 0;
    int tiempo_total_ejecucion = 0;

    while (procesos_restantes > 0) {
        for (int i = 0; i < num_procesos; i++) {
            if (procesos[i].duracion > 0) {
                if (procesos[i].duracion > quantum) {
                    procesos[i].tiempo_espera += tiempo_actual - procesos[i].tiempo_llegada;
                    tiempo_espera_total += procesos[i].tiempo_espera;

                    tiempo_actual += quantum;
                    procesos[i].duracion -= quantum;
                } else {
                    procesos[i].tiempo_espera += tiempo_actual - procesos[i].tiempo_llegada;
                    tiempo_espera_total += procesos[i].tiempo_espera;

                    tiempo_actual += procesos[i].duracion;
                    procesos[i].duracion = 0;
                    procesos_restantes--;
                }
            }
            // Actualizar el tiempo total de ejecución al considerar la duración restante del proceso
            tiempo_total_ejecucion += procesos[i].duracion;
        }
    }

    float tiempo_espera_promedio = tiempo_espera_total / num_procesos;
    float utilizacion_cpu = ((float)tiempo_total_ejecucion / (tiempo_actual - 1)) * 100; // Calcular la utilización de la CPU correctamente
    printf("Round Robin - Tiempo de espera promedio: %.2f\n", tiempo_espera_promedio);
    printf("Utilizacion de la CPU: %.2f%%\n", utilizacion_cpu);
}
//Algoritmo planifacion por prioridad
void planificacion_por_prioridad(Proceso procesos[], int num_procesos){
    int tiempo_actual = 0;
    int procesos_restantes = num_procesos;
    float tiempo_espera_total = 0;

    while (procesos_restantes > 0) {
        int proceso_ejecutar = -1;
        int prioridad_mas_alta = INT_MAX;

        for (int i = 0; i < num_procesos; i++) {
            if (procesos[i].tiempo_llegada <= tiempo_actual && procesos[i].prioridad <= prioridad_mas_alta && procesos[i].duracion > 0) {
                if (procesos[i].prioridad < prioridad_mas_alta || (procesos[i].prioridad == prioridad_mas_alta && procesos[i].tiempo_llegada < procesos[proceso_ejecutar].tiempo_llegada)) {
                    proceso_ejecutar = i;
                    prioridad_mas_alta = procesos[i].prioridad;
                }
            }
        }

        if (proceso_ejecutar == -1) {
            tiempo_actual++;
            continue;
        }

        // Reducir el tiempo de ejecución del proceso encontrado
        procesos[proceso_ejecutar].duracion--;

        // Si la duración es 0, el proceso ha terminado
        if (procesos[proceso_ejecutar].duracion == 0) {
            procesos_restantes--;
            int tiempo_final = tiempo_actual + 1;
            procesos[proceso_ejecutar].tiempo_espera = tiempo_final - procesos[proceso_ejecutar].tiempo_llegada - procesos[proceso_ejecutar].duracion;
            tiempo_espera_total += procesos[proceso_ejecutar].tiempo_espera;
        }

        tiempo_actual++;
    }

    float tiempo_espera_promedio = tiempo_espera_total / num_procesos;
    printf("Planificacion por Prioridad - Tiempo de espera promedio: %.2f\n", tiempo_espera_promedio);
}
//Algoritmo shorted remaining time next
void srtf(Proceso procesos[], int num_procesos){
    int tiempo_actual = 0;
    int procesos_restantes = num_procesos;
    float tiempo_espera_total = 0;

    while (procesos_restantes > 0) {
        int proceso_mas_corto = -1;
        int duracion_mas_corta = INT_MAX;

        for (int i = 0; i < num_procesos; i++) {
            if (procesos[i].tiempo_llegada <= tiempo_actual && procesos[i].duracion > 0) {
                if (procesos[i].duracion < duracion_mas_corta) {
                    proceso_mas_corto = i;
                    duracion_mas_corta = procesos[i].duracion;
                }
            }
        }

        if (proceso_mas_corto == -1) {
            tiempo_actual++;
            continue;
        }

        procesos[proceso_mas_corto].tiempo_espera += tiempo_actual - procesos[proceso_mas_corto].tiempo_llegada;
        tiempo_espera_total += procesos[proceso_mas_corto].tiempo_espera;
        tiempo_actual += procesos[proceso_mas_corto].duracion;
        procesos[proceso_mas_corto].duracion = 0;
        procesos_restantes--;
    }

    float tiempo_espera_promedio = tiempo_espera_total / num_procesos;
    printf("SRTN - Tiempo de espera promedio: %.2f\n", tiempo_espera_promedio);
}

// Función para calcular estadísticas
void calcular_estadisticas(Proceso procesos[], int num_procesos){
    float tiempo_espera_promedio = 0;
    float utilizacion_cpu = 0;

    // Calcular tiempo de espera promedio
    for (int i = 0; i < num_procesos; i++) {
        tiempo_espera_promedio += procesos[i].tiempo_espera;
    }
    tiempo_espera_promedio /= num_procesos;

    // Calcular tiempo total de ejecución de todos los procesos
    int tiempo_total_ejecucion = 0;
    for (int i = 0; i < num_procesos; i++) {
        tiempo_total_ejecucion += procesos[i].duracion;
    }

    // Calcular tiempo total transcurrido durante la ejecución de los procesos
    int tiempo_total_transcurrido = 0;
    for (int i = 0; i < num_procesos; i++) {
        if (procesos[i].tiempo_llegada > tiempo_total_transcurrido) {
            tiempo_total_transcurrido = procesos[i].tiempo_llegada;
        }
        tiempo_total_transcurrido += procesos[i].duracion;
    }

    // Calcular utilización de la CPU como porcentaje del tiempo total transcurrido
    utilizacion_cpu = ((float)tiempo_total_ejecucion / tiempo_total_transcurrido) * 100;

    printf("Tiempo de espera promedio: %.2f\n", tiempo_espera_promedio);
    printf("Utilizacion de la CPU: %.2f%%\n", utilizacion_cpu);
}