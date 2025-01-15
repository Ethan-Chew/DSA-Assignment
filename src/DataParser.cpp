#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>

#include "MyLinkedList.h"
#include "MyList.h"
#include "MyDict.h"

enum class ColumnType {
    INT,
    STRING,
    DOUBLE
};

struct HeaderSpec {
    std::string name;
    ColumnType type;
    HeaderSpec(const std::string &n, ColumnType t) : name(n), type(t) {}
};


template<typename... Ts>
class DataParser {
private:
    std::ifstream file;
    MyDict<std::string, int> headerOffsets;
    MyDict<std::string, ColumnType> headerTypes;

    void ParseHeader() {
         // base case
    }

    template<typename FirstHeader, typename... OtherHeaders>
    void ParseHeader(FirstHeader first, OtherHeaders... others) {
        headerTypes[first.name] = first.type;
        ParseHeader(others...);
    }

public:
    template<typename... Headers>
    DataParser(const std::string &filename, Headers... headers) {
         file.open(filename);
         if (!file.is_open()) {
             throw std::runtime_error("can't find required file: " + filename);
         }

         ParseHeader(headers...);
    }

    ~DataParser() {
        file.close();
    }

    void ParseData(MyDict<std::string, void*> &data) {
        for (const auto &typePair : headerTypes) {

        }
    }
};