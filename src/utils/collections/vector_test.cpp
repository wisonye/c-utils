#include <gtest/gtest.h>

extern "C" {
// #include "string.h"
#include <string.h>

#include "vector.h"
}

TEST(Vector, EmptyVector) {
    SMART_VECTOR(empty_vec) = Vector_new();
    ASSERT_EQ(Vector_len(empty_vec), 0);
    ASSERT_EQ(Vector_capacity(empty_vec), 0);
    VectorIteractor iter = Vector_iter(empty_vec);
    ASSERT_EQ(iter.length, 0);
    ASSERT_EQ(iter.items, NULL);
}

TEST(Vector, EmptyVectorWithCapiticy) {
    usize u16_type_size = sizeof(u16);
    SMART_VECTOR(vec) = Vector_with_capacity(10, u16_type_size);
    ASSERT_EQ(Vector_len(vec), 0);
    ASSERT_EQ(Vector_capacity(vec), 10);
    VectorIteractor iter_2 = Vector_iter(vec);
    ASSERT_EQ(iter_2.length, 0);
    ASSERT_NE(iter_2.items, NULL);

    //
    // `capacity` should NOT change and no `realloc` will be called before
    // pushing the 11th elements
    //
    u16 short_arr[] = {5000, 5001, 5002, 5003, 5004, 5005,
                       5006, 5007, 5008, 5009, 6000};
    Vector_push(vec, &short_arr[0], u16_type_size);
    Vector_push(vec, &short_arr[1], u16_type_size);
    Vector_push(vec, &short_arr[2], u16_type_size);
    Vector_push(vec, &short_arr[3], u16_type_size);
    Vector_push(vec, &short_arr[4], u16_type_size);
    Vector_push(vec, &short_arr[5], u16_type_size);
    Vector_push(vec, &short_arr[6], u16_type_size);
    Vector_push(vec, &short_arr[7], u16_type_size);
    Vector_push(vec, &short_arr[8], u16_type_size);
    Vector_push(vec, &short_arr[9], u16_type_size);
    ASSERT_EQ(Vector_len(vec), 10);
    ASSERT_EQ(Vector_capacity(vec), 10);

    // `capacity` should change to `20`
    Vector_push(vec, &short_arr[10], u16_type_size);
    ASSERT_EQ(Vector_len(vec), 11);
    ASSERT_EQ(Vector_capacity(vec), 20);

    // Element value check
    VectorIteractor iter = Vector_iter(vec);
    ASSERT_EQ(iter.length, 11);
    u16 *temp_arr = (u16 *)iter.items;
    ASSERT_EQ(temp_arr[0], short_arr[0]);
    ASSERT_EQ(temp_arr[1], short_arr[1]);
    ASSERT_EQ(temp_arr[2], short_arr[2]);
    ASSERT_EQ(temp_arr[3], short_arr[3]);
    ASSERT_EQ(temp_arr[4], short_arr[4]);
    ASSERT_EQ(temp_arr[5], short_arr[5]);
    ASSERT_EQ(temp_arr[6], short_arr[6]);
    ASSERT_EQ(temp_arr[7], short_arr[7]);
    ASSERT_EQ(temp_arr[8], short_arr[8]);
    ASSERT_EQ(temp_arr[9], short_arr[9]);
    ASSERT_EQ(temp_arr[10], short_arr[10]);
}

TEST(Vector, PushElement_Integer) {
    int int_arr[] = {100, 200, 300};
    SMART_VECTOR(vec) = Vector_new();
    Vector_push(vec, &int_arr[0], sizeof(int));
    ASSERT_EQ(Vector_len(vec), 1);
    ASSERT_EQ(Vector_capacity(vec), 1);
    Vector_push(vec, &int_arr[1], sizeof(int));
    ASSERT_EQ(Vector_len(vec), 2);
    ASSERT_EQ(Vector_capacity(vec), 2);
    Vector_push(vec, &int_arr[2], sizeof(int));
    ASSERT_EQ(Vector_len(vec), 3);
    ASSERT_EQ(Vector_capacity(vec), 4);

    VectorIteractor iter = Vector_iter(vec);
    ASSERT_EQ(iter.length, Vector_len(vec));
    int *temp_arr = (int *)iter.items;
    ASSERT_NE(temp_arr, NULL);
    ASSERT_EQ(temp_arr[0], 100);
    ASSERT_EQ(temp_arr[1], 200);
    ASSERT_EQ(temp_arr[2], 300);

    int int_arr_2[] = {666, 777, 888, 999};
    SMART_VECTOR(vec_2) = Vector_new();
    Vector_push(vec_2, &int_arr_2[0], sizeof(int));
    ASSERT_EQ(Vector_len(vec_2), 1);
    ASSERT_EQ(Vector_capacity(vec_2), 1);
    Vector_push(vec_2, &int_arr_2[1], sizeof(int));
    ASSERT_EQ(Vector_len(vec_2), 2);
    ASSERT_EQ(Vector_capacity(vec_2), 2);
    Vector_push(vec_2, &int_arr_2[2], sizeof(int));
    ASSERT_EQ(Vector_len(vec_2), 3);
    ASSERT_EQ(Vector_capacity(vec_2), 4);

    //
    // already be able to hold 4 elements. so `capacity` no needs to change,
    // no `realloc` to be called. */
    //
    Vector_push(vec_2, &int_arr_2[3], sizeof(int));
    ASSERT_EQ(Vector_len(vec_2), 4);
    ASSERT_EQ(Vector_capacity(vec_2), 4);

    VectorIteractor iter_2 = Vector_iter(vec_2);
    ASSERT_EQ(iter_2.length, Vector_len(vec_2));
    int *temp_arr_2 = (int *)iter_2.items;
    ASSERT_NE(temp_arr_2, NULL);
    ASSERT_EQ(temp_arr_2[0], 666);
    ASSERT_EQ(temp_arr_2[1], 777);
    ASSERT_EQ(temp_arr_2[2], 888);
    ASSERT_EQ(temp_arr_2[3], 999);
}

