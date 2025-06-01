#include <gtest/gtest.h>
#include "crypto/rsa.h"
namespace crypto = YanLib::crypto;

class crypto_rsa : public ::testing::Test {
protected:
    void SetUp() override {
        std::string data_str = "Hello World!你好世界";
        data.insert(data.end(), data_str.begin(), data_str.end());
    }

    std::vector<uint8_t> data{};
};

TEST_F(crypto_rsa, rsa_384) {
    EXPECT_GT(data.size(), 0);
    crypto::rsa rsa;
    bool is_ok = rsa.generate_key(crypto::RsaKeyBits::Bit384);
    EXPECT_TRUE(is_ok);
    auto pub_key = rsa.pub_blob();
    auto priv_key = rsa.priv_blob();
    EXPECT_GT(pub_key.size(), 0);
    EXPECT_GT(priv_key.size(), 0);
    auto encode_data = rsa.encode(data, pub_key);
    auto decode_data = rsa.decode(encode_data, priv_key);
    EXPECT_EQ(decode_data, data);
    auto encode_to_base64 = rsa.encode_to_base64(data, pub_key);
    auto decode_from_base64 =
            rsa.decode_from_base64(encode_to_base64, priv_key);
    EXPECT_EQ(decode_from_base64, data);
}

TEST_F(crypto_rsa, rsa_512) {
    EXPECT_GT(data.size(), 0);
    crypto::rsa rsa;
    bool is_ok = rsa.generate_key(crypto::RsaKeyBits::Bit512);
    EXPECT_TRUE(is_ok);
    auto pub_key = rsa.pub_blob();
    auto priv_key = rsa.priv_blob();
    EXPECT_GT(pub_key.size(), 0);
    EXPECT_GT(priv_key.size(), 0);
    auto encode_data = rsa.encode(data, pub_key);
    auto decode_data = rsa.decode(encode_data, priv_key);
    EXPECT_EQ(decode_data, data);
    auto encode_to_base64 = rsa.encode_to_base64(data, pub_key);
    auto decode_from_base64 =
            rsa.decode_from_base64(encode_to_base64, priv_key);
    EXPECT_EQ(decode_from_base64, data);
}

TEST_F(crypto_rsa, rsa_768) {
    EXPECT_GT(data.size(), 0);
    crypto::rsa rsa;
    bool is_ok = rsa.generate_key(crypto::RsaKeyBits::Bit768);
    EXPECT_TRUE(is_ok);
    auto pub_key = rsa.pub_blob();
    auto priv_key = rsa.priv_blob();
    EXPECT_GT(pub_key.size(), 0);
    EXPECT_GT(priv_key.size(), 0);
    auto encode_data = rsa.encode(data, pub_key);
    auto decode_data = rsa.decode(encode_data, priv_key);
    EXPECT_EQ(decode_data, data);
    auto encode_to_base64 = rsa.encode_to_base64(data, pub_key);
    auto decode_from_base64 =
            rsa.decode_from_base64(encode_to_base64, priv_key);
    EXPECT_EQ(decode_from_base64, data);
}

TEST_F(crypto_rsa, rsa_1024) {
    EXPECT_GT(data.size(), 0);
    crypto::rsa rsa;
    bool is_ok = rsa.generate_key(crypto::RsaKeyBits::Bit1024);
    EXPECT_TRUE(is_ok);
    auto pub_key = rsa.pub_blob();
    auto priv_key = rsa.priv_blob();
    EXPECT_GT(pub_key.size(), 0);
    EXPECT_GT(priv_key.size(), 0);
    auto encode_data = rsa.encode(data, pub_key);
    auto decode_data = rsa.decode(encode_data, priv_key);
    EXPECT_EQ(decode_data, data);
    auto encode_to_base64 = rsa.encode_to_base64(data, pub_key);
    auto decode_from_base64 =
            rsa.decode_from_base64(encode_to_base64, priv_key);
    EXPECT_EQ(decode_from_base64, data);
}

TEST_F(crypto_rsa, rsa_1536) {
    EXPECT_GT(data.size(), 0);
    crypto::rsa rsa;
    bool is_ok = rsa.generate_key(crypto::RsaKeyBits::Bit1536);
    EXPECT_TRUE(is_ok);
    auto pub_key = rsa.pub_blob();
    auto priv_key = rsa.priv_blob();
    EXPECT_GT(pub_key.size(), 0);
    EXPECT_GT(priv_key.size(), 0);
    auto encode_data = rsa.encode(data, pub_key);
    auto decode_data = rsa.decode(encode_data, priv_key);
    EXPECT_EQ(decode_data, data);
    auto encode_to_base64 = rsa.encode_to_base64(data, pub_key);
    auto decode_from_base64 =
            rsa.decode_from_base64(encode_to_base64, priv_key);
    EXPECT_EQ(decode_from_base64, data);
}

