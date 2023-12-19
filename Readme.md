# [Decomposition Analysis](https://github.com/nandhu-44/DecompositionAnalysis)
> This project is about checking time taken by LU, QR and Cholesky decompositions for a very large matrix.

## Getting Started
- **<h3 style="color:#08b3fc">Clone the repository</h3>**

```bash
git clone https://github.com/nandhu-44/DecompositionAnalysis.git
```

- **<h3 style="color:#08b3fc">Install the requirements</h3>**

```bash
pip install numpy matplotlib
```

- **<h3 style="color:#08b3fc">Run the program</h3>**

### Linux/MacOS

```bash
python3 matrix_generator.py
# Enter the size of the matrix: 1000
```
### Windows

```bash
python matrix_generator.py
# Enter the size of the matrix: 1000
```

<h5 style="color:#ffaa33">This will generate a matrix of size 1000 by 1000. (We need a SPD matrix for cholesky)</h5>

- **<h3 style="color:#08b3fc">Compile and run the C++ program</h3>**

### Linux/MacOS

```bash
g++ main.cpp -o main.out && ./main.out
```

### Windows

```bash
g++ main.cpp -o main.exe
```
```bash
./main.exe
```

<h5 style="color:#ffaa33">Now choose menu option 4 and then input the no of iterations as some value (eg: 100)</h5>
<h5 style="color:#ffaa33">After that, choose menu option 5 to compare time taken by the algorithms</h5>

- **<h3 style="color:#08b3fc">View the plot of the data (also the comparisons) </h3>**

### Linux/MacOS

```bash
python3 compare.py
```

### Windows

```bash
python compare.py
```

<h5 style="color:#ffaa33">This will generate a graph comparing the time taken by each decomposition algorithm and also print the ratios.</h5>

> _Note: If line 4 (main.cpp) is causing you an error, you have to replace it with this._
```diff
- using std::cout, std::endl, std::cin, std::tie;
```
```diff
+ using namespace std;
```
