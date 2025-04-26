#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // Add this include

size_t MAX;
double *A, *B, *C;
FILE *input;
char buffer[32];

int main(const int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <version> <size>\n", argv[0]);
        return 1;
    }

    const int version = atoi(argv[1]);
    MAX = (size_t) atoi(argv[2]);

    A = _aligned_malloc(MAX * sizeof(double), sizeof(double));
    B = _aligned_malloc(MAX * sizeof(double), sizeof(double));
    C = _aligned_malloc(MAX * sizeof(double), sizeof(double));

    if (!A || !B || !C) {
        printf("Memory allocation failed\n");
        _aligned_free(A);
        _aligned_free(B);
        _aligned_free(C);
        return 1;
    }

    input = fopen("D:/Code/Benchmarking/input.txt", "r");
    if (!input) {
        printf("Error opening file\n");
        _aligned_free(A);
        _aligned_free(B);
        _aligned_free(C);
        return 1;
    }

    LARGE_INTEGER frequency;
    if (!QueryPerformanceFrequency(&frequency)) {
        printf("QueryPerformanceFrequency failed\n");
        fclose(input);
        _aligned_free(A);
        _aligned_free(B);
        _aligned_free(C);
        return 1;
    }
    const double freq = (double)frequency.QuadPart;

    LARGE_INTEGER startTime, endTime;
    double time;

    switch (version) {
        case 1: {
            QueryPerformanceCounter(&startTime);

            for (int i = 0; i < MAX; ++i) {
                if (fgets(buffer, sizeof(buffer), input))
                    A[i] = strtod(buffer, NULL);
            }

            for (int i = 0; i < MAX; ++i) {
                if (fgets(buffer, sizeof(buffer), input))
                    B[i] = strtod(buffer, NULL);
            }

            for (int i = 0; i < MAX; ++i) {
                C[i] = A[i] * B[i];
            }

            QueryPerformanceCounter(&endTime);
            time = (double)(endTime.QuadPart - startTime.QuadPart) / freq;
            break;
        }

        case 2: {
            QueryPerformanceCounter(&startTime);

            for (int i = 0; i < MAX; ++i) {
                if (fgets(buffer, sizeof(buffer), input))
                    A[i] = strtod(buffer, NULL);
                if (fgets(buffer, sizeof(buffer), input))
                    B[i] = strtod(buffer, NULL);
            }
            for (int i = 0; i < MAX; ++i) {
                C[i] = A[i] * B[i];
            }

            QueryPerformanceCounter(&endTime);
            time = (double)(endTime.QuadPart - startTime.QuadPart) / freq;
            break;
        }

        case 3: {
            QueryPerformanceCounter(&startTime);

            for (int i = 0; i < MAX; ++i) {
                if (fgets(buffer, sizeof(buffer), input))
                    A[i] = strtod(buffer, NULL);
                if (fgets(buffer, sizeof(buffer), input))
                    B[i] = strtod(buffer, NULL);
                C[i] = A[i] * B[i];
            }

            QueryPerformanceCounter(&endTime);
            time = (double)(endTime.QuadPart - startTime.QuadPart) / freq;
            break;
        }

        default:
            printf("Invalid version\n");
            fclose(input);
            _aligned_free(A);
            _aligned_free(B);
            _aligned_free(C);
            return 1;
    }

    fclose(input);
    _aligned_free(A);
    _aligned_free(B);
    _aligned_free(C);

    FILE *output = fopen("D:/Code/Benchmarking/results.csv", "a");
    if (!output) {
        printf("Error opening output file\n");
        return 1;
    }

    fprintf(output, "%d,%zu,%.9f\n", version, MAX, time); // Increased precision
    fclose(output);

    return 0;
}