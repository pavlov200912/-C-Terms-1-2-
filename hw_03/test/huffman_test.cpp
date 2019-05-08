//
// Created by ivan on 21.04.19.
//

#include "huffman_test.h"
#include <fstream>

// Check Tree Structure
void HuffmanTest::test_huffman_tree_builder() {
    std::map<byte_t, int> input = {{'a',2}, {'b', 3}, {'c', 4}};
    HuffmanTree huffmanTree(input);
    huffmanTree.build_tree();
    // Left is always should be the smallest one
    DO_CHECK(huffmanTree.get_root()->value == 2 + 3 + 4);
    DO_CHECK(huffmanTree.get_root()->left->value == 4);
    DO_CHECK(huffmanTree.get_root()->right->value == 2 + 3);
    DO_CHECK(huffmanTree.get_root()->right->left->value == 2);
    DO_CHECK(huffmanTree.get_root()->right->right->value == 3);
}

void HuffmanTest::test_huffman_tree_get_root() {
    std::map<byte_t, int> input = {{'a',2}, {'b', 3}, {'c', 4}, {'d', 10}, {'e', 1}};
    HuffmanTree huffmanTree(input);
    huffmanTree.build_tree();
    DO_CHECK(huffmanTree.get_root()->value == 2 + 3 + 4 + 10 + 1);
}

void HuffmanTest::test_huffman_archiver_calculate_frequencies() {
    std::vector<char> v = {'a','a','a', 'b','b', 'c', 0, 1, 127};
    HuffmanArhiver huffmanArhiver(v);
    huffmanArhiver.calculate_frequencies();
    DO_CHECK(huffmanArhiver.get_frequencie('a') == 3);
    DO_CHECK(huffmanArhiver.get_frequencie('b') == 2);
    DO_CHECK(huffmanArhiver.get_frequencie('c') == 1);
    DO_CHECK(huffmanArhiver.get_frequencie(1) == 1);
    DO_CHECK(huffmanArhiver.get_frequencie(0) == 1);
    DO_CHECK(huffmanArhiver.get_frequencie(127) == 1);
}

void HuffmanTest::test_huffman_archiver_encode() {
    std::vector<char> v = {5, 5, 5, 5, 5, 1, 3, 3, 3, 6, 6, 6, 6, 6, 6};
    HuffmanArhiver huffmanArhiver(v);
    huffmanArhiver.encode();
    DO_CHECK(huffmanArhiver.get_code(6) == std::vector<bool>({0}));
    DO_CHECK(huffmanArhiver.get_code(5) == std::vector<bool>({1, 1}));
    DO_CHECK(huffmanArhiver.get_code(3) == std::vector<bool>({1, 0, 1}));
    DO_CHECK(huffmanArhiver.get_code(1) == std::vector<bool>({1, 0, 0}));
}

void HuffmanTest::test_file_manager_zip_bits_in_bytes() {
    std::vector<bool> v1 = {1, 0, 1, 1, 0, 1, 0, 0};
    FileManager fileManager("", "");
    std::vector<byte_t> result;
    fileManager.zip_bits_in_bytes(v1, result);
    DO_CHECK(result.size() == 1);
    DO_CHECK(result.at(0) == -76);
    std::vector<bool> v2 = {0, 0, 1, 1, 0, 1, 0, 0, 0, 1};
    result.clear();
    fileManager.zip_bits_in_bytes(v2, result);
    DO_CHECK(result.size() == 2);
    DO_CHECK(result.at(0) == 52);
    DO_CHECK(result.at(1) == 64);
}

void HuffmanTest::test_file_manager_unzip_bytes_in_bits() {
    std::vector<byte_t> v = {1, -76, 52, 64, };
    std::vector<bool> result;
    FileManager fileManager("","");
    fileManager.unzip_bytes_in_bits(v, 24 + 2, result);
    DO_CHECK(result == std::vector<bool>({
        0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 1, 0, 1, 0, 0,
        0, 0, 1, 1, 0, 1, 0, 0,
        0, 1
    }));

}

