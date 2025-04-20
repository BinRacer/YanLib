#include <gtest/gtest.h>
#include "hash/sha512.h"
namespace hash = YanLib::hash;

class hash_sha512 : public ::testing::Test {
private:
    static std::vector<uint8_t> hex_decode(const std::vector<uint8_t> &data) {
        if (data.empty() || data.size() % 2 != 0) return {};

        auto char_to_nibble = [](const uint8_t c) -> int {
            if (std::isdigit(c)) return c - '0';
            if (c >= 'A' && c <= 'F') return c - 'A' + 10;
            if (c >= 'a' && c <= 'f') return c - 'a' + 10;
            return -1;
        };

        std::vector<uint8_t> decoded;
        decoded.reserve(data.size() / 2);
        for (size_t i = 0; i < data.size(); i += 2) {
            const int hi = char_to_nibble(data[i]);
            const int lo = char_to_nibble(data[i + 1]);
            if (hi == -1 || lo == -1) return {};
            decoded.push_back((hi << 4) | lo);
        }
        return decoded;
    }
protected:
    void SetUp() override {
        data_str = "Hello World!你好世界";
        data_vec.insert(data_vec.end(), data_str.begin(), data_str.end());
        ciphertext_str = "cb05378e92ced249fc1dfea151262af57c930f3dc04270f205a9d21be621fc083f24f1b8b687c1d2e5b8cd548cc67b26a803c760bc41223543bf0fa2866ee587";
        ciphertext_vec.insert(ciphertext_vec.end(), ciphertext_str.begin(), ciphertext_str.end());
        ciphertext_vec = hex_decode(ciphertext_vec);
    }

    std::string data_str{};
    std::vector<uint8_t> data_vec{};
    std::string ciphertext_str{};
    std::vector<uint8_t> ciphertext_vec{};
};

TEST_F(hash_sha512, sha512) {
    EXPECT_GT(data_str.size(), 0);
    EXPECT_GT(data_vec.size(), 0);
    EXPECT_GT(ciphertext_str.size(), 0);
    EXPECT_GT(ciphertext_vec.size(), 0);
    hash::sha512 sha512_str(data_str);
    hash::sha512 sha512_vec(data_vec);
    EXPECT_EQ(sha512_str.hash(), ciphertext_vec);
    EXPECT_EQ(sha512_str.hash_string(), ciphertext_str);
    EXPECT_EQ(sha512_vec.hash(), ciphertext_vec);
    EXPECT_EQ(sha512_vec.hash_string(), ciphertext_str);
}
