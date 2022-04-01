#include <stdio.h>
#include <vector>

int main()
{
    // Reads a list of temperature values in Celsius
    // from a file and converts them to Fahrenheit
    using std::vector;

    FILE *inputFile;
    inputFile = fopen("input.txt", "r");

    int numValues;
    fscanf(inputFile, "%d", &numValues);
    vector<float> celValues(numValues);

    for (int i=0; i<numValues; i++)
    {
        fscanf(inputFile, "%f", &celValues[i]);
        float t_fahr = (celValues[i]*1.8) + 32;
        printf("%.2f Celsius = %.2f Fahrenheit!\n", celValues[i], t_fahr);
    }

    return 0;

}