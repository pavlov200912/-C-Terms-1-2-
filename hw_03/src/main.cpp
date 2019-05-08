#include <utility>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include "huffman.h"
#include <fstream>
#include <assert.h>

class CLParser {
public:
    CLParser(int argc, char** argv): argc_(argc), argv_(argv) {}
    void parse() {
        input_file = "";
        output_file = "";
        if (argc_ != 6) {
            throw ParserExceptions("Not enough arguments");
        }
        for (int i = 1; i < argc_; i++) {
            if (strcmp(argv_[i], "-u") == 0) {
                code_ = false;
            } else if (strcmp(argv_[i], "-c") == 0) {
                code_ = true;
            } else if (strcmp(argv_[i], "-f") == 0 || strcmp(argv_[i], "--file") == 0) {
                if (i == argc_ - 1)
                    throw ParserExceptions("Unable to find input filename");
                if (!input_file.empty()) {
                    throw ParserExceptions("Double -f undefined");
                }
                input_file = argv_[++i];
            } else if (strcmp(argv_[i], "-o") == 0 || strcmp(argv_[i], "--output") == 0) {
                if (i == argc_ - 1)
                    throw ParserExceptions("Unable to find output filename");
                if (!output_file.empty()) {
                    throw ParserExceptions("Double -o undefined");
                }
                output_file = argv_[++i];
            } else {
                throw ParserExceptions("Unknown argument: " + std::string(argv_[i]));
            }
        }
    }
    bool is_coding() {return code_;}
    std::string get_input_file() { return input_file;}
    std::string get_output_file() { return output_file;}
private:
    class ParserExceptions: public std::exception{
    public:
        const char* what() const noexcept{
            return (error_message).c_str();
        }
        explicit ParserExceptions(std::string error_message) {
            this->error_message = "ParserException: " + error_message;
        }
    private:
        std::string error_message;
    };
    int argc_;
    char **argv_;
    bool code_{};
    std::string input_file;
    std::string output_file;
};

int main(int argc, char* argv[]) {
    CLParser parser(argc, argv);
    try {
        parser.parse();
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 0;
    }
    try {
        FileManager fileManager(parser.get_input_file(), parser.get_output_file());
        if (parser.is_coding()) {
            std::vector<byte_t> v = fileManager.read_coding_file();
            if (v.size() == 0) {
                // Empty input file
                std::cout << "0\n0\n0\n";
                std::ofstream empty(parser.get_output_file()); // Zero output file
                empty.close();
                return 0;
            }
            HuffmanArhiver huffmanArhiver(v);
            std::map<byte_t, std::vector<bool>> code = huffmanArhiver.encode();
            fileManager.write_coded_message(code);
            std::cout << fileManager.get_input_file_size() << '\n';
            std::cout << fileManager.get_coded_file_size() << '\n';
            std::cout << fileManager.get_table_size() << '\n';
        } else {
            auto[coded_message, bit_size] = fileManager.read_coded_file();
            if (bit_size == -1) {  // This is not a crutch, I wrote everything in the documentation.
                // Empty input file
                std::cout << "0\n0\n0\n";
                std::ofstream empty(parser.get_output_file());  // Zero output file
                empty.close();
                return 0;
            }
            std::vector<byte_t> decoded_message = fileManager.decode_bytes(coded_message, bit_size);
            fileManager.write_decoded_message(decoded_message);
            std::cout << fileManager.get_coded_file_size() << '\n';
            std::cout << fileManager.get_output_file_size() << '\n';
            std::cout << fileManager.get_table_size() << '\n';
        }
    } catch (std::exception &e) {
        std::cout << e.what() << '\n';
    }
}
