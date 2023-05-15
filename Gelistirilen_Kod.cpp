 #include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define ARRAY_SIZE 20
#define GRAPH_SIZE 10
#define MAX_WEIGHT 10
#define INFINITY INT_MAX

void generateRandomNumbers(int a[], int size) {
    for (int i = 0; i < size; i++) {
        a[i] = rand() % (2 * MAX_WEIGHT) - MAX_WEIGHT;
    }
    printf("Array generated successfully.\n");
}

void merge(int a[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];

    i = 0; 
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        }
        else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}

void sortArray(int a[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        sortArray(a, l, m);
        sortArray(a, m + 1, r);

        merge(a, l, m, r);
    }
}

int performOperationOnArray(int a[], int size) {
    int t = 0, current_sum = 0, count=0;
    for (int i = 0; i < size; i++) {
        if (current_sum + a[i] > 0) {
            current_sum = current_sum + a[i];
            count++;
        }
        else {
            current_sum = 0;
        }
        if (current_sum > t) {
            t = current_sum;
        }
    }
    printf("Operation performed on array.\n");
    return count == 0 ? 0 : t/count;
}

void performOperationOnGraph(int g[][GRAPH_SIZE], int d[][GRAPH_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                d[i][j] = 0;
            }
            else if (g[i][j] != 0) {
                d[i][j] = g[i][j];
            }
            else {
                d[i][j] = INFINITY;
            }
        }
    }

    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (d[i][k] != INFINITY && d[k][j] != INFINITY && d[i][k] + d[k][j] < d[i][j]) {
                d[i][j] = d[i][k] + d[k][j];
            }
        }
    }
}
printf("Operation performed on graph.\n"); }

void printArray(int a[], int size) {
for (int i = 0; i < size; i++) {
printf("%d ", a[i]);
if ((i + 1) % 10 == 0) {
printf("\n");
}
}
}

void printMatrix(int g[][GRAPH_SIZE], int size) {
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
if (g[i][j] == INFINITY) {
printf("INF ");
}
else {
printf("%3d ", g[i][j]);
}
}
printf("\n");
}
}

void printOperationResult(int d[][GRAPH_SIZE], int size, int t) {
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
if (i != j && d[i][j] < t) {
printf("%c -> %c: %d\n", 'A' + i, 'A' + j, d[i][j]);
}
}
}
}

int main() {
int array[ARRAY_SIZE];
int graph[GRAPH_SIZE][GRAPH_SIZE] = {
{ 0, 10, 3, 0, 0, 5, 0, 17, 0, 22},
{10, 0, 5, 0, 2, 0, 13, 0, 0, 0},
{ 3, 5, 0, 2, 0, 4, 0, 21, 0, 11},
{ 0, 0, 2, 0, 7, 0, 6, 0, 0, 0},
{ 0, 2, 0, 7, 0, 6, 0, 0, 19, 0},
{ 5, 0, 4, 0, 6, 0, 9, 3, 0, 0},
{ 0, 13, 0, 6, 0, 9, 0, 4, 0, 0},
{17, 0, 21, 0, 0, 3, 4, 0, 8, 0},
{ 0, 0, 0, 0, 19, 0, 0, 8, 0, 5},
{22, 0, 11, 0, 0, 0, 0, 0, 5, 0}
};
int shortestPaths[GRAPH_SIZE][GRAPH_SIZE];
int result;
 srand(time(NULL));

clock_t start, end;
double cpu_time;

start = clock();

generateRandomNumbers(array, ARRAY_SIZE);
printf(" Array:\n");
printArray(array, ARRAY_SIZE);
 sortArray(array, 0, ARRAY_SIZE-1);
printf("\nSorted Array:\n");
printArray(array, ARRAY_SIZE);

result = performOperationOnArray(array, ARRAY_SIZE);
printf("\nAverage of Maximum Sequence: %d\n", result);

printf("\nGraph:\n");
printMatrix(graph, GRAPH_SIZE);

performOperationOnGraph(graph, shortestPaths, GRAPH_SIZE);
printf("\nShortest Paths:\n");
printMatrix(shortestPaths, GRAPH_SIZE);

printf("\nResult for %d:\n", result);
printOperationResult(shortestPaths, GRAPH_SIZE, result);

end = clock();
cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
printf("\nExecution Time: %f seconds\n", cpu_time);

return 0;
}
