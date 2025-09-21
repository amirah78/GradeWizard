# GradeWizard 

GradeWizard is a C++ program that automates coursework grading.  
It was designed around a simple workflow: lecturers export student marks from Excel into a plain `.txt` file. 
This program takes that text file, applies weightage, and generates final totals, percentages and letter grades. 
The output is also written into a `.txt` file so it can be easily converted back into Excel if needed.

I built this project back in my first year of university as part of a programming assignment and I’ve kept it here as an example of my early C++ work.

## Features
- Reads student marks from a plain text file (`CourseworkMarks.txt`) exported from Excel.
- Lets the user set custom weightage for 2 tests and 2 assignments.
- Calculates:
  - Weighted marks
  - Coursework totals
  - Percentages over 100
  - Final grades (A–F)
- Outputs results into `CourseworkMarks_Output.txt`, structured so it can be re-imported into Excel.

## How to Run
1. Make sure you have a C++ compiler installed (e.g. `g++`).
2. Place `GradeWizard.cpp` and `CourseworkMarks.txt` in the same folder.
3. Compile and run:

   ```bash
   g++ GradeWizard.cpp -o GradeWizard
   ./GradeWizard
4. Enter the weightage values as prompted.
5. Open `CourseworkMarks_Output.txt` to see the graded coursework results.
