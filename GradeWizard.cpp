#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

//Function prototypes
void readFile(int*, float*, float*, float* , float*, int);

void calculateWeightedMarks(double*, double*, double*, double*,
                            float*, float*, float*, float*, int,
                            double, double, double, double);

void calculateOver100(double*, double*, double*, double*,
                      double*, double*, int, double);

void categoriseGrades(char*, double*, int);

void writeFile(int*, float*, double*, float*, double*,
               float*, double*, float*, double*,
               double*, double*, char*, int);

int main()
{
	//Declaration of variables
    int numberOfStudents;
    double totalCoursework, test1Weightage, test2Weightage;
    double assignment1Weightage, assignment2Weightage;

	//Welcome message
    cout << "Welcome to the GradeWizard!" << endl;

	//User prompts for inputs
    cout << "Let's get grading by entering the following prompts: " << endl;

    cout << "\nEnter total coursework marks : ";
    cin >> totalCoursework;

    cout << "Enter number of students: ";
    cin >> numberOfStudents;

    cout << "Enter weightage for Test 1: ";
    cin >> test1Weightage;

    cout << "Enter weightage for Test 2: ";
    cin >> test2Weightage;

    cout << "Enter weightage for Assignment 1: ";
    cin >> assignment1Weightage;

    cout << "Enter weightage for Assignment 2: ";
    cin >> assignment2Weightage;

    //Input validations
    while(totalCoursework != (test1Weightage+test2Weightage+assignment1Weightage+assignment2Weightage))
        {
            cout << "\nThe weightages did not sum up to the total coursework marks!" <<endl;
            cout << "Please enter the corresponding weightages correctly." <<endl;

            cout << "\nTotal coursework mark: " << totalCoursework <<endl;
            cout << "Enter weightage for Test 1: ";
            cin >> test1Weightage;

            cout << "Enter weightage for Test 2: ";
            cin >> test2Weightage;

            cout << "Enter weightage for Assignment 1: ";
            cin >> assignment1Weightage;

            cout << "Enter weightage for Assignment 2: ";
            cin >> assignment2Weightage;
        }

    // Attempt to open the input file
    ifstream inFile("CourseworkMarks.txt");

    // Input file error handling
    if (!inFile) {
        cout << "\nError opening input file!" << endl;
        cout << "Please upload your input file first and try again."<<endl;
        return 1; // Terminate the program
    }
	inFile.close();

	//Dynamic memory allocations for arrays
    int* matricNumbers = new int[numberOfStudents];
    float* test1 = new float[numberOfStudents];
    float* test2 = new float[numberOfStudents];
    float* assignment1 = new float[numberOfStudents];
    float* assignment2 = new float[numberOfStudents];
    double* weightedTest1 = new double[numberOfStudents];
    double* weightedTest2 = new double[numberOfStudents];
    double* weightedAssignment1 = new double[numberOfStudents];
    double* weightedAssignment2 = new double[numberOfStudents];
    double* totalCW = new double[numberOfStudents];
    double* totalOver100 = new double[numberOfStudents];
    char* grade = new char[numberOfStudents];

	//Function calls
    readFile(matricNumbers, test1, test2, assignment1, assignment2, numberOfStudents);

    calculateWeightedMarks(weightedTest1, weightedTest2, weightedAssignment1, weightedAssignment2,
                           test1, test2, assignment1, assignment2,
                            numberOfStudents, test1Weightage, test2Weightage, assignment1Weightage, assignment2Weightage);

    calculateOver100(totalCW, totalOver100, weightedTest1, weightedTest2, weightedAssignment1, weightedAssignment2,
                      numberOfStudents, totalCoursework);

    categoriseGrades(grade, totalOver100, numberOfStudents);

    writeFile(matricNumbers, test1, weightedTest1, test2, weightedTest2,
               assignment1, weightedAssignment1, assignment2, weightedAssignment2,
               totalCW, totalOver100, grade, numberOfStudents);

	//Free up dynamic memory
    delete[] matricNumbers;
    delete[] test1;
    delete[] test2;
    delete[] assignment1;
    delete[] assignment2;
    delete[] weightedTest1;
    delete[] weightedTest2;
    delete[] weightedAssignment1;
    delete[] weightedAssignment2;
    delete[] totalCW;
    delete[] totalOver100;
    delete[] grade;

    cout << "\nSuccess! You can now check the generated output file." << endl;
    cout << "Thank you for using this program." << endl;
    cout << "See you again." << endl;

    return 0;
}

