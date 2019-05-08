#include <utility>
//
// Created by ivan on 21.04.19.
//

#include "../src/huffman.h"
#include <fstream>
#include <assert.h>
#include <sstream>

void FileManager::zip_bits_in_bytes(std::vector<bool> &bits, std::vector<byte_t> &result) {
    std::size_t bytes_size;
    if (bits.size() % 8 == 0) {
        bytes_size = bits.size();
    } else {
        bytes_size = bits.size() - (bits.size() % 8) + 8;
    }
    bits.resize(bytes_size, 0);
    result.reserve(bytes_size / 8);
    for (std::size_t i = 0; i < bits.size(); i += 8) {
        byte_t byte = bits[i + 0];
        for (std::size_t bit = 1; bit < 8; bit++) {
            byte = (byte << 1) | bits[i + bit];
        }
        result.push_back(byte);
    }
}

void FileManager::unzip_bytes_in_bits(std::vector<byte_t> &input, int len, std::vector<bool> &bits) {
    assert(input.size() > 0);
    byte_t extra_byte = input.back();
    input.pop_back();
    for (auto byte: input) {
        for (int i = 7; i >= 0; i--) {
            bits.push_back(byte & (1 << i));
        }
    }
    len -= input.size() * 8;
    for (int i = 0; i < std::min(len, 8); i++) {
        bits.push_back(extra_byte & (1 << (7 - i)));
    }
}


std::vector<byte_t> &FileManager::read_coding_file() {
    std::ifstream file(input_file, std::ios::binary);

    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);
    input_file_size = get_file_size(input_file);

    message.reserve(input_file_size);

    // read the data:
    message.insert(message.begin(),
                   std::istreambuf_iterator<byte_t>(file),
                   std::istreambuf_iterator<byte_t>());
    file.close();
    return message;
}


/** Function takes map (byte --> vector<bool>), which matches a bit set to a character
  * Write in output_file map, format:
  * <Number of characters to be encoded, int> Then for each character:
  * <Character, byte_t><Number of bits per character, byte_t><Bits encoding character padded up to bytes, byte_t>
  * <Size of the encoded message in bits, int>
  * Finally: Table size = 4 + C * 3 + 4, where C - number of characters to be coded
 **/
void FileManager::write_coded_message(std::map<byte_t, std::vector<bool>> & code) {
    std::ofstream out(output_file, std::ios::out| std::ios::binary);
    if (code.size() == 0) {
        return;
    }
    int table_size = code.size();
    out.write(reinterpret_cast<char*>(&table_size), sizeof(int));
    for (auto [key, value]: code)  {

        out.write(&key, sizeof(byte_t));

        byte_t len = static_cast<byte_t>(value.size());  // You can prove that the Huffman algorithm does not code
                                                         // Character over 255 bits
        out.write(&len, sizeof(byte_t));
        std::vector<byte_t> bytes;
        zip_bits_in_bytes(value, bytes);
        if (bytes.size() == 0) {
            throw FileManagerExceptions("PANIC: Can't write empty code. Error in zipping bytes.");
            // It is argued that this will never happen, so in this case
            // We urgently need to throw out exception and exit the program.
        }
        for (auto byte: bytes) {
            out.write(&byte, sizeof(byte_t));
        }
    }

    std::vector<bool> coded_msg;
    for (auto coded_character: message) {
        if (code.at(coded_character).size() == 0) {
            throw FileManagerExceptions("PANIC: Huffman Archiver generated empty code");
            // With the proper operation of HuffmanArchiver, this will NEVER happen.
            // If it happened, you need to panic
        }
        coded_msg.insert(coded_msg.end(), code.at(coded_character).begin(), code.at(coded_character).end());
    }

    int msg_size = coded_msg.size();
    out.write(reinterpret_cast<char*>(&msg_size), sizeof(int));

    this->table_size = out.tellp();

    std::vector<byte_t> bytes;
    zip_bits_in_bytes(coded_msg, bytes);
    for (auto byte: bytes) {
        out.write(&byte, sizeof(byte_t));
    }
    out.close();
    coded_file_size = get_file_size(output_file); // Total file size
    coded_file_size -= this->table_size;  // Without table size
}

/** The function reads the table, writes it to map: decode
 *  Then reads bytes from the file and returns a pair: vector of read bytes and size in bits
 *   In the case of an empty input file returns <empty vector, -1>
 */
std::pair<std::vector<byte_t>, int> FileManager::read_coded_file() {
    this->coded_file_size = get_file_size(input_file);
    if (this->coded_file_size == 0) {
        return {std::vector<byte_t>(), -1};
    }
    std::ifstream in(input_file, std::ios::binary);
    int table_size;
    in.read(reinterpret_cast<char*>(&table_size), sizeof(int));
    for (int i = 0; i < table_size; i++) {
        byte_t byte;
        in.read(&byte, sizeof(byte_t));
        byte_t signed_len;
        in.read(&signed_len, sizeof(byte_t));
        auto len = static_cast<unsigned char>(signed_len); // Range of lengths in bits (0, 256)
        std::vector<byte_t> bytes;

        int byte_len;
        if (len % 8 == 0) {
            byte_len = len / 8;
        } else {
            byte_len = len / 8 + 1;
        }

        for (int j = 0; j < byte_len; j++) {
            byte_t code;
            in.read(&code, sizeof(byte_t));
            bytes.push_back(code);
        }

        std::vector<bool> result;
        unzip_bytes_in_bits(bytes, len, result);
        decode[result] = byte;
    }
    int msg_size;
    in.read(reinterpret_cast<char*>(&msg_size), sizeof(int));
    this->table_size = in.tellg();
    this->coded_file_size -= this->table_size;

    int byte_len;
    if (msg_size % 8 == 0) {
        byte_len = msg_size / 8;
    } else {
        byte_len = msg_size / 8 + 1;
    }

    std::vector<byte_t> coded_message;
    for (int i = 0; i < byte_len; i++) {
        byte_t byte;
        in.read(&byte, sizeof(byte_t));
        coded_message.push_back(byte);
    }
    return {coded_message, msg_size};
}

