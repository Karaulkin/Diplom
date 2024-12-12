#include "parser_json.h"

#include <iostream>
#include <fstream>
#include <string>

/**
 * The function `ParserJson` takes an input JSON file and an output text file, reads the JSON data, and
 * stores it for further processing.
 * 
 * @param FilleJson `FilleJson` is a reference to an input file stream (`std::ifstream`) that is used
 * to read a JSON file.
 * @param FilleTxt The `FilleTxt` parameter is a reference to an `std::ofstream` object, which is used
 * for writing data to a file. In the provided code snippet, it is being assigned to the `FilleNameTxt`
 * member variable of the `ParserJson` class.
 */
ParserJson::ParserJson(std::ifstream& FilleJson, std::ofstream& FilleTxt)
{
    FilleNameTxt = &FilleTxt;
    FilleNameJson = &FilleJson;

    if (!*FilleNameJson) {
        // throw
        std::cerr << "Not found json." << std::endl;
    }

    this->JData = json::parse(*FilleNameJson);
}

/**
 * The above function is the destructor for the ParserJson class in C++.
 */
ParserJson::~ParserJson()
{}

/**
 * The `recursive_iterate` function in the `ParserJson` class is a recursive function that iterates
 * over a JSON object or array and performs certain actions based on the type of the JSON element. Here
 * is a breakdown of what the function does:
 */
template<class BinaryFunction>
void ParserJson::recursive_iterate(const json& j, BinaryFunction f, const std::string& parent_key)
{
    for(auto it = j.begin(); it != j.end(); ++it)
    {
        //std::string key = it.key();

        if (it->is_object())
        {
            std::string key = it.key();
            *FilleNameTxt << it.key() << " =" << begin << '\n';
            recursive_iterate(*it, f, key);
            *FilleNameTxt << end << '\n';
        }
        else if (it->is_array())
        {
            //*FilleNameTxt << key << " =" << begin << '\n';
            //std::string key = it.key();

            bool alotLevels = true;

            if ((*it)[0].is_primitive()) {
                alotLevels = false;
                *FilleNameTxt << it.key() << " =" << begin << '\n';
            }

            if (it->size() > 1) {

                for (size_t i = 0; i < it->size(); ++i)
                {
                    if (alotLevels) {
                        *FilleNameTxt << it.key() << "[" << std::to_string(i+1) << "] =" << begin << '\n';
                    }

                    //recursive_iterate((*it)[i], f, it.key());
                    // recursive_iterate((*it)[i], f, "simple_array");

                    if ((*it)[i].is_object() || (*it)[i].is_array()) {
                        recursive_iterate((*it)[i], f, "hard_array");
                    }

                    if ((*it)[i].is_primitive()) {
                        recursive_iterate((*it)[i], f, "simple_array");
                    }

                    if (alotLevels) {
                        *FilleNameTxt << end << '\n';
                    }
                }
            } else {
                *FilleNameTxt << it.key() << " =" << begin << '\n';

                recursive_iterate((*it)[0], f, it.key());
                //recursive_iterate((*it)[0], f, it.key());
                // recursive_iterate((*it)[0], f, parent_key);

                *FilleNameTxt << end << '\n';
            }
            if (alotLevels == false) {
                *FilleNameTxt << end << '\n';
            }
        }
        else
        {
            f(it, parent_key);
        }
    }
}




/**
 * The Parse function iterates through a JSON object and prints key-value pairs to a text file.
 */
void ParserJson::Parse()
{
    recursive_iterate(this->JData, [this](json::const_iterator it, const std::string& parent_key)
    {

        //if (it->is_object()) {
            //*FilleNameTxt << it.key << " = " << it.value() << '\n';
        //} else {
       //     *FilleNameTxt << it.value() << '\n';
        //}
        if (parent_key == "simple_array" && it->is_string() ) {
            *FilleNameTxt << it.value().get<std::string>() << '\n';
        } else {
            if (it->is_string() ) {
                *FilleNameTxt << it.key() << " = " << it.value().get<std::string>() << '\n';
            } else {
                *FilleNameTxt << it.key() << " = " << it.value() << '\n';
            }
        }
    });
}
