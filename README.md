# `c-utils`

This is my personal `C` utilities which contains the following modules:

</br>

- `Collection/SingleLinkList`: Heap allocated single link list.

    This `LinkList` doesn't support normal generic `<T>` (no auto element type
    inference), that's why you have to provide the `sizeof(ELEMENT_TYPE)` when
    appending an element to the `LinkList`.

    When appending an element, `LinkList` executes a shallow copy which means
    doesn't copy the internal heap-allocated content!!!

    </br>

    - Concept:

        A `LinkedList` is a sequential list of nodes that hold data which point to other nodes also containing data.

        **Head** --> Node ---> Node --> **Tail**

        - `Head`: the first node in the list.
        - `Tail`: the last node in the list.
        - `Node`: An object containing data and pointer(s).

        </br>

        - `SingleLinkedList`: Each node only hold the reference to the next node.
        - `DoubleLinkedList`: Each node holds the reference to the next node and the previous node at the same time.

        </br>

    - use cases:

        - Used in many `List`, `Queue` and `Stack` implementation.
        - Great for creating circular lists.
        - Used in separated chaining, which is present certain `hasttable` implementations to deal with hashing collisions.
        - Often used in implementation of adjacency list for graphs.

        </br>

    - Props and cons:

        | |Props | Cons
        |-----: | ---- | -------
        | **SingleLinkedList** | _Use less memory_</br>_Simpler implementation_ | _Cannot easily access previous element_
        | **DoubleLinkedList** |_Can easily access backwards_ | _Takes 2X memory_

        </br>

    - Complexity

        | |SingleLinkedList | DoubleLinkedList
        |-----: | ---- | -------
        | **Search** | **O(n)** | **O(n)**
        | **Insert at head** |**O(1)** | **O(1)**
        | **Insert at tail** |**O(1)** | **O(1)**
        | **Remove at head** |**O(1)** | **O(1)**
        | **Remove at tail** |**O(n)** | **O(1)**
        | **Remove in middle** |**O(n)** | **O(n)**

        </br>

    - Interfaces

        ```c
        //----------------------------------------------------------------------------
        // LinkListNdoe opaque pointer to `struct LLNode`
        //----------------------------------------------------------------------------
        typedef struct LLNode *LinkListNode;

        //----------------------------------------------------------------------------
        // LinkList
        //----------------------------------------------------------------------------
        struct LL {
            size_t _len;
            LinkListNode _head;
            LinkListNode _tail;
        };

        //----------------------------------------------------------------------------
        // LinkList opaque pointer to `struct LL`
        //----------------------------------------------------------------------------
        typedef struct LL *LinkList;

        /*
        * Define smart `LinkList` var that calls `LL_free()` automatically when the
        * variable is out of the scope
        *
        * ```c
        * SMART_LINKLIST(temp_list) = LL_from_empty();
        *
        * // (D) [ SingleLinkList ] > free - self ptr: 0x5472040, total free node
        * amount: 0, total free node data amount: 0
        * ```
        */
        #define SMART_LINKLIST(x) __attribute__((cleanup(auto_free_linklist))) LinkList x

        /*
        * Init empty list
        */
        void LL_init_empty(LinkList self);

        /*
        * Create empty list
        */
        LinkList LL_from_empty();

        /*
        * Create list and insert first node that copies from value
        */
        LinkList LL_from_value(size_t item_size, void *value,
                            CloneFromFunc clone_from_func);

        /*
        * Return the link length
        */
        size_t LL_length(const LinkList self);

        /*
        * Return the header (first node) pointer
        */
        const LinkListNode LL_get_head(const LinkList self);

        /*
        * Return the header (first node) data pointer
        */
        const void *LL_get_head_data(const LinkList self);

        /*
        * Return the tail (last node) pointer
        */
        const LinkListNode LL_get_tail(const LinkList self);

        /*
        * Return the tail (last node) data pointer
        */
        const void *LL_get_tail_data(const LinkList self);

        /*
        * Append to the tail
        *
        * LinkList executes a shallow copy which means doesn't copy the internal
        * heap-allocated content!!!
        */
        void LL_append_value(LinkList self, size_t item_size, void *value,
                            CloneFromFunc clone_from_func);

        /*
        * Iterator
        */
        typedef struct {
            size_t length;
            void *data_arr[];
        } LLIterator;

        /*
        * Define smart `LinkList` var that calls `LL_free()` automatically when the
        * variable is out of the scope
        */
        #define SMART_LINKLIST_ITERATOR(x) __attribute__((cleanup(auto_free_linklist_iter))) LLIterator *x

        /*
        * Return a `Iterator` pointer from the `LinkLiist`:
        *
        * `Iterator.length`: Shows how many data pointer in `Iterator.data_arr`.
        *
        * `Iterator.data_arr`: Stores all list node data pointer, you need to convert
        *                      the correct data type before using it. If
        * `Iterator.length` is zeor, DO NOT access this array!!!
        *
        * The returned `Iterator` pointer has to be freed by calling `LL_free_iter()`.
        */
        LLIterator *LL_iter(const LinkList self);

        /*
        * Free the given `LLIterator`
        */
        void LL_free_iter(LLIterator *iter);

        /*
        * `need_to_free_myself`: If `self` is stack-allocated, set to false!!!
        *
        * `free_func`:
        *
        * When freeing a `LLNode` instance, the best way to avoid memory issue
        * is to call the original `DataType.free(node->data)`, just in case `data` is
        * a complicated struct instance
        */
        void LL_free(LinkList self, bool need_to_free_myself, FreeFunc free_func);
        ```

        </br>

    Examples:

    - If you need stack-allocated instance, you have to init and free explicitly.

        ```c
        usize init_value = 8888;

        struct LL list;
        LL_init_empty(&list);
        LL_append_value(&list, sizeof(usize), &init_value, NULL);

        LL_free(&list, false, NULL);
        ```

        </br>

    - If you need heap-allocated instance, you should use `SMART_LINKLIST` macro
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


- `String`: Wrap and hide all `null-terminated` C-style string in `struct`,
hide the `null-terminated` detail and pointer, just deal with normal function
call.

    ```c
    //
    // Heap allocated string
    //
    typedef struct Str *String;
    
    //
    // `String` is an opaque pointer which uses to hide the `struct Str` detail,
    // which means `struct Str` doesn't exists in the outside world. If you want
    // to get back `sizeof(struct Str)` for some reasons, this function is the
    // anwser.
    //
    const usize Str_struct_size();

    /*
     * Define smart `String` var that calls `Str_free()` automatically when the
     * variable is out of the scope
     *
     * ```c
     * SMART_STRING(src_str) = Str_from_str("Hey:)");
     *
     * // (D) [ String ] > auto_free_string - out of scope with string ptr: 0x5473850, as_str: Hey:)
     * ```
     */
    #define SMART_STRING(x) \
        __attribute__((cleanup(auto_free_string))) String x

    /*
     * Create from empty
     */
    String Str_from_empty();

    /*
     * Create from `char[]`
     */
    String Str_from_arr(const char arr[]);

    /*
     * Create from `char*`
     */
    String Str_from_str(const char *str);

    /*
     * Move from the given `String` instance and move ownership of the
     * heap-allocated memory to the newly created `String` instance
     */
    String Str_move_from(String other);

    /*
     * Push other `String *` at the end
     */
    void Str_push_other(String self, const String other);

    /*
     * Push the given `char *` at the end
     */
    void Str_push_str(String self, const char *str_to_push);

    /*
     * Insert `String *` to the beginning
     */
    void Str_insert_other_to_begin(String self, const String other);

    /*
     * Insert `char *` to the beginning
     */
    void Str_insert_str_to_begin(String self, const char *str_to_insert);

    /*
     * Insert `char *` at the given index
     */
    void Str_insert_at_index(String self, const char *str_to_insert,
                            usize index_to_insert);

    /*
     * Get back string length
     */
    const usize Str_length(const String self);

    /*
     * Get back `char *`
     */
    const char *Str_as_str(const String self);

    /*
     * Find the given `char *` index, return `-1` if not found.
     */
    const long Str_index_of(const String self, const char *str_to_find);

    /*
     * Find the given `char *` (case sensitive) index, return `-1` if not found.
     */
    const long Str_index_of_case_sensitive(const String self,
                                        const char *str_to_find);

    /*
     * Check whether contain the given `char *` or not
     */
    const bool Str_contains(const String self, char *str_to_check);

    /*
     * Reset  to empty string
     */
    void Str_reset_to_empty(String self);

    /*
     * Free allocated memory, reset length to 0 and internal buffer to `NULL`
     */
    void Str_free(String self);
    ```

    </br>

    Example:

    ```c
    SMART_STRING(my_name) = Str_from_str("Wison Ye:)");

    SMART_STRING(empty_str_1) = Str_from_str(NULL);
    SMART_STRING(empty_str_2) = Str_from_str("");

    SMART_STRING(clone_from_empty_str) = Str_clone(my_name);
    DEBUG_LOG(Main, StringTest, "clone_from_empty_str len: %lu, value: %s",
              Str_length(clone_from_empty_str),
              Str_as_str(clone_from_empty_str) == NULL
                  ? "NULL"
                  : Str_as_str(clone_from_empty_str));

    // (D) [ Main ] > StringTest - clone_from_empty_str len: 8, value: Wison Ye⏎

    char temp_id[] = "123456789";
    char temp_id_2[] = {'A', 'B', 'C', 'D', '\0'};
    String str_1 = Str_from_arr(temp_id);
    String str_2 = Str_from_arr(temp_id_2);

    //
    // If you use `SMART_STRING()` macro, then you don't need to free string
    // explicitly. `Str_free()` will be guaranteed to be called when variables
    // are out of scope.
    //
    // Str_free(my_name);
    // Str_free(empty_str_1);
    // Str_free(empty_str_2);
    // Str_free(clone_from_empty_str);
    // Str_free(str_1);
    // Str_free(str_2);
    ```

    The `SMART_STRING` macro ensures the `SingleLinkList` instance auto-free
    heap-allocated memory when it goes out of its scope.

    </br>

