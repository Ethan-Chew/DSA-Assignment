#include <iostream>
#include <filesystem>
#include <fstream>
#include <functional>

#include "DataParser.h"

// enum for possible types
enum class ColumnType {
    INT,
    STRING,
    DOUBLE
};

// header struct caller must pass to provide context to parser
struct HeaderSpec {
    std::string name;
    ColumnType type;
    HeaderSpec(const std::string &n, ColumnType t) : name(n), type(t) {}
};


class DataParser {
private:
    int headerCount = 0;
    std::ifstream file;
    // mapping of offset to header name, useful for knowing which header stores what
    MyDict<int, std::string> headerOffsets;
    // mapping of header name to type, again useful for knowing what datatype to reinterpret/cast as
    MyDict<std::string, ColumnType> headerTypes;
    // insanely ugly, but this boils down to a unique_ptr with a custom function passed as the destructor
    // think: 
    //  data = MyDict<Tk, Tv> 
    //  dtor = void foo(data) { ... free data ... }
    // imperative that the unique_ptr has the destructor as the unique_ptr ownership will be forwarded to caller
    // to allow DataParser to be safely destructed
    // std::function is just the type used by C++ to indicate that something is a function
    // std::function<Tr(MyDict<Tk, Tv>*)> where r=return, k=key and v=val, Dict is a ptr because unique_ptr does store the pointer internally
    std::unique_ptr<MyDict<std::string, void*>, std::function<void(MyDict<std::string, void*>*)>> result;
    // shared in class for init

    void ParseHeader() {
         // base case
    }

    // for the sake of handling variadic arguments i use recursion
    // this maps each header name to the type passed via HeaderSpec
    template<typename FirstHeader, typename... OtherHeaders>
    void ParseHeader(FirstHeader first, OtherHeaders... others) {
        headerTypes[first.name] = first.type;
        (*result)[first.name] = nullptr;
        ParseHeader(others...);
    }

    // splits a line into tokens
    // basically line.split(',') but quote aware
    MyList<std::string> TokeniseLine(const std::string &buf) {
   		MyList<std::string> tokens;
        std::string token;
        const size_t len = buf.length();
        // preallocate worst case memory use
        token.reserve(len);

        for (size_t i = 0; i < len; i++) {
            const char chr = buf[i];
            if (chr == '\"') {
                i++;
                while (i < len && buf[i] != '\"') {
                    token += buf[i];
                    i++;
                }
                continue;
            }

            if (chr != ',') {
                // treat semicolon as comma
                token += (chr == ';' ? ',' : chr);
                continue;
            }

            tokens.append(std::move(token));
            token.clear();
        }
        // last token
        !token.empty() ? tokens.append(std::move(token)) : void();
        return tokens;
    }

    // find offset required to reach header x for all x in the header list
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
        // lambda function passed to unique_ptr to handle cleanup
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

            // discard malformed inputs
            if (tokens.get_length() != headerCount) continue;
            for (int currentOffset = 0; currentOffset < tokens.get_length(); currentOffset++) {
                currentColumn = headerOffsets[currentOffset];

                // excessively complex system to fit everything into 1 hashmap
                // nested templating is too complex, and all pointers can be stored as a void* (64 bit address)
                // and reinterpreted back to what it should be based on the header type mapping
                // quite hacky, please don't touch, this works well and that's all you must know
                // the benefit is that the output can easily be accessed via result[header] reinterpreted
                if ((*result)[currentColumn] == nullptr) { // if there's no header mapping, we make one
                    switch (headerTypes[currentColumn]) {
                        case ColumnType::INT:
                            tempInt = new MyList<int>();
                            tempInt->append(std::stoi(tokens[currentOffset]));
                            (*result)[currentColumn] = reinterpret_cast<void *>(tempInt); // reinterpret into void* so it can be regarded as the same type as the dict Tk
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

        // imperative to give ownership to caller
        // to prevent class destructor from deleting data or double freeing
        return std::move(result);
    }

    void SaveFile(std::unique_ptr<MyDict<std::string, void*>, std::function<void(MyDict<std::string, void*>*)>>) {

    }
};
