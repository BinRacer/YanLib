#include <gtest/gtest.h>
#include "crypto/xxencode.h"
namespace crypto = YanLib::crypto;

class crypto_xxencode : public ::testing::Test {
protected:
    void SetUp() override {
        data_str = "Hello World!你好世界";
        data_vec.insert(data_vec.end(), data_str.begin(), data_str.end());
        ciphertext = "MG4JgP4wUJqxmP4EVt9qUtOKxt9WKttKA";
        ciphertext_vec.insert(ciphertext_vec.end(), ciphertext.begin(),
                              ciphertext.end());
    }

    std::string data_str{};
    std::vector<uint8_t> data_vec{};
    std::string ciphertext{};
    std::vector<uint8_t> ciphertext_vec{};
};

TEST_F(crypto_xxencode, xxencode) {
    EXPECT_GT(data_str.size(), 0);
    EXPECT_GT(data_vec.size(), 0);
    EXPECT_GT(ciphertext.size(), 0);
    EXPECT_GT(ciphertext_vec.size(), 0);
    auto encode_str = crypto::xxencode::encode_string(data_str);
    EXPECT_EQ(encode_str, ciphertext);
    auto encode_vec = crypto::xxencode::encode(data_vec);
    EXPECT_EQ(encode_vec, ciphertext_vec);
    auto decode_str = crypto::xxencode::decode_string(ciphertext);
    EXPECT_EQ(decode_str, data_str);
    auto decode_vec = crypto::xxencode::decode(ciphertext_vec);
    EXPECT_EQ(decode_vec, data_vec);
}
