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
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7
#define VALID 1

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1. Enter Daily Data For A Brand\n"
           "2. Populate A Day Of Sales For All Brands\n"
           "3. Provide Daily Stats\n"
           "4. Print All Data\n"
           "5. Provide Overall (simple) Insights\n"
           "6. Provide Average Delta Metrics\n"
           "7. Exit\n");
}

// Function to clean input buffer
void clearInputBuffer() {
    while (getchar() != '\n');  // clear until newline is encountered
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
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];

    // Initialize the cube with -1s (indicating no data)
    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                cube[i][j][k] = -1;  // Initialize to -1
            }
        }
    }

    int days = 0;  // Track number of days data is entered
    int choice;


    // Main menu loop
    while (VALID) {
        printMenu();
        // Ensure valid input for menu choice
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 7) {
            printf("Invalid input\n");
            clearInputBuffer();  // clear the input buffer after invalid input
            continue; // go back to the menu
        }

        // Clear input buffer after valid choice
        clearInputBuffer();

        switch(choice) {
            case addOne:
                // Enter daily data for a single brand
                {
                    int brand, suv, sedan, coupe, gt;
                    printf("Enter brand index (0-4) and 4 sales numbers (SUV, Sedan, Coupe, GT): ");
                    if (scanf("%d %d %d %d %d", &brand, &suv, &sedan, &coupe, &gt) != 5) {
                        printf("Invalid input! Please enter numeric values for brand index and sales data.\n");
                        clearInputBuffer(); // clear the input buffer on invalid input
                        break;
                    }

                    if (brand < 0 || brand >= NUM_OF_BRANDS) {
                        printf("This brand is not valid\n");
                    } else {
                        // Find the next available day to enter data
                        int dayFound = 0;
                        for (int i = 0; i < DAYS_IN_YEAR; i++) {
                            if (cube[i][brand][0] == -1) {  // Check if the day is empty
                                cube[i][brand][0] = suv;
                                cube[i][brand][1] = sedan;
                                cube[i][brand][2] = coupe;
                                cube[i][brand][3] = gt;
                                printf("Data for brand %s on day %d has been entered.\n", brands[brand], i);
                                dayFound = 1;
                                days++;  // Increment day count
                                break;
                            }
                        }
                        if (!dayFound)
                            printf("No available days to add data.\n");
                    }
                }
                break;

            case addAll:
                // Populate a day of sales for all brands
                {
                    int suv, sedan, coupe, gt;
                    printf("No data for brands Toyoga HyunNight Mazduh FolksVegan Key-Yuh\n");
                printf("Please complete the data\n");
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                        printf("Enter sales data for brand %s (SUV, Sedan, Coupe, GT): ", brands[i]);
                        if (scanf("%d %d %d %d", &suv, &sedan, &coupe, &gt) != 4) {
                            printf("Invalid input! Please enter numeric values for sales data.\n");
                            clearInputBuffer(); // clear the input buffer on invalid input
                            break;
                        }
                        int dayFound = 0;
                        for (int j = 0; j < DAYS_IN_YEAR; j++) {
                            if (cube[j][i][0] == -1) {  // Check if day is empty for this brand
                                cube[j][i][0] = suv;
                                cube[j][i][1] = sedan;
                                cube[j][i][2] = coupe;
                                cube[j][i][3] = gt;
                                printf("Sales for brand %s on day %d have been entered.\n", brands[i], j);

                                break;
                            }
                        }
                    }
                    days++;  // Increment days count
                }
                break;

           case stats:
    // Provide daily stats
    {
        int day;
        // Ensure valid day input (from 1 to 365)
        int validDay = 0;  // Flag to check if the day entered is valid
        while (!validDay) {
            printf("What day would you like to analyze? (1-%d): ", DAYS_IN_YEAR);  // Prompt user with 1 to 365
            if (scanf("%d", &day) != 1 || day < 1 || day > DAYS_IN_YEAR) {
                printf("Please enter a valid day between 1 and %d.\n", DAYS_IN_YEAR);
                clearInputBuffer();  // clear input buffer if invalid input
            } else {
                validDay = 1;  // Valid day entered, exit the loop
            }
        }

        // Convert user input day (1-365) to internal index (0-364)
        int internalDay = day - 1;  // Convert 1-based input to 0-based index

        int totalSales = 0;
        int mostSoldBrandIndex = 0;
        int mostSoldTypeIndex = 0;
        int maxBrandSales = 0;
        int maxTypeSales = 0;

        // Calculate total sales and find the most sold brand/type for the day
        for (int i = 0; i < NUM_OF_BRANDS; i++) {
            int brandSales = 0;
            for (int j = 0; j < NUM_OF_TYPES; j++) {
                brandSales += cube[internalDay][i][j];  // Sum sales for each brand on the chosen day
            }
            totalSales += brandSales;  // Add brand sales to total sales
            if (brandSales > maxBrandSales) {
                maxBrandSales = brandSales;
                mostSoldBrandIndex = i;  // Update most sold brand index
            }
        }

        for (int j = 0; j < NUM_OF_TYPES; j++) {
            int typeSales = 0;
            for (int i = 0; i < NUM_OF_BRANDS; i++) {
                typeSales += cube[internalDay][i][j];  // Sum sales for each car type on the chosen day
            }
            if (typeSales > maxTypeSales) {
                maxTypeSales = typeSales;
                mostSoldTypeIndex = j;  // Update most sold type index
            }
        }

        // Print the results
        printf("In day %d:\n", day);  // Print the day as entered by the user (1 to 365)
        printf("The sales total was %d\n", totalSales);
        printf("The best sold brand with %d sales was ", maxBrandSales);
        printBrand(mostSoldBrandIndex);  // Call function to print the brand name
        printf("\n");
        printf("The best sold type with %d sales was ", maxTypeSales);
        printType(mostSoldTypeIndex);  // Call function to print the car type name
        printf("\n");
    }
    break;

            case print:
                // Print all data
            {
                for (int i = 0; i < DAYS_IN_YEAR; i++) {
                    printf("*****************************************\n");
                    // Display days as 1 to 365 (i+1 instead of i)
                    printf("Sales data for day %d:\n", i + 1);  // This prints days from 1 to 365
                    for (int j = 0; j < NUM_OF_BRANDS; j++) {
                        printf("Sales for %s: ", brands[j]);
                        if (cube[i][j][0] == -1) {
                            printf("No sales data for this brand on day %d\n", i + 1);  // Printing adjusted day
                        } else {
                            printf("SUV: %d Sedan: %d Coupe: %d GT: %d\n", cube[i][j][0], cube[i][j][1], cube[i][j][2], cube[i][j][3]);
                        }
                    }
                    printf("*****************************************\n");
                }
            }
            break;

