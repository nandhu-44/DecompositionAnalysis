#include <iostream>
#include "src/matrix.h"
#include "src/utility.h"
using std::cout, std::endl, std::cin, std::tie;

int main()
{
    std::string fileName = "data/matrix.csv";
    Matrix A(fileName);

    bool continueLoop = true,
         printMatrices = (A.rows < 10 && A.cols < 10); // Printing matrices if they are small enough
    if (!printMatrices)
    {
        char printChoice;
        cout << "The matrices are too large to print. Printing them won't be helpful.\nWould you like to print them anyway? (y/n) : ";
        cin >> printChoice;
        if (printChoice == 'y' || printChoice == 'Y')
        {
            printMatrices = true;
        }
        else
        {
            printMatrices = false;
        }
    }
    while (continueLoop)
    {
        int choice;
        Matrix L, U, Q, R, CL, CLT;
        std::pair<long long, std::tuple<Matrix, Matrix>> timeTakenLU, timeTakenQR, timeTakenCL;
        cout << "\n-------------------------------------------------\n";
        cout << "--------------------Main Menu--------------------\n";
        cout << "1. LU Decomposition\n";
        cout << "2. QR Decomposition\n";
        cout << "3. Cholesky Decomposition\n";
        cout << "4. Run n times (all decompositions)\n";
        cout << "5. Compare\n";
        cout << "6. Exit\n";
        cout << "Enter your choice : ";
        cin >> choice;
        cout << "-------------------------------------------------\n"
             << endl;
        switch (choice)
        {
        case 1:
            try
            {
                timeTakenLU = findTimeTaken(LUDecomposition, A);
                if (printMatrices)
                {
                    tie(L, U) = timeTakenLU.second;
                    cout << "L Matrix : \n";
                    L.printMatrix();
                    cout << "U Matrix : \n";
                    U.printMatrix();
                }
                cout << "Time taken by LU : " << getFormattedTime(timeTakenLU.first) << endl;
            }
            catch (const std::exception &e)
            {
                cout << "Error : " << e.what() << endl;
            }
            break;
        case 2:
            try
            {
                timeTakenQR = findTimeTaken(QRDecomposition, A);
                if (printMatrices)
                {
                    tie(Q, R) = timeTakenQR.second;
                    cout << "Q Matrix : \n";
                    Q.printMatrix();
                    cout << "R Matrix : \n";
                    R.printMatrix();
                }
                cout << "Time taken by QR : " << getFormattedTime(timeTakenQR.first) << endl;
            }
            catch (const std::exception &e)
            {
                cout << "Error : " << e.what() << endl;
            }
            break;
        case 3:
            try
            {
                timeTakenCL = findTimeTaken(CLDecomposition, A);
                if (printMatrices)
                {
                    tie(CL, CLT) = timeTakenCL.second;
                    cout << "L Matrix : \n";
                    CL.printMatrix();
                    cout << "L^T Matrix : \n";
                    CLT.printMatrix();
                }
                cout << "Time taken by CL : " << getFormattedTime(timeTakenCL.first) << endl;
            }
            catch (const std::exception &e)
            {
                cout << "Error : " << e.what() << endl;
            }
            break;
        case 4:
            try
            {
                int tries = 0;
                cout << "Enter the number of times you want to run : ";
                cin >> tries;
                clearFile("data/results.csv");
                for (int i = 0; i < tries; i++)
                {
                    timeTakenLU = findTimeTaken(LUDecomposition, A);
                    timeTakenQR = findTimeTaken(QRDecomposition, A);
                    timeTakenCL = findTimeTaken(CLDecomposition, A);
                    compareAndSave("data/results.csv", timeTakenLU, timeTakenQR, timeTakenCL);
                }
                cout << "Results saved in data/results.csv" << endl;
                // compareTimeRatios("data/results.csv");
            }
            catch (const std::exception &e)
            {
                cout << "Error : " << e.what() << endl;
            }
            break;
        case 5:
            try
            {
                compareTimeRatios("data/results.csv");
            }
            catch (const std::exception &e)
            {
                cout << "Error : " << e.what() << endl;
            }
            break;
        case 6:
            cout << "Thank you for using the program." << endl;
            continueLoop = false;
            break;
        default:
            cout << "Please provide a valid choice!" << endl;
            break;
        }
    }
    cout << "\n-------------------------------------------------" << endl;
    return 0;
}
