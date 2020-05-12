//
// Created by Linoy on 16/01/2020.
//
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "HashMap.hpp"

using namespace std;

/**
 * exit with invalid usage message
 */
void exitWithInvalidUsage()
{
    cerr << "Usage: SpamDetector <database path> <message path> <threshold>\n";
    throw std::invalid_argument("Invalid Usage");
}

/**
 * check number of args
 * @param argc
 */
void checkInvalidNumberOfArgs(int argc)
{
    if (argc != 4)
    {
        exitWithInvalidUsage();
    }
}

/**
 * exit with invalid input message
 */
void exitWithInvalidInput()
{
    std::cerr << "Invalid input\n";
    throw std::invalid_argument("Invalid Input");
}

/**
 *
 * @param s
 * @return true if s is a number, elsewhere false
 */
bool isNumber(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
    { ++it; }
    return !s.empty() && it == s.end();
}

/**
 * check if line is valid
 * @param lineInput
 * @param rank
 */
void checkInvalidLine(std::string lineInput, std::string rank)
{
    if (lineInput.empty())
    {
        exitWithInvalidInput();
    }
    else
    {
        if (lineInput.find(",") == std::string::npos)
        {
            exitWithInvalidInput();
        }

        if (rank.find(",") != std::string::npos || !isNumber(rank))
        {
            exitWithInvalidInput();
        }
    }
}

/**
 * validate rank
 * @param rankNumber
 */
void checkInvalidRank(int rankNumber)
{
    if (rankNumber < 0)
    {
        exitWithInvalidInput();
    }
}

/**
 * print where the message is spam or not spam
 * @param limit
 * @param totalRank
 */
void printResult(int limit, int totalRank)
{
    if (totalRank >= limit)
    {
        cout << "SPAM" << endl;
    }
    else
    {
        cout << "NOT_SPAM" << endl;
    }
}

/**
 * convert string to lower case string
 * @param textString
 */
void strToLowerCase(string &textString)
{
    std::transform(textString.begin(), textString.end(), textString.begin(),
                   [](unsigned char c) { return tolower(c); });
}

/**
 * validate limit
 * @param limitStr
 */
void validLimitInput(const string &limitStr)
{
    if (!isNumber(limitStr) || stoi(limitStr) <= 0)
    {
        exitWithInvalidInput();
    }
}

/**
 * check if file empty
 * @param infile
 * @return
 */
bool isFileEmpty(ifstream &infile)
{ return infile.peek() == char_traits<char>::eof(); }

/**
 * open file or exit if invalid
 * @param fileRankingLocation
 * @param infile
 */
void openFile(const string &fileRankingLocation, ifstream &infile)
{
    infile.open(fileRankingLocation);
    if (!infile.is_open())
    {
        exitWithInvalidInput();
    }
}

/**
 * calculate text rank
 * @param inputMap
 * @param textString
 * @return
 */
int calculateRank(const HashMap<string, int> &inputMap, const string &textString)
{
    int totalRank = 0;
    for (HashMap<string, int>::const_iterator iter = inputMap.begin();
         iter != inputMap.end(); ++iter)
    {
        int occurrences = 0;
        std::string::size_type pos = 0;
        while ((pos = textString.find((*iter).first, pos)) != std::string::npos)
        {
            ++occurrences;
            pos += (*iter).first.length();
        }
        totalRank += occurrences * (*iter).second;
    }
    return totalRank;
}

int main(int argc, char **argv)
{
    try
    {
        checkInvalidNumberOfArgs(argc);

        std::string fileRankingLocation = argv[1];
        std::string fileInputLocation = argv[2];
        std::string limitStr = argv[3];

        std::string lineInput, sentence, rank;
        int rankNumber, limit, totalRank;
        std::ifstream infile;
        HashMap<string, int> inputMap = HashMap<string, int>();

        openFile(fileRankingLocation, infile);
        if (isFileEmpty(infile))
        {
            cout << "NOT_SPAM" << endl;
            return EXIT_SUCCESS;
        }

        while (!infile.eof())
        {
            getline(infile, lineInput);
            if (!(infile.eof() && lineInput.empty()))
            {
                sentence = lineInput.substr(0, lineInput.find(","));
                rank = lineInput.substr(lineInput.find(",") + 1);

                checkInvalidLine(lineInput, rank);
                rankNumber = std::stoi(rank);
                checkInvalidRank(rankNumber);
                strToLowerCase(sentence);
                inputMap.insert(sentence, rankNumber);
            }
        }

        infile.close();

        openFile(fileInputLocation, infile);

        if (isFileEmpty(infile))
        {
            cout << "NOT_SPAM" << endl;
            return (EXIT_SUCCESS);
        }

        infile.close();

        std::ifstream t(fileInputLocation);
        std::string textString((std::istreambuf_iterator<char>(t)),
                               std::istreambuf_iterator<char>());
        t.close();

        validLimitInput(limitStr);
        strToLowerCase(textString);
        totalRank = calculateRank(inputMap, textString);
        limit = stoi(argv[3]);
        printResult(limit, totalRank);
    }
    catch (const std::invalid_argument &ia)
    {
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Invalid input\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}
