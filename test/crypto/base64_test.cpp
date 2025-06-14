#include <gtest/gtest.h>
#include "crypto/base64.h"
namespace crypto = YanLib::crypto;

class crypto_base64 : public ::testing::Test {
protected:
    void SetUp() override {
        data_str = "Hello World!你好世界";
        data_vec.insert(data_vec.end(), data_str.begin(), data_str.end());
        ciphertext = "SGVsbG8gV29ybGQh5L2g5aW95LiW55WM";
        ciphertext_vec.insert(ciphertext_vec.end(), ciphertext.begin(),
                              ciphertext.end());

        url_str = "https://cn.bing.com/"
                  "search?q=base64加密解密&PC=U316&FORM=CHROMN";
        url_vec.insert(url_vec.end(), url_str.begin(), url_str.end());
        url_ciphertext =
                "aHR0cHM6Ly9jbi5iaW5nLmNvbS9zZWFyY2g_"
                "cT1iYXNlNjTliqDlr4bop6Plr4YmUEM9VTMxNiZGT1JNPUNIUk9NTg";
        url_ciphertext_vec.insert(url_ciphertext_vec.end(),
                                  url_ciphertext.begin(), url_ciphertext.end());
    }

    std::string data_str{};
    std::vector<uint8_t> data_vec{};
    std::string ciphertext{};
    std::vector<uint8_t> ciphertext_vec{};
    std::string url_str{};
    std::vector<uint8_t> url_vec{};
    std::string url_ciphertext{};
    std::vector<uint8_t> url_ciphertext_vec{};
};

TEST_F(crypto_base64, base64) {
    EXPECT_GT(data_str.size(), 0);
    EXPECT_GT(data_vec.size(), 0);
    EXPECT_GT(ciphertext.size(), 0);
    EXPECT_GT(ciphertext_vec.size(), 0);
    auto encode_str = crypto::base64::encode_string(data_str);
    EXPECT_EQ(encode_str, ciphertext);
    auto encode_vec = crypto::base64::encode(data_vec);
    EXPECT_EQ(encode_vec, ciphertext_vec);
    auto decode_str = crypto::base64::decode_string(ciphertext);
    EXPECT_EQ(decode_str, data_str);
    auto decode_vec = crypto::base64::decode(ciphertext_vec);
    EXPECT_EQ(decode_vec, data_vec);
}

TEST_F(crypto_base64, base64_url) {
    EXPECT_GT(url_str.size(), 0);
    EXPECT_GT(url_vec.size(), 0);
    EXPECT_GT(url_ciphertext.size(), 0);
    EXPECT_GT(url_ciphertext_vec.size(), 0);
    auto encode_str = crypto::base64::encode_url(url_str);
    EXPECT_EQ(encode_str, url_ciphertext);
    auto encode_vec = crypto::base64::encode_url(url_vec);
    EXPECT_EQ(encode_vec, url_ciphertext_vec);
    auto decode_str = crypto::base64::decode_url(encode_str);
    EXPECT_EQ(decode_str, url_str);
    auto decode_vec = crypto::base64::decode_url(url_ciphertext_vec);
    EXPECT_EQ(decode_vec, url_vec);
}
