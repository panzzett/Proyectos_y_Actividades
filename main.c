#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4

void imprimirMatriz(float matriz[N][N+1], int numColumnas) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < numColumnas; j++) {
            printf("%f\t", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void intercambiarFilas(float matriz[N][N+1], int fila1, int fila2) {
    for (int j = 0; j < N; j++) {
        float temp = matriz[fila1][j];
        matriz[fila1][j] = matriz[fila2][j];
        matriz[fila2][j] = temp;
    }
}

void eliminacionGaussiana(float matriz[N][N+1], int numColumnas) {
    for (int i = 0; i < N-1; i++) {
        // Paso 2: Identificar el elemento pivote en la columna actual
        int filaPivote = i;
        for (int k = i+1; k < N; k++) {
            if (fabs(matriz[k][i]) > fabs(matriz[filaPivote][i])) {
                filaPivote = k;
            }
        }

        // Paso 3: Intercambiar filas si es necesario
        if (filaPivote != i) {
            printf("Intercambio de filas %d y %d:\n", i+1, filaPivote+1);
            intercambiarFilas(matriz, i, filaPivote);
            imprimirMatriz(matriz, numColumnas);
        }

        // Paso 4: Aplicar eliminación gaussiana
        for (int k = i+1; k < N; k++) {
            float factor = matriz[k][i] / matriz[i][i];
            for (int j = i; j < numColumnas; j++) {
                matriz[k][j] -= factor * matriz[i][j];
            }
        }
        printf("Eliminacion gaussiana en la columna %d:\n", i+1);
        imprimirMatriz(matriz, numColumnas);
    }
}

void formaEscalonadaReducida(float matriz[N][N+1]) {
    // Método adicional para obtener la forma escalonada reducida
    for (int i = N-1; i >= 0; i--) {
        // Paso 1: Hacer el coeficiente principal de la fila igual a 1
        float factor = 1 / matriz[i][i];
        for (int j = i; j <= N; j++) {
            matriz[i][j] *= factor;
        }

        // Paso 2: Hacer cero los demás elementos en la columna
        for (int k = i-1; k >= 0; k--) {
            factor = matriz[k][i];
            for (int j = i; j <= N; j++) {
                matriz[k][j] -= factor * matriz[i][j];
            }
        }
    }

    // Mostrar la forma escalonada reducida
    printf("Forma escalonada reducida:\n");
    imprimirMatriz(matriz, N+1);
}

void resolverSistema(float matriz[N][N+1]) {
    // Procedimiento para resolver el sistema hacia atrás
    printf("Resolucion hacia atras del sistema:\n");
    float soluciones[N];
    for (int i = N-1; i >= 0; i--) {
        soluciones[i] = matriz[i][N];
        for (int j = i+1; j < N; j++) {
            soluciones[i] -= matriz[i][j] * soluciones[j];
        }
        printf("x%d = %f\n", i+1, soluciones[i]);
    }
}

int main() {
    float matriz[N][N+1];
    char confirmacion;
    char confirmacionAmp;

    // Inicializar la matriz
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N+1; j++) {
            matriz[i][j] = 0.0f;
        }
    }

    // Paso 1: Pedir al usuario que introduzca los valores de la matriz reducida 4x4
    do {
        printf("Introduce los coeficientes de la matriz reducida 4x4 (filas x columnas):\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("Matriz[%d][%d]: ", i + 1, j + 1);
                scanf("%f", &matriz[i][j]);
            }
        }

        // Mostrar la matriz reducida
        printf("Matriz reducida 4x4:\n");
        imprimirMatriz(matriz, N);

        // Paso 2: Preguntar al usuario si está de acuerdo con los valores de la matriz reducida 4x4
        printf("¿Estas de acuerdo con la matriz reducida? (s/n): ");
        scanf(" %c", &confirmacion);

        // Limpiar el búfer de entrada
        while ((getchar()) != '\n');
    } while (confirmacion == 'n' || confirmacion == 'N');

    // Paso 3: Pedir al usuario que introduzca los valores del vector de términos independientes
    do {
        printf("Introduce los valores del vector de terminos independientes:\n");
        for (int i = 0; i < N; i++) {
            printf("Vector[%d]: ", i + 1);
            scanf("%f", &matriz[i][N]);
        }

        // Paso 4: Mostrar la matriz ampliada 4x5
        printf("Matriz ampliada 4x5:\n");
        imprimirMatriz(matriz, N + 1);

        // Paso 5: Preguntar al usuario si está de acuerdo con la matriz ampliada
        printf("¿Estas de acuerdo con la matriz ampliada? (s/n): ");
        scanf(" %c", &confirmacionAmp);
    }while(confirmacionAmp == 'n' || confirmacionAmp == 'N');
    // Paso 6: Ejecutar la eliminación gaussiana y resolver el sistema si el usuario está de acuerdo
    if (confirmacionAmp == 's' || confirmacionAmp == 'S') {
        eliminacionGaussiana(matriz, N+1);

        printf("Matriz triangular superior resultante:\n");
        imprimirMatriz(matriz, N+1);

        formaEscalonadaReducida(matriz);

        resolverSistema(matriz);
    } else {
        printf("Operacion cancelada por el usuario.\n");
    }

    return 0;
}
