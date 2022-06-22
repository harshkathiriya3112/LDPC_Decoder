#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
//https://onlinegdb.com/GulVEyeRl
int main()
{
    int length = 12;
    int row = 9;
    ifstream file("H-matrix3 (9-12).txt");
    vector<vector<int>> H_matrix;
    //vector<int> rowVector;
    string line;
    while (getline(file, line))
    {
        vector<int> rowVector;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] != ',')
            {
                rowVector.push_back(line[i] - '0');
            }
        }
        H_matrix.push_back(rowVector);
    }
    // for (int i = 0; i < row; i++)
    // {
    //     for (int j = 0; j < length; j++)
    //     {
    //         cout << H_matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    //int N = 12, U = 9
    int i, j, k, count, c1, c2, c3, flag = 1, terminate = 1, Nsim = 10000, K_, l;
    int Ncorr[11] = {0}, Nerr[11] = {0};
    float prob[11];
    float p = 0;
    for (int i = 0; i < 11; i++)
    {
        prob[i] = p;
        p = p + 0.1;
    }

    float r;
    // Tanner Graph Decoding With Monte Carlo Simulations

    srand(time(NULL));
    for (l = 0; l < 11; l++)
    {
        for (K_ = 1; K_ <= Nsim; K_++)
        {
            int tr[length] = {0};    // Transmitted Signal
            int noise[length] = {0}; // Received Signal

            for (i = 0; i < length; i++)
            {
                r = ((float)rand() / RAND_MAX);
                if (r > prob[l])
                    noise[i] = tr[i];
                else
                    noise[i] = -1;
            }
            for (int i = 0; i < 30; i++)
            {
                int check = 0;
                for (int i = 0; i < length; i++)
                {
                    if (noise[i] == -1)
                    {
                        check++;
                    }
                }
                if (check == 0)
                {
                    Ncorr[l]++;
                    break;
                }
                for (int ii = 0; ii < row; ii++)
                {
                    int ind_matrix[length] = {0};
                    int z = 0;
                    for (int jj = 0; jj < length; jj++)
                    {
                        if (H_matrix[ii][jj] == 1)
                        {
                            if (noise[jj] == -1)
                            {
                                ind_matrix[z] = jj;
                                z++;
                            }
                        }
                    }
                    if (z != 1)
                    {
                        continue;
                    }
                    int sum = 0;
                    for (int jj = 0; jj < length; jj++)
                    {
                        if (H_matrix[ii][jj] == 1 && jj != ind_matrix[0])
                        {
                            sum += noise[jj];
                        }
                    }
                    noise[ind_matrix[0]] = sum % 2;
                }
                int check_equal;
                int countt = 0;
                for (int jj = 0; jj < length; jj++)
                {
                    check_equal = noise[jj] - tr[jj];
                    if (check_equal == 0)
                    {
                        countt++;
                    }
                }
                if (countt == length)
                {
                    Ncorr[l]++;
                    break;
                }
                int flagg = 0;
                for (int i = 0; i < length; i++)
                {
                    if (noise[i] == -1)
                    {
                        Nerr[l]++;
                        flagg++;
                        break;
                    }
                }
                if (flagg != 0)
                {
                    break;
                }
            }
        }
    }
    cout << "Output from Hmatrix3 (9*12) : " << endl;
    for (i = 0; i < 11; i++)
        cout << "p = " << prob[i] << " "
             << "Ncorr = " << Ncorr[i] << " Nerr = " << Nerr[i] << " Ncorr/Nsim = " << (Ncorr[i] * 1.0) / Nsim << endl
             << endl;
}