void HuffmanTest::test_file_manager_write_coded_message_table() {
    std::map<byte_t, std::vector<bool>> code = {{'a', std::vector<bool>({0, 0, 1})},
                                                {'b', std::vector<bool>({0, 1, 0})}};
    FileManager fileManager("test.txt", "text.txt");
    fileManager.write_coded_message(code);
    std::ifstream in("text.txt", std::ios::binary);

    in.ignore( std::numeric_limits<std::streamsize>::max() ); // Some magic
    std::streamsize length = in.gcount();
    in.clear();
    in.seekg( 0, std::ios_base::beg );
    DO_CHECK(length == sizeof(int) + 2 * 3 + sizeof(int));

    int table_size;
    in.read((char*)&table_size, sizeof(int));
    DO_CHECK(table_size == 2);
    byte_t byte_a;
    in.read(&byte_a, sizeof(byte_t));
    DO_CHECK(byte_a == 'a');
    byte_t len_a;
    in.read(&len_a, sizeof(byte_t));
    DO_CHECK(len_a == 3);
    byte_t code_a;
    in.read(&code_a, sizeof(byte_t));
    DO_CHECK(code_a == 32);
    byte_t byte_b;
    in.read(&byte_b, sizeof(byte_t));
    DO_CHECK(byte_b == 'b');
    byte_t len_b;
    in.read(&len_b, sizeof(byte_t));
    DO_CHECK(len_b == 3);
    byte_t code_b;
    in.read(&code_b, sizeof(byte_t));
    DO_CHECK(code_b == 64);
    int msg_size;
    in.read((char *)&msg_size, sizeof(int));
    DO_CHECK(msg_size == 0);
    in.close();
}

void HuffmanTest::test_file_manager_write_coded_message_stronger() {
    std::ofstream out("test.txt");
    out << "aaabba";
    out.close();

    std::map<byte_t, std::vector<bool>> code = {{'a', std::vector<bool>({0})},
                                                {'b', std::vector<bool>({1})}};
    FileManager fileManager("test.txt", "test.bin");
    fileManager.read_coding_file();
    fileManager.write_coded_message(code);
    std::ifstream in("test.bin", std::ios::binary);

    in.ignore( std::numeric_limits<std::streamsize>::max() ); // Some magic
    std::streamsize length = in.gcount();
    in.clear();
    in.seekg( 0, std::ios_base::beg );
    DO_CHECK(length == sizeof(int) + 3 * 2 + sizeof(int) + 1);

    int table_size;
    in.read((char*)&table_size, sizeof(int));
    DO_CHECK(table_size == 2);
    byte_t byte_a;
    in.read(&byte_a, sizeof(byte_t));
    DO_CHECK(byte_a == 'a');
    byte_t len_a;
    in.read(&len_a, sizeof(byte_t));
    DO_CHECK(len_a == 1);
    byte_t code_a;
    in.read(&code_a, sizeof(byte_t));
    DO_CHECK(code_a == char(0));
    byte_t byte_b;
    in.read(&byte_b, sizeof(byte_t));
    DO_CHECK(byte_b == 'b');
    byte_t len_b;
    in.read(&len_b, sizeof(byte_t));
    DO_CHECK(len_b == 1);
    byte_t code_b;
    in.read(&code_b, sizeof(byte_t));
    DO_CHECK(code_b == char(128));
    int msg_size;
    in.read((char*)&msg_size, sizeof(int));
    DO_CHECK(msg_size == 6);
    byte_t msg;
    in.read(&msg, sizeof(byte_t));
    DO_CHECK(msg == (8 + 16));
    in.close();
}

void HuffmanTest::test_file_manager_code_one_byte() {
    std::ofstream of("test.txt");
    of << 'a';
    of.close();

    std::map<byte_t, std::vector<bool>> code = {{'a', std::vector<bool>({0, 0, 1})}};
    FileManager fileManager("test.txt", "test.bin");
    fileManager.read_coding_file();
    fileManager.write_coded_message(code);
    std::ifstream in("test.bin", std::ios::binary);

    in.ignore( std::numeric_limits<std::streamsize>::max() ); // Some magic
    std::streamsize length = in.gcount();
    in.clear();
    in.seekg(0, std::ios_base::beg );
    DO_CHECK(length == sizeof(int) + 3 * 1 + sizeof(int) + 1);

    int table_size;
    in.read((char*)&table_size, sizeof(int));
    DO_CHECK(table_size == 1);
    byte_t byte_a;
    in.read(&byte_a, sizeof(byte_t));
    DO_CHECK(byte_a == 'a');
    byte_t len_a;
    in.read(&len_a, sizeof(byte_t));
    DO_CHECK(len_a == 3);
    byte_t code_a;
    in.read(&code_a, sizeof(byte_t));
    DO_CHECK(code_a == 32);
    int msg_size;
    in.read((char*)&msg_size, sizeof(int));
    DO_CHECK(msg_size == 3);
    byte_t msg;
    in.read(&msg, sizeof(byte_t));
    DO_CHECK(msg == 32);
    in.close();

}

