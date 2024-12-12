#include <iostream>
#include <fstream>

#include "ParserJSON/parser_json.h"
#include "Tabulation/tabulation.h"

int main() {
    // std::string NameJson = "../example.json";
    // std::string NameTxt = "example.txt";
    std::string NameJson = "../test_usertask.json";
    std::string NameTxt = "test_usertask.txt";

    /// Создан поток
    std::ifstream fille_json = std::ifstream(NameJson);
    std::ofstream fille_txt = std::ofstream(NameTxt, std::ios::app);

    /// Создан параметр
    ParserJson p(fille_json, fille_txt);


    p.Parse(); // TODO(katinaka): возвращать имя файла и путь, желатьльно создавать с именем который пришёл на вход

    /// Закрыт поток
    fille_json.close();
    fille_txt.close();

    // formating txt
    TabulationTxt t(NameTxt);
    // TODO(katinaka): приятный кронструктор который будет вежлив к предачи просто файлов и пути к файлу

    t.Parse();

    // TODO(katinaka): GoogleTests, возможно автоматическая документация

    return 0;
}