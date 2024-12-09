/******************
Name: Jonathan Djerassi    
ID: 303013098
Assignment: ex3
*******************/

#include <stdio.h>


#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2
#define stats   3
#define print   4
#define insights 5
#define deltas  6
#define done    7
#define VALID   1

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

void printMenu() {
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}

void clearInputBuffer() {
    while (getchar() != '\n');
}

void printBrand(int index) {
    if (index >= 0 && index < NUM_OF_BRANDS)
        printf("%s", brands[index]);
}

void printType(int index) {
    if (index >= 0 && index < NUM_OF_TYPES)
        printf("%s", types[index]);
}

int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] = {{{-1}}};
    int days = 0; // Track the number of days for which data has been entered
    int choice;

    while (VALID) {
        printMenu();
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 7) {
            printf("Invalid input\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        switch (choice) {
            case addOne: {
                printf("This option is not implemented in the current example.\n");
                break;
            }

            case addAll: {
                if (days >= DAYS_IN_YEAR) {
                    printf("No more days available to add data.\n");
                    break;
                }

                printf("No data for brands ");
                for (int b = 0; b < NUM_OF_BRANDS; b++) {
                    printf("%s ", brands[b]);
                }
                printf("\nPlease complete the data\n");

                for (int b = 0; b < NUM_OF_BRANDS; b++) {
                    int suv, sedan, coupe, gt;
                    printf("Enter sales data for brand %s (SUV, Sedan, Coupe, GT): ", brands[b]);
                    if (scanf("%d %d %d %d", &suv, &sedan, &coupe, &gt) != 4 || suv < 0 || sedan < 0 || coupe < 0 || gt < 0) {
                        printf("Invalid input! Please re-enter data for %s.\n", brands[b]);
                        clearInputBuffer();
                        b--; // Retry the current brand
                        continue;
                    }
                    cube[days][b][0] = suv;
                    cube[days][b][1] = sedan;
                    cube[days][b][2] = coupe;
                    cube[days][b][3] = gt;

                    printf("Sales for brand %s on day %d have been entered.\n", brands[b], days + 1);
                }
                days++;
                break;
            }

            case stats: {
                printf("What day would you like to analyze?\n");
                int day;
                if (scanf("%d", &day) != 1 || day < 1 || day > days) {
                    printf("Please enter a valid day.\n");
                    break;
                }
                int internalDay = day - 1;
                int totalSales = 0, bestBrandSales = 0, bestTypeSales = 0;
                int bestBrandIndex = -1, bestTypeIndex = -1;

                for (int b = 0; b < NUM_OF_BRANDS; b++) {
                    int brandSales = 0;
                    for (int t = 0; t < NUM_OF_TYPES; t++) {
                        brandSales += cube[internalDay][b][t];
                    }
                    if (brandSales > bestBrandSales) {
                        bestBrandSales = brandSales;
                        bestBrandIndex = b;
                    }
                    totalSales += brandSales;
                }

                for (int t = 0; t < NUM_OF_TYPES; t++) {
                    int typeSales = 0;
                    for (int b = 0; b < NUM_OF_BRANDS; b++) {
                        typeSales += cube[internalDay][b][t];
                    }
                    if (typeSales > bestTypeSales) {
                        bestTypeSales = typeSales;
                        bestTypeIndex = t;
                    }
                }

                printf("In day number %d:\n", day);
                printf("The sales total was %d\n", totalSales);
                printf("The best sold brand with %d sales was ", bestBrandSales);
                printBrand(bestBrandIndex);
                printf("\n");
                printf("The best sold type with %d sales was ", bestTypeSales);
                printType(bestTypeIndex);
                printf("\n");
                break;
            }

            case print: {
                printf("*****************************************\n");
                for (int b = 0; b < NUM_OF_BRANDS; b++) {
                    printf("Sales for %s:\n", brands[b]);
                    for (int d = 0; d < days; d++) {
                        printf("Day %d- SUV: %d Sedan: %d Coupe: %d GT: %d\n", d + 1,
                               cube[d][b][0], cube[d][b][1], cube[d][b][2], cube[d][b][3]);
                    }
                }
                printf("*****************************************\n");
                break;
            }

            case insights: {
                int totalBrandSales[NUM_OF_BRANDS] = {0};
                int totalTypeSales[NUM_OF_TYPES] = {0};
                int mostProfitableDay = 0, maxDailySales = 0;

                for (int d = 0; d < days; d++) {
                    int dailySales = 0;
                    for (int b = 0; b < NUM_OF_BRANDS; b++) {
                        for (int t = 0; t < NUM_OF_TYPES; t++) {
                            totalBrandSales[b] += cube[d][b][t];
                            totalTypeSales[t] += cube[d][b][t];
                            dailySales += cube[d][b][t];
                        }
                    }
                    if (dailySales > maxDailySales) {
                        maxDailySales = dailySales;
                        mostProfitableDay = d;
                    }
                }

                int bestBrandIndex = 0, bestTypeIndex = 0;
                for (int b = 1; b < NUM_OF_BRANDS; b++) {
                    if (totalBrandSales[b] > totalBrandSales[bestBrandIndex]) {
                        bestBrandIndex = b;
                    }
                }
                for (int t = 1; t < NUM_OF_TYPES; t++) {
                    if (totalTypeSales[t] > totalTypeSales[bestTypeIndex]) {
                        bestTypeIndex = t;
                    }
                }

                printf("The best-selling brand overall is ");
                printBrand(bestBrandIndex);
                printf(": %d sales$\n", totalBrandSales[bestBrandIndex]);
                printf("The best-selling type of car is ");
                printType(bestTypeIndex);
                printf(": %d sales$\n", totalTypeSales[bestTypeIndex]);
                printf("The most profitable day was day number %d: %d sales$\n", mostProfitableDay + 1, maxDailySales);
                break;
            }

            case deltas: {
                if (days < 2) {
                    printf("Not enough data to calculate deltas (at least 2 days required).\n");
                    break;
                }

                for (int b = 0; b < NUM_OF_BRANDS; b++) {
                    double totalDelta = 0;
                    int deltaCount = 0;

                    for (int d = 1; d < days; d++) {
                        int currentDaySales = 0, previousDaySales = 0;
                        for (int t = 0; t < NUM_OF_TYPES; t++) {
                            currentDaySales += cube[d][b][t];
                            previousDaySales += cube[d - 1][b][t];
                        }
                        totalDelta += (double)(currentDaySales - previousDaySales);
                        deltaCount++;
                    }

                    double avgDelta = deltaCount > 0 ? totalDelta / deltaCount : 0.0;
                    printf("Brand: %s, Average Delta: %.6f\n", brands[b], avgDelta);
                }
                break;
            }

            case done:
                return 0;
        }
    }
}
