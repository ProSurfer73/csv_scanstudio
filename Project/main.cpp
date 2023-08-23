#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

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

    double minAll = 1000;
    double minUpper = 1000;
    double minLower = 1000;

    double maxUpper = -1;
    double maxLower = -1;
    double maxAll = -1;

    for(unsigned i=2; i<v.size()-1; ++i)
    {
        const double d = (v[i-1].position - v[i].position);
        sumAll += d;
        nbAll++;

        if(d < minAll)
            minAll = d;
        if(d > maxAll)
            maxAll = d;

        if(v[i].value == 0)
        {
            sumUpper += d;
            nbUpper++;

            if(d < minUpper)
                minUpper = d;
            if(d > maxUpper)
                maxUpper = d;
        }
        else if(v[i].value == 1)
        {
            sumLower += d;
            nbLower++;

            if(d < minLower)
                minLower = d;
            if(d > maxLower)
                maxLower = d;
        }

    }


    /// 4. Let's display the obtained results.

    std::cout << "average all: " << (sumAll/nbAll) << " (over " << nbAll << " curves)." << std::endl;
    std::cout << "average upper: " << (sumUpper/nbUpper) << " (over " << nbUpper << " curves)." << std::endl;
    std::cout << "average lower: " << (sumLower/nbLower) << " (over " << nbLower << " curves)." << std::endl;

    std::cout << "\nmin all: " << minAll << std::endl;
    std::cout << "max all: " << maxAll << std::endl;
    std::cout << "min upper: " << minUpper << std::endl;
    std::cout << "max upper: " << maxUpper << std::endl;
    std::cout << "min lower: " << minLower << std::endl;
    std::cout << "max upper: " << maxUpper << std::endl;


    // calculate the variance

    double varSumUpper = 0;
    double varSumLower = 0;
    double varSumAll = 0;

    for(unsigned i=2; i<v.size()-1; ++i)
    {
        varSumAll += pow(((v[i-1].position - v[i].position) - (sumAll/nbAll)),2);

        if(v[i].value == 0)
        {
            varSumUpper += pow(((v[i-1].position - v[i].position) - (sumUpper/nbUpper)),2);
        }
        else if(v[i].value == 1)
        {
            varSumLower += pow(((v[i-1].position - v[i].position) - (sumLower/nbLower)),2);
        }
    }

    std::cout << "variance all: " << (varSumAll/nbAll) << std::endl;
    std::cout << "variance upper: " << (varSumUpper/nbUpper) << std::endl;
    std::cout << "variance lower: " << (varSumLower/nbLower) << std::endl;

    std::getline(std::cin, userInput);


    return 0;
}
