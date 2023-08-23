#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

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

    struct Data {
        double position;
        double value;
    };

    std::vector<struct Data> v;

    // if some values are not equal to 0 or 1, then we cannot read this non-binary signal.
    bool thereIsProblem=false;

    while(std::getline(file, userInput))
    {
        std::stringstream ss(userInput);

        struct Data data;

        if(ss >> data.position)
        {
            char c;
            ss >> c;
            if(c == ';')
            {
                ss >> data.value;

                if(data.value != 0 && data.value != 1)
                    thereIsProblem = true;
                else
                    v.push_back(data);

                while(ss >> c)
                {
                    if(c == ';')
                    {
                        std::cout << "ERROR: You are using multiple channels." << std::endl;
                        std::cout << "Please export your csv file with only one channel." << std::endl;

                        std::getline(std::cin, userInput);
                    }
                }
            }
        }
    }

    // Let's display an important warning.
    if(thereIsProblem)
    {
        std::cout << "WARNING: Some values are not equal to 0 or 1, when they must be." << std::endl;
        std::cout << "The results are therefore incorrect." << std::endl;
    }



    /// 3. Proceed to the measurements.

    double sumAll = 0;
    double sumUpper = 0;
    double sumLower = 0;

    unsigned nbAll = 0;
    unsigned nbUpper = 0;
    unsigned nbLower = 0;

    for(unsigned i=2; i<v.size()-1; ++i)
    {
        sumAll += (v[i].position - v[i-1].position);
        nbAll++;

        if(v[i].value == 0)
        {
            sumUpper += (v[i].position - v[i-1].position);
            nbUpper++;
        }
        else if(v[i].value == 1)
        {
            sumLower += (v[i].position - v[i-1].position);
            nbLower++;
        }

    }


    /// 4. Let's display the obtained results.

    std::cout << "average all: " << (sumAll/nbAll) << " (over " << nbAll << " curves)." << std::endl;
    std::cout << "average upper: " << (sumUpper/nbUpper) << " (over " << nbUpper << " curves)." << std::endl;
    std::cout << "average lower: " << (sumLower/nbLower) << " (over " << nbLower << " curves)." << std::endl;

    std::getline(std::cin, userInput);

    return 0;
}
