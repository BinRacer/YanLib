#include <gtest/gtest.h>
#include "crypto/aes256.h"
namespace crypto = YanLib::crypto;

class crypto_aes256 : public ::testing::Test {
protected:
    void SetUp() override {
        std::string data_str = "Hello,这是待加密的示例数据";
        data.insert(data.end(), data_str.begin(), data_str.end());
        std::string key_str = "1234567890abcdefghijklmnopqrstuv";
        key.insert(key.end(), key_str.begin(), key_str.end());
        std::string iv_str = "1234567890abcdef";
        iv.insert(iv.end(), iv_str.begin(), iv_str.end());
    }

    std::vector<uint8_t> data{};
    std::vector<uint8_t> key{};
    std::vector<uint8_t> iv{};
};

TEST_F(crypto_aes256, cbc_pkcs7) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes256 aes;
    auto encode = aes.encode_cbc(data, key, iv, crypto::AesPadding::PKCS7);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "1dbf3d477f59e16aa5ba30f3e8161c6537e1cdef9e330aaeb38a"
              "702cde93fed336b103735b5388143d44656a7cc305d6");
    auto decode = aes.decode_cbc(encode, key, iv, crypto::AesPadding::PKCS7);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes256, cbc_iso10126) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes256 aes;
    auto encode = aes.encode_cbc(data, key, iv, crypto::AesPadding::ISO10126);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    auto decode = aes.decode_cbc(encode, key, iv, crypto::AesPadding::ISO10126);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes256, cbc_ansi_x923) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes256 aes;
    auto encode = aes.encode_cbc(data, key, iv, crypto::AesPadding::ANSIX923);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "1dbf3d477f59e16aa5ba30f3e8161c6537e1cdef9e330aaeb38a"
              "702cde93fed398a7dc8cbefd9264039edd5b26f0bd5a");
    auto decode = aes.decode_cbc(encode, key, iv, crypto::AesPadding::ANSIX923);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes256, ecb_pkcs7) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    crypto::aes256 aes;
    auto encode = aes.encode_ecb(data, key, crypto::AesPadding::PKCS7);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "8cff0eaea69ad07bb2f43c16b9c2b277b6750f7bbc2ef753212b"
              "3bb15b92ee72e3f02edf5eef68fa1fac667bbf5937a3");
    auto decode = aes.decode_ecb(encode, key, crypto::AesPadding::PKCS7);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes256, ecb_iso10126) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    crypto::aes256 aes;
    auto encode = aes.encode_ecb(data, key, crypto::AesPadding::ISO10126);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    auto decode = aes.decode_ecb(encode, key, crypto::AesPadding::ISO10126);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes256, ecb_ansi_x923) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    crypto::aes256 aes;
    auto encode = aes.encode_ecb(data, key, crypto::AesPadding::ANSIX923);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "8cff0eaea69ad07bb2f43c16b9c2b277b6750f7bbc2ef753212b"
              "3bb15b92ee7224a0367c6c4d482ef85765d517db9fc8");
    auto decode = aes.decode_ecb(encode, key, crypto::AesPadding::ANSIX923);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes256, cfb_pkcs7) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes256 aes;
    auto encode = aes.encode_cfb(data, key, iv, crypto::AesPadding::PKCS7);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "126e195559516223803df1df43f5d6000de9d85b9386b72c48b1"
              "214d9eaf9202c4ca208e401a8166a0600e7cbb6d9dbe");
    auto decode = aes.decode_cfb(encode, key, iv, crypto::AesPadding::PKCS7);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes256, cfb_iso10126) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes256 aes;
    auto encode = aes.encode_cfb(data, key, iv, crypto::AesPadding::ISO10126);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    auto decode = aes.decode_cfb(encode, key, iv, crypto::AesPadding::ISO10126);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes256, cfb_ansi_x923) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes256 aes;
    auto encode = aes.encode_cfb(data, key, iv, crypto::AesPadding::ANSIX923);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "126e195559516223803df1df43f5d6000de9d85b9386b72c48b1"
              "214d9eaf9202c4ca208e4c4c1c8a993661729f397264");
    auto decode = aes.decode_cfb(encode, key, iv, crypto::AesPadding::ANSIX923);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}
