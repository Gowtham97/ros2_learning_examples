#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include <iostream>

class SleepTest: public testing::Test{
    protected:
    void SetUp() override {
    }

    void TearDown() {
        thread_obj.join();
    }

    void set_val(){
        sleep(2);
        output = 5;
    }

    bool sleep_for(){
        thread_obj = std::thread(std::bind(&SleepTest::set_val, this));
        return true;
    }

    std::thread thread_obj;
    int output;

};

TEST_F(SleepTest, sleep_test_for_1s){
    ASSERT_TRUE(sleep_for());
    std::this_thread::sleep_for(std::chrono::seconds(3));
    ASSERT_EQ(output, 5);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
