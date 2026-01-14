#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float series(int n, float r[]){ // function for calculating equivalent resistor in series
    float Rs = 0;

    printf("Enter the resistor values (in ohm): ");

    for (int i = 0; i < n; i++){
        scanf("%f", &r[i]);
        Rs += r[i];
    }

    return Rs;
}

float parallel(int n, float r[]){ // function for calculating equivalent resistor in parallel
    printf("Enter the resistor values (in ohm): ");
    scanf("%f", &r[0]);
    float Rp = r[0];

    for (int i = 1; i < n; i++){
        scanf("%f", &r[i]);
        Rp = (Rp*r[i]) / (Rp+r[i]);
    }

    return Rp;
}

int power(int x, int n){ // calculates power of 10 for resistor multiplier calculation
    int pwr = 1;

    for (int i = 0; i < n; i++){
        pwr *= x;
    }

    return pwr;
}

void resistor(){  // function to find the resistance of a resistor based on it's color
    char color[12][10] = {"Black", "Brown", "Red", "Orange", "Yellow",
                            "Green", "Blue", "Violet", "Gray", "White",
                                "Gold", "Silver"};

    char color1[10], color2[10], multiplier[10];
    double resistance;

    printf("===== Resistor Value Determiner =====\n");

    printf("Band color list: ");
    for(int i = 0; i < 12; i++){
        printf("%s", color[i]);
        if(i<11){printf(", ");}
    }
    printf("\n");

    printf("Enter the color of the first band: ");
    scanf("%s", &color1);

    printf("Enter the color of the second band: ");
    scanf("%s", &color2);

    printf("Enter the color of the multiplier band: ");
    scanf("%s", &multiplier);

    int i, j, k;

    for(i = 0; i<=9; i++){
        int first = strcmp(color1, color[i]);
        if (first == 0){break;}
    }

    for (j = 0; j<=9; j++){
        int second = strcmp(color2, color[j]);
        if (second == 0){break;}
    }

    for (k = 0; k<12; k++){
        int mult = strcmp(multiplier, color[k]);
        if (mult == 0){break;}
    }

    if (k <= 9){
        resistance = ((10 * i) + j) * power(10, k);
    } else if(k == 10){
        resistance = ((10 * i) + j) * 0.1;
    } else {
        resistance = ((10 * i) + j) * 0.01;
    }

    printf("Your resistance value is: %g ohm\n\n", resistance);
}

void eqResistance (){ //calculated equivalent resistance using other two functions - series and parallel function
    printf("===== Equivalent Resistance Calculator =====\n");

    char type;
    int n;
    float eqRes = 0;

    printf("Enter the values by each segment of series or parallel for easier calculation: \n");

    char go = 'y';

    while (go == 'y'){ //using series and parallel function repeatedly
        printf("\nSegment type - Series(s) or Parallel(p): ");
        scanf(" %c", &type);

        if (type == 's'){
            printf("\nEnter the number of resistor in series: ");
            scanf("%d", &n);

            float Rseries[n];

            printf("\nEquivalent resistance in series: %g\n", series(n, Rseries));
        } else {
            printf("\nEnter the number of resistor in parallel: ");
            scanf("%d", &n);

            float Rparallel[n];

            printf("\nEquivalent resistance in series: %g\n", parallel(n, Rparallel));
        }

        printf("Continue? Yes(y) or No(n):");
        scanf(" %c", &go);
    }
    printf("\n");
}

