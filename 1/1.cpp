* @brief Точка входа в программу
 * @return 0 - если программа выполнена корректно, иначе - 1
 */
int main()
{
    const double x = 0.61;
    const double y = 3.4;
    const double z = 16.5;

    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl;
    cout << "a = " << calculateA(x, y, z) << endl;
    cout << "b = " << calculateB(x, y, z) << endl;

    return 0;
}

double calculateA(const double x, const double y, const double z)
{
    return pow(x, 3) * pow(tan(pow(x + y, 2)), 2) + z / sqrt(x + y);
}

double calculateB(const double x, const double y, const double z)
{
    return (y * pow(x, 2) - z) / (exp(z * x) - 1);
}
