//
// Created by Sadza on 20.08.2021.
//

#ifndef SADZA_SYSASSERT_HPP
#define SADZA_SYSASSERT_HPP

#define SYS_ASSERT_PRINT_STR "%s:%d"
#define SYS_ASSERT_PRINT_ARG __FILE__, __LINE__

#define ASSERT_TRUE(cond) { if(!(cond)) { printf("ASSERT_TRUE(%s) failed at %s:%d %s \n", \
    #cond, __FILE__, __LINE__, __FUNCTION__); exit(EXIT_FAILURE); } }

#define ASSERT_FALSE(cond) { if(cond) { printf("ASSERT_FALSE(%s) %s:%d %s\n", \
    #cond, __FILE__, __LINE__, __FUNCTION__); exit(EXIT_FAILURE); } }

#define ASSERT_EQ(cond1, cond2) { if(cond1 != cond2) { printf("ASSERT_EQ(%s, %s) %s:%d %s\n", \
    #cond1, #cond2, __FILE__, __LINE__, __FUNCTION__); exit(EXIT_FAILURE); } }

#define ASSERT_NE(cond1, cond2) { if(cond1 == cond2) { printf("ASSERT_NE(%s, %s) %s:%d %s\n", \
    #cond1, #cond2, __FILE__, __LINE__, __FUNCTION__); exit(EXIT_FAILURE); } }

#define ASSERT_GT(cond1, cond2) { if(cond1 <= cond2) { printf("ASSERT_GT(%s, %s) %s:%d %s\n", \
    #cond1, #cond2, __FILE__, __LINE__, __FUNCTION__); exit(EXIT_FAILURE); } }

#define ASSERT_GE(cond1, cond2) { if(cond1 < cond2) { printf("ASSERT_GT(%s, %s) %s:%d %s\n", \
    #cond1, #cond2, __FILE__, __LINE__, __FUNCTION__); exit(EXIT_FAILURE); } }

#define ASSERT_LT(cond1, cond2) { if(cond1 >= cond2) { printf("ASSERT_GT(%s, %s) %s:%d %s\n", \
    #cond1, #cond2, __FILE__, __LINE__, __FUNCTION__); exit(EXIT_FAILURE); } }

#define ASSERT_LE(cond1, cond2) { if(cond1 > cond2) { printf("ASSERT_GT(%s, %s) %s:%d %s\n", \
    #cond1, #cond2, __FILE__, __LINE__, __FUNCTION__); exit(EXIT_FAILURE); } }

#endif //SADZA_SYSASSERT_HPP
