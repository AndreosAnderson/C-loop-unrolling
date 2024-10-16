#include <stdlib.h>
#include <windows.h>
#include <psapi.h>

void multiplyMatrix(double** m1, double** m2, double** result, int n) {
    // Loop unrolling for the innermost loop
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;
            int k = 0;

            // Unrolling loop with a step size of 4
            while (k + 4 <= n) {
                result[i][j] += m1[i][k] * m2[k][j]
                    + m1[i][k + 1] * m2[k + 1][j]
                    + m1[i][k + 2] * m2[k + 2][j]
                    + m1[i][k + 3] * m2[k + 3][j];
                k += 4;
            }

            // Process the remaining elements if n is not divisible by 4
            while (k < n) {
                result[i][j] += m1[i][k] * m2[k][j];
                k++;
            }
        }
    }
}

double** allocateMatrix(int n) {
    double** matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
    }
    return matrix;
}

void freeMatrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void printMemoryAndCPUUsage() {
    PROCESS_MEMORY_COUNTERS memCounter;
    BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter));
    if (result) {
        printf("Memory usage: %ld KB\n", memCounter.WorkingSetSize / 1024);
    }

    FILETIME creationTime, exitTime, kernelTime, userTime;
    if (GetProcessTimes(GetCurrentProcess(), &creationTime, &exitTime, &kernelTime, &userTime)) {
        ULARGE_INTEGER kernel, user;
        kernel.LowPart = kernelTime.dwLowDateTime;
        kernel.HighPart = kernelTime.dwHighDateTime;
        user.LowPart = userTime.dwLowDateTime;
        user.HighPart = userTime.dwHighDateTime;

        double system_cpu_time = (double)kernel.QuadPart / 1e7;
        double user_cpu_time = (double)user.QuadPart / 1e7;

        printf("User CPU time: %f seconds\n", user_cpu_time);
        printf("System CPU time: %f seconds\n", system_cpu_time);
    }
}
