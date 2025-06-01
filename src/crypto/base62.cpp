//
// Created by forkernel on 2025/4/9.
//

#include "base62.h"

namespace YanLib::crypto {
    std::vector<uint8_t> base62::encode(const std::vector<uint8_t> &data) {
        constexpr uint8_t BASE62_CHARS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXY"
                                           "Zabcdefghijklmnopqrstuvwxyz";

        if (data.empty())
            return {};

        std::vector<uint8_t> result;
        result.reserve(
                static_cast<size_t>(static_cast<double>(data.size()) * 1.37) +
                3);
        std::vector<uint32_t> digits(data.begin(), data.end());

        while (!digits.empty()) {
            uint32_t remainder = 0;
            std::vector<uint32_t> new_digits;
            new_digits.reserve(digits.size());

            for (const uint32_t num : digits) {
                uint64_t val = static_cast<uint64_t>(remainder) * 256 + num;
                auto quot = static_cast<uint32_t>(val / 62);
                remainder = static_cast<uint32_t>(val % 62);

                if (!new_digits.empty() || quot != 0) {
                    new_digits.push_back(quot);
                }
            }

            result.push_back(remainder);
            digits.assign(new_digits.begin(), new_digits.end());
        }

        std::reverse(result.begin(), result.end());

        std::vector<uint8_t> encoded;
        encoded.reserve(result.size());
        for (const uint8_t num : result) {
            encoded.push_back(BASE62_CHARS[num]);
        }

        return encoded;
    }

    std::vector<uint8_t> base62::decode(const std::vector<uint8_t> &data) {
        constexpr uint8_t BASE62_CHARS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXY"
                                           "Zabcdefghijklmnopqrstuvwxyz";
        if (data.empty())
            return {};
        std::vector<uint8_t> table(256, -1);
        for (int32_t i = 0; i < 62; i++) {
            table[BASE62_CHARS[i]] = i;
        }
        std::vector<uint8_t> result;
        for (const auto c : data) {
            size_t pos = table[c];
            if (pos == -1) {
                return {};
            }
            auto num = static_cast<uint32_t>(pos);

            uint32_t carry = num;
            for (int32_t i = static_cast<int32_t>(result.size()) - 1; i >= 0;
                 --i) {
                uint32_t temp = result[i] * 62 + carry;
                result[i] = static_cast<uint8_t>(temp % 256);
                carry = temp / 256;
            }

            while (carry > 0) {
                result.insert(result.begin(), carry % 256);
                carry /= 256;
            }
        }

        if (!data.empty() && result.empty()) {
            result.push_back(0);
        }

        return result;
    }

    std::string base62::encode_string(const std::string &data) {
        std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> encoded = encode(input);
        std::string result(encoded.begin(), encoded.end());
        return result;
    }

    std::string base62::decode_string(const std::string &data) {
        std::vector<uint8_t> input(data.begin(), data.end());
        std::vector<uint8_t> decoded = decode(input);
        std::string result(decoded.begin(), decoded.end());
        return result;
    }
} // namespace YanLib::crypto