- `Vector`: Heap allocated dynamic array.

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

    - Create empty vector:

        ```c
        // `SMART_VECTOR(variable_name, element_type);`
        SMART_VECTOR(empty_vec, usize);
        // (D) [ Vector ] > auto_free_vector - out of scope with vector ptr: 0x5472040, length: 0
        ```

        </br>

    - Create empty vector with pre-allocated space to avoid `realloc` cost:

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
        String u16_vec_desc = Vec_join(u16_vec, " , ");
        printf("\n>>> u16_vec_desc: %s\n", Str_as_str(u16_vec_desc));
        Str_free(u16_vec_desc);
        // (D) [ String ] > from_empty - self ptr: 0x54743a0
        // >>> u16_vec_desc: 5000 , 5001 , 5002 , 5003 , 5004 , 5005 , 5006 , 5007 , 5008 , 5009 , 6000

        // Auto free when out of scope
        // (D) [ Vector ] > auto_free_vector - out of scope with vector ptr: 0x5474260, length: 11
        ```

        </br>

    - Get element via `index`:

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

    - Use `String`:

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

        String string_vec_desc = Vec_join(string_vec, " , ");
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

    - Custom struct case:

        ```c
        // Person list
        typedef struct {
            char first_name[10];
            char last_name[10];
            u8 age;
        } Person;

        Person wison = {.first_name = "Wison", .last_name = "Ye", .age = 88};
        Person fion = {.first_name = "Fion", .last_name = "Li", .age = 99};
        Person nobody = {
            .first_name = "Nobody", .last_name = "Nothing", .age = 100};

        SMART_VECTOR(person_list) = Vec_new(sizeof(Person));

        Vector_push(person_list, &wison);
        Vector_push(person_list, &fion);
        Vector_push(person_list, &nobody);

        VectorIteractor person_list_iter = Vector_iter(person_list);
        Person *temp_person_arr = (Person *)person_list_iter.items;
        for (usize index = 0; index < person_list_iter.length; index++) {
            DEBUG_LOG(Main, test_vector, "person_list_iter[%lu].first_name: %s",
                    index, temp_person_arr[index].first_name);
            DEBUG_LOG(Main, test_vector, "person_list_iter[%lu].last_name: %s",
                    index, temp_person_arr[index].last_name);
            DEBUG_LOG(Main, test_vector, "person_list_iter[%lu].age: %u", index,
                    temp_person_arr[index].age);
        }

        // (D) [ Main ] > test_vector - person_list_iter[0].first_name: Wison
        // (D) [ Main ] > test_vector - person_list_iter[0].last_name: Ye
        // (D) [ Main ] > test_vector - person_list_iter[0].age: 88
        // (D) [ Main ] > test_vector - person_list_iter[1].first_name: Fion
        // (D) [ Main ] > test_vector - person_list_iter[1].last_name: Li
        // (D) [ Main ] > test_vector - person_list_iter[1].age: 99
        // (D) [ Main ] > test_vector - person_list_iter[2].first_name: Nobody
        // (D) [ Main ] > test_vector - person_list_iter[2].last_name: Nothing
        // (D) [ Main ] > test_vector - person_list_iter[2].age: 100
        // (D) [ Vector ] > auto_free_vector - out of scope with vector ptr: 0x5473360, length: 3
        ```

        </br>


    - Use `String` (struct Str*) case:

        ```c
        SMART_VECTOR(vec) = Vector_new(Str_struct_size());

        //
        // Create smart string: de-allocated automatic when out of scope
        //
        SMART_STRING(str1) = Str_from_str("String in vector");
        SMART_STRING(str2) = Str_from_str("Second string in vector");

        //
        // `Str_struct_size()` return `sizeof(struct Str)`, otherwise, it
        // won't work without correct struct size!!!
        //
        Vector_push(vec, str1);
        Vector_push(vec, str2);
        printf("\n>>> Str_struct_size(): %lu", Str_struct_size());

        const String ele1 = (const String)Vector_get(vec, 0);
        const String ele2 = (const String)Vector_get(vec, 1);
        printf("\n>>> ele1 ptr: %p, value: %s", ele1, Str_as_str(ele1));
        printf("\n>>> ele2 ptr: %p, value: %s", ele2, Str_as_str(ele2));

        const VectorIteractor vec_it = Vector_iter(vec);
        void *it_string_item = vec_it.items;

        //
        // As `it_string_item[i]` is `struct Str` which doesn't exis in the
        // outside world, that's why you CANNOT access String element in
        // that way.
        //
        // You have to use `void *` + offset to get back the correct `String`
        // (opaque pointer to `struct Str`) before accessing `String` element.
        //
        for (usize i = 0; i < vec_it.length; i++) {
            String temp_str = (String)(it_string_item + i * Str_struct_size());
            DEBUG_LOG(Main, test_vector_element_destructor,
                      "vec element ptr: %p, string value: %s", temp_str,
                      Str_as_str(temp_str));
        }
        ```

        </br>

- `Log`: Handy logging implementation.

    - `LOG_VAR` macro, only available when `ENABLE_DEBUG_LOG` is defined!!!

        Use to print the single variable's value, only for debugging purpose.

        ```c
        char *string_value = "Wison Ye";
        char char_value = 'c';
        u8 u8_value = 255;

        LOG_VAR(string_value);
        LOG_VAR(char_value);
        LOG_VAR(u8_value);

        LOG_VAR(sizeof(int));
        LOG_VAR(sizeof(long));

        // >>> string_value: Wison Ye
        // >>> char_value: c
        // >>> u8_value: 255
        // >>> sizeof(int): 4
        // >>> sizeof(long): 8
        ```

        </br>

    - `printf` liked formatted logger

        ```c
        #include "utils/log.h"
        #include "utils/string.h"

        String my_str = Str_from_str("My name is Wison Ye");
        DEBUG_LOG(Main, main, "add(2, 3): %d", add(2, 3));
        DEBUG_LOG(Main, main, "2 + 2 :%d", 2 + 2);
        DEBUG_LOG(Main, main, "my_str value is: %s", Str_as_str(my_str));
        INFO_LOG(Main, main, "my_str value is: %s", Str_as_str(my_str));
        WARN_LOG(Main, main, "my_str value is: %s", Str_as_str(my_str));
        ERROR_LOG(Main, main, "my_str value is: %s", Str_as_str(my_str));

        // (D) [ Main ] > main - add(2, 3): 5
        // (D) [ Main ] > main - 2 + 2 :4
        // (D) [ Main ] > main - my_str value is: My name is Wison Ye
        // (I) [ Main ] > main - my_str value is: My name is Wison Ye
        // (W) [ Main ] > main - my_str value is: My name is Wison Ye
        // (E) [ Main ] > main - my_str value is: My name is Wison Ye⏎
        ```

        </br>

- `HexBuffer`: Handle convertion between `char *` and `u8[]`

    ```c
    /*
     * Opaque pointer to `struct _HexBuffer`
     */
    typedef struct _HexBuffer *HexBuffer;

    /*
     * Iteractor
     */
    typedef struct {
        usize length;
        u8 *arr;
    } HexBufferIteractor;

    /*
     * Create `HexBuffer` from the given `char *`. Only accept `0~9` `a~f` `A~F`
     * characters, all another characters will be ignored.
     *
     * Return `NULL` if:
     *
     * - `hex_str` is NULL or empty string
     * - `hex_str` (after ignored all invalid characters) has an odd length
     */
    HexBuffer Hex_from_string(const char *hex_str);

    /*
     * Return the hex buffer length
     */
    usize Hex_length(HexBuffer self);

    /*
     * Return `out_buffer` size (same with strlen()) if `HexBuffer` is an valid
     * `HexBuffer`.
     *
     * Return 0 when something wrong
     * Return -1 when `out_buffer_size` is not big enough to hold the hex string.
     */
    int Hex_to_string(const HexBuffer self, char *out_buffer,
                      usize out_buffer_size);

    /*
     * Return the u8 array iterator
     */
    const HexBufferIteractor Hex_iter(const HexBuffer self);

    /*
     * Free
     */
    void Hex_free(HexBuffer self);
    ```

    </br>

    Example:

    - `char *` to `HexBuffer`

        ```c
        char hex_str_1[] = "AABBCCDD";
        HexBuffer buffer_1 = Hex_from_string(hex_str_1);
        HexBufferIteractor hex_iter = Hex_iter(buffer_1);
        for (usize index = 0; index < hex_iter.length; index++) {
            printf("\n>>> hex_iter[%lu]: 0x%02X", index, hex_iter.arr[index]);
        }

        // (D) [ HexBuffer ] > Hex_from_string - valid_hex_str len: 8, value: AABBCCDD
        // (D) [ HexBuffer ] > Hex_from_string - temp_hex_str: AA, strlen: 2
        // (D) [ HexBuffer ] > Hex_from_string - buffer->_buffer[0]: AA
        // (D) [ HexBuffer ] > Hex_from_string - temp_hex_str: BB, strlen: 2
        // (D) [ HexBuffer ] > Hex_from_string - buffer->_buffer[1]: BB
        // (D) [ HexBuffer ] > Hex_from_string - temp_hex_str: CC, strlen: 2
        // (D) [ HexBuffer ] > Hex_from_string - buffer->_buffer[2]: CC
        // (D) [ HexBuffer ] > Hex_from_string - temp_hex_str: DD, strlen: 2
        // (D) [ HexBuffer ] > Hex_from_string - buffer->_buffer[3]: DD
        // >>> hex_iter[0]: 0xAA
        // >>> hex_iter[1]: 0xBB
        // >>> hex_iter[2]: 0xCC
        // >>> hex_iter[3]: 0xDD
        ```

        </br>

    - `HexBuffer` to `char *`

        ```c
        // `+1` is for the `null-terminated` character
        usize out_buffer_size = Hex_length(buffer_1) * 2 + 1;

        // Create return `char *` buffer and init to all `0`
        char hex_string[out_buffer_size];
        memset(hex_string, 0, out_buffer_size);
        PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(char [], hex_string, out_buffer_size);

        usize return_hex_len = Hex_to_string(buffer_1, hex_string, out_buffer_size);
        DEBUG_LOG(Main, test_hex_buffer, "return_hex_len: %lu", return_hex_len);
        if (return_hex_len > 0) {
            DEBUG_LOG(Main, test_hex_buffer, "hex_string len: %lu, value: %s",
                      strlen(hex_string), hex_string);
        }
        PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(char [], hex_string, out_buffer_size);

        // (D) [ Memory ] > print_memory_block - [ char [] hex_string, size: 9 ]
        // (D) [ Memory ] > print_memory_block - ------------------
        // (D) [ Memory ] > print_memory_block - 000000000000000000
        // (D) [ Memory ] > print_memory_block - ------------------
        // 
        // (D) [ HexBuffer ] > Hex_to_string - copied_buffer_size: 8, out_buffer_size: 9
        // (D) [ HexBuffer ] > Hex_to_string - self->_len: 4, copied_buffer_size: 8, self->_buffer: 0xAABBCCDD
        // (D) [ HexBuffer ] > Hex_to_string - copied_size: 2, hex_value: AA
        // (D) [ HexBuffer ] > Hex_to_string - copied_size: 2, hex_value: BB
        // (D) [ HexBuffer ] > Hex_to_string - copied_size: 2, hex_value: CC
        // (D) [ HexBuffer ] > Hex_to_string - copied_size: 2, hex_value: DD
        // (D) [ Main ] > test_hex_buffer - return_hex_len: 8
        // (D) [ Main ] > test_hex_buffer - hex_string len: 8, value: AABBCCDD
        // (D) [ Memory ] > print_memory_block - [ char [] hex_string, size: 9 ]
        // (D) [ Memory ] > print_memory_block - ------------------
        // (D) [ Memory ] > print_memory_block - 414142424343444400
        // (D) [ Memory ] > print_memory_block - ------------------
        ```

        </br>


- `Memory`: Handy memory utils.

    - `PRINT_MEMORY_BLOCK` macro, only available when `ENABLE_DEBUG_LOG` is defined!!!

        used to print the memory block data in HEX format from a given variable.

        ```c
        struct Person {
            char birthday[9];
            u8 age;
        };

        struct Person me = {
            .birthday = "19880531",
            .age = 0xAA,
        };
        PRINT_MEMORY_BLOCK(struct Person, me)

        int data = 10;
        PRINT_MEMORY_BLOCK(int, data);

        // (D) [ Memory ] > print_memory_block - [ struct Person me, size: 10 ]
        // (D) [ Memory ] > print_memory_block - --------------------
        // (D) [ Memory ] > print_memory_block - 313938383035333100AA
        // (D) [ Memory ] > print_memory_block - --------------------
        //
        // (D) [ Memory ] > print_memory_block - [ int data, size: 4 ]
        // (D) [ Memory ] > print_memory_block - --------
        // (D) [ Memory ] > print_memory_block - 0A000000
        // (D) [ Memory ] > print_memory_block - --------
        ```

        </br>

    - `PRINT_MEMORY_BLOCK_FOR_SMART_TYPE` macro, only available when
    `ENABLE_DEBUG_LOG` is defined!!!

        It works like the same with the `PRINT_MEMORY_BLOCK` macro but focuses
        on the`SMART_XXXX` variable case, as those variables are `opaque pointer`
        types without the original `struct` type available.

        ```c
        SMART_STRING(str1) = Str_from_str("String in vector");
        PRINT_MEMORY_BLOCK_FOR_SMART_TYPE(struct Str, str1, Str_struct_size());

        // (D) [ String ] > from_str - self ptr: 0x82346a000, malloc ptr: 0x82346b000, from_str: String in vector
        // (D) [ Memory ] > print_memory_block - [ struct Str str1, size: 16 ]
        // (D) [ Memory ] > print_memory_block - --------------------------------
        // (D) [ Memory ] > print_memory_block - 100000000000000000B0462308000000
        // (D) [ Memory ] > print_memory_block - --------------------------------
        ```

        As you can see above, proven by the `lldb` memory block printing in
        `Big Endian` order:

        ```bash
        (lldb) v str1
        # (String) str1 = 0x000000082346a000

        (lldb) memory read -s `sizeof(struct Str)` -c1 -fX `str1`
        # 0x82346a000: 0x000000082346B0000000000000000010
        ```

        </br>


- `Timer`: High resolution timer utils

    ```c
    //
    // Time unit
    //
    typedef enum TimeUnit {
        TU_NANOSECONDS = 0x01,
        TU_MICROSECONDS = 0x02,
        TU_MILLISECONDS = 0x03,
        TU_SECONDS = 0x04,
    } TimeUnit;

    /*
     * Get back current time in the given time unit
     */
    long double Timer_get_current_time(TimeUnit time_unit);
    ```

    </br>

    Example:

    ```c
    long double start_time = Timer_get_current_time(TU_NANOSECONDS);
    long double end_time = Timer_get_current_time(TU_NANOSECONDS);
    long double elapsed_time = end_time - start_time;

    DEBUG_LOG(Main, test_timer, "elapsed_time: %Lf\n", elapsed_time);
    ```

    </br>

    ```bash
    time ./build_memory_leak_checking/c-utils

    # (D) [ Timer ] > Timer_get_current_time - FreeBSD Initialization
    # (D) [ Main ] > test_timer - elapsed_time: 238.000000
    # 
    # ________________________________________________________
    # Executed in    3.35 millis    fish           external
    #    usr time    0.98 millis  981.00 micros    0.00 millis
    #    sys time    5.93 millis    0.00 micros    5.93 millis
    ```

    </br>

- `Smart ptr`:

    `make_unique_ptr` simulates the `std::make_unique` in `C++`:

    </br>

    ```c
    String return_string_on_the_heap() {
        String str_on_the_heap = Str_from_str("String allocated on the heap:)");
        return str_on_the_heap;
    }

    Vector return_vector_on_the_heap() {
        usize double_size = sizeof(double);
        Vector temp_vec = Vector_with_capacity(5, double_size);
        double d = 888.88;
        Vector_push(temp_vec, &d, double_size);
        return temp_vec;
    }

    void test_smart_ptr() {
        //
        // `return_str` will be destroyed by calling `auto_free_string` automatic
        //
        make_unique_ptr(String return_str = return_string_on_the_heap(),
                        auto_free_string);

        //
        // `return_vector` will be destroyed by calling `auto_free_vector` automatic
        //
        make_unique_ptr(Vector return_vec = return_vector_on_the_heap(),
                        auto_free_vector);

        DEBUG_LOG(Main, test_smart_ptr, "return_str: %p, value: %s", return_str,
                  Str_as_str(return_str));
        DEBUG_LOG(Main, test_smart_ptr,
                  "return_vec: %p, len: %lu, first elemnt: %f", return_vec,
                  Vector_len(return_vec),
                  *((double *)Vector_get(return_vec, 0, sizeof(double))));
    }

    // (D) [ String ] > from_str - self ptr: 0x5472040, malloc ptr: 0x5472090, from_str: String allocated on the heap:)
    // (D) [ Vector ] > with_capacity - self pointer: 0x5474130, capacity: 5
    // (D) [ Main ] > test_smart_ptr - return_str: 0x5472040, value: String allocated on the heap:)
    // (D) [ Main ] > test_smart_ptr - return_vec: 0x5474130, len: 1, first elemnt: 888.880000
    // (D) [ Vector ] > auto_free_vector - out of scope with vector ptr: 0x5474130, length: 1
    // (D) [ String ] > auto_free_string - out of scope with string ptr: 0x5472040, as_str: String allocated on the heap:)==42550==
    ```

    </br>

- `Bits`: handy macros to handle bits, only available when `ENABLE_DEBUG_LOG` is defined!!!

    - `PRINT_BITS`

        ```c
        unsigned char status = 0x3D;
        PRINT_BITS(status);

        unsigned short int status_16 = 0x376D;
        PRINT_BITS(status_16);

        int status_32 = 0x376DAA0B;
        PRINT_BITS(status_32);

        long long status_64 = 0x376DAA0B5F8E9ABC;
        PRINT_BITS(status_64);

        // (D) [ Bits ] > PRINT_BITS "u08" - >>> 0x3D bits: 00111101
        // (D) [ Bits ] > PRINT_BITS "u16" - >>> 0x376D bits: 0011011101101101
        // (D) [ Bits ] > PRINT_BITS "u32" - >>> 0x376DAA0B bits: 00110111011011011010101000001011
        // (D) [ Bits ] > PRINT_BITS "u64" - >>> 0x376DAA0B5F8E9ABC bits: 0011011101101101101010100000101101011111100011101001101010111100
        ```

        </br>

    - `IS_BIT_1`: Check whether the given bit is `1` or not

        ```c
        v = 0xCD;
        PRINT_BITS(v);
        which_bit = 1;
        printf("\n>>> bit %d in '0x%02X' is 1?: %s", which_bit, v,
               v >> (which_bit - 1) & 0x01 ? "Yes" : "No");
        which_bit = 2;
        printf("\n>>> bit %d in '0x%02X' is 1?: %s", which_bit, v,
               v >> (which_bit - 1) & 0x01 ? "Yes" : "No");
        which_bit = 3;
        printf("\n>>> bit %d in '0x%02X' is 1?: %s", which_bit, v,
               v >> (which_bit - 1) & 0x01 ? "Yes" : "No");
        which_bit = 4;
        printf("\n>>> bit %d in '0x%02X' is 1?: %s", which_bit, v,
               v >> (which_bit - 1) & 0x01 ? "Yes" : "No");
        which_bit = 5;
        printf("\n>>> bit %d in '0x%02X' is 1?: %s", which_bit, v,
               v >> (which_bit - 1) & 0x01 ? "Yes" : "No");
        which_bit = 6;
        printf("\n>>> bit %d in '0x%02X' is 1?: %s", which_bit, v,
               v >> (which_bit - 1) & 0x01 ? "Yes" : "No");
        which_bit = 7;
        printf("\n>>> bit %d in '0x%02X' is 1?: %s", which_bit, v,
               v >> (which_bit - 1) & 0x01 ? "Yes" : "No");
        which_bit = 8;
        printf("\n>>> bit %d in '0x%02X' is 1?: %s", which_bit, v,
               v >> (which_bit - 1) & 0x01 ? "Yes" : "No");

        // (D) [ Bits ] > PRINT_BITS "u08" - >>> 0xCD bits: 11001101
        // >>> bit 1 in '0xCD' is 1?: Yes
        // >>> bit 2 in '0xCD' is 1?: No
        // >>> bit 3 in '0xCD' is 1?: Yes
        // >>> bit 4 in '0xCD' is 1?: Yes
        // >>> bit 5 in '0xCD' is 1?: No
        // >>> bit 6 in '0xCD' is 1?: No
        // >>> bit 7 in '0xCD' is 1?: Yes
        // >>> bit 8 in '0xCD' is 1?: Yes
        ```

        </br>



### 0. `CMake` configurations

This project has 2 `cmake` setups for different purposes:

- `use_c_compiler_to_run_main/CMakeLists.txt`

   Use `C` compiler to compile `main.c` and then use `memory leaking tools` to
   check memory leaking issue on the pure `C` binary. Otherwise, if I use `CPP`
   compiler to compile the binary which links to `gtest`, then faulty memory
   leaking is detected!!!

   </br>


- `use_cpp_compiler_to_run_googletest/CMakeLists.txt`

    As `GoogleTest` only work for `CPP`, that's why you need the separated `CPP`
    compilation setup.

    </br>



### 1. Make sure you compile and install `GoogleTest`

```bash
cd ~/temp
git clone https://github.com/google/googletest.git -b release-1.12.1
cd googletest        # Main directory of the cloned repository.
mkdir build          # Create a directory to hold the build output.
cd build
cmake .. -DBUILD_GMOCK=OFF

