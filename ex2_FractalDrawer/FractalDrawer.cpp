
#include <fstream>
#include <iostream>
#include "Fractal.h"

/**
 * declaration of exit With InvalidInput
 * @return
 */
void exitWithInvalidInput();

/**
 * declaration of exit With InvalidUsage
 * @return
 */
void exitWithInvalidUsage();

/**
 * declaration of draw fractal
 * @param typeI
 * @param dimI
 */
void drawFractal(std::vector<int>::iterator &typeI, std::vector<int>::iterator &dimI);

/**
 * function to check if the given is number
 * @param s
 * @return
 */
bool isNumber(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
    { ++it; }
    return !s.empty() && it == s.end();
}

/**
 * function to check if the num of the given args is valid
 * @param argc
 * @return
 */
void checkInvalidNumberOfArgs(int argc)
{
    if (argc != 2)
    {
        exitWithInvalidUsage();
    }

}

/**
 * function to check if the end of the file is valid (.csv)
 * @param fileLocation
 * @return
 */
void checkInvalidFileLocationEnding(std::string fileLocation)
{
    if (fileLocation.find(".csv") == std::string::npos)
    {
        exitWithInvalidInput();

    }
    else
    {
        if (fileLocation.substr(fileLocation.find(".csv")) != ".csv")
        {
            exitWithInvalidInput();
        }
    }
}

/**
 * function to check if the line is valid
 * @param infile
 * @param lineInput
 * @param type
 * @param dim
 * @return
 */
void
checkInvalidLine(std::ifstream &infile, std::string lineInput, std::string type, std::string dim)
{
    if (lineInput == "")
    {
        bool flag = true;
        while (!infile.eof())
        {
            getline(infile, lineInput);
            if (lineInput == "")
            { continue; }
            else
            {
                flag = false;
                break;
            }
        }
        if (!flag)
        { exitWithInvalidInput(); }
    }
    if (lineInput != "" && lineInput.find(",") == std::string::npos)
    {
        exitWithInvalidInput();
    }

    if ((dim.find(",") != std::string::npos && lineInput != "") ||
        (!isNumber(dim) && lineInput != "") || (!isNumber(type) && lineInput != ""))
    {
        exitWithInvalidInput();
    }
}

/**
 * func to check Invalid Dim
 * @param dimNumber
 * @return
 */
void checkInvalidDim(int dimNumber)
{
    if (dimNumber < 1 || dimNumber > 6)
    {
        exitWithInvalidInput();
    }
}

/**
 * func to check Invalid type
 * @param typeNumber
 * @return
 */
void checkInvalidType(int typeNumber)
{
    if (typeNumber < 1 || typeNumber > 3)
    {
        exitWithInvalidInput();

    }
}

/**
 * func main . runing the program
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv)
{

    std::string lineInput, type, dim;
    int typeNumber, dimNumber;
    std::vector<int> inputTypes, inputDims;
    std::ifstream infile;
    if (argc != 2)
    {
        exitWithInvalidUsage();
    }

    std::string fileLocation = argv[1];
    checkInvalidNumberOfArgs(argc);
    checkInvalidFileLocationEnding(fileLocation);
    infile.open(fileLocation);
    if (!infile.is_open())
    {
        exitWithInvalidInput();
    }
    if (infile.peek() == std::ifstream::traits_type::eof())
    {
        exit(EXIT_SUCCESS);
    }
    while (!infile.eof())
    {
        getline(infile, lineInput);
        type = lineInput.substr(0, lineInput.find(","));
        dim = lineInput.substr(lineInput.find(",") + 1);

        checkInvalidLine(infile, lineInput, type, dim);

        if (lineInput != "")
        {
            typeNumber = std::stoi(type);
            checkInvalidType(typeNumber);
            inputTypes.push_back(typeNumber);

            dimNumber = std::stoi(dim);
            checkInvalidDim(dimNumber);
            inputDims.push_back(dimNumber);
        }
    }
    infile.close();

    auto typeI = inputTypes.end(), dimI = inputDims.end();
    bool isDone = false;
    typeI--;
    dimI--;
    while (!isDone)
    {
        drawFractal(typeI, dimI);
        std::cout << std::endl;

        if (typeI == inputTypes.begin() || dimI == inputDims.begin())
        {
            isDone = true;
        }
        else
        {
            typeI--;
            dimI--;
        }
    }

    exit(EXIT_SUCCESS);
}

/**
 * func to draw fractal up to the file
 * @param typeI
 * @param dimI
 */
void drawFractal(std::vector<int>::iterator &typeI, std::vector<int>::iterator &dimI)
{
    if (*typeI == 1)
    {
        Carpet carpet(*dimI);
        carpet.drawFractal();
    }

    if (*typeI == 2)
    {
        SierpinskiTriangle sierpinskiTriangle(*dimI);
        sierpinskiTriangle.drawFractal();
    }

    if (*typeI == 3)
    {
        Vicsek vicsek(*dimI);
        vicsek.drawFractal();
    }
}

/**
 * func to exit With Invalid Usage
 * @return

 */
void exitWithInvalidUsage()
{
    std::cerr << "Usage: FractalDrawer <file path>\n";
    exit(EXIT_FAILURE);
}

/**
 * unc to exit With Invalid input
 * @return
 */
void exitWithInvalidInput()
{
    std::cerr << "Invalid input\n";
    exit(EXIT_FAILURE);
}





