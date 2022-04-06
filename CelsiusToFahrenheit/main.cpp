#include <stdio.h>
#include <vector>

int main()
{
    // Reads a list of temperature values in Celsius
    // from a file and converts them to Fahrenheit
    using std::vector;

    FILE *inputFile;
    fopen_s(&inputFile, "input.txt", "r");

    // The first value in the file indicates the number of values
    int numValues;
    fscanf_s(inputFile, "%d", &numValues);
    vector<float> celValues(numValues);

    // Read and convert the temperature values
    for (int i=0; i<numValues; i++)
    {
        fscanf_s(inputFile, "%f", &celValues[i]);
        float t_fahr = (celValues[i]*1.8f) + 32.0f;
        printf("%.2f Celsius = %.2f Fahrenheit!\n", celValues[i], t_fahr);
    }

    return 0;
}