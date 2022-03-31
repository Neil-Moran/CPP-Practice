#include <stdio.h>

int main()
{
    FILE *inputFile;
    inputFile = fopen("input.txt", "r");

    const int numValues = 6;
    float celValues[numValues];

    for (int i=0; i<numValues; i++)
    {
        fscanf(inputFile, "%f", &celValues[i]);
        float t_fahr = (celValues[i]*1.8) + 32;
        printf("%.2f Celsius = %.2f Fahrenheit!\n", celValues[i], t_fahr);
    }

    return 0;

}