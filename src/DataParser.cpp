#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>
#include <functional>

#include "DataParser.h"

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


class DataParser {
private:
    int headerCount = 0;
    std::ifstream file;
    MyDict<int, std::string> headerOffsets;
    MyDict<std::string, ColumnType> headerTypes;
    std::unique_ptr<MyDict<std::string, void*>, std::function<void(MyDict<std::string, void*>*)>> result;
 // shared in class for init

    void ParseHeader() {
         // base case
    }

    template<typename FirstHeader, typename... OtherHeaders>
    void ParseHeader(FirstHeader first, OtherHeaders... others) {
        headerTypes[first.name] = first.type;
        (*result)[first.name] = nullptr;
        ParseHeader(others...);
    }

    MyList<std::string> TokeniseLine(const std::string &buf) {
   		MyList<std::string> tokens;
        std::string token;
		bool quote = false;

        for (const char &chr : buf) {
         	if (chr == '\"') {
                quote = !quote;
                continue;
            }
			if ((chr != ',') || quote) {
            	token += chr;
                continue;
            }

            tokens.append(token);
			token = "";
        }
        // last token
        !token.empty() ? tokens.append(token) : void();
        return tokens;
    }

    void InitHeaderOffset(const std::string &buf) {
        MyList<std::string> tokens = TokeniseLine(buf);

        for (const std::string &token : tokens) {
            headerOffsets[headerCount] = token;
            headerCount++;
        }
    }



public:
    template<typename... Headers>
    DataParser(const std::string &filename, Headers... headers)
    : result(new MyDict<std::string, void*>,
        [this](MyDict<std::string, void*>* dict) {
         for (int i = 0; i < headerCount; i++) {
             void* store = (*dict)[headerOffsets[i]];
             switch(headerTypes[headerOffsets[i]]) {
                 case ColumnType::INT:
                     delete reinterpret_cast<MyList<int>*>(store);
                     break;
                 case ColumnType::DOUBLE:
                     delete reinterpret_cast<MyList<double>*>(store);
                     break;
                 case ColumnType::STRING:
                     delete reinterpret_cast<MyList<std::string>*>(store);
                     break;
             }
         }
         delete dict;
        }){

        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("can't find required file: " + std::filesystem::absolute(filename).string());
        }

        ParseHeader(headers...);
    }

    ~DataParser() {
        file.close();
    }

    std::unique_ptr<MyDict<std::string, void*>, std::function<void(MyDict<std::string, void*>*)>> ParseData() {
        std::string currentColumn;
      	std::string buffer;

        // early var init for switch case
        MyList<int> *tempInt;
        MyList<double> *tempDouble;
        MyList<std::string> *tempString;

        std::getline(file, buffer);
      	InitHeaderOffset(buffer);

        while (!file.eof()) {
            std::getline(file, buffer);
            MyList<std::string> tokens = TokeniseLine(buffer);
            for (int currentOffset = 0; currentOffset < tokens.get_length(); currentOffset++) {
                currentColumn = headerOffsets[currentOffset];
                if ((*result)[currentColumn] == nullptr) {
                    switch (headerTypes[currentColumn]) {
                        case ColumnType::INT:
                            tempInt = new MyList<int>();
                            tempInt->append(std::stoi(tokens[currentOffset]));
                            (*result)[currentColumn] = reinterpret_cast<void *>(tempInt);
                            break;
                        case ColumnType::DOUBLE:
                            tempDouble = new MyList<double>();
                            tempDouble->append(std::stod(tokens[currentOffset]));
                            (*result)[currentColumn] = reinterpret_cast<void *>(tempDouble);
                            break;
                        case ColumnType::STRING:
                            tempString = new MyList<std::string>();
                            tempString->append(tokens[currentOffset]);
                            (*result)[currentColumn] = reinterpret_cast<void *>(tempString);
                            break;
                    }
                } else {
                    switch (headerTypes[currentColumn]) {
                        case ColumnType::INT:
                            reinterpret_cast<MyList<int>*>((*result)[currentColumn])->append(std::stoi(tokens[currentOffset]));
                            break;
                        case ColumnType::DOUBLE:
                            reinterpret_cast<MyList<double>*>((*result)[currentColumn])->append(std::stod(tokens[currentOffset]));
                            break;
                        case ColumnType::STRING:
                            reinterpret_cast<MyList<std::string>*>((*result)[currentColumn])->append(tokens[currentOffset]);
                            break;
                    }
                }
            }
        }

        return std::move(result);
    }
};