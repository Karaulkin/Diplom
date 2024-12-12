#ifndef PARSERJSONPROJECT_PARSER_JSON_H
#define PARSERJSONPROJECT_PARSER_JSON_H

#include "single_include/nlohmann/json.hpp"

using json = nlohmann::json;

    class ParserJson
    {
    private:
        std::ifstream* FilleNameJson;
        std::ofstream* FilleNameTxt;

        json JData; // full file >> JSON || Something key >> JData

        std::string begin = " %%begin";
        std::string end = "%%end";

        template<class BinaryFunction>
        void recursive_iterate(const json& j, BinaryFunction f, const std::string& parent_key = ""); // реекурсивная

        void printStruct(json::const_iterator it, const std::string& parent_key);



    public:
        ParserJson(std::ifstream& FilleJson, std::ofstream& FilleTxt); // по потоку чтения и записи

        void Parse();

        ~ParserJson();
    };
#endif // PARSERJSONPROJECT_PARSER_JSON_H