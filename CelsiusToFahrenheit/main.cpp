#include <iostream>

using namespace std;

int main()
{
    double t_cel;
    cout << "Enter a temperature in Celsius: ";
    cin >> t_cel;

    double t_fahr = (t_cel*1.8) + 32;
    cout << t_cel << " Celsius = " << t_fahr << " Fahrenheit!" << endl;

    return 0;
}