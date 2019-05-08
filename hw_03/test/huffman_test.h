//
// Created by ivan on 21.04.19.
//

#ifndef HW_03_HUFFMANTEST_H
#define HW_03_HUFFMANTEST_H

#include <iostream>
#include "autotest.h"
#include "../src/huffman.h"
class HuffmanTest: Test{
public:
    void runAllTests() override;
private:
    void test_huffman_tree_builder();
    void test_huffman_tree_get_root();
    void test_huffman_archiver_calculate_frequencies();
    void test_huffman_archiver_encode();
    void test_file_manager_zip_bits_in_bytes();
    void test_file_manager_unzip_bytes_in_bits();
    void test_file_manager_write_coded_message_table();
    void test_file_manager_write_coded_message_stronger();
    void test_file_manager_code_one_byte();
    void test_file_manager_read_coded_file();
    void test_file_manager_read_coded_file_stronger();
    void test_file_manager_read_coded_file_small();
    void test_file_manager_decode_bytes();
    void test_file_manager_write_decoded_message();
    void test_file_manager_decode_bytes_small();
};


#endif //HW_03_HUFFMANTEST_H
