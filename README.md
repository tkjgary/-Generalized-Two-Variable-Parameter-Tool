# GeneralizedTwoVariableParameterTool

This program evaluates the consistency and accuracy of measured data compared to user-defined approximations. It supports flexible input sizes, user-defined equations, and tolerance-based validation for mean and standard deviation.

---

Below is the table of contents for navigating the repository.

## Table of Contents
| File                                                   | Function                                               |
|--------------------------------------------------------|--------------------------------------------------------|
| [How to Run](README.md#how-to-run)                     | Instructions to execute the program                    |
| [Detailed Explanation](README.md#detailed-explanation) | Detailed explanation of the program                    |
| [Theoretical Aspects](README.md#theoretical-aspects)   | Explains the theoretical framework and formulas        |
| [Sample Runs](Sample_Runs/)                            | Screenshots of sample program outputs                  |
| [Source Code](Code.m)                                  | Program written in C                                   |
| [Program Workflow](Program_Workflow/)                  | Flowchart showing the program’s logic                  |
| [Input File Example](input.txt)                        | Example of the input text file that can be read by the program|
| [Result File Example](results.txt)                     | Example of result text file generated by the program   |


## How to Run

### Requirements
- A C compiler (e.g., GCC)
- Input data file named `input.txt` in the same directory as the program.

### Steps to Compile and Execute
1. **Compile the Program**:
   - Open your terminal and run the following command:  
   ```bash
   gcc main.c -o program -lm
   ```
   - This will generate an executable file named program.

3. **Prepare the Input File**:
   - Create an input.txt file in the following format:
   - The first line contains the column headers for the Var2 values.
   - The second line contains the numerical values of Var2.
   - The subsequent lines contain Var1 values followed by their corresponding measurements.

     Example:
     ```
     Var1/Var2   1.0   2.0   3.0
     1.0         2.1   2.3   2.5
     2.0         3.2   3.4   3.6
     ```

3. **Run the Program**:
   - Execute the compiled program.

5. **Provide Inputs**:
   - The program will ask for:
     - Number of rows and columns in the dataset.
     - Coefficients for the user-defined equation.
     - Tolerance values for mean and standard deviation.

5. **Output**:
   - Results will be displayed on the terminal.
   - A detailed report will be written to result.txt.



---

## Detailed Explanation
This project implements a data analysis tool for comparing measured data against approximated values calculated using a user-defined linear equation. It evaluates the consistency of the data based on the mean and standard deviation differences. The program is designed for numerical datasets arranged in a grid format, typically used in engineering or scientific experiments.

It is assumed that:
1. Data is provided in a structured input file (`input.txt`).
2. Measurements are obtained from reliable experimental setups.
3. The user-defined equation is linear in nature and takes the form:

$$
Output = Intercept + Coef1 × Var1 + Coef2 × Var2
$$

This code can be applied in various fields, including:
- **Engineering**: Validate experimental data consistency in domains such as materials testing or thermal analysis.
- **Scientific Research**: Compare theoretical models with empirical observations.
- **Quality Control**: Assess production data to ensure consistency with design specifications.

By providing a detailed comparison between measured and calculated data, the program enables informed decision-making and highlights areas requiring further investigation.


## Theoretical Aspects

The program applies statistical principles to evaluate data consistency:

### 1. **Mean**  
The mean is a measure of central tendency, calculated as the average of all values in a dataset.  
The formula for the mean is:

$$  
Mean = \frac{Σ xᵢ}{N}
$$

Where:
- xᵢ: Individual data points
- N: Total number of data points


### 2. **Standard Deviation (SD)**  
Standard deviation is a measure of data dispersion, which quantifies the amount of variation in a dataset.  
The formula for standard deviation is:  

$$SD = \sqrt{\frac{Σ (xᵢ - x̄)²}{N}}$$


Where:
- xᵢ: Individual data points
- x̄: Mean of the dataset
- N: Total number of data points


### 3. **Percent Difference**  
Percent difference is used to compare the consistency between measured and calculated datasets.  
The formula for percent difference is:  


$$Percent Difference = \frac{Measured - Calculated}{Calculated} × 100$$


Where:
- Measured: Mean or standard deviation of the measured dataset
- Calculated: Mean or standard deviation of the calculated dataset


### Application in the Program
- The **mean** and **standard deviation** are calculated for both the measured and approximated datasets.  
- The **percent difference** is evaluated for mean and standard deviation to check if they are within the user-defined tolerances.  

These statistical measures allow the program to assess the consistency between the measured and calculated datasets.



