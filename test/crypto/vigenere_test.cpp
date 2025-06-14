#include <gtest/gtest.h>
#include "crypto/vigenere.h"
namespace crypto = YanLib::crypto;

class crypto_vigenere : public ::testing::Test {
protected:
    void SetUp() override {
        data_str = "Hello World!你好世界";
        data_vec.insert(data_vec.end(), data_str.begin(), data_str.end());
        key_str = "Thisisakey";
        key_vec.insert(key_vec.end(), key_str.begin(), key_str.end());
        ciphertext = "Altdw Oobpb!你好世界";
        ciphertext_vec.insert(ciphertext_vec.end(), ciphertext.begin(),
                              ciphertext.end());
    }

    std::string data_str{};
    std::vector<uint8_t> data_vec{};
    std::string key_str{};
    std::vector<uint8_t> key_vec{};
    std::string ciphertext{};
    std::vector<uint8_t> ciphertext_vec{};
};

TEST_F(crypto_vigenere, vigenere) {
    EXPECT_GT(data_str.size(), 0);
    EXPECT_GT(data_vec.size(), 0);
    EXPECT_GT(ciphertext.size(), 0);
    EXPECT_GT(ciphertext_vec.size(), 0);
    auto encode_str = crypto::vigenere::encode_string(data_str, key_str);
    EXPECT_EQ(encode_str, ciphertext);
    auto encode_vec = crypto::vigenere::encode(data_vec, key_vec);
    EXPECT_EQ(encode_vec, ciphertext_vec);
    auto decode_str = crypto::vigenere::decode_string(ciphertext, key_str);
    EXPECT_EQ(decode_str, data_str);
    auto decode_vec = crypto::vigenere::decode(ciphertext_vec, key_vec);
    EXPECT_EQ(decode_vec, data_vec);
}
