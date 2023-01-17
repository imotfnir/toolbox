#include <io_lib.h>

#include <CUnit/Automated.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/Console.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

int MySum(int a1, int b1) {
    int res1;
    res1 = a1 + b1;
    return res1;
}

void test_MySum(void) {
    CU_ASSERT(4 == MySum(2, 2));
    CU_ASSERT(8 == MySum(5, 3));
    CU_ASSERT(2 == MySum(-2, 4));
    CU_ASSERT(7 == MySum(0, 7));
}

int main(void) {
    CU_pSuite pSuite1 = NULL;

    if(CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

    pSuite1 = CU_add_suite("Test Suite1", init_suite, clean_suite);
    if(NULL == pSuite1) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if((NULL
        == CU_add_test(pSuite1, "\n\nSum function Testing\n\n", test_MySum))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}