#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

int ratingsRows = 0;
int ratingsCols = 0;

void load_csv (char *path, int  **ratings);
void factorize();
int getRandomNumber();
void initRandomMatrix(int **matrix, int rows, int cols);
void als(int **ratings, int maxUserId, int maxMovieId, int rank, int threadNumber);
void transpose(int **matrix, int rows, int cols, int **transpose);
void sumVectors(int *v1, int *v2,  int size, int **result);
int multiplyRowByCol(int *row, int *col, int size) ;
void escalarByVector(float escalar, int *vector, int size, int **result);
void getCol(int **matrix, int rows, int nCol, int **result);
void setCol(int **matrix, int rows, int nCol, int *newCol, int **result);
void multiplyMatrixes(int **m1, int **m2, int colsRows, int rowsM1, int colsM2, int **result);
void subsctracMatrixes(int **m1, int **m2, int rows, int cols, int **result);
void square(int **matrix, int rows, int cols, int **result);
float sumElements(int **matrix, int rows, int cols);

int main(int argc, char ** argv) {
    time_t t;

	// initializes random number generator
	srand((unsigned) time(&t));

    factorize();
    return 0;
}

void load_csv (char *path, int  **ratings) {

    int ** toReturn;

    FILE* data = fopen(path, "r");
    char line[1024];
    int r=0, c;
    toReturn = (int **)calloc(29, sizeof(int *));
    while (fgets(line, 1024, data) != NULL) {
        toReturn[r] = (int *)calloc(3, sizeof(int *));
        c = 0;
        char * number = strtok(line, ",");
        while (number != NULL) {
            toReturn[r][c] = atoi(number);
            c++;
            number = strtok(NULL, ",");
        }
        r++;

    }

    ratingsRows = r;
    ratingsCols = c;
    *ratings = toReturn;

}

void factorize() {
    int **ratings;
    load_csv("data.txt", &ratings);
    int maxUserId = 7;
    int maxMovieId = 9;
    int cols = maxMovieId, rows = maxUserId;

    for (int i = 4; i < 5; ++i) {
        printf("Thread number: %d\n", i);
        als(ratings, maxUserId, maxMovieId, 4, 1);
    }

}

int getRandomNumber() {
	return rand() % 1000 / 100;
}


void initRandomMatrix(int **matrix, int rows, int cols) {
    int **m = (int **)calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++) {
        m[i] = (int *)calloc(cols, sizeof(int *));
		for (int j = 0; j < cols; j++) {
			m[i][j] = getRandomNumber();
		}
	}
    *matrix = m;
}

void als(int **ratings, int maxUserId, int maxMovieId, int rank, int threadNumber) {

    int **U, **M;
    initRandomMatrix(&U, maxUserId, rank);
    initRandomMatrix(&M, rank, maxMovieId);

    // for (int i = 0; i < maxUserId; i++) {
    //     for (int j = 0; j < rank; j++)
    //     {
    //         printf("U[%d][%d]: %d\n", i, j, U[i][j]);
    //     }
        
    // }
    
    // for (int i = 0; i < rank; i++) {
    //     for (int j = 0; j < maxMovieId; j++)
    //     {
    //         printf("M[%d][%d]: %d\n", i, j, M[i][j]);
    //     }
        
    // }
    

    int **A = (int **)calloc(maxUserId, sizeof(int *));
    int **W = (int **)calloc(maxUserId, sizeof(int *));
    
    for (int i = 0; i < maxUserId; i++) {
        A[i] = (int *)calloc(maxMovieId, sizeof(int *));
        W[i] = (int *)calloc(maxMovieId, sizeof(int *));
    }
    

    for (int i = 0; i < ratingsRows; i++) {
        int ui = ratings[i][0] - 1; // userId index
        int mi = ratings[i][1] - 1; // movieId index
        int ri = ratings[i][2]; // rating
        A[ui][mi] = ri;
        W[ui][mi] = 1;
    }
    
    float Eta = 0.03;
    float eta = Eta;
    int maxIteration = 2000;

    int ui, mi, ri;
    float error;
    int *tempU;
    float *errorHistory = (float *)calloc(maxIteration, sizeof(float *));
    int errorHistorySize = 0;
    float start = omp_get_wtime();
     for (int iteration = 0; iteration < maxIteration; ++iteration) {

        #pragma omp parallel for num_threads(threadNumber) schedule(static) private(ui, mi, ri, error, tempU)
        for (int i = 0; i < ratingsRows; ++i) {
            int ui = ratings[i][0] - 1; // userId index
            int mi = ratings[i][1] - 1; // movieId index
            int ri = ratings[i][2]; // rating
            
            tempU = (int *)calloc(rank, sizeof(int *));
            int *MCol;
            getCol(M, rank, mi, &MCol);
            error = ri - multiplyRowByCol(U[ui], MCol, rank);
            
            escalarByVector(eta*error, MCol, rank, &tempU);
            sumVectors(U[ui], tempU, rank, &tempU);

            int *MColTemp;
            escalarByVector(eta*error, U[ui], rank, &MColTemp);
            sumVectors(MColTemp, MCol, rank, &MColTemp);

            setCol(M, rank, mi, MColTemp, &M);
            U[ui] = tempU;
        }

        if (iteration % ((int) maxIteration /15) == 0) {
            eta*=0.8;
            
            int **mTemp;
            multiplyMatrixes(U, M, rank, maxUserId, maxMovieId, &mTemp);
            subsctracMatrixes(A, mTemp, maxUserId, maxMovieId, &mTemp);
            square(mTemp, maxUserId, maxMovieId, &mTemp);
            errorHistory[errorHistorySize] = sumElements(mTemp, maxUserId, maxMovieId);
            errorHistorySize++;
        }
    }

    double elapse = omp_get_wtime() - start;
    printf("elapse: %f\n", elapse);
    printf("errors:\n");
    for (int j = 0; j < errorHistorySize; j++) {
        printf("error: %.2f\n", errorHistory[j]);
    }
    

}

