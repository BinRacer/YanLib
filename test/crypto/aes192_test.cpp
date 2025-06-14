#include <gtest/gtest.h>
#include "crypto/aes192.h"
namespace crypto = YanLib::crypto;

class crypto_aes192 : public ::testing::Test {
protected:
    void SetUp() override {
        std::string data_str = "Hello,这是待加密的示例数据";
        data.insert(data.end(), data_str.begin(), data_str.end());
        std::string key_str = "1234567890abcdefghijklmn";
        key.insert(key.end(), key_str.begin(), key_str.end());
        std::string iv_str = "1234567890abcdef";
        iv.insert(iv.end(), iv_str.begin(), iv_str.end());
    }

    std::vector<uint8_t> data{};
    std::vector<uint8_t> key{};
    std::vector<uint8_t> iv{};
};

TEST_F(crypto_aes192, cbc_pkcs7) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes192 aes;
    auto encode = aes.encode_cbc(data, key, iv, crypto::AesPadding::PKCS7);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "d22345a705a00bcc4457a83cb386c7641fc410cb4cdcb2b7f2c4"
              "a7b370717f3c4dfa94cef8977ef9bb78dd46ea65d048");
    auto decode = aes.decode_cbc(encode, key, iv, crypto::AesPadding::PKCS7);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes192, cbc_iso10126) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes192 aes;
    auto encode = aes.encode_cbc(data, key, iv, crypto::AesPadding::ISO10126);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    auto decode = aes.decode_cbc(encode, key, iv, crypto::AesPadding::ISO10126);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes192, cbc_ansi_x923) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes192 aes;
    auto encode = aes.encode_cbc(data, key, iv, crypto::AesPadding::ANSIX923);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "d22345a705a00bcc4457a83cb386c7641fc410cb4cdcb2b7f2c4"
              "a7b370717f3c09a3140184fb2029987f0858553ab9b0");
    auto decode = aes.decode_cbc(encode, key, iv, crypto::AesPadding::ANSIX923);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes192, ecb_pkcs7) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    crypto::aes192 aes;
    auto encode = aes.encode_ecb(data, key, crypto::AesPadding::PKCS7);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "d63ca8059e16d64e124e8567f74f7a8c93c628cdf3707dcfac8c"
              "805445213d8c3e9b8d74e18f754c9a4f34ebd8adbacf");
    auto decode = aes.decode_ecb(encode, key, crypto::AesPadding::PKCS7);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes192, ecb_iso10126) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    crypto::aes192 aes;
    auto encode = aes.encode_ecb(data, key, crypto::AesPadding::ISO10126);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    auto decode = aes.decode_ecb(encode, key, crypto::AesPadding::ISO10126);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes192, ecb_ansi_x923) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    crypto::aes192 aes;
    auto encode = aes.encode_ecb(data, key, crypto::AesPadding::ANSIX923);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "d63ca8059e16d64e124e8567f74f7a8c93c628cdf3707dcfac8c"
              "805445213d8cf87413dad4289d951644a5cbd25dc6c0");
    auto decode = aes.decode_ecb(encode, key, crypto::AesPadding::ANSIX923);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes192, cfb_pkcs7) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes192 aes;
    auto encode = aes.encode_cfb(data, key, iv, crypto::AesPadding::PKCS7);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "dd8b490a5ec973835dd0d3a675d4d643616cbc744a7793c4075d"
              "a8a2ff4e7788ab12d82eae5fd985a1af66002b36fdbc");
    auto decode = aes.decode_cfb(encode, key, iv, crypto::AesPadding::PKCS7);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes192, cfb_iso10126) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes192 aes;
    auto encode = aes.encode_cfb(data, key, iv, crypto::AesPadding::ISO10126);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    auto decode = aes.decode_cfb(encode, key, iv, crypto::AesPadding::ISO10126);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}

TEST_F(crypto_aes192, cfb_ansi_x923) {
    EXPECT_GT(data.size(), 0);
    EXPECT_GT(key.size(), 0);
    EXPECT_GT(iv.size(), 0);
    crypto::aes192 aes;
    auto encode = aes.encode_cfb(data, key, iv, crypto::AesPadding::ANSIX923);
    auto encode_hex = aes.hex_string();
    EXPECT_GT(encode.size(), 0);
    EXPECT_EQ(encode_hex,
              "dd8b490a5ec973835dd0d3a675d4d643616cbc744a7793c4075d"
              "a8a2ff4e7788ab12d82ea293aefede5518968604e754");
    auto decode = aes.decode_cfb(encode, key, iv, crypto::AesPadding::ANSIX923);
    EXPECT_GT(decode.size(), 0);
    EXPECT_EQ(decode, data);
}