//*************************************************Function Definitions****************************************************//

//Function to read data from the input file
void readFile(int* matricNumbers, float* test1, float* test2, float* assignment1, float* assignment2, int numberOfStudents)
{
    ifstream inFile;
    inFile.open("CourseworkMarks.txt");

	//Read header of the input file and ignores it
    string header;
    getline(inFile, header);

	//Read data of each students
    for (int i = 0; i < numberOfStudents; i++)
    {
        inFile >> matricNumbers[i];
        inFile.ignore(); // Ignore the comma
        inFile >> test1[i];
        inFile.ignore();
        inFile >> test2[i];
        inFile.ignore();
        inFile >> assignment1[i];
        inFile.ignore();
        inFile >> assignment2[i];
    }
    inFile.close();
}

//Function to calculate weighted marks for Test 1, Test 2, Assignment 1 and Assignment 2
void calculateWeightedMarks(double* weightedTest1, double* weightedTest2, double* weightedAssignment1, double* weightedAssignment2,
                            float* test1, float* test2, float* assignment1, float* assignment2, int numStudents,
                            double test1Weightage, double test2Weightage, double assignment1Weightage, double assignment2Weightage)
{
    for (int i = 0; i < numStudents; i++)
    {
        weightedTest1[i] = test1Weightage * (test1[i] / 100.0);
        weightedAssignment1[i] = assignment1[i] * (assignment1Weightage / 100.0);
        weightedTest2[i] = test2[i] * (test2Weightage / 100.0);
        weightedAssignment2[i] = assignment2[i] * (assignment2Weightage / 100.0);
    }
}

//Function to calculate total marks and percentage over 100
void calculateOver100(double* totalCW, double* totalOver100, double* weightedTest1, double* weightedTest2,
                      double* weightedAssignment1, double* weightedAssignment2, int numStudents, double totalCoursework)
{
    for (int i = 0; i < numStudents; i++)
    {
        totalCW[i] = weightedTest1[i] + weightedTest2[i] + weightedAssignment1[i] + weightedAssignment2[i];
        totalOver100[i] = (totalCW[i] / totalCoursework) * 100.0;
    }
}

//Function to categorises each over 100 marks to its corresponding grades
void categoriseGrades(char* grade, double* totalOver100, int numStudents)
{
    for (int i = 0; i < numStudents; i++)
    {
        if (totalOver100[i] >= 80.0 && totalOver100[i] <= 100.0)
            grade[i] = 'A';
        else if (totalOver100[i] >= 70.0 && totalOver100[i] <= 79.9)
            grade[i] = 'B';
        else if (totalOver100[i] >= 60.0 && totalOver100[i] <= 69.9)
            grade[i] = 'C';
        else if (totalOver100[i] >= 50.0 && totalOver100[i] <= 59.9)
            grade[i] = 'D';
        else
            grade[i] = 'F';
    }
}

//Function to write to output file
void writeFile(int* matricNumbers, float* test1, double* weightedTest1, float* test2, double* weightedTest2,
               float* assignment1, double* weightedAssignment1, float* assignment2, double* weightedAssignment2,
               double* totalCW, double* totalOver100, char* grade, int numStudents)
{
    ofstream outFile;
    outFile.open("CourseworkMarks_Output.txt");

	//Write header to the output file
    outFile << "Matric Number,Test 1,Test1_Weightage,Test 2,Test2_Weightage,Assignment 1,Assignment1_Weightage,";
	  outFile << "Assignment 2,Assignment2_Weightage,Total CW,over 100,Grade\n";

	//Write data to each students to output file
    for (int i = 0; i < numStudents; i++)
    {
    	outFile << setprecision(2) << fixed;
      outFile << matricNumbers[i] << "," << test1[i] << "," << weightedTest1[i] << "," << test2[i] << "," << weightedTest2[i]
                << "," << assignment1[i] << "," << weightedAssignment1[i] << "," << assignment2[i] << "," << weightedAssignment2[i]
                << "," << totalCW[i] << "," << totalOver100[i] << "," << grade[i] << "\n";
    }

    outFile.close();
}