# -- The C compiler identification is Clang 14.0.5
# -- The CXX compiler identification is Clang 14.0.5
# -- Detecting C compiler ABI info
# -- Detecting C compiler ABI info - done
# -- Check for working C compiler: /usr/bin/cc - skipped
# -- Detecting C compile features
# -- Detecting C compile features - done
# -- Detecting CXX compiler ABI info
# -- Detecting CXX compiler ABI info - done
# -- Check for working CXX compiler: /usr/bin/c++ - skipped
# -- Detecting CXX compile features
# -- Detecting CXX compile features - done
# -- Found Python: /usr/local/bin/python3.9 (found version "3.9.16") found components: Interpreter
# -- Performing Test CMAKE_HAVE_LIBC_PTHREAD
# -- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Failed
# -- Looking for pthread_create in pthreads
# -- Looking for pthread_create in pthreads - not found
# -- Looking for pthread_create in pthread
# -- Looking for pthread_create in pthread - found
# -- Found Threads: TRUE
# -- Configuring done
# -- Generating done
# -- Build files have been written to: /usr/home/wison/googletest/build
```

</br>

Install headers and libs:

```bash
doas make install

# [ 25%] Building CXX object googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
# [ 50%] Linking CXX static library ../lib/libgtest.a
# [ 50%] Built target gtest
# [ 75%] Building CXX object googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
# [100%] Linking CXX static library ../lib/libgtest_main.a
# [100%] Built target gtest_main
# Install the project...
# -- Install configuration: ""
# -- Installing: /usr/local/lib/cmake/GTest/GTestTargets.cmake
# -- Installing: /usr/local/lib/cmake/GTest/GTestTargets-noconfig.cmake
# -- Installing: /usr/local/lib/cmake/GTest/GTestConfigVersion.cmake
# -- Installing: /usr/local/lib/cmake/GTest/GTestConfig.cmake
# -- Up-to-date: /usr/local/include
# -- Installing: /usr/local/include/gtest
# -- Installing: /usr/local/include/gtest/internal
# -- Installing: /usr/local/include/gtest/internal/gtest-death-test-internal.h
# -- Installing: /usr/local/include/gtest/internal/gtest-port.h
# -- Installing: /usr/local/include/gtest/internal/gtest-type-util.h
# -- Installing: /usr/local/include/gtest/internal/gtest-string.h
# -- Installing: /usr/local/include/gtest/internal/custom
# -- Installing: /usr/local/include/gtest/internal/custom/gtest-port.h
# -- Installing: /usr/local/include/gtest/internal/custom/README.md
# -- Installing: /usr/local/include/gtest/internal/custom/gtest-printers.h
# -- Installing: /usr/local/include/gtest/internal/custom/gtest.h
# -- Installing: /usr/local/include/gtest/internal/gtest-param-util.h
# -- Installing: /usr/local/include/gtest/internal/gtest-filepath.h
# -- Installing: /usr/local/include/gtest/internal/gtest-port-arch.h
# -- Installing: /usr/local/include/gtest/internal/gtest-internal.h
# -- Installing: /usr/local/include/gtest/gtest-matchers.h
# -- Installing: /usr/local/include/gtest/gtest-assertion-result.h
# -- Installing: /usr/local/include/gtest/gtest-typed-test.h
# -- Installing: /usr/local/include/gtest/gtest_pred_impl.h
# -- Installing: /usr/local/include/gtest/gtest-message.h
# -- Installing: /usr/local/include/gtest/gtest.h
# -- Installing: /usr/local/include/gtest/gtest-printers.h
# -- Installing: /usr/local/include/gtest/gtest-test-part.h
# -- Installing: /usr/local/include/gtest/gtest_prod.h
# -- Installing: /usr/local/include/gtest/gtest-spi.h
# -- Installing: /usr/local/include/gtest/gtest-death-test.h
# -- Installing: /usr/local/include/gtest/gtest-param-test.h
# -- Installing: /usr/local/lib/libgtest.a
# -- Installing: /usr/local/lib/libgtest_main.a
# -- Installing: /usr/local/lib/pkgconfig/gtest.pc
# -- Installing: /usr/local/lib/pkgconfig/gtest_main.pc
```

</br>

### 2. `cmake` setup and run

#### 2.1 Use `C` compiler to compile `main.c`

```bash
# Make sure you're in the project root folder
./configure_valgrind.sh
```

</br>

It Generates everything needs into `build_c` folder and the
`build/compile_commands.json` for `clangd_extensions` neovim plugin

</br>

Compile and run:

```bash
./run_valgrind.sh