typedef struct {
    char first_name[10];
    char last_name[10];
    u8 age;
} Person;

TEST(Vector, PushElement_custom_struct) {
    Person wison = {.first_name = "Wison", .last_name = "Ye", .age = 88};
    Person fion = {.first_name = "Fion", .last_name = "Li", .age = 99};
    Person nobody = {
        .first_name = "Nobody", .last_name = "Nothing", .age = 100};
    SMART_VECTOR(vec) = Vector_new();
    Vector_push(vec, &wison, sizeof(Person));
    ASSERT_EQ(Vector_len(vec), 1);
    ASSERT_EQ(Vector_capacity(vec), 1);
    Vector_push(vec, &fion, sizeof(Person));
    ASSERT_EQ(Vector_len(vec), 2);
    ASSERT_EQ(Vector_capacity(vec), 2);
    Vector_push(vec, &nobody, sizeof(Person));
    ASSERT_EQ(Vector_len(vec), 3);
    ASSERT_EQ(Vector_capacity(vec), 4);

    VectorIteractor iter = Vector_iter(vec);
    ASSERT_EQ(iter.length, Vector_len(vec));
    Person *temp_arr = (Person *)iter.items;
    ASSERT_NE(temp_arr, NULL);
    ASSERT_EQ(strcmp(temp_arr[0].first_name, "Wison"), 0);
    ASSERT_EQ(strcmp(temp_arr[0].last_name, "Ye"), 0);
    ASSERT_EQ(temp_arr[0].age, 88);
    ASSERT_EQ(strcmp(temp_arr[1].first_name, "Fion"), 0);
    ASSERT_EQ(strcmp(temp_arr[1].last_name, "Li"), 0);
    ASSERT_EQ(temp_arr[1].age, 99);
    ASSERT_EQ(strcmp(temp_arr[2].first_name, "Nobody"), 0);
    ASSERT_EQ(strcmp(temp_arr[2].last_name, "Nothing"), 0);
    ASSERT_EQ(temp_arr[2].age, 100);
}

double double_arr[] = {11.11, 22.22, 33.33};
usize double_type_size = sizeof(double);
usize double_arr_len = sizeof(double_arr) / sizeof(double_arr[0]);

Person person_arr[] = {
    {.first_name = "first_1", .last_name = "last_1", .age = 11},
    {.first_name = "first_2", .last_name = "last_2", .age = 22},
    {.first_name = "first_3", .last_name = "last_3", .age = 33},
};
usize person_type_size = sizeof(Person);
usize person_arr_len = sizeof(person_arr) / sizeof(person_arr[0]);

TEST(Vector, immutable_get) {
    SMART_VECTOR(double_vec) =
        Vector_with_capacity(double_arr_len, double_type_size);
    for (usize di = 0; di < double_arr_len; di++) {
        Vector_push(double_vec, &double_arr[di], double_type_size);
    }
    ASSERT_EQ(Vector_len(double_vec), double_arr_len);
    ASSERT_EQ(Vector_capacity(double_vec), double_arr_len);

    const double *d_value_1 =
        (const double *)Vector_get(double_vec, 0, double_type_size);
    const double *d_value_2 =
        (const double *)Vector_get(double_vec, 1, double_type_size);
    const double *d_value_3 =
        (const double *)Vector_get(double_vec, 2, double_type_size);
    ASSERT_EQ(*d_value_1, double_arr[0]);
    ASSERT_EQ(*d_value_2, double_arr[1]);
    ASSERT_EQ(*d_value_3, double_arr[2]);
    const double *d_value_4 =
        (const double *)Vector_get(double_vec, 3, double_type_size);
    ASSERT_EQ(d_value_4, NULL);

    SMART_VECTOR(person_vec) =
        Vector_with_capacity(person_arr_len, person_type_size);
    for (usize pi = 0; pi < double_arr_len; pi++) {
        Vector_push(person_vec, &person_arr[pi], person_type_size);
    }
    ASSERT_EQ(Vector_len(person_vec), person_arr_len);
    ASSERT_EQ(Vector_capacity(person_vec), person_arr_len);

    const Person *person_1 =
        (const Person *)Vector_get(person_vec, 0, person_type_size);
    const Person *person_2 =
        (const Person *)Vector_get(person_vec, 1, person_type_size);
    const Person *person_3 =
        (const Person *)Vector_get(person_vec, 2, person_type_size);

    ASSERT_EQ(strcmp(person_1->first_name, person_arr[0].first_name), 0);
    ASSERT_EQ(strcmp(person_1->last_name, person_arr[0].last_name), 0);
    ASSERT_EQ(person_1->age, person_arr[0].age);
    ASSERT_EQ(strcmp(person_2->first_name, person_arr[1].first_name), 0);
    ASSERT_EQ(strcmp(person_2->last_name, person_arr[1].last_name), 0);
    ASSERT_EQ(person_2->age, person_arr[1].age);
    ASSERT_EQ(strcmp(person_3->first_name, person_arr[2].first_name), 0);
    ASSERT_EQ(strcmp(person_3->last_name, person_arr[2].last_name), 0);
    ASSERT_EQ(person_3->age, person_arr[2].age);

    const Person *person_4 =
        (const Person *)Vector_get(person_vec, 3, person_type_size);
    ASSERT_EQ(person_4, NULL);
}
