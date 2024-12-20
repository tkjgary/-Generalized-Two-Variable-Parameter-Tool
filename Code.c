#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Function prototypes */
float mean(float **x, int rows, int cols);
float sd(float **x, int rows, int cols);
void paired_t_test(float **measurements, float **calc_measurements, int rows, int cols);
void check_data_consistency(float **measurements, float **calc_measurements, int rows, int cols, float tolerance_mean, float tolerance_sd);

int main() {
    FILE *fp2;
    fp2 = fopen("result.txt", "w");

    /* Input data */
    FILE *fp1;
    fp1 = fopen("input.txt", "r");
    if (!fp1) {
        printf("Error: Cannot open file 'input.txt'\n");
        return 1;
    }

    int rows, cols;
    printf("Enter the number of rows (Var1 values): ");
    scanf("%d", &rows);
    printf("Enter the number of columns (Var2 values): ");
    scanf("%d", &cols);

    float *var2 = malloc(cols * sizeof(float));
    float *var1 = malloc(rows * sizeof(float));
    float **measurements = malloc(rows * sizeof(float *));
    float **calc_measurements = malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++) {
        measurements[i] = malloc(cols * sizeof(float));
        calc_measurements[i] = malloc(cols * sizeof(float));
    }

    printf("The data from the measurements\n");
    fprintf(fp2, "The data from the measurements\n");

    char text[10];
    fscanf(fp1, " %s", text);
    printf(" %s  ", text);
    fprintf(fp2, " %s  ", text);

    for (int c = 0; c < cols; ++c) {
        fscanf(fp1, "%f", &var2[c]);
        printf(" %5.2f ", var2[c]);
        fprintf(fp2, " %5.2f ", var2[c]);
    }

    for (int r = 0; r < rows; ++r) {
        fscanf(fp1, "%f", &var1[r]);
        printf("\n");
        fprintf(fp2, "\n");
        printf("%5.1f ", var1[r]);
        fprintf(fp2, "%5.1f ", var1[r]);

        for (int c = 0; c < cols; ++c) {
            fscanf(fp1, "%f", &measurements[r][c]);
            printf(" %5.2f ", measurements[r][c]);
            fprintf(fp2, " %5.2f ", measurements[r][c]);
        }
    }

    printf("\n\n\n");
    fprintf(fp2, "\n\n\n");

    /* User-defined equation */
    float coef1, coef2, intercept;
    printf("Enter the equation in the form: intercept coef1*Var1 + coef2*Var2\n");
    printf("Example: 73.39 0.0503 0.1672\n");
    printf("Enter intercept, coef1, and coef2: ");
    scanf("%f %f %f", &intercept, &coef1, &coef2);

    /* Approximated values using user-defined equation */
    printf("The approximated values of measurements\n");
    fprintf(fp2, "The approximated values of measurements\n");

    printf(" Var1\\Var2  ");
    fprintf(fp2, " Var1\\Var2  ");

    for (int c = 0; c < cols; ++c) {
        printf(" %5.2f ", var2[c]);
        fprintf(fp2, " %5.2f ", var2[c]);
    }

    for (int r = 0; r < rows; ++r) {
        printf("\n%.1f ", var1[r]);
        fprintf(fp2, "\n%.1f ", var1[r]);
        for (int c = 0; c < cols; ++c) {
            calc_measurements[r][c] = intercept + coef1 * var1[r] + coef2 * var2[c];
            printf(" %5.2f ", calc_measurements[r][c]);
            fprintf(fp2, " %5.2f ", calc_measurements[r][c]);
        }
    }

    printf("\n\n\n");
    fprintf(fp2, "\n\n\n");

    /* Ask for user-defined tolerance values */
    float tolerance_mean, tolerance_sd;
    printf("Enter the tolerance percentage for the mean (e.g., 5 for 5%%): ");
    scanf("%f", &tolerance_mean);
    printf("Enter the threshold percentage for standard deviation (e.g., 10 for 10%%): ");
    scanf("%f", &tolerance_sd);

    /* Check data consistency based on mean and standard deviation */
    check_data_consistency(measurements, calc_measurements, rows, cols, tolerance_mean, tolerance_sd);

    /* Free dynamically allocated memory */
    free(var1);
    free(var2);
    for (int i = 0; i < rows; i++) {
        free(measurements[i]);
        free(calc_measurements[i]);
    }
    free(measurements);
    free(calc_measurements);

    fclose(fp1);
    fclose(fp2);
    return 0;
}

/* Function to calculate the mean of a 2D array */
float mean(float **x, int rows, int cols) {
    float sum = 0.0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            sum += x[r][c];
        }
    }
    return sum / (rows * cols);
}

/* Function to calculate the standard deviation of a 2D array */
float sd(float **x, int rows, int cols) {
    float m = mean(x, rows, cols);
    float sqr_sum = 0.0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            sqr_sum += pow(x[r][c] - m, 2);
        }
    }
    return sqrt(sqr_sum / (rows * cols));
}

/* Function to check if the data is consistent with the expected values */
void check_data_consistency(float **measurements, float **calc_measurements, int rows, int cols, float tolerance_mean, float tolerance_sd) {
    // Calculate mean and standard deviation of both measurements and calculated values
    float mean_measurements = mean(measurements, rows, cols);
    float mean_calc_measurements = mean(calc_measurements, rows, cols);
    float sd_measurements = sd(measurements, rows, cols);
    float sd_calc_measurements = sd(calc_measurements, rows, cols);

    // Check if the mean difference is within tolerance
    float mean_diff_percentage = fabs(mean_measurements - mean_calc_measurements) / mean_calc_measurements * 100;
    if (mean_diff_percentage <= tolerance_mean) {
        printf("The mean difference is within the acceptable tolerance (%.2f%%).\n", mean_diff_percentage);
    } else {
        printf("The mean difference exceeds the acceptable tolerance (%.2f%%).\n", mean_diff_percentage);
    }

    // Check if the standard deviation is within the threshold
    float sd_diff_percentage = fabs(sd_measurements - sd_calc_measurements) / sd_calc_measurements * 100;
    if (sd_diff_percentage <= tolerance_sd) {
        printf("The standard deviation difference is within the acceptable threshold (%.2f%%).\n", sd_diff_percentage);
    } else {
        printf("The standard deviation difference exceeds the acceptable threshold (%.2f%%).\n", sd_diff_percentage);
    }
}