case insights:
    // Provide overall (simple) insights
    {
        int bestBrandIndex = -1, bestTypeIndex = -1;
        int bestBrandSales = 0, bestTypeSales = 0;
        int mostProfitableDay = -1, maxSalesOnDay = 0;

        // Calculate the best-selling brand
        for (int i = 0; i < NUM_OF_BRANDS; i++) {
            int brandSales = 0;
            for (int j = 0; j < DAYS_IN_YEAR; j++) {
                for (int k = 0; k < NUM_OF_TYPES; k++) {
                    if (cube[j][i][k] != -1)  // Check if sales data is valid for this day
                        brandSales += cube[j][i][k];  // Sum sales for the brand across all types
                }
            }
            if (brandSales > bestBrandSales) {
                bestBrandSales = brandSales;
                bestBrandIndex = i;  // Update best-selling brand index
            }
        }

        // Calculate the best-selling type
        int typeSales[NUM_OF_TYPES] = {0};  // Array to store total sales for each type
        for (int i = 0; i < NUM_OF_TYPES; i++) {
            for (int j = 0; j < DAYS_IN_YEAR; j++) {
                for (int k = 0; k < NUM_OF_BRANDS; k++) {
                    if (cube[j][k][i] != -1)  // Check if sales data is valid for this day
                        typeSales[i] += cube[j][k][i];  // Sum sales for the car type across all brands
                }
            }
            if (typeSales[i] > bestTypeSales) {
                bestTypeSales = typeSales[i];
                bestTypeIndex = i;  // Update best-selling type index
            }
        }

        // Calculate the most profitable day
        for (int i = 0; i < DAYS_IN_YEAR; i++) {
            int dailySales = 0;
            for (int j = 0; j < NUM_OF_BRANDS; j++) {
                for (int k = 0; k < NUM_OF_TYPES; k++) {
                    if (cube[i][j][k] != -1)  // Check if sales data is valid for this day
                        dailySales += cube[i][j][k];  // Sum sales for all brands and types on this day
                }
            }
            if (dailySales > maxSalesOnDay) {
                maxSalesOnDay = dailySales;
                mostProfitableDay = i;  // Update most profitable day index
            }
        }

        // Print the results
        printf("Overall Insights:\n");
        printf("The best-selling brand overall is ");
        printBrand(bestBrandIndex);  // Print the best-selling brand
        printf(": %d sales$\n", bestBrandSales);
        printf("The best-selling type of car is ");
        printType(bestTypeIndex);  // Print the best-selling type of car
        printf(": %d sales$\n", bestTypeSales);
        printf("The most profitable day was day %d: %d sales$\n", mostProfitableDay + 1, maxSalesOnDay);
    }
    break;
            case deltas:
                // Provide average delta sales metrics
            {
                if (days <= 1) {
                    printf("Not enough data to calculate deltas (at least 2 days required).\n");
                    break;
                }

                // Initialize arrays to store daily sales totals for each brand
                int dailySales[NUM_OF_BRANDS][DAYS_IN_YEAR] = {0};

                // Calculate total sales for each brand on each day
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    for (int j = 0; j < DAYS_IN_YEAR; j++) {
                        if (cube[j][i][0] != -1) {  // Check if there's valid data for the brand on this day
                            for (int k = 0; k < NUM_OF_TYPES; k++) {
                                dailySales[i][j] += cube[j][i][k];  // Sum up the sales for each type
                            }
                        }
                    }
                }

                // Calculate and print the average delta for each brand
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    double totalDelta = 0;  // Accumulate the deltas for this brand
                    int deltaCount = 0;  // Count the number of valid deltas

                    for (int j = 1; j < days; j++) {  // Start from day 1 to day (n-1)
                        if (dailySales[i][j-1] != 0 && dailySales[i][j] != 0) {  // Only calculate delta if both days have sales data
                            double delta = dailySales[i][j] - dailySales[i][j-1];
                            totalDelta += delta;
                            deltaCount++;
                        }
                    }

                    if (deltaCount > 0) {
                        double avgDelta = totalDelta / deltaCount;
                        printf("Brand: %s, Average Delta: %.2f$\n", brands[i], avgDelta);
                    } else {
                        printf("Brand: %s, Average Delta: N/A (not enough data)\n", brands[i]);
                    }
                }
            }
            break;
            case done:
                // Exit program
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid option, please try again.\n");
                break;
        }
    }

}