# [100%] Built target c-utils
# ==85724== Memcheck, a memory error detector
# ==85724== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
# ==85724== Using Valgrind-3.20.0 and LibVEX; rerun with -h for copyright info
# ==85724== Command: ./c-utils
# ==85724==
# 
# // ...ignore...
# 
# ==85724== HEAP SUMMARY:
# ==85724==     in use at exit: 4,096 bytes in 1 blocks
# ==85724==   total heap usage: 37 allocs, 36 frees, 4,633 bytes allocated
# ==85724==
# ==85724== LEAK SUMMARY:
# ==85724==    definitely lost: 0 bytes in 0 blocks
# ==85724==    indirectly lost: 0 bytes in 0 blocks
# ==85724==      possibly lost: 0 bytes in 0 blocks
# ==85724==    still reachable: 0 bytes in 0 blocks
# ==85724==         suppressed: 4,096 bytes in 1 blocks
# ==85724==
# ==85724== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
# --85724--
# --85724-- used_suppression:      1 MEMCHECK-LIBC-REACHABLE-1 /usr/local/libexec/valgrind/default.supp:582 suppressed: 4,096 bytes in 1 blocks
# ==85724==
# ==85724== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

</br>

#### 2.1.1 Use `C` compiler to compile `main.c` but use Google [`AddressSanitizer`](https://github.com/google/sanitizers/wiki/AddressSanitizer) instead of `valgrind` for checking memory leaking:

```bash
# Make sure you're in the project root folder
./configure_address_sanitizer.sh
```

</br>

It Generates everything needs into `build_c` folder and the
`build/compile_commands.json` for `clangd_extensions` neovim plugin

</br>


By default, `BSD` builtin `clang/clang++` doesn't support `AddressSanitizer`.

If you want to enable `AddressSanitizer` in BSD (`MacOS` or `FreeBSD`), then
have to use installed `llvm clang/clang++` instead of the builtin `clang/clang++`!!!

Also, you need to add the following env var setting when running your binary:

```bash
ASAN_OPTIONS=detect_leaks=1 YOUR_BINARY_HERE
```

</br>


Compile and run:

```bash
./run_address_sanitizer.sh

# [100%] Built target c-utils
#
# // ...ignore...
#
# =================================================================
# ==49381==ERROR: LeakSanitizer: detected memory leaks
#
# Direct leak of 16 byte(s) in 1 object(s) allocated from:
#     #0 0x10d795000 in wrap_malloc+0xa0 (libclang_rt.asan_osx_dynamic.dylib:x86_64+0x4a000) (BuildId: eb137767d72432a1a6e32c107b9c74d42400000010000000000a0a0000010c00)
#     #1 0x10d71c549 in Str_from_str string.c:80
#     #2 0x10d71f2bd in test_string main.c:74
#     #3 0x10d722768 in main main.c:556
#     #4 0x7fff204faf3c in start+0x0 (libdyld.dylib:x86_64+0x15f3c) (BuildId: 5fbd0e1aacce36dbb11c622f26c8513232000000200000000100000000060b00)
#
# Indirect leak of 11 byte(s) in 1 object(s) allocated from:
#     #0 0x10d795000 in wrap_malloc+0xa0 (libclang_rt.asan_osx_dynamic.dylib:x86_64+0x4a000) (BuildId: eb137767d72432a1a6e32c107b9c74d42400000010000000000a0a0000010c00)
#     #1 0x10d71c593 in Str_from_str string.c:88
#     #2 0x10d71f2bd in test_string main.c:74
#     #3 0x10d722768 in main main.c:556
#     #4 0x7fff204faf3c in start+0x0 (libdyld.dylib:x86_64+0x15f3c) (BuildId: 5fbd0e1aacce36dbb11c622f26c8513232000000200000000100000000060b00)
#
# SUMMARY: AddressSanitizer: 27 byte(s) leaked in 2 allocation(s).
```

</br>


#### 2.2 Use `CPP` compiler to compile `main.cpp`

```bash
# Make sure you're in the project root folder
./configure_unit_test.sh
```

It Generates everything needs into `build_unit_test` folder and the
`build/compile_commands.json` for `clangd_extensions` neovim plugin

</br>

Pay attention to the following output:

```bash
# -- Found GTest: /usr/local/lib/cmake/GTest/GTestConfig.cmake (found version "1.12.1")
# >>> GTest_FOUND: TRUE
```

That means `cmake` find the installed `GoogleTest` and it knows where to find
the header files and link `GTest::gtest` and `GTest::gtest_main` libraries.

</br>

Compile and run all unit test:

```bash
./run_unit_test.sh

# [100%] Linking CXX executable c-utils-unit-test
# [100%] Built target c-utils-unit-test
# [==========] Running 3 tests from 1 test suite.
# [----------] Global test environment set-up.
# [----------] 3 tests from SingleLinkList
# [ RUN      ] SingleLinkList.CreateEmptyList
# [       OK ] SingleLinkList.CreateEmptyList (0 ms)
# [ RUN      ] SingleLinkList.IntegerList
# [       OK ] SingleLinkList.IntegerList (0 ms)
# [ RUN      ] SingleLinkList.DoubleList
# [       OK ] SingleLinkList.DoubleList (0 ms)
# [----------] 3 tests from SingleLinkList (0 ms total)
# 
# [----------] Global test environment tear-down
# [==========] 3 tests from 1 test suite ran. (0 ms total)
# [  PASSED  ] 3 tests.
```

