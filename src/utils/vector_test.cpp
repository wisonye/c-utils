#include <gtest/gtest.h>

extern "C" {
// #include "string.h"
#include <string.h>

#include "vector.h"
}

TEST(Vector, EmptyVector) {
    Vector empty_vec = Vector_from_empty();
    ASSERT_EQ(Vector_length(empty_vec), 0);
    ASSERT_EQ(Vector_capacity(empty_vec), 0);
    VectorIteractor iter = Vector_iter(empty_vec);
    ASSERT_EQ(iter.length, 0);
    ASSERT_EQ(iter.items, NULL);

    Vector_free(empty_vec);
}

TEST(Vector, PushElement_Integer) {
    int int_arr[] = {100, 200, 300};
    Vector vec = Vector_from_empty();
    Vector_push(vec, &int_arr[0], sizeof(int));
    ASSERT_EQ(Vector_length(vec), 1);
    ASSERT_EQ(Vector_capacity(vec), 1);
    Vector_push(vec, &int_arr[1], sizeof(int));
    ASSERT_EQ(Vector_length(vec), 2);
    ASSERT_EQ(Vector_capacity(vec), 2);
    Vector_push(vec, &int_arr[2], sizeof(int));
    ASSERT_EQ(Vector_length(vec), 3);
    ASSERT_EQ(Vector_capacity(vec), 4);

    VectorIteractor iter = Vector_iter(vec);
    ASSERT_EQ(iter.length, Vector_length(vec));
    int *temp_arr = (int *)iter.items;
    ASSERT_NE(temp_arr, NULL);
    ASSERT_EQ(temp_arr[0], 100);
    ASSERT_EQ(temp_arr[1], 200);
    ASSERT_EQ(temp_arr[2], 300);

    Vector_free(vec);
    ASSERT_EQ(Vector_length(vec), 0);
    ASSERT_EQ(Vector_capacity(vec), 0);
    VectorIteractor iter_after_free = Vector_iter(vec);
    ASSERT_EQ(iter_after_free.length, 0);
    ASSERT_EQ(iter_after_free.items, NULL);

    int int_arr_2[] = {666, 777, 888, 999};
    Vector vec_2 = Vector_from_empty();
    Vector_push(vec_2, &int_arr_2[0], sizeof(int));
    ASSERT_EQ(Vector_length(vec_2), 1);
    ASSERT_EQ(Vector_capacity(vec_2), 1);
    Vector_push(vec_2, &int_arr_2[1], sizeof(int));
    ASSERT_EQ(Vector_length(vec_2), 2);
    ASSERT_EQ(Vector_capacity(vec_2), 2);
    Vector_push(vec_2, &int_arr_2[2], sizeof(int));
    ASSERT_EQ(Vector_length(vec_2), 3);
    ASSERT_EQ(Vector_capacity(vec_2), 4);

    // already be able to hold 4 elements. so `capacity` no needs to change, no
    // `realloc` to be called.
    Vector_push(vec_2, &int_arr_2[3], sizeof(int));
    ASSERT_EQ(Vector_length(vec_2), 4);
    ASSERT_EQ(Vector_capacity(vec_2), 4);

    VectorIteractor iter_2 = Vector_iter(vec_2);
    ASSERT_EQ(iter_2.length, Vector_length(vec_2));
    int *temp_arr_2 = (int *)iter_2.items;
    ASSERT_NE(temp_arr_2, NULL);
    ASSERT_EQ(temp_arr_2[0], 666);
    ASSERT_EQ(temp_arr_2[1], 777);
    ASSERT_EQ(temp_arr_2[2], 888);
    ASSERT_EQ(temp_arr_2[3], 999);

    Vector_free(vec_2);
    ASSERT_EQ(Vector_length(vec_2), 0);
    ASSERT_EQ(Vector_capacity(vec_2), 0);
    VectorIteractor iter_after_free_2 = Vector_iter(vec_2);
    ASSERT_EQ(iter_after_free_2.length, 0);
    ASSERT_EQ(iter_after_free_2.items, NULL);
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
    Vector vec = Vector_from_empty();
    Vector_push(vec, &wison, sizeof(Person));
    ASSERT_EQ(Vector_length(vec), 1);
    ASSERT_EQ(Vector_capacity(vec), 1);
    Vector_push(vec, &fion, sizeof(Person));
    ASSERT_EQ(Vector_length(vec), 2);
    ASSERT_EQ(Vector_capacity(vec), 2);
    Vector_push(vec, &nobody, sizeof(Person));
    ASSERT_EQ(Vector_length(vec), 3);
    ASSERT_EQ(Vector_capacity(vec), 4);

    VectorIteractor iter = Vector_iter(vec);
    ASSERT_EQ(iter.length, Vector_length(vec));
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

    Vector_free(vec);
    ASSERT_EQ(Vector_length(vec), 0);
    ASSERT_EQ(Vector_capacity(vec), 0);
    VectorIteractor iter_after_free = Vector_iter(vec);
    ASSERT_EQ(iter_after_free.length, 0);
    ASSERT_EQ(iter_after_free.items, NULL);
}
