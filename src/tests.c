#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

// ============================================================
// Forward declarations — implemented in code.c
// ============================================================

typedef struct Node {
    int value;
    struct Node *nextPtr;
} Node;

void  swap(int *aPtr, int *bPtr);
char* find_last_char(char *sPtr);
void  link_three(Node *aPtr, Node *bPtr, Node *cPtr);
void  remove_middle(Node *aPtr, Node *bPtr, Node *cPtr);
void  remove_last(Node *bPtr);
void  remove_first(Node *aPtr);
void  swap_ptrs(int **aPtrPtr, int **bPtrPtr);
void  nullify(int **ppPtr);
void  assign_bytes(long long *nPtr);
int   sum_chain(Node *headPtr);


// ============================================================
//  UNIT TESTS
//
//  Rules:
//  - Set up all variables on the STACK — no malloc.
//  - Call the function under test.
//  - Use TEST_ASSERT_* to verify the result.
//  - Each function must be self-contained.
//  - Do NOT modify function names or signatures.
// ============================================================


// ============================================================
// test_swap_basic
//
// Call swap with two different integer values.
// Verify that both variables hold the exchanged values
// after the call.
// ============================================================

void test_swap_basic(void)
{
    int a = 3;
    int b = 5;

    swap(&a, &b);

    TEST_ASSERT_EQUAL_INT(5, a);
    TEST_ASSERT_EQUAL_INT(3, b);
}


// ============================================================
// test_swap_equal
//
// Call swap with two variables that hold the same value.
// Verify that both variables still hold that value after
// the call — nothing should change.
// ============================================================

void test_swap_equal(void)
{
    int a = 7;
    int b = 7;

    swap(&a, &b);

    TEST_ASSERT_EQUAL_INT(7, a);
    TEST_ASSERT_EQUAL_INT(7, b);
}


// ============================================================
// test_find_last_basic
//
// Call find_last_char on a string with multiple characters.
// Verify that the returned pointer points to the correct
// last character and has the correct address.
// ============================================================

void test_find_last_basic(void)
{
    char str[] = "hello";
    char *returnedPtr = find_last_char(str);

    TEST_ASSERT_EQUAL_CHAR('o', *returnedPtr);
    TEST_ASSERT_EQUAL_PTR(&str[4], returnedPtr);
}


// ============================================================
// test_find_last_single
//
// Call find_last_char on a string with exactly one character.
// Verify that the returned pointer points to that character
// and equals the address of the first element.
// ============================================================

void test_find_last_single(void)
{
    char str[] = "A";
    char *returnedPtr = find_last_char(str);

    TEST_ASSERT_EQUAL_CHAR('A', *returnedPtr);
    TEST_ASSERT_EQUAL_PTR(&str[0], returnedPtr);
}


// ============================================================
// test_find_last_empty
//
// Call find_last_char on an empty string.
// Verify that the function returns NULL.
// ============================================================

void test_find_last_empty(void)
{
    char str[] = "";
    char *returnedPtr = find_last_char(str);

    TEST_ASSERT_NULL(returnedPtr);
}


// ============================================================
// test_link_three_chain
//
// Declare three Node variables on the stack.
// Call link_three to connect them.
// Verify that:
//   - aPtr->nextPtr points to bPtr
//   - bPtr->nextPtr points to cPtr
//   - cPtr->nextPtr is NULL
// ============================================================

void test_link_three_chain(void)
{
    Node a, b, c;

    link_three(&a, &b, &c);

    TEST_ASSERT_EQUAL_PTR(&b, a.nextPtr);
    TEST_ASSERT_EQUAL_PTR(&c, b.nextPtr);
    TEST_ASSERT_NULL(c.nextPtr);
}


// ============================================================
// test_remove_middle_reconnects
//
// Build the chain a -> b -> c -> NULL using link_three.
// Call remove_middle.
// Verify that:
//   - aPtr->nextPtr now points directly to cPtr
//   - bPtr->nextPtr is NULL (disconnected)
// ============================================================

void test_remove_middle_reconnects(void)
{
    Node a, b, c;

    link_three(&a, &b, &c);
    remove_middle(&a, &b, &c);

    TEST_ASSERT_EQUAL_PTR(&c, a.nextPtr);
    TEST_ASSERT_NULL(b.nextPtr);
}


// ============================================================
// test_remove_last_truncates
//
// Build the chain a -> b -> c -> NULL using link_three.
// Call remove_last with bPtr.
// Verify that:
//   - bPtr->nextPtr is NULL
//   - aPtr->nextPtr still points to bPtr (unchanged)
// ============================================================

void test_remove_last_truncates(void)
{
    Node a, b, c;

    link_three(&a, &b, &c);
    remove_last(&b);

    TEST_ASSERT_NULL(b.nextPtr);
    TEST_ASSERT_EQUAL_PTR(&b, a.nextPtr);
}


