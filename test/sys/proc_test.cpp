#include <gtest/gtest.h>
#include "sys/proc.h"
namespace sys = YanLib::sys;

class sys_proc : public ::testing::Test {
protected:
    void SetUp() override {
    }

    sys::proc proc;
};

TEST_F(sys_proc, env) {
    std::string var = "A";
    std::string val = "B";
    EXPECT_TRUE(proc.set_env_var(var, val));
    EXPECT_EQ(proc.get_env_var(var), val);

    std::wstring var_wide = L"C";
    std::wstring val_wide = L"D";
    EXPECT_TRUE(proc.set_env_var(var_wide, val_wide));
    EXPECT_EQ(proc.get_env_var(var_wide), val_wide);

    std::string env;
    EXPECT_TRUE(proc.get_env(env));
    EXPECT_GT(env.size(), 0);

    std::wstring env2;
    EXPECT_TRUE(proc.get_env(env2));
    EXPECT_GT(env2.size(), 0);

    std::vector<std::string> env3;
    EXPECT_TRUE(proc.get_env(env3));
    EXPECT_GT(env3.size(), 0);

    std::vector<std::wstring> env4;
    EXPECT_TRUE(proc.get_env(env4));
    EXPECT_GT(env4.size(), 0);

    std::unordered_map<std::string, std::string> env5;
    EXPECT_TRUE(proc.get_env(env5));
    EXPECT_GT(env5.size(), 0);

    std::unordered_map<std::wstring, std::wstring> env6;
    EXPECT_TRUE(proc.get_env(env6));
    EXPECT_GT(env6.size(), 0);
}

TEST_F(sys_proc, cmdline) {
    std::string cmdline;
    proc.get_cmdline(cmdline);
    EXPECT_GT(cmdline.size(), 0); 
    EXPECT_NE(cmdline.find("test.exe"), std::string::npos);

    std::wstring cmdline2;
    proc.get_cmdline(cmdline2);
    EXPECT_GT(cmdline2.size(), 0);
    EXPECT_NE(cmdline2.find(L"test.exe"), std::wstring::npos);

    std::string cmdline3;
    EXPECT_TRUE(proc.get_cmdline(proc.proc_handle(), cmdline3));
    EXPECT_GT(cmdline3.size(), 0);
    EXPECT_NE(cmdline3.find("test.exe"), std::string::npos);

    std::wstring cmdline4;
    EXPECT_TRUE(proc.get_cmdline(proc.proc_handle(), cmdline4));
    EXPECT_GT(cmdline4.size(), 0);
    EXPECT_NE(cmdline4.find(L"test.exe"), std::wstring::npos);

    std::string cmdline5;
    EXPECT_TRUE(proc.get_cmdline(proc.proc_id(), cmdline5));
    EXPECT_GT(cmdline5.size(), 0);
    EXPECT_NE(cmdline5.find("test.exe"), std::string::npos);

    std::wstring cmdline6;
    EXPECT_TRUE(proc.get_cmdline(proc.proc_id(), cmdline6));
    EXPECT_GT(cmdline6.size(), 0);
    EXPECT_NE(cmdline6.find(L"test.exe"), std::wstring::npos);
}

TEST_F(sys_proc, owner) {
    std::string owner;
    EXPECT_TRUE(proc.get_owner(proc.proc_handle(), owner));
    EXPECT_GT(owner.size(), 0);

    std::wstring owner2;
    EXPECT_TRUE(proc.get_owner(proc.proc_handle(), owner2));
    EXPECT_GT(owner2.size(), 0);

    std::string owner3;
    EXPECT_TRUE(proc.get_owner(proc.proc_id(), owner3));
    EXPECT_GT(owner3.size(), 0);

    std::wstring owner4;
    EXPECT_TRUE(proc.get_owner(proc.proc_id(), owner4));
    EXPECT_GT(owner4.size(), 0);
}

TEST_F(sys_proc, image_name) {
    std::string image_name;
    EXPECT_TRUE(proc.get_image_name(proc.proc_handle(), image_name));
    EXPECT_NE(image_name.find("test.exe"), std::string::npos);

    std::wstring image_name2;
    EXPECT_TRUE(proc.get_image_name(proc.proc_handle(), image_name2));
    EXPECT_NE(image_name2.find(L"test.exe"), std::wstring::npos);

    std::string image_name3;
    EXPECT_TRUE(proc.get_image_name(proc.proc_handle(), image_name3, true));
    EXPECT_NE(image_name3.find("test.exe"), std::string::npos);

    std::wstring image_name4;
    EXPECT_TRUE(proc.get_image_name(proc.proc_handle(), image_name4, true));
    EXPECT_NE(image_name4.find(L"test.exe"), std::wstring::npos);
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

    auto processor_num = proc.processor_num();
    EXPECT_GE(processor_num, 0);
}