</br>

#### 3. How to preview preprocess step source code

It's beneficial if you can print out the source code content after the
preprocessor step (but before throwing it into the compiler)

```bash
# `-D`: Use to define macros
# `-E`: Run the preprocessor stage.
clang -E -D ENABLE_DEBUG_LOG src/main.c | bat
```

</br>


#### 4. How to print all supported macros on current computer and OS

```bash
clang -dM -E - < /dev/null
```

</br>

Also, you can use it to confirm whether the parituclar OS macro defines or not:

```bash
clang -dM -E - < /dev/null | rg BSD
#define __FreeBSD__ 14
#define __FreeBSD_cc_version 1400001
```

</br>

Support OS:

|OPERATING SYSTEM | MACRO PRESENT | NOTES
| --------------- | ------------- | ----- |
|Windows 32 bit + 64 bit | _WIN32 | for all Windows OS ||
|Windows 64 bit | _WIN64 | Only for 64 bit Windows ||
|Apple | __APPLE__ | for all Apple OS|
|Apple | __MACH__ | alternative to above|
|iOS embedded | TARGET_OS_EMBEDDED | include TargetConditionals.h|
|iOS stimulator | TARGET_IPHONE_SIMULATOR | include TargetConditionals.h|
|iPhone | TARGET_OS_IPHONE | include TargetConditionals.h|
|MacOS | TARGET_OS_MAC | include TargetConditionals.h|
|Android | __ANDROID__ | subset of linux|
|Unix based OS | __unix__ ||
|Linux | __linux__ | subset of unix|
|POSIX based | _POSIX_VERSION | Windows with Cygwin|
|Solaris | __sun | |
|HP UX | __hpux | |
|BSD | BSD | all BSD flavors|
|DragonFly BSD | __DragonFly__ | |
|FreeBSD | __FreeBSD__ | |
|NetBSD | __NetBSD__ | |
|OpenBSD | __OpenBSD__ | |


### 4. `C` -> `Rust` transition

#### 4.1. Primitive Data Types

Here is the [`C Date Types`](https://en.wikipedia.org/wiki/C_data_types)

| **C** | **Rust** |
|-------|----------|
| [ Integer ] |
| char              | i8            |
| unsigned char     | u8            |
| short             | i16           |
| unsigned short    | u16           |
| int               | i32           |
| unsigned int      | u32           |
| long              | i64           |
| unsigned long     | u64           |
| size_t            | u64/usize (But u32 in `FreeBSD`)     |
| [ Floating point ] |
| float             | f32           |
| double            | f64           |
| [ Boolean ] |
| _Bool             | bool           |

</br>



#### 4.2. `printf` related

- How to print fixed width HEX

    - C
        ```c
        unsigned char unsigned_char_v = 0x0A;
        unsigned short unsigned_short_v = 0x0123;

        // `02` means left-padding `0` until output len is 2
        // Output: >>> unsigned_char_v: 0x0A
        printf("\n>>> unsigned_char_v: 0x%02X", unsigned_char_v);

        // `04` means left-padding `0` until output len is 4
        // Output: >>> unsigned_short_v: 0x0123
        printf("\n>>> unsigned_short_v: 0x%04X", unsigned_short_v);
        ```

        </br>

    - Rust
        ```rust
        let u8_v = 0x0Au8;
        let u16_v = 0x0Bu16;
        println!("u8_v: 0x{u8_v:#02X?}, size: {}", core::mem::size_of::<u8>());
        println!("u16_v: 0x{u16_v:#02X?}, size: {}", core::mem::size_of::<u16>());
        ```

        </br>


- How to format string (sequence of chars)

    - C
        `snprintf` is the safe version of [`sprintf`](https://cplusplus.com/reference/cstdio/snprintf/)

        ```c
        const size_t BUFFER_SIZE = 100;
        char buffer[BUFFER_SIZE];

        char *my_name = "Wison Ye";
        int my_age = 888;

        int buffer_str_size =
            snprintf(buffer, BUFFER_SIZE, "%s, %i", my_name, my_age);
        printf(
            "\nformatted_str: %s, formatted_buffer_size: %i, sizeof: %lu, strlen: "
            "%lu",
            buffer, buffer_str_size, sizeof(buffer), strlen(buffer));

        // Output: formatted_str: Wison Ye, 888, formatted_buffer_size: 13, sizeof: 100, strlen: 13⏎
        ```

        </br>

    - Rust

        ```rust
        let u16_v = 0x0Bu16;
        let formatted_str = format!("u16_v: 0x{u16_v:#02X?}, size: {}", core::mem::size_of::<u16>());
        println!("formatted_str: {formatted_str}");
        ```

        </br>


### 4.3. `string` related

`string` actually just a sequance of characters.

```c
char my_name[] = "wisonye";
```

`sizeof(my_name)` is `8`, as it includes the final `\0` null-terminated character!!!

`strlen(my_name)` is `7`, as it doesn't count the final `\0` null-terminated character!!!

</br>

But you **CANNOT** use `sizeof` on a `char *` (pointer, NOT `char []`), otherwise
you always get back `4` (4bytes on 32bit) or `8` (8bytes on 64bit):

```c
char *my_name_2 = "wisonye wisonye";
printf("\nsizeof(my_name_2): %lu", sizeof(my_name_2));
printf("\nstrlen(my_name_2): %lu", strlen(my_name_2));

// sizeof(my_name_2): 8
// strlen(my_name_2): 15⏎
```

</br>


- Safey verison of `strncat`

    ```c
    //
    // Safey verison of `strncat`:
    //
    // `max_dest_len` should be the `sizeof(char dest[])`
    //
    char *strncat_safe(char *dest, const char *src, size_t max_dest_len) {
        // `dest` and `src` both are `char *`, that's why you should use
        // `strlen` instead of `sizeof`. If you use `sizeof`, it always
        // return `4` or `8`, as that the size of a pointer (4 bytes on
        // 32bit, 8 bytes in 64bit)!!!
        size_t src_len = strlen(src);
        size_t current_dest_str_len = strlen(dest);

        // printf("\n\ndest_len: %lu, src_len: %lu, max_dest_len: %lu", current_dest_str_len, src_len, max_dest_len);

        // `-1` because you need to count the `\0` null-terminated character
        // to end the string.
        size_t available_dest_len = max_dest_len - 1;

        if (current_dest_str_len == 0 && available_dest_len >= src_len) {
            // printf("\n>>> 1");
            return strncat(dest, src, available_dest_len);
        }
        if (current_dest_str_len > 0 &&
            available_dest_len >= current_dest_str_len + src_len) {
            // printf("\n>>> 2");
            return strncat(dest, src, available_dest_len);
        } else {
            if (available_dest_len - current_dest_str_len > 0) {
                // printf("\n>>> 3");
                return strncat(dest, src,
                               available_dest_len - current_dest_str_len);
            } else {
                // printf("\n>>> 4");
                return dest;
            }
        }
    }
    ```

    </br>

### 4.4 Life time

In `C`, actually it has the lifetime concept and it works the same way with
`Rust`:

- Local variable will be destroyed after it's out of the scope (code block/function body)

- Return value by copying it, same with `passing by value`

</br>

So, let's take a look at a few real-world examples:

- Return a struct in funciton works:

    ```c
    typedef struct {
        char *first_name;
        char *last_name;
    } Name2;

    //
    // This works: by returning a struct instance.
    //
    // It does the same thing of passing by value which means a copy of the struct
    // instance.
    //
    // By proving this, you can print out the local var's address and compare to
    // the outer caller return struct instance's address, they should be the
    // different pointer!!!
    //
    Name2 create_your_name(char *first_name, char *last_name) {
        Name2 your_name = {first_name, last_name};

        printf("\n>>> (from create_your_name function) - `your_name` stack local var pointer: %p", &your_name);
        // >>> (from create_your_name function) - `your_name` stack local var pointer: 0x7ffeeecff090

        return your_name;
    }

    // Call it and compare the struct instance address and they're different
    char first_name[] = "Wison";
    char last_name[] = "Ye";
    Name2 the_name_you_created = create_your_name(first_name, last_name);

    printf("\n>>> `the_name_you_created` pointer: %p", &the_name_you_created);
    // >>> `the_name_you_created` pointer: 0x7ffeeecff0d0
    ```

    As you can see that the `create_your_name` return a new struct instance by
    copying it and it works.

    `0x7ffeee` proves that it's the stack frame local variable, as stack frame
    located at the very high address area.

    If you doubt that `why it works` even it has the `char *` pointer???

    That's because the pointer is passed by outside, so here is the trick:

    `the_name_you_created.first_name` --> `char first_name[]`

    `the_name_you_created.last_name` --> `char last_name[]`

    And both `first_name` and `last_name` still exists and available after the
    function (`create_your_name`) stack frame has been destroyed, that's why
    it works:)

    </br>


- Return a struct in funciton that doesn't work:

    ```c
    typedef struct {
        char *first_name;
        char *last_name;
    } Name2;


    //
    // This won't work: by returning a struct instance but there is local stack
    // address reference!!!
    //
    Name2 create_temp_name() {
        char temp_first_name[] = "No first name";
        char temp_last_name[] = "No last name";

        Name2 your_name = {temp_first_name, temp_last_name};
        printf("\n\n>>> (from create_temp_name function) - `your_name` stack local var pointer: %p", &your_name);
        // >>> (from create_temp_name function) - `your_name` stack local var pointer: 0x7ffeeecff068

        // After returning (or say by copying) the `your_name` struct instance,
        // `your_name.first_name` and `your_name.last_name` point to invalid memory
        // address!!!
        return your_name;
    }

    // Call it and compare the struct instance address and they're different
    Name2 the_name_wont_work = create_temp_name();

    printf("\n>>> `the_name_wont_work ` pointer: %p", &the_name_wont_work);
    // `the_name_wont_work` pointer: 0x7ffeeecff0b0
    ```

    As you can see that the `create_temp_name` return a new struct instance by
    copying it and it SHOULD work.

    But in fact, it doesn't work at all!!!

    That's because:

    `the_name_wont_work.first_name` --> `char temp_first_name[]`

    `the_name_wont_work.last_name` --> `char temp_last_name[]`

    And both `temp_first_name` and `temp_last_name` won't be exists and
    unavailable after the function (`create_temp_name`) stack frame has been
    destroyed, that's why it won't work:)

    Yes, it compiles and runs, but ..... the values aren't the values you think
    they're and might crash in sometimes!!!

    That's why passing any stack memory pointer to outside world is super
    dangerous and it's very difficult to debug!!!

    </br>


    Also, have a look at the "./c_demo_struct_stack_frame_analysis.txt", as it
    shows the function call stack details.

    </br>


