import matplotlib.pyplot as plt

def plot_comparison(filename):
    data = []

    with open(filename, 'r') as file:
        next(file)
        for line in file:
            values = line.strip().split(',')
            data.append(list(map(int, values)))

    data = list(map(list, zip(*data)))

    labels = ['LU Decomposition', 'QR Decomposition', 'Cholesky Decomposition']

    for i, values in enumerate(data):
        plt.plot(values, label=labels[i])

    # Showing how the performance was with each run.
    plt.xlabel('No of times run')
    plt.ylabel('Time taken (microseconds)')
    plt.title('Comparison of Decomposition Algorithms')
    plt.legend()
    plt.show()

def calculate_ratios(filename):
    data = []

    with open(filename, 'r') as file:
        next(file)
        for line in file:
            values = line.strip().split(',')
            data.append(list(map(int, values)))

    average_times = [sum(values) / len(values) for values in zip(*data)]

    # Calculating the ratios of the algorithms wrt LU Decomposition
    lu_ratio = average_times[0] / average_times[0]
    qr_ratio = average_times[1] / average_times[0]
    cl_ratio = average_times[2] / average_times[0]

    return lu_ratio, qr_ratio, cl_ratio

if __name__ == "__main__":
    filename = 'data/results.csv'
    lu_ratio, qr_ratio, cl_ratio = calculate_ratios(filename)
    min_ratio = min(lu_ratio, qr_ratio, cl_ratio)

    # Ratios of the algorithms wrt LU Decomposition
    print(f'LU Decomposition Ratio: {lu_ratio}')
    print(f'QR Decomposition Ratio: {qr_ratio}')
    print(f'Cholesky Decomposition Ratio: {cl_ratio}')

    # Normalizing and rounding off the ratios to get approximate values
    lu_ratio , qr_ratio, cl_ratio = lu_ratio / min_ratio, qr_ratio / min_ratio, cl_ratio / min_ratio
    lu_ratio, qr_ratio, cl_ratio = round(lu_ratio), round(qr_ratio), round(cl_ratio)
    print(f"LU : QR : CL ≈ {lu_ratio:.2f} : {qr_ratio:.2f} : {cl_ratio:.2f}")
    
    # Plotting the graph
    plot_comparison(filename)