// Not Unit Test
void HuffmanTest::test_file_manager_read_coded_file() {
    std::ofstream out("test.txt");
    out << "aaabba";
    out.close();
    std::map<byte_t, std::vector<bool>> code = {{'a', std::vector<bool>({0, 0, 1})},
                                                {'b', std::vector<bool>({0, 1, 0})}};
    FileManager writer("test.txt", "test.bin");
    writer.read_coding_file();
    writer.write_coded_message(code);
    FileManager reader("test.bin", "test.txt");
    auto [coded, sz] = reader.read_coded_file();
    DO_CHECK(sz == 6 * 3);
    DO_CHECK(reader.get_decoded_bits(code['a']) == 'a');
    DO_CHECK(reader.get_decoded_bits(code['b']) == 'b');
    DO_CHECK(coded.size() == 3);
    DO_CHECK(coded.at(0) == 36); // 00100100
    DO_CHECK(coded.at(1) == char(4 + 32 + 128)); // 1 asdasd010 010 0
    DO_CHECK(coded.at(2) == 64); // 01 000 000
}

void HuffmanTest::test_file_manager_read_coded_file_small() {
    std::ofstream out("test.txt");
    out << "aa";
    out.close();
    std::map<byte_t, std::vector<bool>> code = {{'a', std::vector<bool>({0})}};
    FileManager writer("test.txt", "test.bin");
    writer.read_coding_file();
    writer.write_coded_message(code);
    FileManager reader("test.bin", "test.txt");
    auto [coded, sz] = reader.read_coded_file();
    std::vector<bool> msg;
    reader.unzip_bytes_in_bits(coded, sz, msg);
    DO_CHECK(msg == std::vector<bool>({0, 0}));
}


void HuffmanTest::test_file_manager_decode_bytes_small() {
    std::ofstream out("test.txt");
    out << "aa";
    out.close();
    std::map<byte_t, std::vector<bool>> code = {{'a', std::vector<bool>({0})}};
    FileManager writer("test.txt", "test.bin");
    writer.read_coding_file();
    writer.write_coded_message(code);
    FileManager reader("test.bin", "test.txt");
    auto [coded, sz] = reader.read_coded_file();
    std::vector<byte_t> msg;
    msg = reader.decode_bytes(coded,sz);
    DO_CHECK(msg == std::vector<byte_t>({'a', 'a'}));
}


void HuffmanTest::test_file_manager_read_coded_file_stronger() {
    std::ofstream out("test.txt");
    out << "IO IS COOL";
    out.close();
    FileManager writer("test.txt", "test.bin");
    std::vector<byte_t > v = writer.read_coding_file();
    HuffmanArhiver huffmanArhiver(v);
    std::map<byte_t, std::vector<bool>> code = huffmanArhiver.encode();
    writer.write_coded_message(code);

    FileManager reader("test.bin", "");
    auto [coded_msg, sz] = reader.read_coded_file();
    std::vector<byte_t> decoded_msg = reader.decode_bytes(coded_msg, sz);
    DO_CHECK(decoded_msg.size() == std::string("IO IS COOL").size());
    DO_CHECK(decoded_msg == std::vector<byte_t>(
            {'I', 'O', ' ', 'I', 'S', ' ', 'C', 'O', 'O', 'L'}));
}

void HuffmanTest::test_file_manager_decode_bytes() {
    // Build decode table
    std::map<byte_t, std::vector<bool>> code = {{'a', std::vector<bool>({0, 0, 1})},
                                                {'b', std::vector<bool>({0, 1, 0})}};
    FileManager writer("", "test.bin");
    writer.write_coded_message(code);
    FileManager reader("test.bin", "");
    auto [coded, sz] = reader.read_coded_file();

    std::vector<byte_t> input = {36, char(4 + 32 + 128), 64};
    std::vector<byte_t> result = reader.decode_bytes(input, 18);
    DO_CHECK(result.size() == 6);
    DO_CHECK(result == std::vector<byte_t>({'a', 'a', 'a', 'b', 'b', 'a'}));
}

void HuffmanTest::test_file_manager_write_decoded_message() {
    FileManager fileManager("", "test.txt");
    std::vector<byte_t> decoded_msg = {'a', 'a', 'a', 'b', 'b', 'a'};
    fileManager.write_decoded_message(decoded_msg);
    std::ifstream in("test.txt");

    in.ignore( std::numeric_limits<std::streamsize>::max() ); // Some magic
    std::streamsize length = in.gcount();
    in.clear();
    in.seekg(0, std::ios_base::beg );

    DO_CHECK(length == 6);
}

void HuffmanTest::runAllTests() {
    test_huffman_tree_builder();
    test_huffman_tree_get_root();
    test_huffman_archiver_calculate_frequencies();
    test_huffman_archiver_encode();

    test_file_manager_zip_bits_in_bytes();
    test_file_manager_unzip_bytes_in_bits();
    test_file_manager_write_coded_message_table();
    test_file_manager_write_coded_message_stronger();
    test_file_manager_code_one_byte();

    test_file_manager_read_coded_file();
    test_file_manager_decode_bytes();
    test_file_manager_write_decoded_message();
    test_file_manager_read_coded_file_stronger();
    test_file_manager_read_coded_file_small();
    test_file_manager_decode_bytes_small();
}



