//
// Created by kirill on 09.05.24.
//
#ifndef PARSERJSONPROJECT_TABULATION_H
#define PARSERJSONPROJECT_TABULATION_H

class TabulationTxt {
    private:
        std::string temp = "out.txt";
        std::string FilleTxt;
        std::ifstream txtFille;
        std::ofstream outFille;
        std::string line;

        int FindBeginEnd(std::string text);

        std::string makeTabs(int count);

        void rename(std::string txtName);

    public:
        TabulationTxt(std::string Fille);
        TabulationTxt(std::string  Fille, std::string &temp_fille);

        void Parse();

        ~TabulationTxt();
};


#endif //PARSERJSONPROJECT_TABULATION_H
