#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>

using namespace std;

void gaussJordan(vector<vector<double>> &augmented, int n)
{
    for (int i = 0; i < n; ++i)
    {
        // Find the row with the max pivot in column i
        int maxRow = i;
        for (int k = i + 1; k < n; ++k)
        {
            if (fabs(augmented[k][i]) > fabs(augmented[maxRow][i]))
            {
                maxRow = k;
            }
        }

        if (fabs(augmented[maxRow][i]) < 1e-12)
        {
            throw runtime_error("Matrix is singular or nearly singular.");
        }

        // Swap rows if needed
        if (maxRow != i)
        {
            swap(augmented[i], augmented[maxRow]);
        }

        // Normalize pivot row
        double pivot = augmented[i][i];
        for (int j = 0; j < 2 * n + 1; ++j)
        {
            augmented[i][j] /= pivot;
        }

        // Eliminate other rows
        for (int k = 0; k < n; ++k)
        {
            if (k != i)
            {
                double factor = augmented[k][i];
                for (int j = 0; j < 2 * n + 1; ++j)
                {
                    augmented[k][j] -= factor * augmented[i][j];
                }
            }
        }
    }
}

int main()
{
    int n;
    cout << "Enter the size of the matrix (n): ";
    cin >> n;

    if (n <= 0)
    {
        cerr << "Matrix size must be positive." << endl;
        return 1;
    }

    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);

    cout << "\nEnter the " << n << "x" << n << " matrix A row by row:" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < n; ++j)
        {
            cin >> A[i][j];
        }
    }

    cout << "\nEnter the RHS vector b (" << n << " values): ";
    for (int i = 0; i < n; ++i)
    {
        cin >> b[i];
    }

    // Build augmented matrix: [A | I | b]
    vector<vector<double>> augmented(n, vector<double>(2 * n + 1));
    for (int i = 0; i < n; ++i)
    {
        // Copy A
        for (int j = 0; j < n; ++j)
        {
            augmented[i][j] = A[i][j];
        }

        // Identity matrix
        for (int j = 0; j < n; ++j)
        {
            augmented[i][n + j] = (i == j) ? 1.0 : 0.0;
        }

        // Append b
        augmented[i][2 * n] = b[i];
    }

    try
    {
        gaussJordan(augmented, n);
    }
    catch (runtime_error &e)
    {
        cout << "Error: " << e.what() << endl;
        return 1;
    }

    // Output solution vector x
    cout << "\nSolution Vector x:\n";
    cout << fixed << setprecision(6);
    for (int i = 0; i < n; ++i)
    {
        cout << "x" << i + 1 << " = " << augmented[i][2 * n] << endl;
    }

    // Output inverse of A
    cout << "\nInverse of A:\n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = n; j < 2 * n; ++j)
        {
            cout << setw(10) << augmented[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

///  To run the program use the bellow comand
///  g++ -o gauss_jordan gauss_jordan.cpp
///  ./gauss_jordan