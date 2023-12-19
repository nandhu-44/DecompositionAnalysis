import numpy as np
import csv

# Generating a symmetric positive definite matrix and saving it to a csv file
def generate_and_save_spd_matrix(size, filename):
    A = np.random.randint(0, 10, size=(size, size))
    symmetric_matrix = (A + A.T) // 2
    spd_matrix = symmetric_matrix @ symmetric_matrix.T

    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        for row in spd_matrix:
            writer.writerow(row)

# Writing to a text file for viewing
def csv_to_txt(csv_file, txt_file):
    with open(csv_file, 'r') as csv_file:
        csv_reader = csv.reader(csv_file)
        with open(txt_file, 'w') as txt_file:
            for line in csv_reader:
                txt_file.write(" ".join(line) + "\n")    

matrix_size = int(input('Enter the size of the matrix: '))
file_name = 'data/matrix.csv'
generate_and_save_spd_matrix(matrix_size, file_name)
csv_to_txt(file_name, 'data/matrix.txt')