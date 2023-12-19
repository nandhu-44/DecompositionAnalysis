#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

template <typename Func, typename... Args>
std::pair<long long, decltype(std::declval<Func>()(std::declval<Args>()...))>
findTimeTaken(Func &&func, Args &&...args)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto result = std::forward<Func>(func)(std::forward<Args>(args)...);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    return std::make_pair(duration, result);
}

std::string getFormattedTime(long long timeTaken)
{
    std::string formattedTime;
    if (timeTaken < 1000)
    {
        formattedTime = std::to_string(timeTaken) + " microseconds";
    }
    else if (timeTaken < 1000000)
    {
        formattedTime = std::to_string(timeTaken / 1000) + "." + std::to_string(timeTaken % 1000) + " milliseconds";
    }
    else
    {
        formattedTime = std::to_string(timeTaken / 1000000) + "." + std::to_string((timeTaken % 1000000) / 1000) + " seconds";
    }
    return formattedTime;
}

void compareAndSave(std::string filename, std::pair<long long, std::tuple<Matrix, Matrix>> timeTakenLU, std::pair<long long, std::tuple<Matrix, Matrix>> timeTakenQR, std::pair<long long, std::tuple<Matrix, Matrix>> timeTakenCL)
{
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::app);
    if (file.is_open())
    {
        file << timeTakenLU.first << "," << timeTakenQR.first << "," << timeTakenCL.first << "\n";
    }
    else
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    file.close();
}

void clearFile(std::string filename)
{
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::trunc);
    if (file.is_open())
    {
        file << "LU,QR,CL\n";
    }
    else
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    file.close();
}

void compareTimeRatios(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    std::vector<std::vector<int>> data;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::vector<int> values;
        int value;
        while (ss >> value)
        {
            values.push_back(value);
            if (ss.peek() == ',' || ss.peek() == ' ')
            {
                ss.ignore();
            }
        }
        data.push_back(values);
    }

    file.close();

    std::vector<double> average_times;
    for (size_t i = 0; i < data[0].size(); ++i)
    {
        double sum = 0.0;
        for (const auto &values : data)
        {
            sum += values[i];
        }
        average_times.push_back(sum / data.size());
    }

    // Calculate ratios
    double lu_ratio = average_times[0] / average_times[0];
    double qr_ratio = average_times[1] / average_times[0];
    double cl_ratio = average_times[2] / average_times[0];

    // Normalize ratios
    double min_ratio = std::min({lu_ratio, qr_ratio, cl_ratio});
    lu_ratio /= min_ratio;
    qr_ratio /= min_ratio;
    cl_ratio /= min_ratio;

    // Round off ratios to get approximate values
    int rounded_lu_ratio = static_cast<int>(std::round(lu_ratio));
    int rounded_qr_ratio = static_cast<int>(std::round(qr_ratio));
    int rounded_cl_ratio = static_cast<int>(std::round(cl_ratio));

    // Output ratios
    std::cout << "LU Decomposition Ratio: " << lu_ratio << std::endl;
    std::cout << "QR Decomposition Ratio: " << qr_ratio << std::endl;
    std::cout << "Cholesky Decomposition Ratio: " << cl_ratio << std::endl;
    std::cout << "LU : QR : CL ≈ " << rounded_lu_ratio << " : " << rounded_qr_ratio << " : " << rounded_cl_ratio << std::endl;
}

#endif
