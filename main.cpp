#include <iostream>

#include "DataParser.h"

int main()
{
    DataParser testParser(
            "./data/test.csv",
            HeaderSpec("tegfnfst", ColumnType::INT),
            HeaderSpec("skbiditoilet", ColumnType::STRING)
            );

    auto testResult = testParser.ParseData();
    auto *row1 = reinterpret_cast<MyList<int>*>((*testResult)["tegfnfst"]);
    auto *row2 = reinterpret_cast<MyList<std::string>*>((*testResult)["skbiditoilet"]);

    row1->print();
    row2->print();

    DataParser parser(
            "./data/actors.csv",
            HeaderSpec("id", ColumnType::INT),
            HeaderSpec("name", ColumnType::STRING),
            HeaderSpec("birth", ColumnType::INT));

    auto result = parser.ParseData();

    auto *names = reinterpret_cast<MyList<std::string>*>((*result)["name"]);
    auto *ids = reinterpret_cast<MyList<int>*>((*result)["id"]);
    auto *birth = reinterpret_cast<MyList<int>*>((*result)["birth"]);

    std::cout << std::endl;


    for (int i = 0; i < names->get_length(); i++) {
        std::cout
                << "row" << std::setw(2) << i+1 << ": "
                << std::setw(8) << ids->get(i)
                << std::setw(20) << std::left << names->get(i)
                << std::setw(6) << birth->get(i)
                << "\n";
    }
    return 0;
}