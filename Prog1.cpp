#include <iostream>
#include <string>
#include <vector>

// Get row based on first of stack
int GetRow(char rowChar) {
    switch (rowChar) {
        case 'E':
            return 0;
        case 'Q':
            return 1;
        case 'T':
            return 2;
        case 'R':
            return 3;
        case 'F':
            return 4;
        default:
            return 10;   // To indicate error
    }
}

// Get column based on first of input
int GetColumn(char columnChar) {
    switch (columnChar) {
        case 'a':
            return 0;
            break;
        case '+':
            return 1;
            break;
        case '-':
            return 2;
            break;
        case '*':
            return 3;
            break;
        case '/':
            return 4;
            break;
        case '(':
            return 5;
            break;
        case ')':
            return 6;
            break;
        case '$':
            return 7;
        default:
            return 10;  // To indicate error
    }
}

int main() {
    // Get user input
    std::string userInput = "";
    std::cout << "Enter test string: ";
    std::cin >> userInput;
    
    // Put user input into vector of chars
    std::vector<char> charInput(userInput.begin(), userInput.end());
    std::vector<char> copyInput = charInput;

    // Parse table
    std::string parseTable [5][8] = {
    //    a     +     -    *      /      (    )     $
        {"TQ", "NA", "NA", "NA", "NA", "TQ", "NA", "NA"},                           // E
        {"NA", "+TQ", "-TQ", "NA", "NA", "NA", "epsilon", "epsilon"},               // Q
        {"FR", "NA", "NA", "NA", "NA", "FR", "epsilon", "epsilon"},                 // T
        {"NA", "epsilon", "epsilon", "*FR", "/FR", "NA", "epsilon", "epsilon"},     // R
        {"a", "NA", "NA", "NA", "NA", "(E)", "NA", "NA"}                            // F
    };
    
    // Stack
    std::vector<char> stack;
    stack.push_back('E');
    stack.push_back('$');

    char rowChar;
    int row = 0;
    char columnChar;
    int column = 0;

    std::string prediction = " ";
    bool pass = true;

    while (charInput.size() != 1 && pass == true) {
        // Prints stack and input
        // std::cout << "Stack: " << std::endl;
        // for (auto i = stack.begin(); i < stack.end(); i++) {
        //     std::cout << *i << " ";
        // }
        // std::cout << std::endl;
        // std::cout << "Input: " << std::endl;
        // for (auto it = charInput.begin(); it != charInput.end(); it ++) {
        //     std::cout << *it << " ";
        // }
        // std::cout << std::endl;

        // Get prediction
        rowChar = stack.front();
        columnChar = charInput.front();
        prediction = parseTable[GetRow(rowChar)][GetColumn(columnChar)];
        // std::cout << "The prediction is: " << rowChar << " -> " << prediction << std::endl;
        if (GetRow(rowChar) == 10 || GetColumn(columnChar) == 10) {
            pass = false;
            break;
        }

        if (prediction == "NA") {
            pass = false;
            break;
        } else if (prediction == "epsilon") {
            // since it is epsilon, removes the first in stack
            stack.erase(stack.begin());
        } else {
            // prepared to put prediction in stack
            std::vector<char> predictionVec(prediction.begin(), prediction.end());
            std::reverse(predictionVec.begin(), predictionVec.end());

            // Put prediction in stack
            stack.erase(stack.begin());
            for(auto it = predictionVec.begin(); it < predictionVec.end(); it++) {
                stack.insert(stack.begin(), *it);
            }

            // Check for match
            if (stack.front() == charInput.front()) {
                stack.erase(stack.begin());
                charInput.erase(charInput.begin());
            }
        }
        // check for match
        if (stack.front() == charInput.front()) {
                stack.erase(stack.begin());
                charInput.erase(charInput.begin());
            } else {
                continue;
            }
    }

    // Display final results
    std::cout << "Input: ";
    for (auto it = copyInput.begin(); it != copyInput.end(); it ++) {
        std::cout << *it;
    }
    std::cout << std::endl;
    std::cout << "Stack: [";
    for (auto i = stack.begin(); i < stack.end(); i++) {
        if (i != stack.begin()) {
            std::cout << "',";
        }
        std::cout << "'" << *i;
    }
    std::cout << "']" << std::endl;
    if (pass == true) {
        std::cout << "String is accepted/ valid" << std::endl;
    } else {
        std::cout << "String is not accepted/ invalid" << std::endl;
    }

    return 0;
}