#### 3.4 The relationship between `Pointer` and `Array`

Actually, `pointer` is just like an `array` in the other form, the `C` design
assumes that you use a `pointer` like an `array`. That's why the following
code works:

```c

u16 temp_arr[] = {1, 2, 3, 4, 5};

//
// `sizeof` is an operator, NOT a function!!!
//
usize arr_len = sizeof(temp_arr) / sizeof(temp_arr[0]);

//
// Use `pointer` to print the loop
//
u16 *loop_ptr = temp_arr;
for (usize index = 0; index < arr_len; index++) {
    printf("\n>>> (pointer_in_arr - loop 2) - %p: %u", loop_ptr + index,
            *(loop_ptr + index));
}

// >>> (pointer_in_arr - loop 2) - 0x820d9d686: 1
// >>> (pointer_in_arr - loop 2) - 0x820d9d688: 2
// >>> (pointer_in_arr - loop 2) - 0x820d9d68a: 3
// >>> (pointer_in_arr - loop 2) - 0x820d9d68c: 4
// >>> (pointer_in_arr - loop 2) - 0x820d9d68e: 5
```

You can found a fews things from the above code:

- `loop_ptr` is a `pointer to u16` type

- `loop_ptr + X`:

    It's saying: add/move the pointer address to `X unit of pointed type` from
    the current position (start from `0x820d9d686` on above print out sample).

    That's why `loop_ptr + 1` actually moved 2 bytes (`0x820d9d686 + 2`), as
    the pointer points to type `u16`!!!

    </br>

For the `temp_arr` variable, actually the compile treats it as `a pointer that
points to the first element of the allocated array`, and you can use that
`temp_arr` as just a pointer. That's why the following code works:

```c

// `temp_arr` acts like the `loop_str` in above sample, as in fact, it just
// an pointer:)
for (usize index = 0; index < arr_len; index++) {
    printf("\n>>> (pointer_in_arr - loop 1.1) - %p: %u", temp_arr + index,
            *(temp_arr + index));
}

>>> (pointer_in_arr - loop 1.1) - 0x8206a92a6: 1
>>> (pointer_in_arr - loop 1.1) - 0x8206a92a8: 2
>>> (pointer_in_arr - loop 1.1) - 0x8206a92aa: 3
>>> (pointer_in_arr - loop 1.1) - 0x8206a92ac: 4
>>> (pointer_in_arr - loop 1.1) - 0x8206a92ae: 5
```

</br>

And one more thing to prove that you can swap the `pointer` and `array (var name)`
is this sample:

```c
u16 *loop_ptr_2 = temp_arr;
for (usize index = 0; index < arr_len; index++) {
    printf("\n>>> (pointer_in_arr - loop 1.1.) - %p: %u", loop_ptr_2 + index,
            loop_ptr_2[index]);
}

// >>> (pointer_in_arr - loop 1.1.) - 0x8205fda16: 1
// >>> (pointer_in_arr - loop 1.1.) - 0x8205fda18: 2
// >>> (pointer_in_arr - loop 1.1.) - 0x8205fda1a: 3
// >>> (pointer_in_arr - loop 1.1.) - 0x8205fda1c: 4
// >>> (pointer_in_arr - loop 1.1.) - 0x8205fda1e: 5
```

Plz pay attention to that `loop_ptr_2[index]`, all the following codes present
the same meaning: get the value that the pointer points to, AKA: dereference

- `temp_arr[index]`
- `loop_ptr_2[index]`
- `*(loop_ptr_2 + index)`
- `*(temp_arr + index)`

</br>

Again: **An array variable is just a pointer, you can swap using them at any
given time.**

But the slight difference between the `array variable` and the `pointer` is
that:

_The compiler can check and detect the array boundary errors but NOT check on
the pointer form_

Consider the following code:

```c
temp_arr[10] = 10;
loop_ptr_2[10] = 10;
*(loop_ptr_2 + 10) = 10;
```

Compiler produces the error on line of `temp_arr[10] = 10` but not the rest of
lines:

```bash
warning: array index 10 is past the end of the array (which contains 5 elements) [-Warray-bounds]
temp_arr[10] = 10;
^        ~~
note: array 'temp_arr' declared here
u16 temp_arr[] = {1, 2, 3, 4, 5};
^
1 warning generated.
```

</br>


### 4. The tricky things in `C Pointer`

#### 4.1 constants pointer differences

- `const TYPE *var` and `TYPE const *var`

    For the pointer to constants, you can change the pointer var (address)
    value itself, but you can't change the value it points to!!!

    ```c
    char a = 'a';
    char b = 'b';

    const char *a_ptr = &a;
    // char const *a_ptr = &a;

    // You can change the pointer (address) value itself
    a_ptr = &b;

    // But you CANNOT change the value it points to
    // error: read-only variable is not assignable
    a_ptr = 'c';
    ```

    </br>

- `*const TYPE var`

    For the constants pointer, you can change the value it points to, but you
    can't change the pointer (address) value itself!!!

    ```c
    char a = 'a';
    char b = 'b';

    char *const a_ptr = &a;
    // char const *a_ptr = &a;

    // You can change the value it points to
    *a_ptr = 'c';

    // But you CANNOT change the pointer value itself
    // error: cannot assign to variable 'a_ptr' with const-qualified type 'char *const'
    a_ptr = &b;
    ```

    </br>

- `const TYPE *const var` and `TYPE const *const var`

    For the constants pointer to constants, you can't change both!!!

    ```c
    char a = 'a';
    char b = 'b';

    const char *const a_ptr = &a;
    // char const *const a_ptr = &a;

    // You can't change both

    // error: read-only variable is not assignable
    *a_ptr = 'c';

    // error: cannot assign to variable 'a_ptr' with const-qualified type 'const char *const'
    a_ptr = &b;
    ```

    </br>

### 5. Macro

The macro in `C` is a super powerful weapon that helps you to generate the most
flexible source code.

#### 5.1 How to only run the preprocessor stage

You can run `CC` with the `-E` flag to generate the source code that only apply
the preprocessor stage before compiling it.

```bash
CC -E src/utils/vec.c | bat
clang -E src/utils/vec.c | bat
```

</br>

#### 5.2 Comment and empty line in macro

You only can use `/* */` comment in macro body, `//` won't work!!!

If you want an empty line, just add a `\` (multi line character) there.

```c
#define MY_MACRO(PARAM1) \
    /* Here is the comment line 1 */ \
    /* Here is the comment line 2 */ \
    /* Follow by a empty line */\
    \
    printf("Just a macro sample.")
```

</br>


#### 5.3 String in macro

When using a macro argument starts with `#` (in the macro body), it treats as
a string. That's why the `#FORMAT_TYPE` (in the following sample) will become
a part of the `printf` format string!!!

```c
#define MACRO_PARAM_AS_STRING(INTEGER, FORMAT_TYPE) \
    printf("Here is integer you provied: " #FORMAT_TYPE, INTEGER)

int main() {
    MACRO_PARAM_AS_STRING(888, %u);
}
```

The above code will expand as the following:

```c
int main() {
    printf("Here is integer you provied: " "%u", 888);
}

// And it prints out:
// Here is integer you provied: 888⏎
```

</br>

#### 5.4 Expression in macro

If you want the macro parameter support passing in an expression, then you should
wrap the parameter with `()` (in the macro body).

When you want to put all code expanded by macro into a code block scope, wrap
your code inside `({})`.

Here is the sample:

```c
#include <stdio.h>
#include <time.h>

#define GET_AND_PRINT_CURRENT_TIME(PRINT_PREFIX, USE_CUSTOM_FORMAT)          \
    ({                                                                       \
        time_t t = time(NULL);                                               \
        if (USE_CUSTOM_FORMAT) {                                             \
            struct tm tm = *localtime(&t);                                   \
            printf("\n>>> " #PRINT_PREFIX " %d-%02d-%02d %02d:%02d:%02d\n",  \
                   tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, \
                   tm.tm_min, tm.tm_sec);                                    \
        } else {                                                             \
            printf("\n>>> " #PRINT_PREFIX " %s", ctime(&t));                 \
        }                                                                    \
    })

//
int main() {
    GET_AND_PRINT_CURRENT_TIME("The current time in custom format: ", 2 > 1);
    GET_AND_PRINT_CURRENT_TIME("The current time: ", 1 > 2);
}
```

</br>

#### 5.5 How to write a macro that includes `#ifdef`?

The answer is `NO, you can't do that!!!` and you have to define 2 macros with
the same name and wrap them into a `#ifdef #else #endif` block like below:

```c
#ifdef PRINT_VEC_DEBUG_LOG
#define ASSIGN_PUSH_VEC_ELEMENT(PTR_TYPE)                                      \
    PTR_TYPE *next_ptr = (self->len == 1)                                      \
                             ? (PTR_TYPE *)self->data                          \
                             : (PTR_TYPE *)self->data + self->len - 1;         \
    printf("\n>>> " #PTR_TYPE " >>> self->data: %p, next_ptr: %p", self->data, \
           next_ptr);                                                          \
    *next_ptr = *(PTR_TYPE *)value;
#else
#define ASSIGN_PUSH_VEC_ELEMENT(PTR_TYPE)                              \
    PTR_TYPE *next_ptr = (self->len == 1)                              \
                             ? (PTR_TYPE *)self->data                  \
                             : (PTR_TYPE *)self->data + self->len - 1; \
    *next_ptr = *(PTR_TYPE *)value;
#endif
```

</br>

#### 5.6 Auto type infer in macro

