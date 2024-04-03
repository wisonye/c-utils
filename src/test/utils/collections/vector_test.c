#include "./vector_test.h"

#define UNITY_INCLUDE_DOUBLE
// #define UNITY_DOUBLE_PRECISION 0.00001f
#define UNITY_DOUBLE_PRECISION 1e-12f

#include <string.h>

#include "../../../utils/collections/vector.h"
#include "unity.h"

///
/// This is run before EACH TEST
///
void setUp(void) {
    printf("\n>>> [ vector_test_setUp ] - run.");
}

///
/// This is run after EACH TEST
///
void tearDown(void) {
    printf("\n>>> [ vector_test_tearDown ] - run.");
}

void test_vector_empty_vector(void) {
    defer_vector(empty_vec, int, NULL);
    TEST_ASSERT_EQUAL_UINT(Vec_len(empty_vec), 0);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(empty_vec), 0);
    VectorIteractor iter = Vec_iter(empty_vec);
    TEST_ASSERT_EQUAL_UINT(iter.length, 0);
    TEST_ASSERT_NULL(iter.items);
}

void test_vector_empty_vector_with_capacity(void) {
    defer_vector_with_capacity(vec, u16, 10, NULL);
    TEST_ASSERT_EQUAL_UINT(Vec_len(vec), 0);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(vec), 10);
    VectorIteractor iter_2 = Vec_iter(vec);
    TEST_ASSERT_EQUAL_UINT(iter_2.length, 0);
    TEST_ASSERT_NOT_NULL(iter_2.items);

    //
    // `capacity` should NOT change and no `realloc` will be called before
    // pushing the 11th elements
    //
    u16 short_arr[] =
        {5000, 5001, 5002, 5003, 5004, 5005, 5006, 5007, 5008, 5009, 6000};
    Vec_push(vec, &short_arr[0]);
    Vec_push(vec, &short_arr[1]);
    Vec_push(vec, &short_arr[2]);
    Vec_push(vec, &short_arr[3]);
    Vec_push(vec, &short_arr[4]);
    Vec_push(vec, &short_arr[5]);
    Vec_push(vec, &short_arr[6]);
    Vec_push(vec, &short_arr[7]);
    Vec_push(vec, &short_arr[8]);
    Vec_push(vec, &short_arr[9]);
    TEST_ASSERT_EQUAL_UINT(Vec_len(vec), 10);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(vec), 10);

    // `capacity` should change to `20`
    Vec_push(vec, &short_arr[10]);
    TEST_ASSERT_EQUAL_UINT(Vec_len(vec), 11);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(vec), 20);

    // Element value check
    VectorIteractor iter = Vec_iter(vec);
    TEST_ASSERT_EQUAL_UINT(iter.length, 11);
    u16 *temp_arr = (u16 *)iter.items;
    TEST_ASSERT_EQUAL_UINT(temp_arr[0], short_arr[0]);
    TEST_ASSERT_EQUAL_UINT(temp_arr[1], short_arr[1]);
    TEST_ASSERT_EQUAL_UINT(temp_arr[2], short_arr[2]);
    TEST_ASSERT_EQUAL_UINT(temp_arr[3], short_arr[3]);
    TEST_ASSERT_EQUAL_UINT(temp_arr[4], short_arr[4]);
    TEST_ASSERT_EQUAL_UINT(temp_arr[5], short_arr[5]);
    TEST_ASSERT_EQUAL_UINT(temp_arr[6], short_arr[6]);
    TEST_ASSERT_EQUAL_UINT(temp_arr[7], short_arr[7]);
    TEST_ASSERT_EQUAL_UINT(temp_arr[8], short_arr[8]);
    TEST_ASSERT_EQUAL_UINT(temp_arr[9], short_arr[9]);
    TEST_ASSERT_EQUAL_UINT(temp_arr[10], short_arr[10]);
}

