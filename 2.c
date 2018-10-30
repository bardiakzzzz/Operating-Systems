#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t *callThd;
pthread_t aggregatorTh;
typedef struct _my_arg_t {
    int **a;
    int **b;
    int sizeofMatrix;
    int **result;
    int row;
    int currentRow;
    int n;
} my_arg;

my_arg arg;
pthread_mutex_t mutex_row;
pthread_cond_t cond_row;
int *resultRow;

void *calcResault(void *args) {
    int offset = (int) args;
    int start, end;
    start = offset * arg.sizeofMatrix;
    end = start + arg.sizeofMatrix;
    printf("Thread %d : Computing My Part \n", offset + 1);
    for (int i = start; i < end; ++i) {
        for (int j = 0; j < arg.n; ++j) {
            for (int k = 0; k < arg.n; ++k) {
                arg.result[i][j] += arg.a[i][k] * arg.b[k][j];
            }
        }
        printf("Thread %d: got one line ready, calling CalcEachRow \n", offset + 1);
        pthread_mutex_lock(&mutex_row);
        arg.row += 1;
        pthread_cond_signal(&cond_row);
        pthread_mutex_unlock(&mutex_row);
    }
    pthread_exit(0);
    return NULL;
}

void *CalcEachRow() {
    while (arg.currentRow != arg.row || arg.row != arg.n) {
        pthread_mutex_lock(&mutex_row);
        while (arg.currentRow == arg.row) {
            pthread_cond_wait(&cond_row, &mutex_row);
        }
        int sum = 0;
        pthread_mutex_unlock(&mutex_row);
        printf("AggregatorThraed: I’m awake\n");
        for (int i = 0; i < arg.n; ++i) {
            sum += arg.result[arg.currentRow][i];
        }
        resultRow[arg.currentRow] = sum;
        arg.currentRow++;
    }
    printf("AggregatorThraed: I’m done aggregating all rows. Joining! ");
    pthread_exit(0);
    return NULL;
}

void printMatrix(int n,int **a) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            printf("%d , ", a[i][j]);
        }
        printf("%d\n",a[i][n-1]);
    }
}

int main() {
    int count, n;
    printf("Enter matrix length: ");
    scanf("%d", &n);
    printf("Enter number of multiplier threads: ");
    scanf("%d", &count);
    callThd = (pthread_t *) malloc(count * sizeof(pthread_t));
    resultRow = (int *) malloc(n * sizeof(int));
    int **a = (int **) malloc(n * sizeof(int *));
    int **b = (int **) malloc(n * sizeof(int *));
    int **result = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        a[i] = (int *) malloc(n * sizeof(int));
        b[i] = (int *) malloc(n * sizeof(int));
        result[i] = (int *) malloc(n * sizeof(int));
    }
    printf("Main Thread : filling the matrices with random numbers.\n");
    srand((unsigned int) time(NULL));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            b[i][j] = rand() % 11;
            a[i][j] = rand() % 11;
            result[i][j] = 0;
        }
    }
    printf("Main Thread : Matrix1 = \n");
    printMatrix(n, a);
    printf("Main Thread : Matrix2 = \n");
    printMatrix(n, b);
    arg.sizeofMatrix = n / count;
    arg.a = a;
    arg.b = a;
    arg.result = result;
    arg.row = 0;
    arg.n = n;
    arg.currentRow = 0;
    pthread_mutex_init(&mutex_row, NULL);
    pthread_cond_init(&cond_row, NULL);
    printf("Main thread: Creating %d multiplier threads ", count);
    for (int i = 0; i < count; i++) {
        pthread_create(&callThd[i], NULL, calcResault, (void *) i);
    }
    printf("Main thread: Creating the Aggregator threads ");
    pthread_create(&aggregatorTh, NULL, CalcEachRow, NULL);
    for (int i = 0; i < count; i++) {
        pthread_join(callThd[i], NULL);
    }
    pthread_join(aggregatorTh, NULL);
    printf("Main thread: Aggregator Joined. The aggregate vector = \n<");
    for (int j = 0; j < n-1; ++j) {
        printf("%d , ", resultRow[j]);
    }
    printf("%d >", resultRow[n - 1]);
    free(a);
    free(b);
    free(result);
    pthread_mutex_destroy(&mutex_row);
    pthread_cond_destroy(&cond_row);
    return 0;
}