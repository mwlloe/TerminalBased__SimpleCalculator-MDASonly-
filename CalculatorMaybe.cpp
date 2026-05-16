#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

double equationFunc(string equation){
    vector<double> numbers; // stores numbers from equation
    vector<char> ops;       // stores operator types from equation
    string curr;            // keep track of

    // tokenize
    for (char c : equation){
        if (isdigit(c) || c == '.'){
            curr += c;
        } else {
            // if current string is not empty then store it into the vector of numbers
            if (!curr.empty()){
                numbers.push_back(stod(curr));
                curr.clear();  // empty the string 
            }

            if (c == '+' || c == '-' || c == '*' || c == '/'){
                ops.push_back(c);
            }
        }
    }

    // after tokenizing, save other numbers
    if (!curr.empty()){
        numbers.push_back(stod(curr));
    }

    // handle multplication & division
    for (size_t i = 0; i < ops.size();){
        if (ops[i] == '*' || ops[i] == '/'){
            double result;
            
            // multiplication first: number by next number, else divide
            if (ops[i] == '*'){
                result = numbers[i] * numbers[i + 1];
            } else {
                result = numbers[i] / numbers[i + 1];
            }

            // store the reult in current index of numbers, then clear equation thus far
            numbers[i] = result;
            numbers.erase(numbers.begin() + i + 1);
            ops.erase(ops.begin() + i);
        } else {
            i++;
        }
    }

    // handle addition and subtraction
    double result = numbers[0]; // <- should be the result from last operation(s)

    for (size_t i = 0; i < ops.size(); i++){
        if (ops[i] == '+'){
            result += numbers[i + 1];
        } else {
            result -= numbers[i + 1];
        }
    }

    return result;
}

int main()
{
    string equation;

    cout << "Welcome to terminal calculator." << endl;
    cout << "Enter an equation then hit enter to see the result, or enter empty field to quit." << endl;
    bool tryAgain = true;

    // main calculation menu. Loops until no equation is entered
    while (tryAgain){
        getline(cin, equation);
        if (equation.empty()){
            tryAgain = false;
        } else {
            double result = equationFunc(equation);
            cout << equation << " = " << result << endl;
        }
    }

    // should show if exited properly or not
    if (!tryAgain){
        cout << "Exiting..." << endl;
    } else {
        cout << "Exited unexpectedly." << endl;
    }

    return 0;
}