void test_vector_push_element(void) {
    int int_arr[] = {100, 200, 300};
    defer_vector(vec, int, NULL);
    Vec_push(vec, &int_arr[0]);
    TEST_ASSERT_EQUAL_UINT(Vec_len(vec), 1);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(vec), 1);
    Vec_push(vec, &int_arr[1]);
    TEST_ASSERT_EQUAL_UINT(Vec_len(vec), 2);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(vec), 2);
    Vec_push(vec, &int_arr[2]);
    TEST_ASSERT_EQUAL_UINT(Vec_len(vec), 3);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(vec), 4);

    const VectorIteractor iter = Vec_iter(vec);
    TEST_ASSERT_EQUAL_UINT(iter.length, Vec_len(vec));
    const int *temp_arr = (const int *)iter.items;
    TEST_ASSERT_NOT_NULL(temp_arr);
    TEST_ASSERT_EQUAL_UINT(temp_arr[0], 100);
    TEST_ASSERT_EQUAL_UINT(temp_arr[1], 200);
    TEST_ASSERT_EQUAL_UINT(temp_arr[2], 300);

    int int_arr_2[] = {666, 777, 888, 999};
    defer_vector(vec_2, int, NULL);
    Vec_push(vec_2, &int_arr_2[0]);
    TEST_ASSERT_EQUAL_UINT(Vec_len(vec_2), 1);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(vec_2), 1);
    Vec_push(vec_2, &int_arr_2[1]);
    TEST_ASSERT_EQUAL_UINT(Vec_len(vec_2), 2);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(vec_2), 2);
    Vec_push(vec_2, &int_arr_2[2]);
    TEST_ASSERT_EQUAL_UINT(Vec_len(vec_2), 3);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(vec_2), 4);

    //
    // already be able to hold 4 elements. so `capacity` no needs to change,
    // no `realloc` to be called. */
    //
    Vec_push(vec_2, &int_arr_2[3]);
    TEST_ASSERT_EQUAL_UINT(Vec_len(vec_2), 4);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(vec_2), 4);

    VectorIteractor iter_2 = Vec_iter(vec_2);
    TEST_ASSERT_EQUAL_UINT(iter_2.length, Vec_len(vec_2));
    int *temp_arr_2 = (int *)iter_2.items;
    TEST_ASSERT_NOT_NULL(temp_arr_2);
    TEST_ASSERT_EQUAL_UINT(temp_arr_2[0], 666);
    TEST_ASSERT_EQUAL_UINT(temp_arr_2[1], 777);
    TEST_ASSERT_EQUAL_UINT(temp_arr_2[2], 888);
    TEST_ASSERT_EQUAL_UINT(temp_arr_2[3], 999);
}

typedef struct {
    char first_name[10];
    char last_name[10];
    u8 age;
} Person;

String Person_to_string(void *person_ref) {
    String desc = HS_from_empty_with_capacity(100);

    HS_push_str(desc, "{firstName:");
    HS_push_str(desc, ((Person *)person_ref)->first_name);
    HS_push_str(desc, ",lastName:");
    HS_push_str(desc, ((Person *)person_ref)->last_name);
    HS_push_str(desc, ",age:");

    const char age_str[4] = {0};
    snprintf((char *)age_str,
             sizeof(age_str),
             "%d",
             ((Person *)person_ref)->age);
    HS_push_str(desc, age_str);
    HS_push_str(desc, "}");

    return desc;
}

void test_vector_push_element_with_custom_strcut(void) {
    Person wison  = {.first_name = "Wison", .last_name = "Ye", .age = 88};
    Person fion   = {.first_name = "Fion", .last_name = "Li", .age = 99};
    Person nobody = {.first_name = "Nobody",
                     .last_name  = "Nothing",
                     .age        = 100};
    defer_vector(vec, Person, NULL);
    Vec_push(vec, &wison);
    TEST_ASSERT_EQUAL_UINT(Vec_len(vec), 1);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(vec), 1);
    Vec_push(vec, &fion);
    TEST_ASSERT_EQUAL_UINT(Vec_len(vec), 2);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(vec), 2);
    Vec_push(vec, &nobody);
    TEST_ASSERT_EQUAL_UINT(Vec_len(vec), 3);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(vec), 4);

    VectorIteractor iter = Vec_iter(vec);
    TEST_ASSERT_EQUAL_UINT(iter.length, Vec_len(vec));
    Person *temp_arr = (Person *)iter.items;
    TEST_ASSERT_NOT_NULL(temp_arr);
    TEST_ASSERT_EQUAL_UINT(strcmp(temp_arr[0].first_name, "Wison"), 0);
    TEST_ASSERT_EQUAL_STRING(temp_arr[0].last_name, "Ye");
    TEST_ASSERT_EQUAL_UINT(temp_arr[0].age, 88);
    TEST_ASSERT_EQUAL_STRING(temp_arr[1].first_name, "Fion");
    TEST_ASSERT_EQUAL_STRING(temp_arr[1].last_name, "Li");
    TEST_ASSERT_EQUAL_UINT(temp_arr[1].age, 99);
    TEST_ASSERT_EQUAL_STRING(temp_arr[2].first_name, "Nobody");
    TEST_ASSERT_EQUAL_STRING(temp_arr[2].last_name, "Nothing");
    TEST_ASSERT_EQUAL_UINT(temp_arr[2].age, 100);

    //
    // Test join string
    //
    defer_string(join_string) = Vec_join(vec, ";", Person_to_string);
    TEST_ASSERT_EQUAL_STRING(
        HS_as_str(join_string),
        "{firstName:Wison,lastName:Ye,age:88};{firstName:Fion,lastName:Li,age:"
        "99};{firstName:Nobody,lastName:Nothing,age:100}");
}