[Official doc](https://gcc.gnu.org/onlinedocs/gcc/Typeof.html)

</br>

Auto type infer supports by `typeof` and `__auto_type`

```c
#define SHOW_TYPE_OF_VAR(A, B, C, D, E, F) \
    ({                                     \
        typeof(A) a = (A);                 \
        typeof(B) b = (B);                 \
        typeof(C) c = (C);                 \
        typeof(D) d = (D);                 \
        typeof(E) e = (E);                 \
        typeof(F) f = (F);                 \
    })

#define SHOW_TYPE_OF_VAR_2(A, B, C, D, E, F) \
    ({                                       \
        __auto_type a = (A);                 \
        __auto_type b = (B);                 \
        __auto_type c = (C);                 \
        __auto_type d = (D);                 \
        __auto_type e = (E);                 \
        __auto_type f = (F);                 \
    })

//
int main() {
    printf("\n>>> [Auto type infer in macro]\n");

    SHOW_TYPE_OF_VAR(0xFF, 256, -100, 3.5, -4.5, 100000);
    SHOW_TYPE_OF_VAR_2(0xFF, 256, -100, 3.5, -4.5, 100000);
}
```

</br>

#### 5.7 Useful macro: Get back the data type from a variable

That's the `_Generic` selection at compile time, doc is [here](https://en.cppreference.com/w/c/language/generic)

```c
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define TYPE_NAME(x) \
    _Generic((x),                                                   \
    _Bool: "_Bool",                                                 \
    unsigned char: "unsigned char",                                 \
    char: "char",                                                   \
    signed char: "signed char",                                     \
    short int: "short int",                                         \
    unsigned short int: "unsigned short int",                       \
    int: "int",                                                     \
    unsigned int: "unsigned int",                                   \
    long int: "long int",                                           \
    unsigned long int: "unsigned long int",                         \
    long long int: "long long int",                                 \
    unsigned long long int: "unsigned long long int",               \
    float: "float",                                                 \
    double: "double",                                               \
    long double: "long double",                                     \
    char *: "pointer to char",                                      \
    void *: "pointer to void",                                      \
    _Bool *: "pointer to Bool",                                     \
    unsigned char *: "pointer to unsigned char",                    \
    signed char *: "pointer to signed char",                        \
    short int *: "pointer to short int",                            \
    unsigned short int *: "pointer to unsigned short int",          \
    int *: "pointer to int",                                        \
    unsigned int *: "pointer to unsigned int",                      \
    long int *: "pointer to long int",                              \
    unsigned long int *: "pointer to unsigned long int",            \
    long long int *: "pointer to long long int",                    \
    unsigned long long int *: "pointer to unsigned long long int",  \
    float *: "pointer to float",                                    \
    double *: "pointer to double",                                  \
    long double *: "pointer to long double",                        \
    default: "other")

//
//
//
int main() {
    printf("\n>>> [ Get data type from variable ]");

    uint8_t u8_v = 100;
    uint16_t u16_v = 100;
    uint32_t u32_v = 100;
    uint64_t u64_v = 100;
    int8_t i8_v = 100;
    int16_t i16_v = 100;
    int32_t i32_v = 100;
    int64_t i64_v = 100;
    size_t sizet_v = 100;
    _Bool _Bool_v = true;
    unsigned char unsigned_char_v = 0x0A;
    char char_v = 'a';
    signed char signed_char_v = 'a';
    short int short_int_v = 100;
    unsigned short int unsigned_short_int_v = 100;
    int int_v = 100;
    unsigned int unsigned_int_v = 100;
    long int long_int_v = 100;
    unsigned long int unsigned_long_int_v = 100;
    long long int long_long_int_v = 100;
    unsigned long long int unsigned_long_long_int_v = 100;
    float float_v = 1.0;
    double double_v = 1.0;
    long double long_double_v = 1.0;
    char *pointer_to_char_v = NULL;
    void *pointer_to_void_v = NULL;
    _Bool *pointer_to_Bool_v = NULL;
    unsigned char *pointer_to_unsigned_char_v = NULL;
    signed char *pointer_to_signed_char_v = NULL;
    short int *pointer_to_short_int_v = NULL;
    unsigned short int *pointer_to_unsigned_short_int_v = NULL;
    int *pointer_to_int_v = NULL;
    unsigned int *pointer_to_unsigned_int_v = NULL;
    long int *pointer_to_long_int_v = NULL;
    unsigned long int *pointer_to_unsigned_long_int_v = NULL;
    long long int *pointer_to_long_long_int_v = NULL;
    unsigned long long int *pointer_to_unsigned_long_long_int_v = NULL;
    float *pointer_to_float_v = NULL;
    double *pointer_to_double_v = NULL;
    long double *pointer_to_long_double_v = NULL;

    printf("\n>>> Type of 'u8_v' is: %s", TYPE_NAME(u8_v));
    printf("\n>>> Type of 'u16_v' is: %s", TYPE_NAME(u16_v));
    printf("\n>>> Type of 'u32_v' is: %s", TYPE_NAME(u32_v));
    printf("\n>>> Type of 'u64_v' is: %s", TYPE_NAME(u64_v));
    printf("\n>>> Type of 'i8_v' is: %s", TYPE_NAME(i8_v));
    printf("\n>>> Type of 'i16_v' is: %s", TYPE_NAME(i16_v));
    printf("\n>>> Type of 'i32_v' is: %s", TYPE_NAME(i32_v));
    printf("\n>>> Type of 'i64_v' is: %s", TYPE_NAME(i64_v));
    printf("\n>>> Type of 'usizet_v' is: %s", TYPE_NAME(sizet_v));
    printf("\n>>> Type of '_Bool_v' is: %s", TYPE_NAME(_Bool_v));
    printf("\n>>> Type of 'unsigned_char_v': %s", TYPE_NAME(unsigned_char_v));
    printf("\n>>> Type of 'char_v': %s", TYPE_NAME(char_v));
    printf("\n>>> Type of 'signed_char_v': %s", TYPE_NAME(signed_char_v));
    printf("\n>>> Type of 'short_int_v': %s", TYPE_NAME(short_int_v));
    printf("\n>>> Type of 'unsigned_short_int_v': %s",
           TYPE_NAME(unsigned_short_int_v));
    printf("\n>>> Type of 'int_v': %s", TYPE_NAME(int_v));
    printf("\n>>> Type of 'unsigned_int_v': %s", TYPE_NAME(unsigned_int_v));
    printf("\n>>> Type of 'long_int_v': %s", TYPE_NAME(long_int_v));
    printf("\n>>> Type of 'unsigned_long_int_v': %s",
           TYPE_NAME(unsigned_long_int_v));
    printf("\n>>> Type of 'long_long_int_v': %s", TYPE_NAME(long_long_int_v));
    printf("\n>>> Type of 'unsigned_long_long_int_v': %s",
           TYPE_NAME(unsigned_long_long_int_v));
    printf("\n>>> Type of 'float_v': %s", TYPE_NAME(float_v));
    printf("\n>>> Type of 'double_v': %s", TYPE_NAME(double_v));
    printf("\n>>> Type of 'long_double_v': %s", TYPE_NAME(long_double_v));
    printf("\n>>> Type of '*pointer_to_char_v': %s",
           TYPE_NAME(pointer_to_char_v));
    printf("\n>>> Type of '*pointer_to_void_v': %s",
           TYPE_NAME(pointer_to_void_v));
    printf("\n>>> Type of '*pointer_to_Bool_v': %s",
           TYPE_NAME(pointer_to_Bool_v));
    printf("\n>>> Type of '*pointer_to_unsigned_char_v': %s",
           TYPE_NAME(pointer_to_unsigned_char_v));
    printf("\n>>> Type of '*pointer_to_signed_char_v': %s",
           TYPE_NAME(pointer_to_signed_char_v));
    printf("\n>>> Type of '*pointer_to_short_int_v': %s",
           TYPE_NAME(pointer_to_short_int_v));
    printf("\n>>> Type of '*pointer_to_unsigned_short_int_v': %s",
           TYPE_NAME(pointer_to_unsigned_short_int_v));
    printf("\n>>> Type of '*pointer_to_int_v': %s",
           TYPE_NAME(pointer_to_int_v));
    printf("\n>>> Type of '*pointer_to_unsigned_int_v': %s",
           TYPE_NAME(pointer_to_unsigned_int_v));
    printf("\n>>> Type of '*pointer_to_long_int_v': %s",
           TYPE_NAME(pointer_to_long_int_v));
    printf("\n>>> Type of '*pointer_to_unsigned_long_int_v': %s",
           TYPE_NAME(pointer_to_unsigned_long_int_v));
    printf("\n>>> Type of '*pointer_to_long_long_int_v': %s",
           TYPE_NAME(pointer_to_long_long_int_v));
    printf("\n>>> Type of '*pointer_to_unsigned_long_long_int_v': %s",
           TYPE_NAME(pointer_to_unsigned_long_long_int_v));
    printf("\n>>> Type of '*pointer_to_float_v': %s",
           TYPE_NAME(*pointer_to_float_v));
    printf("\n>>> Type of '*pointer_to_double_v': %s",
           TYPE_NAME(pointer_to_double_v));
    printf("\n>>> Type of '*pointer_to_long_double_v': %s",
           TYPE_NAME(pointer_to_long_double_v));
}

// >>> [ Get data type from variable ]
// >>> Type of 'u8_v' is: unsigned char
// >>> Type of 'u16_v' is: unsigned short int
// >>> Type of 'u32_v' is: unsigned int
// >>> Type of 'u64_v' is: unsigned long long int
// >>> Type of 'i8_v' is: signed char
// >>> Type of 'i16_v' is: short int
// >>> Type of 'i32_v' is: int
// >>> Type of 'i64_v' is: long long int
// >>> Type of 'usizet_v' is: unsigned long int
// >>> Type of '_Bool_v' is: _Bool
// >>> Type of 'unsigned_char_v': unsigned char
// >>> Type of 'char_v': char
// >>> Type of 'signed_char_v': signed char
// >>> Type of 'short_int_v': short int
// >>> Type of 'unsigned_short_int_v': unsigned short int
// >>> Type of 'int_v': int
// >>> Type of 'unsigned_int_v': unsigned int
// >>> Type of 'long_int_v': long int
// >>> Type of 'unsigned_long_int_v': unsigned long int
// >>> Type of 'long_long_int_v': long long int
// >>> Type of 'unsigned_long_long_int_v': unsigned long long int
// >>> Type of 'float_v': float
// >>> Type of 'double_v': double
// >>> Type of 'long_double_v': long double
// >>> Type of '*pointer_to_char_v': pointer to char
// >>> Type of '*pointer_to_void_v': pointer to void
// >>> Type of '*pointer_to_Bool_v': pointer to Bool
// >>> Type of '*pointer_to_unsigned_char_v': pointer to unsigned char
// >>> Type of '*pointer_to_signed_char_v': pointer to signed char
// >>> Type of '*pointer_to_short_int_v': pointer to short int
// >>> Type of '*pointer_to_unsigned_short_int_v': pointer to unsigned short int
// >>> Type of '*pointer_to_int_v': pointer to int
// >>> Type of '*pointer_to_unsigned_int_v': pointer to unsigned int
// >>> Type of '*pointer_to_long_int_v': pointer to long int
// >>> Type of '*pointer_to_unsigned_long_int_v': pointer to unsigned long int
// >>> Type of '*pointer_to_long_long_int_v': pointer to long long int
// >>> Type of '*pointer_to_unsigned_long_long_int_v': pointer to unsigned long long int
// >>> Type of '*pointer_to_float_v': float
// >>> Type of '*pointer_to_double_v': pointer to double
// >>> Type of '*pointer_to_long_double_v': pointer to long double
```
</br>


#### 5.7.1 Useful macro: Is it the same type between 2 variables/values

```c

//
//
//
#define IS_IT_THE_SAME_TYPE(a, b)                                            \
    ({                                                                       \
        char _a_type[50] = TYPE_NAME((a));                                   \
        char _b_type[50] = TYPE_NAME((b));                                   \
        _Bool is_same_str_non_case_sensitive = strcasecmp(_a_type, _b_type); \
        (is_same_str_non_case_sensitive == 0);                               \
    })

int main() {
    /* usize *aaa = NULL; */
    /* size_t *bbb = NULL; */
    /* char aaa[10] = "asdfasdf"; */
    /* char bbb[20] = "AAAA"; */
    uint8_t aaa[5] = {1, 2, 3, 4, 5};
    uint8_t bbb[3] = {9, 10, 11};
    printf("\n>>> aaa type is: %s",TYPE_NAME(aaa));
    printf("\n>>> bbb type is: %s",TYPE_NAME(bbb));

    _Bool is_same_type_between_a_and_b = IS_IT_THE_SAME_TYPE(aaa, bbb);

    if (is_same_type_between_a_and_b) {
        printf("\n>>>> Yes, a and b ARE the same type.");
    } else {
        printf("\n>>>> Yes, a and b ARE NOT the same type.");
    }

    return 0;
}

// >>> aaa type is: pointer to unsigned char
// >>> bbb type is: pointer to unsigned char
// >>>> Yes, a and b ARE the same type.⏎
```

</br>


#### 5.8 Generic implementation by using macro

Let's see what `C` deals with generic:)

The `Result` type here is just trying to show you how the magic word
`generic` works under the hood.

Let's take the `Rust` generic type `Result<T,E>` as an example.

Suppose you have the following rust code:

```rust
pub struct MyResult<T, E> {
    success: bool,
    ok_value: T,
    err_value: E,
}

fn main() {
    let result_1: MyResult<usize, u8> = MyResult::<usize, u8> {
         success: true,
         ok_value: 100,
         err_value: 0
    };

    let result_2: MyResult<f32, u8> = MyResult::<f32, u8> {
         success: true,
         ok_value: 1.0f32,
         err_value: 0
    };
}
```

When Rust compiles this code, it performs **`monomorphization`**. During the
process, the `rustc`read the values that have need used in `MyResult<T,E>`,
and produce 2 different types wit the concrete types like below:

The sample code comes from [`Generic Data Types`](https://doc.rust-lang.org/book/ch10-01-syntax.html#performance-of-code-using-generics
) in the Rust official guide (`The Rust Programming Language`):

```rust
// pseudo code

pub struct MyResult_usize_u8{
    success: bool,
    ok_value: usize,
    err_value: u8,
}

pub struct MyResult_f32_u8 {
    success: bool,
    ok_value: f32,
    err_value: u8,
}
```

So, that's `nearly duplicated code`? YES, you're right and that's how it
works:)

