//
// Created by kirill on 09.05.24.
//

#include <iostream>
#include <fstream>
#include <string>

#include "tabulation.h"
/**
 * The TabulationTxt constructor initializes input and output file streams based on the provided file
 * name.
 * 
 * @param Fille It looks like there are some issues in the code snippet you provided. Let me help you
 * correct it.
 */
TabulationTxt::TabulationTxt(std::string Fille)
{
    txtFille = std::ifstream(Fille);
    outFille = std::ofstream (temp);
}
/**
 * The TabulationTxt constructor initializes input and output file streams based on the provided file
 * names.
 * 
 * @param Fille It looks like you were about to provide some information about the parameter "Fille" in
 * your code. Could you please complete your sentence or provide more context so that I can better
 * assist you?
 * @param temp_fille It looks like you are trying to define a constructor for a class `TabulationTxt`.
 * The constructor takes two parameters: `Fille` of type `std::string` and `temp_fille` of type
 * `std::string&`.
 */
TabulationTxt::TabulationTxt(std::string Fille, std::string &temp_fille)
{
    txtFille = std::ifstream(Fille);

    if (!txtFille) {
        // throw
        std::cerr << "Not found txt." << std::endl;
    }

    if (!empty(temp_fille))
        outFille = std::ofstream(temp_fille);
    else
        outFille = std::ofstream(temp);
}

/**
 * The TabulationTxt destructor closes the txtFille and outFille file streams if they are open.
 */
TabulationTxt::~TabulationTxt()
{
    if (txtFille)
    {
        txtFille.close();
    }
    outFille.close();
}
/**
 * The function `FindBeginEnd` in the `TabulationTxt` class checks for the presence of "%%begin" and
 * "%%end" in a given text and returns a value based on their occurrences.
 * 
 * @param text The `FindBeginEnd` function takes a `std::string` parameter named `text` which
 * represents a piece of text. The function searches for the occurrence of two specific substrings
 * within the text: "%%begin" and "%%end". It increments the result by 1 if "%%
 * 
 * @return The function `FindBeginEnd` returns an integer value that represents the balance of
 * occurrences of "%%begin" and "%%end" in the input `text`.
 */
int TabulationTxt::FindBeginEnd(std::string text)
{
    int res = 0;
    if (text.find("%%begin") != std::string::npos)
        res += 1;
    if (text.find("%%end") != std::string::npos)
        res -= 1;

    return res;
}

/**
 * The function `makeTabs` returns a string consisting of a specified number of tab characters.
 * 
 * @param count The `count` parameter in the `makeTabs` function represents the number of tab
 * characters that should be generated and returned as a string. If the `count` is less than or equal
 * to 0, an empty string is returned. Otherwise, a string containing `count` tab characters is created
 * 
 * @return If the `count` parameter is greater than 0, the function will return a `std::string`
 * consisting of `count` number of tab characters ('\t'). If `count` is less than or equal to 0, an
 * empty `std::string` will be returned.
 */
std::string TabulationTxt::makeTabs(int count)
{
    if (count <= 0)
        return std::string("");
    else
        return std::string(count,'\t');
}

/**
 * The function `Parse` reads lines from a text file, adds tabs based on certain conditions, and writes
 * the modified lines to an output file.
 */
void TabulationTxt::Parse()
{
    int count_begin = 0;

    while (std::getline(txtFille, line))
    {
        if (line.find("%%begin") != std::string::npos)
        {
            outFille << makeTabs(count_begin) << line << '\n';
            count_begin += FindBeginEnd(line);
        }else if (line.find("%%end") != std::string::npos)
        {
            count_begin += FindBeginEnd(line);
            outFille << makeTabs(count_begin) << line << '\n';
        } else
        {
            count_begin += FindBeginEnd(line);
            outFille << makeTabs(count_begin) << line << '\n';
        }
    }
}