double double_arr[]    = {11.11, 22.22, 33.33};
usize double_type_size = sizeof(double);
usize double_arr_len   = sizeof(double_arr) / sizeof(double_arr[0]);

Person person_arr[] = {
    {.first_name = "first_1", .last_name = "last_1", .age = 11},
    {.first_name = "first_2", .last_name = "last_2", .age = 22},
    {.first_name = "first_3", .last_name = "last_3", .age = 33},
};
usize person_type_size = sizeof(Person);
usize person_arr_len   = sizeof(person_arr) / sizeof(person_arr[0]);

void test_vector_immutable_get(void) {
    defer_vector_with_capacity(double_vec, double, double_arr_len, NULL);
    for (usize di = 0; di < double_arr_len; di++) {
        Vec_push(double_vec, &double_arr[di]);
    }
    TEST_ASSERT_EQUAL_UINT(Vec_len(double_vec), double_arr_len);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(double_vec), double_arr_len);

    const double *d_value_1 = (const double *)Vec_get(double_vec, 0);
    const double *d_value_2 = (const double *)Vec_get(double_vec, 1);
    const double *d_value_3 = (const double *)Vec_get(double_vec, 2);
    TEST_ASSERT_NOT_NULL(d_value_1);
    TEST_ASSERT_NOT_NULL(d_value_2);
    TEST_ASSERT_NOT_NULL(d_value_3);
    TEST_ASSERT_EQUAL_DOUBLE(double_arr[0], *d_value_1);
    TEST_ASSERT_EQUAL_DOUBLE(double_arr[1], *d_value_2);
    TEST_ASSERT_EQUAL_DOUBLE(double_arr[2], *d_value_3);
    const double *d_value_4 = (const double *)Vec_get(double_vec, 3);
    TEST_ASSERT_NULL(d_value_4);

    defer_vector_with_capacity(person_vec, Person, person_arr_len, NULL);
    for (usize pi = 0; pi < double_arr_len; pi++) {
        Vec_push(person_vec, &person_arr[pi]);
    }
    TEST_ASSERT_EQUAL_UINT(Vec_len(person_vec), person_arr_len);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(person_vec), person_arr_len);

    const Person *person_1 = (const Person *)Vec_get(person_vec, 0);
    const Person *person_2 = (const Person *)Vec_get(person_vec, 1);
    const Person *person_3 = (const Person *)Vec_get(person_vec, 2);

    TEST_ASSERT_EQUAL_STRING(person_1->first_name, person_arr[0].first_name);
    TEST_ASSERT_EQUAL_STRING(person_1->last_name, person_arr[0].last_name);
    TEST_ASSERT_EQUAL_UINT(person_1->age, person_arr[0].age);
    TEST_ASSERT_EQUAL_STRING(person_2->first_name, person_arr[1].first_name);
    TEST_ASSERT_EQUAL_STRING(person_2->last_name, person_arr[1].last_name);
    TEST_ASSERT_EQUAL_UINT(person_2->age, person_arr[1].age);
    TEST_ASSERT_EQUAL_STRING(person_3->first_name, person_arr[2].first_name);
    TEST_ASSERT_EQUAL_STRING(person_3->last_name, person_arr[2].last_name);
    TEST_ASSERT_EQUAL_UINT(person_3->age, person_arr[2].age);

    const Person *person_4 = (const Person *)Vec_get(person_vec, 3);
    TEST_ASSERT_NULL(person_4);
}

void test_vector_null(void) {
    TEST_ASSERT_EQUAL_UINT(Vec_len(NULL), 0);
    TEST_ASSERT_EQUAL_UINT(Vec_capacity(NULL), 0);
    VectorIteractor iter = Vec_iter(NULL);
    TEST_ASSERT_EQUAL_UINT(iter.length, 0);
    TEST_ASSERT_NULL(iter.items);
}