In `C`, you can do the same thing with the `magical` macro:)



Because the `magical` thing is all about the `nearly duplicated code`, that
means you can't use the regular `include guard` pattern like below to
prevent the generic implementation `.h` file from being included more than
once:

```c
#ifndef __RESULT_H__
#define __RESULT_H__

//... Your code inside include guard

#endif
```

</br>


So, suppose that you want to implement the same `MyResult` type above in the
generic way in `C`. That means you need 3 generic types:

- `MY_RESULT_TYPE` as the `typedef struct` type name
- `MY_RESULT_SUCCESS_TYPE` as the `ok` data type
- `MY_RESULT_ERROR_TYPE` as the `err` data type

</br>

Let's do it:

```c
//
// Throw error if the caller doesn't define the following `type name` which
// uses to generate the concrete type struct definition
//
#if !defined(MY_RESULT_TYPE) || !defined(MY_RESULT_SUCCESS_TYPE) || \
    !defined(MY_RESULT_ERROR_TYPE)
#error Missing MY_RESULT_TYPE or MY_RESULT_SUCCESS_TYPE or MY_RESULT_ERROR_TYPE definition
#endif

//
// Define macros that uses to create concrete type struct definition
//
#define MY_RESULT_CONCAT(tag, method) tag##_##method
#define MY_RESULT_METHOD2(tag, method) MY_RESULT_CONCAT(tag, method)
#define MY_RESULT_METHOD(method) MY_RESULT_METHOD2(MY_RESULT_TYPE, method)

//
// Generic (result type) struct
//
typedef struct {
    _Bool success;
    MY_RESULT_SUCCESS_TYPE *ok;
    MY_RESULT_ERROR_TYPE *err;
} MY_RESULT_TYPE;

//
// Similar to `Result::Ok(T)` and allocate on the heap
//
MY_RESULT_TYPE *MY_RESULT_METHOD(Ok)(MY_RESULT_SUCCESS_TYPE *ok) {
    MY_RESULT_TYPE *r = malloc(sizeof(MY_RESULT_TYPE));
    r->success = true;
    r->ok = ok;
    r->err = NULL;

    return r;
}

//
// Similar to `Result::Err(T)` and allocate on the heap
//
MY_RESULT_TYPE *MY_RESULT_METHOD(Err)(MY_RESULT_ERROR_TYPE *err) {
    MY_RESULT_TYPE *r = malloc(sizeof(MY_RESULT_TYPE));
    r->success = false;
    r->ok = NULL;
    r->err = err;

    return r;
}

#undef MY_RESULT_TYPE
#undef MY_RESULT_SUCCESS_TYPE
#undef MY_RESULT_ERROR_TYPE
#undef MY_RESULT_CONCAT
#undef MY_RESULT_METHOD2
#undef MY_RESULT_METHOD
```

</br>

Ok, let's explain step-by-step:

- Check the caller (`includer`) to see whether it defines the required type
macros or not:

    ```c
    //
    // Throw error if the caller doesn't define the following `type name` which
    // uses to generate the concrete type struct definition
    //
    #if !defined(MY_RESULT_TYPE) || !defined(MY_RESULT_SUCCESS_TYPE) || \
            !defined(MY_RESULT_ERROR_TYPE)
    #error Missing MY_RESULT_TYPE or MY_RESULT_SUCCESS_TYPE or MY_RESULT_ERROR_TYPE definition
    #endif
    ```

    The directive `#error` causes the preprocessor to report a fatal error,
    then you can see the error when you compile the project.

    </br>


- Define the helper macro to define `XX_YY` method function name


    ```C
    //
    // Define macros that uses to create concrete type struct definition
    //
    #define MY_RESULT_CONCAT(struct_name, method_name) struct_name##_##method_name
    #define CREATE_STRUCT_METHOD_HELPER(struct_name, method_name) MY_RESULT_CONCAT(struct_name, method_name)
    #define CREATE_STRUCT_METHOD(method_name) CREATE_STRUCT_METHOD_HELPER(MY_RESULT_TYPE, method_name)
    ```

    Suppose the caller (`includer`) source file has the following macros:

    ```C
    #define MY_RESULT_TYPE EndpointApiResult
    ```

    So, the `CREATE_STRUCT_METHOD(Ok)` macro call will be expanded as `*EndpointApiResult_Ok`. That's the way to generate the generic struct method name:)

    </br>

- The final important part is to undefine the caller (`includer`)'s macros


    ```c
    #undef MY_RESULT_TYPE
    #undef MY_RESULT_SUCCESS_TYPE
    #undef MY_RESULT_ERROR_TYPE
    #undef MY_RESULT_CONCAT
    #undef CREATE_STRUCT_METHOD_HELPER
    #undef CREATE_STRUCT_METHOD
    ```

    </br>

- So, from now on, every source code is able to include this `.h` to create
their own concrete type version of `MyResult` struct and method.

    Here is the example to show it:

    ```c
    #define MY_RESULT_TYPE EndpointApiResult
    #define MY_RESULT_SUCCESS_TYPE char
    #define MY_RESULT_ERROR_TYPE uint16_t

    #include "utils/result.h"

    char *success_result = "Got something back:)";
    uint16_t fail_result = 404;

    //
    EndpointApiResult *simulate_call_api_success(_Bool simulate_success) {
        EndpointApiResult *result = (simulate_success)
                                        ? EndpointApiResult_Ok(success_result)
                                        : EndpointApiResult_Err(&fail_result);
    
        return result;
    }
    ```

    As you can see above, a few things to pay attention to :

    - Those 3 `#define` should be written before the `#include "utils/result.h"`, as preprocessor handle source file from top to bottom.

    - Before the `#include "utils/result.h"` be evaluated, the `EndpointApiResult` doesn't exists. It only exists after the preprocessor finishs:

        You can run the `CC -E src/result_demo.c` to see the preprocessor
        result:

        ```c
        typedef struct {
            _Bool success;
            char *ok;
            uint16_t *err;
        } EndpointApiResult;

        EndpointApiResult *EndpointApiResult_Ok(char *ok) {
            EndpointApiResult *r = malloc(sizeof(EndpointApiResult));
            r->success = 1;
            r->ok = ok;
            r->err = ((void*)0);

            return r;
        }

        EndpointApiResult *EndpointApiResult_Err(uint16_t *err) {
            EndpointApiResult *r = malloc(sizeof(EndpointApiResult));
            r->success = 0;
            r->ok = ((void*)0);
            r->err = err;

            return r;
        }
        ```

        That's the way how `C` deals with generic:)

        </br>

For more details, open `src/utils/result.h` and `src/result_demo.c` to have
a look and run the following command to give it a try:

```bash
make c_demo_result && ./c_demo_result

# >>> [ Result type demo ]
# Result {
#         success: true
#         ok: Got something back:)
#         err: NULL
# }
# 
# Result {
#         success: false
#         ok: NULL
#         ok: 404
# }
```
