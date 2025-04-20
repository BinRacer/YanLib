#include <gtest/gtest.h>
#include "sys/security.h"
namespace sys = YanLib::sys;

class sys_security : public ::testing::Test {
protected:
    void SetUp() override {
    }

    sys::security security;
};

TEST_F(sys_security, check_level) {
    auto elevation = security.check_proc_elevation();
    auto [security_level, token_policy, resource_level, system_policy] = security.check_proc_integrity_level();
    EXPECT_EQ(elevation.first, TokenElevationTypeLimited);
    EXPECT_EQ(elevation.second, true);
    EXPECT_EQ(security_level, sys::security::SECURITY_MEDIUM);
    EXPECT_EQ(token_policy, sys::security::TOKEN_NO_WRITE_UP);
    EXPECT_EQ(resource_level, sys::security::RESOURCE_MEDIUM);
    EXPECT_EQ(system_policy, sys::security::SYSTEM_NO_READ_UP);

    auto session_id = security.curr_session_id();
    EXPECT_GT(session_id, 0);
}
