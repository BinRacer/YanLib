#include <gtest/gtest.h>
#include "sys/snapshot.h"
namespace sys = YanLib::sys;

class sys_snapshot : public ::testing::Test {
protected:
    void SetUp() override {
    }

    sys::snapshot snapshot;
};

TEST_F(sys_snapshot, list_info) {
    auto procs = snapshot.ls_procs();
    EXPECT_GT(procs.size(), 0);
    auto threads = snapshot.ls_threads();
    EXPECT_GT(threads.size(), 0);
    auto modules = snapshot.ls_modules();
    EXPECT_GT(modules.size(), 0);
    auto heaps = snapshot.ls_heaps();
    EXPECT_GT(heaps.size(), 0);
}