// ============================================================
// test_remove_first_isolates
//
// Build the chain a -> b -> c -> NULL using link_three.
// Call remove_first with aPtr.
// Verify that:
//   - aPtr->nextPtr is NULL (isolated)
//   - bPtr->nextPtr still points to cPtr (unchanged)
// ============================================================

void test_remove_first_isolates(void)
{
    Node a, b, c;

    link_three(&a, &b, &c);
    remove_first(&a);

    TEST_ASSERT_NULL(a.nextPtr);
    TEST_ASSERT_EQUAL_PTR(&c, b.nextPtr);
}


// ============================================================
// test_swap_ptrs_redirects
//
// Declare two integer variables and two pointers to them.
// Call swap_ptrs.
// Verify that each pointer now points to the other variable.
// ============================================================

void test_swap_ptrs_redirects(void)
{
    int x = 3;
    int y = 5;
    int *ptr1 = &x;
    int *ptr2 = &y;

    swap_ptrs(&ptr1, &ptr2);

    TEST_ASSERT_EQUAL_PTR(&y, ptr1);
    TEST_ASSERT_EQUAL_PTR(&x, ptr2);
}


// ============================================================
// test_swap_ptrs_values_unchanged
//
// Declare two integer variables and two pointers to them.
// Call swap_ptrs.
// Verify that the INTEGER VALUES at the original addresses
// are completely unchanged after the call.
// ============================================================

void test_swap_ptrs_values_unchanged(void)
{
    int x = 3;
    int y = 5;
    int *ptr1 = &x;
    int *ptr2 = &y;

    swap_ptrs(&ptr1, &ptr2);

    TEST_ASSERT_EQUAL_INT(3, x);
    TEST_ASSERT_EQUAL_INT(5, y);
}


// ============================================================
// test_nullify_sets_null
//
// Declare an integer and a pointer to it.
// Verify the pointer is NOT NULL before the call.
// Call nullify.
// Verify the pointer IS NULL after the call.
// ============================================================

void test_nullify_sets_null(void)
{
    int x = 3;
    int *ptr = &x;

    TEST_ASSERT_NOT_NULL(ptr);

    nullify(&ptr);

    TEST_ASSERT_NULL(ptr);
}


// ============================================================
// test_nullify_value_unchanged
//
// Declare an integer and a pointer to it.
// Call nullify.
// Verify that the INTEGER VALUE at the original address
// is unchanged after the call.
// ============================================================

void test_nullify_value_unchanged(void)
{
    int x = 3;
    int *ptr = &x;

    nullify(&ptr);

    TEST_ASSERT_EQUAL_INT(3, x);
}


// ============================================================
// test_assign_bytes_first_and_last
//
// Declare a long long variable initialized to zero.
// Call assign_bytes.
// Cast the address to unsigned char* and verify that
// byte 0 equals 1 and byte 7 equals 8.
// ============================================================

void test_assign_bytes_first_and_last(void)
{
    long long x = 0;
    assign_bytes(&x);

    unsigned char *bytePtr = (unsigned char *)&x;

    TEST_ASSERT_EQUAL_UINT8(1, bytePtr[0]);
    TEST_ASSERT_EQUAL_UINT8(8, bytePtr[7]);
}


// ============================================================
// test_assign_bytes_all
//
// Declare a long long variable initialized to zero.
// Call assign_bytes.
// Cast the address to unsigned char* and verify that
// every byte i contains the value i + 1.
// ============================================================

void test_assign_bytes_all(void)
{
    long long x = 0;
    assign_bytes(&x);

    unsigned char *bytePtr = (unsigned char *)&x;

    for (int i = 0; i < 8; i++) {
        TEST_ASSERT_EQUAL_UINT8(i + 1, bytePtr[i]); // Help from Gemini
    }
}


// ============================================================
// test_sum_chain_basic
//
// Declare three Node variables on the stack.
// Link them into a chain using link_three.
// Assign known values to each node.
// Call sum_chain and verify the returned sum is correct.
// ============================================================

void test_sum_chain_basic(void)
{
    Node a, b, c;

    link_three(&a, &b, &c);

    a.value = 1;
    b.value = 2;
    c.value = 3;

    int sum = sum_chain(&a);

    TEST_ASSERT_EQUAL_INT(6, sum);
}


// ============================================================
// test_sum_chain_single
//
// Declare a single Node with a known value.
// Set nextPtr to NULL.
// Call sum_chain and verify it returns that single value.
// ============================================================

void test_sum_chain_single(void)
{
    Node a;

    a.value = 3;
    a.nextPtr = NULL;

    int sum = sum_chain(&a);

    TEST_ASSERT_EQUAL_INT(3, sum);
}


// ============================================================
// test_sum_chain_null
//
// Call sum_chain with NULL.
// Verify the function returns 0 without crashing.
// ============================================================

void test_sum_chain_null(void)
{
    int sum = sum_chain(NULL);

    TEST_ASSERT_EQUAL_INT(0, sum);
}