float sumElements(int **matrix, int rows, int cols) {
    float sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            
            sum += matrix[i][j];
        }
    }
    return sum;
}

void square(int **matrix, int rows, int cols, int **result) {
    int **r = (int **)calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++) {
        r[i] = (int *)calloc(cols, sizeof(int *));
        for (int j = 0; j < cols; j++) {
            r[i][j] = matrix[i][j] * matrix[i][j];
        }
    }
    *result = r;
}

void subsctracMatrixes(int **m1, int **m2, int rows, int cols, int **result) {
    int **r = (int **)calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++) {
        r[i] = (int *)calloc(cols, sizeof(int *));
        for (int j = 0; j < cols; j++) {
            r[i][j] = m1[i][j] - m2[i][j];
        }
    }
    *result = r;
}

void getCol(int **matrix, int rows, int nCol, int **result) {
    int *r = (int *)calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++) {
        // printf("%d\n", matrix[i][nCol]);
        r[i] = matrix[i][nCol];
        // printf("%d\n", r[i]);
    }
    *result = r;
}

void setCol(int **matrix, int rows, int nCol, int *newCol, int **result) {
    for (int i = 0; i < rows; i++) {
        // printf("%d\n", matrix[i][nCol]);
        matrix[i][nCol] = newCol[i];
        // printf("%d\n", matrix[i][nCol]);
    }
    *result = matrix;
    
}

void multiplyMatrixes(int **m1, int **m2, int colsRows, int rowsM1, int colsM2, int **result) {
    int **r = (int **)calloc(rowsM1, sizeof(int *));
    for (int i = 0; i < rowsM1; i++) {
        r[i] = (int *)calloc(colsM2, sizeof(int *));
        for (int j = 0; j < colsM2; j++) {
            int sum = 0;
            for (int k = 0; k < colsRows; k++){
                sum+= m1[i][k] * m2[k][j];
            }
            r[i][j] = sum;
        }
    }
    *result = r;
}


void transpose(int **matrix, int rows, int cols, int **transpose) {
    int **mt = (int **)calloc(cols, sizeof(int *));
    for (int i = 0; i < cols; i++) {
        mt[i] = (int *)calloc(rows, sizeof(int *));
        for (int j = 0; j < rows; j++) {
            mt[i][j] = matrix[j][i];
        }
        
    }

    *transpose = mt;
    
}

void sumVectors(int *v1, int *v2,  int size, int **result) {
    int *r = (int *)calloc(size, sizeof(int *));
    for (int i = 0; i < size; i++) {
        r[i] = v1[i] + v2[i];
    }
    *result = r;
}

void escalarByVector(float escalar, int *vector, int size, int **result) {
    int *r = (int *)calloc(size, sizeof(int *));
    for (int i = 0; i < size; i++) {
        r[i] = vector[i] * escalar;
    }
    *result = r;

}

int multiplyRowByCol(int *row, int *col, int size) {
    int toReturn = 0;
    for (int i = 0; i < size; i++) {
        toReturn += row[i] * col[i];
    }
    return toReturn;
}