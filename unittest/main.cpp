#include "common.h"


int main(int argc, char **argv) {
    std::cout <<"----------------------------------------" << std::endl;
    if(argc > 2) {
        // Set the test filter to run only the specified test
        ::testing::GTEST_FLAG(filter) = argv[1];
    }
    
    // Initialize Google Test framework
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
