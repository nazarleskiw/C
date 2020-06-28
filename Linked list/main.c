#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "list.h"

// quick and dirty test implementation,
// more proper approach - use test framework, googletest like
// assert(false) or assert(0) causes stop of program execution in debug mode(-g switch)
// in release mode, asserts are ignored

// test to check create/destroy api
void test_1(void) {
    printf("%s:%d\n",__func__, __LINE__);
    List * a = NULL;
    assert(!a);
    a = create_list();
    assert(a);
    destroy_list(&a);
    assert(!a);
}

// test to check append_to_list and count_elements
void test_2(void) {
    printf("%s:%d\n",__func__, __LINE__);
    List * list = create_list();
    assert((count_elements(list)==0));
    append_to_list(list,99);
    assert((count_elements(list)==1));
    append_to_list(list,199);
    assert((count_elements(list)==2));
    append_to_list(list,299);
    assert((count_elements(list)==3));
    destroy_list(&list);
}

//test to check get_nth_element
void test_3(void) {
    printf("%s:%d\n",__func__, __LINE__);
    List * list = create_list();
    append_to_list(list,101);
    append_to_list(list,102);
    append_to_list(list,103);
    assert(count_elements(list)==3);
    assert(get_nth_element(list,0)==101);
    assert(get_nth_element(list,1)==102);
    assert(get_nth_element(list,2)==103);
    destroy_list(&list);
}

//test to check clear list
void test_4(void) {
    printf("%s:%d\n",__func__, __LINE__);
    List * list = create_list();
    append_to_list(list,101);
    append_to_list(list,102);
    append_to_list(list,103);
    assert(count_elements(list)==3);
    clear_list(list);
    assert(count_elements(list)==0);
    destroy_list(&list);
}

// test to check insert_to_list
void test_insert(void) {
    printf("%s:%d\n",__func__, __LINE__);
    List * list = create_list();
    assert(count_elements(list)==0);

    //insert to empty
    insert_to_list(list,101,0);
    assert(count_elements(list)==1);
    assert(get_nth_element(list,0)==101);

    // insert to beginning
    insert_to_list(list,99,0);
    assert(count_elements(list)==2);
    assert(get_nth_element(list,0)==99);
    assert(get_nth_element(list,1)==101);

    //insert to end
    insert_to_list(list,102,2);
    assert(count_elements(list)==3);
    assert(get_nth_element(list,0)==99);
    assert(get_nth_element(list,1)==101);
    assert(get_nth_element(list,2)==102);

    //insert to after first
    insert_to_list(list,100,1);
    assert(count_elements(list)==4);
    assert(get_nth_element(list,0)==99);
    assert(get_nth_element(list,1)==100);
    assert(get_nth_element(list,2)==101);
    assert(get_nth_element(list,3)==102);

    destroy_list(&list);

}

// basic test for delete operation
void test_mini_delete(void) {
    printf("%s:%d\n",__func__, __LINE__);
    List * list = create_list();
    assert(count_elements(list)==0);
    append_to_list(list,0);
    assert(count_elements(list)==1);
    remove_nth_element(list, 0);
    assert(count_elements(list)==0);
    destroy_list(&list);
}

//more complex test for delete operation
void test_delete(void) {
    printf("%s:%d\n",__func__, __LINE__);
    List * list = create_list();
    for (int i=100;i<105;++i)
        append_to_list(list,i);
    assert(count_elements(list)==5);

    // delete middle one
    remove_nth_element(list, 2);
    assert(count_elements(list)==4);
    assert(get_nth_element(list,0)==100);
    assert(get_nth_element(list,1)==101);
    assert(get_nth_element(list,2)==103);
    assert(get_nth_element(list,3)==104);

    //delete last one
    remove_nth_element(list, 3);
    assert(count_elements(list)==3);
    assert(get_nth_element(list,0)==100);
    assert(get_nth_element(list,1)==101);
    assert(get_nth_element(list,2)==103);


    //delete first one
    remove_nth_element(list, 0);
    assert(count_elements(list)==2);
    assert(get_nth_element(list,0)==101);
    assert(get_nth_element(list,1)==103);
    remove_nth_element(list, 1);
    remove_nth_element(list, 0);

    assert(count_elements(list)==0);

    destroy_list(&list);
}

void test_mini_sort() {
    printf("%s:%d\n",__func__, __LINE__);
    List * list = create_list();

    sort_list(list);
    append_to_list(list, 10);
    sort_list(list);
    assert(get_nth_element(list,0)==10);
    append_to_list(list, 5);
    sort_list(list);
    assert(get_nth_element(list,0)==5);
    assert(get_nth_element(list,1)==10);

    destroy_list(&list);
}

void test_mini_reverse() {
    printf("%s:%d\n",__func__, __LINE__);
    List * list = create_list();

    reverse_list(list);
    append_to_list(list, 10);
    reverse_list(list);
    assert(get_nth_element(list,0)==10);
    append_to_list(list, 5);
    reverse_list(list);
    assert(get_nth_element(list,0)==5);
    assert(get_nth_element(list,1)==10);

    destroy_list(&list);
}

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

void test_sort_and_reverse(void) {
    printf("%s:%d\n",__func__, __LINE__);
    List * list = create_list();

    srand(time(0));
    const int SIZE = 20;
    int tosort[SIZE];
    for (int i=0;i<SIZE;++i) {
        tosort[i] = rand()%100-50;
        append_to_list(list,tosort[i]);
    }

    qsort(tosort, SIZE, sizeof(int), cmpfunc);
    sort_list(list);

    for (int i=0;i<SIZE;++i) {
        assert(tosort[i]==get_nth_element(list,i));
    }

    printf("%s:reverse:%d\n",__func__, __LINE__);
    reverse_list(list);
    for (int i=0;i<SIZE;++i) {
        assert(tosort[SIZE-i-1]==get_nth_element(list,i));
    }


    destroy_list(&list);
}

// funciton to execute tests
void tests(void)
{
    test_1();
    test_2();
    test_3();
    test_4();
    test_insert();
    test_mini_delete();
    test_delete();
    test_mini_reverse();
    test_mini_sort();
    test_sort_and_reverse();
}

//More correct approach is to have two separate binaries
//one main.c with real functionality, which create one binary
//second ut_main.c with unit tests functionality, which creates separate libray
int main (int argc, char ** argv)
{
    tests();

    return 0;

}

