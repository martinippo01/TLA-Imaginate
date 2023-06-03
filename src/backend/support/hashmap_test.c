#include <assert.h>
#include <stdio.h>
#include "hashmap.h"


/*
 * Para compilar:
 * gcc -o hashmap_test hashmap.c hashmap_test.c 
 *
 * Para ejecutar:
 * ./hashmap_test 
 *
 * */

void test_hashmap() {
    HashMap hashmap;
    initHashMap(hashmap);

    Value v1 = {"scope1", "type1", "init1"};
    Value v2 = {"scope2", "type2", "init2"};

    assert(put(hashmap, "id1", v1) == 1);
    assert(put(hashmap, "id2", v2) == 1);

    assert(exists(hashmap, "id1") == 1);
    assert(exists(hashmap, "id2") == 1);

    Value default_value = {"default", "default", "default"};

    Value *v1_out = getOrDefault(hashmap, "id1", &default_value);
    assert(strcmp(v1_out->scope, v1.scope) == 0);
    assert(strcmp(v1_out->type, v1.type) == 0);
    assert(strcmp(v1_out->initialization, v1.initialization) == 0);

    Value *v2_out = getOrDefault(hashmap, "id2", &default_value);
    assert(strcmp(v2_out->scope, v2.scope) == 0);
    assert(strcmp(v2_out->type, v2.type) == 0);
    assert(strcmp(v2_out->initialization, v2.initialization) == 0);

    destroy(hashmap);
}

void test2_hashmap() {
    HashMap hashmap;
    initHashMap(hashmap);

    Value v1 = {"scope1", "type1", "init1"};
    Value v2 = {"scope2", "type2", "init2"};
    Value v3 = {"scope3", "type3", "init3"};
    Value v4 = {"scope4", "type4", "init4"};

    // Test adding to the hashmap
    assert(put(hashmap, "id1", v1) == 1);
    assert(put(hashmap, "id2", v2) == 1);
    assert(put(hashmap, "id3", v3) == 1);
    assert(put(hashmap, "id4", v4) == 1);

    // Test that all keys exist
    assert(exists(hashmap, "id1") == 1);
    assert(exists(hashmap, "id2") == 1);
    assert(exists(hashmap, "id3") == 1);
    assert(exists(hashmap, "id4") == 1);

    // Test that non-existent key does not exist
    assert(exists(hashmap, "id5") == 0);

    Value default_value = {"default", "default", "default"};

    // Test getting values
    Value *v1_out = getOrDefault(hashmap, "id1", &default_value);
    assert(strcmp(v1_out->scope, v1.scope) == 0);
    assert(strcmp(v1_out->type, v1.type) == 0);
    assert(strcmp(v1_out->initialization, v1.initialization) == 0);

    Value *v2_out = getOrDefault(hashmap, "id2", &default_value);
    assert(strcmp(v2_out->scope, v2.scope) == 0);
    assert(strcmp(v2_out->type, v2.type) == 0);
    assert(strcmp(v2_out->initialization, v2.initialization) == 0);

    Value *v3_out = getOrDefault(hashmap, "id3", &default_value);
    assert(strcmp(v3_out->scope, v3.scope) == 0);
    assert(strcmp(v3_out->type, v3.type) == 0);
    assert(strcmp(v3_out->initialization, v3.initialization) == 0);

    Value *v4_out = getOrDefault(hashmap, "id4", &default_value);
    assert(strcmp(v4_out->scope, v4.scope) == 0);
    assert(strcmp(v4_out->type, v4.type) == 0);
    assert(strcmp(v4_out->initialization, v4.initialization) == 0);

    // Test getting non-existent value
    Value *v5_out = getOrDefault(hashmap, "id5", &default_value);
    assert(strcmp(v5_out->scope, default_value.scope) == 0);
    assert(strcmp(v5_out->type, default_value.type) == 0);
    assert(strcmp(v5_out->initialization, default_value.initialization) == 0);

    destroy(hashmap);
}


int main() {
    puts("Initiliasing tests!");
    test_hashmap();
    test2_hashmap();
    puts("All tests passed!");
    return 0;
}

