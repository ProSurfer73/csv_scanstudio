#include <iostream>
#include <fstream>

int main()
{
    // Useful variables
    std::ifstream file;
    std::string userInput;

    /// 1. Lets ask the user for the csv file.
    do {
        std::cout << "Please enter the file path to a csv file first:" << std::endl;

        std::getline(std::cin, userInput);

        if(userInput.empty())
            return 0;

        file.open(userInput);
    }
    while(!file);


    /// 2. Lets read the file.



    return 0;
}