TEST_F(crypto_rsa, rsa_2048) {
    EXPECT_GT(data.size(), 0);
    crypto::rsa rsa;
    bool is_ok = rsa.generate_key(crypto::RsaKeyBits::Bit2048);
    EXPECT_TRUE(is_ok);
    auto pub_key = rsa.pub_blob();
    auto priv_key = rsa.priv_blob();
    EXPECT_GT(pub_key.size(), 0);
    EXPECT_GT(priv_key.size(), 0);
    auto encode_data = rsa.encode(data, pub_key);
    auto decode_data = rsa.decode(encode_data, priv_key);
    EXPECT_EQ(decode_data, data);
    auto encode_to_base64 = rsa.encode_to_base64(data, pub_key);
    auto decode_from_base64 =
            rsa.decode_from_base64(encode_to_base64, priv_key);
    EXPECT_EQ(decode_from_base64, data);
}

TEST_F(crypto_rsa, rsa_3072) {
    EXPECT_GT(data.size(), 0);
    crypto::rsa rsa;
    bool is_ok = rsa.generate_key(crypto::RsaKeyBits::Bit3072);
    EXPECT_TRUE(is_ok);
    auto pub_key = rsa.pub_blob();
    auto priv_key = rsa.priv_blob();
    EXPECT_GT(pub_key.size(), 0);
    EXPECT_GT(priv_key.size(), 0);
    auto encode_data = rsa.encode(data, pub_key);
    auto decode_data = rsa.decode(encode_data, priv_key);
    EXPECT_EQ(decode_data, data);
    auto encode_to_base64 = rsa.encode_to_base64(data, pub_key);
    auto decode_from_base64 =
            rsa.decode_from_base64(encode_to_base64, priv_key);
    EXPECT_EQ(decode_from_base64, data);
}

TEST_F(crypto_rsa, rsa_4096) {
    EXPECT_GT(data.size(), 0);
    crypto::rsa rsa;
    bool is_ok = rsa.generate_key(crypto::RsaKeyBits::Bit4096);
    EXPECT_TRUE(is_ok);
    auto pub_key = rsa.pub_blob();
    auto priv_key = rsa.priv_blob();
    EXPECT_GT(pub_key.size(), 0);
    EXPECT_GT(priv_key.size(), 0);
    auto encode_data = rsa.encode(data, pub_key);
    auto decode_data = rsa.decode(encode_data, priv_key);
    EXPECT_EQ(decode_data, data);
    auto encode_to_base64 = rsa.encode_to_base64(data, pub_key);
    auto decode_from_base64 =
            rsa.decode_from_base64(encode_to_base64, priv_key);
    EXPECT_EQ(decode_from_base64, data);
}

// TEST_F(crypto_rsa, rsa_8192) {
//     EXPECT_GT(data.size(), 0);
//     crypto::rsa rsa;
//     bool is_ok = rsa.generate_key(crypto::RsaKeyBits::RSA_8192BIT_KEY);
//     EXPECT_TRUE(is_ok);
//     auto pub_key = rsa.pub_blob();
//     auto priv_key = rsa.priv_blob();
//     EXPECT_GT(pub_key.size(), 0);
//     EXPECT_GT(priv_key.size(), 0);
//     auto encode_data = rsa.encode(data, pub_key);
//     auto decode_data = rsa.decode(encode_data, priv_key);
//     EXPECT_EQ(decode_data, data);
//     auto encode_to_base64 = rsa.encode_to_base64(data, pub_key);
//     auto decode_from_base64 = rsa.decode_from_base64(encode_to_base64,
//     priv_key); EXPECT_EQ(decode_from_base64, data);
// }

// TEST_F(crypto_rsa, rsa_16384) {
//     EXPECT_GT(data.size(), 0);
//     crypto::rsa rsa;
//     bool is_ok = rsa.generate_key(crypto::RsaKeyBits::RSA_16384BIT_KEY);
//     EXPECT_TRUE(is_ok);
//     auto pub_key = rsa.pub_blob();
//     auto priv_key = rsa.priv_blob();
//     EXPECT_GT(pub_key.size(), 0);
//     EXPECT_GT(priv_key.size(), 0);
//     auto encode_data = rsa.encode(data, pub_key);
//     auto decode_data = rsa.decode(encode_data, priv_key);
//     EXPECT_EQ(decode_data, data);
//     auto encode_to_base64 = rsa.encode_to_base64(data, pub_key);
//     auto decode_from_base64 = rsa.decode_from_base64(encode_to_base64,
//     priv_key); EXPECT_EQ(decode_from_base64, data);
// }
