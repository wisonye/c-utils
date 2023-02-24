# Collection

[1. `Vector`: Heap allocated dynamic array](#1-vector-heap-allocated-dynamic-array)</br>
[1.1 Create empty vector](#11-create-empty-vector)</br>
[1.2 Create empty vector with pre-allocated space to avoid `realloc` cost](#12-create-empty-vector-with-pre-allocated-space-to-avoid-realloc-cost)</br>
[1.3 Get element via `index`](#13-get-element-via-index)</br>
[1.4 Use `String`](#14-use-string)</br>
[1.5 Custom struct case](#15-custom-struct-case)</br>
[2. `SingleLinkList`](#2-singlelinklist)</br>
[2.1 Concept](#21-concept)</br>
[2.2 use cases](#22-use-cases)</br>
[2.3 Props and cons](#23-props-and-cons)</br>
[2.4 Complexity](#24-complexity)</br>
[2.5 Stack-allocated](#25-stack-allocated)</br>
[2.6 Heap-allocated](#26-heap-allocated)</br>


## 1. `Vector`: Heap allocated dynamic array.

This `Vector` doesn't support normal generic `<T>` (no auto element type
inference), that's why you have to provide the `sizeof(ELEMENT_TYPE)` when
creating a `Vector`.

When pushing an element, `Vector` executes a shallow copy which means doesn't
copy the internal heap-allocated content!!!

The `SMART_VECTOR` and `SMART_VECTOR_WITH_CAPACITY` macro ensures the
heap-allocated instance auto-free heap-allocated memory when it goes out of
its scope.

</br>

Examples:

</br>

#### 1.1 Create empty vector:

```c
// `SMART_VECTOR(variable_name, element_type);`
SMART_VECTOR(empty_vec, usize);
// (D) [ Vector ] > auto_free_vector - out of scope with vector ptr: 0x5472040, length: 0
```

</br>

#### 1.2 Create empty vector with pre-allocated space to avoid `realloc` cost:

```c
// `SMART_VECTOR_WITH_CAPACITY(variable_name, element_type, capacity);`

//
// u16 vec
//
SMART_VECTOR_WITH_CAPACITY(u16_vec, u16, 10);
// (D) [ Vector ] > with_capacity - self pointer: 0x5474260, element_type_size: 2, capacity: 10, self->items: 0x54742d0

//
// `capacity` should NOT change and no `realloc` will be called before
// pushing the 11th elements
//
u16 short_arr[] = {5000, 5001, 5002, 5003, 5004, 5005,
                    5006, 5007, 5008, 5009, 6000};
Vec_push(u16_vec, &short_arr[0]);
Vec_push(u16_vec, &short_arr[1]);
Vec_push(u16_vec, &short_arr[2]);
Vec_push(u16_vec, &short_arr[3]);
Vec_push(u16_vec, &short_arr[4]);
Vec_push(u16_vec, &short_arr[5]);
Vec_push(u16_vec, &short_arr[6]);
Vec_push(u16_vec, &short_arr[7]);
Vec_push(u16_vec, &short_arr[8]);
Vec_push(u16_vec, &short_arr[9]);

// `capacity` should change to `20`
Vec_push(u16_vec, &short_arr[10]);
// (D) [ Vector ] > Vec_Push - Realloc needed, current capacity: 10, length+1: 11, after capacity: 20, self->item: 0x5474330

// Print element value
VectorIteractor short_arr_iter = Vec_iter(u16_vec);
u16 *temp_short_arr = (u16 *)short_arr_iter.items;
for (usize sa_index = 0; sa_index < short_arr_iter.length; sa_index++) {
    DEBUG_LOG(Main, test_vector, "short_arr_iter[%lu]: %d", sa_index,
                temp_short_arr[sa_index]);
}
// (D) [ Main ] > test_vector - short_arr_iter[0]: 5000
// (D) [ Main ] > test_vector - short_arr_iter[1]: 5001
// (D) [ Main ] > test_vector - short_arr_iter[2]: 5002
// (D) [ Main ] > test_vector - short_arr_iter[3]: 5003
// (D) [ Main ] > test_vector - short_arr_iter[4]: 5004
// (D) [ Main ] > test_vector - short_arr_iter[5]: 5005
// (D) [ Main ] > test_vector - short_arr_iter[6]: 5006
// (D) [ Main ] > test_vector - short_arr_iter[7]: 5007
// (D) [ Main ] > test_vector - short_arr_iter[8]: 5008
// (D) [ Main ] > test_vector - short_arr_iter[9]: 5009
// (D) [ Main ] > test_vector - short_arr_iter[10]: 6000

// `Vec_join` get back a `String` instance
String u16_vec_desc = Vec_join(u16_vec, " , ", NULL);
printf("\n>>> u16_vec_desc: %s\n", Str_as_str(u16_vec_desc));
Str_free(u16_vec_desc);
// (D) [ String ] > from_empty - self ptr: 0x54743a0
// >>> u16_vec_desc: 5000 , 5001 , 5002 , 5003 , 5004 , 5005 , 5006 , 5007 , 5008 , 5009 , 6000

// Auto free when out of scope
// (D) [ Vector ] > auto_free_vector - out of scope with vector ptr: 0x5474260, length: 11
```

</br>

#### 1.3 Get element via `index`:

```c
// Double list
double double_arr[] = {11.11, 22.22, 33.33};
usize double_type_size = sizeof(double);
usize double_arr_len = sizeof(double_arr) / sizeof(double_arr[0]);

SMART_VECTOR_WITH_CAPACITY(double_vec, double, double_arr_len);
for (usize di = 0; di < double_arr_len; di++) {
    Vec_push(double_vec, &double_arr[di]);
}

const double *d_value_1 = (const double *)Vec_get(double_vec, 0);
const double *d_value_2 = (const double *)Vec_get(double_vec, 1);
const double *d_value_3 = (const double *)Vec_get(double_vec, 2);

DEBUG_LOG(Main, test_vector, "d_value_1: %f", *d_value_1);
DEBUG_LOG(Main, test_vector, "d_value_2: %f", *d_value_2);
DEBUG_LOG(Main, test_vector, "d_value_3: %f", *d_value_3);

// (D) [ Main ] > test_vector - d_value_1: 11.110000
// (D) [ Main ] > test_vector - d_value_2: 22.220000
// (D) [ Main ] > test_vector - d_value_3: 33.330000⏎
// (D) [ Vector ] > auto_free_vector - out of scope with vector ptr: 0x5473210, length: 3
```

</br>

#### 1.4 Use `String`:

```c
//
// String vec
//
SMART_STRING(temp_str_1) = Str_from_str("Vector works:)");
SMART_STRING(temp_str_2) = Str_from_str("Generic vector works:)");
SMART_STRING(temp_str_3) =
    Str_from_str("My Generic vector works, yeah!!!:)>>>>:(");

SMART_VECTOR_WITH_CAPACITY(string_vec, struct Str, 3);
Vec_push(string_vec, temp_str_1);
Vec_push(string_vec, temp_str_2);
Vec_push(string_vec, temp_str_3);

String string_vec_desc = Vec_join(string_vec, " , ", NULL);
printf("\n>>> string_vec: %s\n", Str_as_str(string_vec_desc));
Str_free(string_vec_desc);

// (D) [ String ] > from_str - self ptr: 0x5475050, malloc ptr: 0x54750a0, from_str: Vector works:)
// (D) [ String ] > from_str - self ptr: 0x54750f0, malloc ptr: 0x5475140, from_str: Generic vector works:)
// (D) [ String ] > from_str - self ptr: 0x54751a0, malloc ptr: 0x54751f0, from_str: My Generic vector works, yeah!!!:)>>>>:(
// (D) [ Vector ] > with_capacity - self pointer: 0x5475260, element_type_size: 16, capacity: 3, self->items: 0x54752d0
// (D) [ String ] > from_empty - self ptr: 0x5475340
// >>> string_vec: Vector works:) , Generic vector works:) , My Generic vector works, yeah!!!:)>>>>:(

// (D) [ Vector ] > auto_free_vector - out of scope with vector ptr: 0x5475260, length: 3
```

</br>

#### 1.5 Custom struct case:

```c
typedef struct {
    char first_name[10];
    char last_name[10];
    u8 age;
} Person;

// Used in `Vec_join`: Get back custom `String`
String get_person_desc(Person *self) {
    usize buffer_size = sizeof(Person) + 34 + 1;
    char buffer[sizeof(Person) + 34 + 1] = {0};
    snprintf(buffer, buffer_size, "(first_name: %s, last_name: %s, age: %u)",
                self->first_name, self->last_name, self->age);
    String desc = Str_from_str(buffer);
    return desc;
}

//
// Person list
//
SMART_VECTOR(person_list, Person);
// (D) [ Vector ] > with_capacity - self pointer: 0x54755c0, element_type_size: 21, capacity: 3, self->items: 0x5475630

Person wison = {.first_name = "Mr C", .last_name = "cool", .age = 88};
Person fion = {.first_name = "Mr CPP", .last_name = "not bad", .age = 99};
Person nobody = {.first_name = "Nobody", .last_name = "Nothing", .age = 100};
Vec_push(person_list, &wison);
Vec_push(person_list, &fion);
Vec_push(person_list, &nobody);

// Print element value
VectorIteractor person_list_iter = Vec_iter(person_list);
Person *temp_person_arr = (Person *)person_list_iter.items;
for (usize index = 0; index < person_list_iter.length; index++) {
    DEBUG_LOG(Main, test_vector, "person_list_iter[%lu].first_name: %s",
                index, temp_person_arr[index].first_name);
    DEBUG_LOG(Main, test_vector, "person_list_iter[%lu].last_name: %s",
                index, temp_person_arr[index].last_name);
    DEBUG_LOG(Main, test_vector, "person_list_iter[%lu].age: %u", index,
                temp_person_arr[index].age);
}

// (D) [ Main ] > test_vector - person_list_iter[0].first_name: Mr C
// (D) [ Main ] > test_vector - person_list_iter[0].last_name: cool
// (D) [ Main ] > test_vector - person_list_iter[0].age: 88
// (D) [ Main ] > test_vector - person_list_iter[1].first_name: Mr CPP
// (D) [ Main ] > test_vector - person_list_iter[1].last_name: not bad
// (D) [ Main ] > test_vector - person_list_iter[1].age: 99
// (D) [ Main ] > test_vector - person_list_iter[2].first_name: Nobody
// (D) [ Main ] > test_vector - person_list_iter[2].last_name: Nothing
// (D) [ Main ] > test_vector - person_list_iter[2].age: 100


String person_vec_desc = Vec_join(
    person_list, " , ", (struct Str * (*)(void *)) get_person_desc);
printf("\n>>> person_vec: %s\n", Str_as_str(person_vec_desc));
Str_free(person_vec_desc);

// >>> person_vec: (first_name: Mr C, last_name: cool, age: 88) , (first_name: Mr CPP, last_name: not bad, age: 99) , (first_name: Nobody, last_name: Nothing, age: 100)

// (D) [ Vector ] > auto_free_vector - out of scope with vector ptr: 0x54755c0, length: 3
```

</br>

## 2. `SingleLinkList`

This `LinkList` doesn't support normal generic `<T>` (no auto element type
inference), that's why you have to provide the `sizeof(ELEMENT_TYPE)` when
appending an element to the `LinkList`.

When appending an element, `LinkList` executes a shallow copy which means
doesn't copy the internal heap-allocated content!!!

</br>

#### 2.1 Concept

A `LinkedList` is a sequential list of nodes that hold data which point to other nodes also containing data.

**Head** --> Node ---> Node --> **Tail**

- `Head`: the first node in the list.
- `Tail`: the last node in the list.
- `Node`: An object containing data and pointer(s).

</br>

- `SingleLinkedList`: Each node only hold the reference to the next node.
- `DoubleLinkedList`: Each node holds the reference to the next node and the previous node at the same time.

</br>

#### 2.2 use cases

- Used in many `List`, `Queue` and `Stack` implementation.
- Great for creating circular lists.
- Used in separated chaining, which is present certain `hasttable` implementations to deal with hashing collisions.
- Often used in implementation of adjacency list for graphs.

</br>

#### 2.3 Props and cons

| |Props | Cons
|-----: | ---- | -------
| **SingleLinkedList** | _Use less memory_</br>_Simpler implementation_ | _Cannot easily access previous element_
| **DoubleLinkedList** |_Can easily access backwards_ | _Takes 2X memory_

</br>

#### 2.4 Complexity

| |SingleLinkedList | DoubleLinkedList
|-----: | ---- | -------
| **Search** | **O(n)** | **O(n)**
| **Insert at head** |**O(1)** | **O(1)**
| **Insert at tail** |**O(1)** | **O(1)**
| **Remove at head** |**O(1)** | **O(1)**
| **Remove at tail** |**O(n)** | **O(1)**
| **Remove in middle** |**O(n)** | **O(n)**

</br>


Examples:

#### 2.5 Stack-allocated

If you need stack-allocated instance, you have to init and free explicitly.

```c
usize init_value = 8888;

struct LL list;
LL_init_empty(&list);
LL_append_value(&list, sizeof(usize), &init_value, NULL);

LL_free(&list, false, NULL);
```

</br>

#### 2.6 Heap-allocated

If you need heap-allocated instance, you should use `SMART_LINKLIST` macro
to create `LinkList` (opaque pointer to `struct LL`), as it will be freed
automatic!!!


```c
SMART_LINKLIST(short_int_list) = LL_from_empty();

// Append a few nodes
usize values[] = {111, 222, 333, 444, 555};
LL_append_value(short_int_list, sizeof(uint16), &values[0], NULL);
LL_append_value(short_int_list, sizeof(uint16), &values[1], NULL);
LL_append_value(short_int_list, sizeof(uint16), &values[2], NULL);
LL_append_value(short_int_list, sizeof(uint16), &values[3], NULL);
LL_append_value(short_int_list, sizeof(uint16), &values[4], NULL);

// Get back the iter and check all data
SMART_LINKLIST_ITERATOR(iter) = LL_iter(short_int_list);
for (usize iter_index = 0; iter_index < iter->length; iter_index++) {
    usize temp_value = *((uint16_t *)iter->data_arr[iter_index]);
    printf("\n>>>> temp_value: %lu", temp_value);
}


// (D) [ SingleLinkList ] > from_empty - self ptr: 0x54732e0
// (D) [ SingleLinkList ] > LL_iter - self ptr: 0x54732e0, iter ptr: 0x5473660
// >>>> temp_value: 111
// >>>> temp_value: 222
// >>>> temp_value: 333
// >>>> temp_value: 444
// >>>> temp_value: 555
// (D) [ SingleLinkList ] > auto_free_linklist_iter - out of scope with LinkListIterator ptr: 0x5473660
// (D) [ SingleLinkList ] > auto_free_linklist - out of scope with LinkList ptr: 0x54732e0
// (D) [ SingleLinkList ] > free - self ptr: 0x54732e0, total free node amount: 5, total free node data amount: 5
```

</br>
