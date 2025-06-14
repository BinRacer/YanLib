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
    auto [security_level, token_policy, resource_level, system_policy] =
            security.check_proc_integrity_level();
    EXPECT_EQ(elevation.first, TokenElevationTypeLimited);
    EXPECT_EQ(elevation.second, true);
    EXPECT_EQ(security_level, sys::SecurityLevel::Medium);
    EXPECT_EQ(token_policy, sys::TokenPolicy::NoWriteUp);
    EXPECT_EQ(resource_level, sys::ResourceLevel::Medium);
    EXPECT_EQ(system_policy, sys::SystemPolicy::NoReadUp);

    auto session_id = security.curr_session_id();
    EXPECT_GT(session_id, 0);
}