void voltageDivide(){ //finds output voltage or resistance for expected output voltage
    printf("===== Voltage Divider =====\n");

    // Circuit diagram to ease the user to understand the formula and the variables
    printf("\nCircuit Diagram: Vin___\n");
    printf("                        |\n");
    printf("                     R1 ! 1\n");
    printf("                        |\n");
    printf("                        \\\n");
    printf("                        \/\n");
    printf("                        \\\n");
    printf("                        \/   2\n");
    printf("                        \\<--.-- Vout\n");
    printf("                        \/\n");
    printf("                        \\\n");
    printf("                        \/\n");
    printf("                        \\\n");
    printf("                        \/\n");
    printf("                        |\n");
    printf("                     R2 ! 3\n");
    printf("                      __|__\n");
    printf("                       ___\n");
    printf("                        _ \n");

    printf("\nChoose one option:\na. Output voltage determiner\nb. Resistance calculation for desired output\n");

    char option;

    printf("\nOption a or b: ");
    scanf(" %c", &option);

    float Vin, R1, R2, Vout;

    if (option == 'a'){
        printf("\nEnter the input voltage value (Vin): ");
        scanf("%f", &Vin);

        printf("Enter first resistor value (R1): ");
        scanf("%f", &R1);

        printf("Enter second resistor value (R2): ");
        scanf("%f", &R2);

        Vout = (Vin * R2) / (R1 + R2);

        printf("\nOutput voltage: %g\n\n", Vout);
    } else if (option == 'b'){
        printf("\nEnter the input voltage value (Vin): ");
        scanf("%f", &Vin);

        printf("Enter first resistor value (R1): ");
        scanf("%f", &R1);

        printf("Enter the expected output voltage (Vout): ");
        scanf("%f", &Vout);

        while (Vout > Vin){
            printf("Output voltage must be less than input voltage: \n");
            printf("Output voltage (Vout): ");
            scanf("%f", &Vout);
        }

        R2 = (R1 * Vout) / (Vin - Vout);
        printf("\nResistor value based on your given voltage output: %g\n\n", R2);
    }
}

void main()
{
    int choice;
    while (1){ // program will run before user chooses to exit
        printf(" _____________________________\n");
        printf("|       EEE Pocket Tool       |\n");
        printf("|_____________________________|\n\n");
        printf("1. Series Circuit Solver\n");
        printf("2. Parallel Circuit Solver\n");
        printf("3. Resistor Value Determiner\n");
        printf("4. Equivalent Resistance Calculator\n");
        printf("5. Voltage Divider Calculator\n");
        printf("0. Exit\n");


        printf("Enter your choice: \n");
        scanf("%d", &choice);

        switch (choice){
            case 1:{
                float Vs, Rs;
                int n;

                printf("===== Series Circuit Solver =====\n");

                printf("Enter the value of voltage source (in V): ");
                scanf("%f", &Vs);

                printf("Enter the number of resistor in series: ");
                scanf("%d", &n);

                float r[n];

                Rs = series(n, r);

                printf("\nEquivalent resistance = %g ohm\n", Rs);

                printf("\nCurrent flowing though the circuit = %g A\n", (Vs/Rs));

                printf("\nVoltage drop through each resistor:\n\n");

                for (int i = 0; i < n; i++){
                    printf("R%d: %g ohm resistor = %g V\n", (i+1), r[i], ((Vs/Rs)*r[i]));
                }
                printf("\n");
            }
                break;

            case 2:{
                float Vs, Rp;
                int n;

                printf("===== Parallel Circuit Solver =====\n");

                printf("Enter the value of voltage source (in V): ");
                scanf("%f", &Vs);

                printf("Enter the number of resistor in parallel: ");
                scanf("%d", &n);

                float r[n];

                Rp = parallel(n, r);

                printf("\nEquivalent resistance = %g ohm\n", Rp);

                printf("\nTotal Current = %g A\n", (Vs/Rp));

                printf("\nCurrent through each resistor:\n\n");

                for (int i = 0; i < n; i++){
                    printf("R%d: %g ohm resistor = %g A\n", (i+1), r[i], (Vs/r[i]));
                }
                printf("\n");
            }
                break;
            case 3:
                resistor();
                break;
            case 4:
                eqResistance();
                break;
            case 5:
                voltageDivide();
                break;
            case 0:
                printf("Shutting down...");
                return 0;
            default:
                printf("Please enter a valid choice from the list.\n");
        }
    }
}

