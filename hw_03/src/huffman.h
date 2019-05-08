//
// Created by ivan on 21.04.19.
//

#ifndef HW_03_HUFFMAN_H
#define HW_03_HUFFMAN_H

#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <algorithm>
#include <iostream>

typedef char byte_t;
/// This class gets file and parse it to bytes and vice versa
class KekManager {
    int x;
};
class FileManager {
public:
    FileManager(std::string input_file, std::string output_file): input_file(input_file), output_file(output_file) {}

    std::vector<byte_t> & read_coding_file();
    std::pair<std::vector<byte_t>, int> read_coded_file();
    void write_coded_message(std::map<byte_t, std::vector<bool>> &code);
    void write_decoded_message(std::vector<byte_t> &decoded_message);

    void zip_bits_in_bytes(std::vector<bool> &bits, std::vector<byte_t> &result);
    void unzip_bytes_in_bits(std::vector<byte_t> &input, int len, std::vector<bool> &bits);
    byte_t get_decoded_bits(std::vector<bool> &bits);

    std::vector<byte_t> decode_bytes(std::vector<byte_t> &code_message, int bit_size);

    int get_input_file_size() const;

    int get_coded_file_size() const;

    int get_table_size() const;

    int get_output_file_size() const;

private:
    int input_file_size;
    int coded_file_size;
    int table_size;
    int output_file_size;
    class FileManagerExceptions: public std::exception{
    public:
        const char* what() const noexcept{
            return (error_message).c_str();
        }
        explicit FileManagerExceptions(std::string error_message) {
            this->error_message = "File IO exception: " + error_message;
        }
    private:
        std::string error_message;
    };
    std::streampos get_file_size(std::string filename);
    std::map<std::vector<bool>, byte_t> decode;
    std::string input_file;
    std::string output_file;
    //std::vector<byte_t> bytes;
    std::vector<byte_t> message;
};



class TreeNode {
public:
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    int value{};
    bool is_leaf;
    byte_t byte{};
    TreeNode(TreeNode* parent = nullptr, TreeNode* left = nullptr,
             TreeNode* right = nullptr, int value = 0, bool is_leaf = false, byte_t byte = 0);
};

class HuffmanTree {
protected:
    class HuffmanTreeExceptions: public std::exception{
    public:
        const char* what() const noexcept{
            return (error_message).c_str();
        }
        explicit HuffmanTreeExceptions(std::string error_message) {
            this->error_message = "HuffmanTree exception: " + error_message;
        }
    private:
        std::string error_message;
    };
    std::map<byte_t, int> frequencies;
    std::map<byte_t, TreeNode*> references;
    std::set<std::pair<int, TreeNode*>> ordered_list;
    void initialize_tree();
    void delete_tree(TreeNode* v);
public:
    HuffmanTree(std::map<byte_t, int> &frequencies);
    void build_tree();
    TreeNode* get_root();
    ~HuffmanTree();
};



class HuffmanArhiver {
protected:
    class HuffmanArchiverExceptions: public std::exception{
    public:
        const char* what() const noexcept{
            return (error_message).c_str();
        }
        explicit HuffmanArchiverExceptions(std::string error_message) {
            this->error_message = "HuffmanArchiver exception: " + error_message;
        }
    private:
        std::string error_message;
    };
    std::map<byte_t, int> frequencies;
    std::map<byte_t, std::vector<bool>> code;
    std::vector<byte_t> bytes;
    void dfs(TreeNode* v, std::vector<bool> &prefix_code);
public:
    void calculate_frequencies();
    int get_frequencie(byte_t byte) {return frequencies[byte];}
    HuffmanArhiver(std::vector<byte_t> &v);
    std::map<byte_t, std::vector<bool>> &encode();
    std::vector<bool>& get_code(byte_t byte) {return code[byte];}
    ~HuffmanArhiver() {}
};
#endif //HW_03_HUFFMAN_H