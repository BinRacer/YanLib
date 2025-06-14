#include <gtest/gtest.h>
#include "hash/md5.h"
namespace hash = YanLib::hash;

class hash_md5 : public ::testing::Test {
private:
    static std::vector<uint8_t> hex_decode(const std::vector<uint8_t> &data) {
        if (data.empty() || data.size() % 2 != 0)
            return {};

        auto char_to_nibble = [](const uint8_t c) -> int {
            if (std::isdigit(c))
                return c - '0';
            if (c >= 'A' && c <= 'F')
                return c - 'A' + 10;
            if (c >= 'a' && c <= 'f')
                return c - 'a' + 10;
            return -1;
        };

        std::vector<uint8_t> decoded;
        decoded.reserve(data.size() / 2);
        for (size_t i = 0; i < data.size(); i += 2) {
            const int hi = char_to_nibble(data[i]);
            const int lo = char_to_nibble(data[i + 1]);
            if (hi == -1 || lo == -1)
                return {};
            decoded.push_back((hi << 4) | lo);
        }
        return decoded;
    }

protected:
    void SetUp() override {
        data_str = "Hello World!你好世界";
        data_vec.insert(data_vec.end(), data_str.begin(), data_str.end());
        ciphertext_str = "dd0b9ee4c12cdd367fc3d96fa9f881e8";
        ciphertext_vec.insert(ciphertext_vec.end(), ciphertext_str.begin(),
                              ciphertext_str.end());
        ciphertext_vec = hex_decode(ciphertext_vec);
        zlib_str = "fdb4930015bb5410e35f4a2dbdce99fc";
        zlib_vec.insert(zlib_vec.end(), zlib_str.begin(), zlib_str.end());
        zlib_vec = hex_decode(zlib_vec);
    }

    std::string data_str{};
    std::vector<uint8_t> data_vec{};
    std::string ciphertext_str{};
    std::vector<uint8_t> ciphertext_vec{};
    const wchar_t *zlib = L"..\\..\\test\\testdata\\zlibd1_64.dll";
    std::string zlib_str{};
    std::vector<uint8_t> zlib_vec{};
};

TEST_F(hash_md5, md5) {
    EXPECT_GT(data_str.size(), 0);
    EXPECT_GT(data_vec.size(), 0);
    EXPECT_GT(ciphertext_str.size(), 0);
    EXPECT_GT(ciphertext_vec.size(), 0);
    hash::md5 md5_str(data_str);
    hash::md5 md5_vec(data_vec);
    hash::md5 md5_file(zlib);
    EXPECT_EQ(md5_str.hash(), ciphertext_vec);
    EXPECT_EQ(md5_str.hash_string(), ciphertext_str);
    EXPECT_EQ(md5_vec.hash(), ciphertext_vec);
    EXPECT_EQ(md5_vec.hash_string(), ciphertext_str);
    EXPECT_EQ(md5_file.hash(), zlib_vec);
    EXPECT_EQ(md5_file.hash_string(), zlib_str);
}