byte_t FileManager::get_decoded_bits(std::vector<bool> &bits) {
    return decode[bits];
}


std::vector<byte_t> FileManager::decode_bytes(std::vector<byte_t> &coded_message, int bit_size) {
    std::vector<byte_t> decoded_message;
    std::vector<bool> bits;
    unzip_bytes_in_bits(coded_message, bit_size, bits);
    std::vector<bool> bit_prefix;
    for (int i = 0; i < bit_size; i++) {
        bit_prefix.push_back(bits[i]);
        if (decode.count(bit_prefix)) {
            decoded_message.push_back(decode[bit_prefix]);
            bit_prefix.clear();
        }
    }
    return decoded_message;
}

/** The function returns the size of the file.
 *  StackOverflow code that works great
 */
//  I wonder why in C++ there is no way to just know the file size.
std::streampos FileManager::get_file_size(std::string filename) {
    std::ifstream stream(filename, std::ios::binary);
    stream.ignore( std::numeric_limits<std::streamsize>::max() );
    std::streamsize length = stream.gcount();
    stream.clear();
    stream.seekg( 0, std::ios_base::beg );
    return length;
}

void FileManager::write_decoded_message(std::vector<byte_t> &decoded_message) {
    std::ofstream out(output_file, std::ios::binary);
    out.write(reinterpret_cast<char*>(&decoded_message[0]), decoded_message.size() * sizeof(byte_t));
    out.close();
    output_file_size = get_file_size(output_file);
}

int FileManager::get_input_file_size() const {
    return input_file_size;
}

int FileManager::get_coded_file_size() const {
    return coded_file_size;
}

int FileManager::get_table_size() const {
    return table_size;
}

int FileManager::get_output_file_size() const {
    return output_file_size;
}


TreeNode::TreeNode(TreeNode *parent, TreeNode *left,
                   TreeNode *right, int value, bool is_leaf, byte_t byte):
        parent(parent), left(left), right(right), value(value), is_leaf(is_leaf), byte(byte){};


HuffmanTree::HuffmanTree(std::map<byte_t, int> & frequencies) : frequencies(frequencies){}


void HuffmanTree::initialize_tree() {
    for (auto [key, value]: frequencies) {
        auto* node = new TreeNode(nullptr, nullptr, nullptr, value, true, key);
        references[key] = node;
        ordered_list.insert(std::make_pair(value, node));
    }
}


void HuffmanTree::build_tree() {
    initialize_tree();
    while (ordered_list.size() > 1) {
        auto left = ordered_list.begin()->second;
        ordered_list.erase(ordered_list.begin());
        auto right = ordered_list.begin()->second;
        ordered_list.erase(ordered_list.begin());
        auto* parent = new TreeNode(nullptr, left, right, left->value + right->value, false, 0);
        left->parent = parent;
        right->parent = parent;
        ordered_list.insert(std::make_pair(parent->value, parent));
    }
}


TreeNode *HuffmanTree::get_root() {
    if (ordered_list.empty()) {
        throw HuffmanTreeExceptions("Root Not Found. Tree is empty");
    }
    return ordered_list.begin()->second;
}


/** The function starts from the root and recursively deletes the entire tree.
 */
//  Works great! Smarter than smart pointers.
void HuffmanTree::delete_tree(TreeNode* v) {
    if (v->left == nullptr && v->right == nullptr) {
        delete(v);
        return;
    }
    delete_tree(v->left);
    delete_tree(v->right);
    delete(v);
}


HuffmanTree::~HuffmanTree() {
    delete_tree(get_root());
}


HuffmanArhiver::HuffmanArhiver(std::vector<byte_t > &bytes): bytes(std::move(bytes)) {}


void HuffmanArhiver::calculate_frequencies() {
    for (auto byte: bytes) {
        if (!frequencies.count(byte)) {
            frequencies[byte] = 1;
        } else {
            frequencies[byte] = frequencies[byte] + 1;
        }
    }
}


void HuffmanArhiver::dfs(TreeNode* v, std::vector<bool> &prefix_code) {
    if (v->is_leaf) {
        code[v->byte] = prefix_code;
    } else {
        prefix_code.push_back(0);
        dfs(v->left, prefix_code);
        prefix_code.pop_back();
        prefix_code.push_back(1);
        dfs(v->right, prefix_code);
        prefix_code.pop_back();
    }
}


std::map<byte_t, std::vector<bool>> & HuffmanArhiver::encode() {
    calculate_frequencies();
    HuffmanTree huffmanTree(frequencies);
    huffmanTree.build_tree();
    std::vector<bool> prefix_code = {};
    if (huffmanTree.get_root() -> left == nullptr && huffmanTree.get_root() -> right == nullptr) {
        if (huffmanTree.get_root() != nullptr) {
            code[huffmanTree.get_root()->byte] = std::vector<bool>({0}); // The tree consists only of the root
        } else {
            throw HuffmanArchiverExceptions("Bytes to code not found");  // Empty tree
        }
    } else dfs(huffmanTree.get_root(), prefix_code);
    return code;
}
