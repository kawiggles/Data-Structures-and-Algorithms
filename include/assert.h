#define ASSERT_H

#ifndef ASSERT_H
#define ASSERT(n)
#else
#define ASSERT(n) \
    if(!(n)) { \
    printf("%s - Failed\n", #n); \
    printf("At %s ", __TIME__); \
    printf("in file %s ", __FILE__); \
    printf("at line %d\n", __LINE__); \
    exit(1); } \

#endif
