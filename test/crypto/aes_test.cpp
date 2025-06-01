#include <gtest/gtest.h>
#include "crypto/aes.h"
namespace crypto = YanLib::crypto;

class crypto_aes : public ::testing::Test {
protected:
    void SetUp() override {
        std::string data_str = "Hello,这是待加密的示例数据";
        data.insert(data.end(), data_str.begin(), data_str.end());
        std::string key_str = "1234567890abcdef";
        key.insert(key.end(), key_str.begin(), key_str.end());
        std::string iv_str = "1234567890abcdef";
        iv.insert(iv.end(), iv_str.begin(), iv_str.end());
    }

    std::vector<uint8_t> data{};
    std::vector<uint8_t> key{};
    std::vector<uint8_t> iv{};
};

TEST_F(crypto_aes, cbc_pkcs7) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes aes;
    auto encode = aes.encode_cbc(data, key, iv, crypto::AesPadding::PKCS7);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "99bab35bf35923f01790a920042ab7f0888dee83a7de3d5652a5"
              "2e342c8ab51471f2c704f39eb4e13e2da84dd8f3bf9c");
    auto decode = aes.decode_cbc(encode, key, iv, crypto::AesPadding::PKCS7);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes, cbc_iso10126) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes aes;
    auto encode = aes.encode_cbc(data, key, iv, crypto::AesPadding::ISO10126);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    auto decode = aes.decode_cbc(encode, key, iv, crypto::AesPadding::ISO10126);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes, cbc_ansi_x923) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes aes;
    auto encode = aes.encode_cbc(data, key, iv, crypto::AesPadding::ANSIX923);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "99bab35bf35923f01790a920042ab7f0888dee83a7de3d5652a5"
              "2e342c8ab51461f9a7d7b0b789bf82eaba0cd85a6f4a");
    auto decode = aes.decode_cbc(encode, key, iv, crypto::AesPadding::ANSIX923);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes, ecb_pkcs7) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    crypto::aes aes;
    auto encode = aes.encode_ecb(data, key, crypto::AesPadding::PKCS7);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "b74acf58c49c94565a3086580f8ea1b0f1d43a5dfefcb4cdb976"
              "9144e06e6eebee4f4f499aa9aef5ee91d08ac4341f0e");
    auto decode = aes.decode_ecb(encode, key, crypto::AesPadding::PKCS7);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes, ecb_iso10126) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    crypto::aes aes;
    auto encode = aes.encode_ecb(data, key, crypto::AesPadding::ISO10126);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    auto decode = aes.decode_ecb(encode, key, crypto::AesPadding::ISO10126);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes, ecb_ansi_x923) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    crypto::aes aes;
    auto encode = aes.encode_ecb(data, key, crypto::AesPadding::ANSIX923);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "b74acf58c49c94565a3086580f8ea1b0f1d43a5dfefcb4cdb976"
              "9144e06e6eeb50da3d578dcb86111430010b48fd0d78");
    auto decode = aes.decode_ecb(encode, key, crypto::AesPadding::ANSIX923);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes, cfb_pkcs7) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes aes;
    auto encode = aes.encode_cfb(data, key, iv, crypto::AesPadding::PKCS7);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "ddd1be0807ade6c73451a815fd81a40bf45add144aa2248b88ef"
              "3c78cfb1299e08d299c2697a152f7f17e4d5107666d5");
    auto decode = aes.decode_cfb(encode, key, iv, crypto::AesPadding::PKCS7);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes, cfb_iso10126) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes aes;
    auto encode = aes.encode_cfb(data, key, iv, crypto::AesPadding::ISO10126);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    auto decode = aes.decode_cfb(encode, key, iv, crypto::AesPadding::ISO10126);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes, cfb_ansi_x923) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes aes;
    auto encode = aes.encode_cfb(data, key, iv, crypto::AesPadding::ANSIX923);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "ddd1be0807ade6c73451a815fd81a40bf45add144aa2248b88ef"
              "3c78cfb1299e08d299c265f13f16fd26917de3e3fa1c");
    auto decode = aes.decode_cfb(encode, key, iv, crypto::AesPadding::ANSIX923);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}
