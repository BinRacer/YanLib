#include <gtest/gtest.h>
#include "sys/proc.h"
namespace sys = YanLib::sys;

class sys_proc : public ::testing::Test {
protected:
    void SetUp() override {
    }

    sys::proc proc;
};

TEST_F(sys_proc, cmdline) {
    auto cmdline = proc.cmdline(proc.proc_handle());
    EXPECT_GT(cmdline.size(), 0);
    EXPECT_NE(cmdline.find("proc_test.exe"), std::string::npos);
    auto cmdline2 = proc.cmdline();
    EXPECT_GT(cmdline2.size(), 0);
    EXPECT_NE(cmdline2.find(L"proc_test.exe"), std::wstring::npos);
    auto cmdline3 = proc.cmdline_wide(proc.proc_handle());
    EXPECT_GT(cmdline3.size(), 0);
    EXPECT_NE(cmdline3.find(L"proc_test.exe"), std::wstring::npos);
    auto cmdline4 = proc.cmdline(proc.proc_id());
    EXPECT_GT(cmdline4.size(), 0);
    EXPECT_NE(cmdline4.find("proc_test.exe"), std::string::npos);
    auto cmdline5 = proc.cmdline_wide(proc.proc_id());
    EXPECT_GT(cmdline5.size(), 0);
    EXPECT_NE(cmdline5.find(L"proc_test.exe"), std::wstring::npos);
}

TEST_F(sys_proc, owner) {
    auto owner = proc.owner(proc.proc_handle());
    EXPECT_GT(owner.size(), 0);
    auto owner2 = proc.owner(proc.proc_id());
    EXPECT_GT(owner2.size(), 0);
    auto owner3 = proc.owner_wide(proc.proc_handle());
    EXPECT_GT(owner3.size(), 0);
    auto owner4 = proc.owner_wide(proc.proc_id());
    EXPECT_GT(owner4.size(), 0);
}

TEST_F(sys_proc, image_base) {
    auto image_base = proc.image_base();
    EXPECT_NE(image_base, nullptr);
    auto image_base2 = proc.image_base(proc.proc_handle());
    EXPECT_NE(image_base2, nullptr);
    auto image_base3 = proc.image_base(proc.proc_id());
    EXPECT_NE(image_base3, nullptr);
}

TEST_F(sys_proc, priority) {
    auto proc_priority = proc.get_priority(proc.proc_handle());
    EXPECT_GT(proc_priority, 0);
    auto thread_priority = proc.get_priority(proc.proc_handle());
    EXPECT_GT(thread_priority, 0);
}

TEST_F(sys_proc, counters) {
    auto handle_count = proc.handle_count(proc.proc_handle());
    EXPECT_GT(handle_count, 0);
    auto gui_handle_count = proc.gui_handle_count(proc.proc_handle());
    EXPECT_EQ(gui_handle_count, 0);

    auto processor_num = proc.processor_num();
    EXPECT_GT(processor_num, 0);
}
