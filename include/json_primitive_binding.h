#ifndef JSON_PRIMITIVES_BINDING_H
#define JSON_PRIMITIVES_BINDING_H

#include <stdlib.h>
#include "cJSON.h"


typedef enum {
    JSON_STRING,
    JSON_NUMBER,
    JSON_BOOL,
    JSON_NULL
} json_primitive_type_t;

typedef struct __attribute__((packed))  {
    char* json_field_name;
    json_primitive_type_t type;
    void *field_ptr;
    size_t field_size;

} json_primitive_binding_t;

/**
 * @brief initializes a json_primitive_binding_t struct with the provided parameters
 * 
 * @param binding  the binding to initialize
 * @param name  the name of the json field to bind, must be a null-terminated string
 * @param type  the type of the json field value to bind
 * @param field_ptr  a pointer to the field where the deserialized value will be stored
 * @param field_size  the size of the field where the deserialized value will be stored
 * @return int  0 on success, 1 if an error occurred during initialization, -1 if an error occurred
 */
int json_primitive_binding_init(json_primitive_binding_t* binding, char* json_field_name, json_primitive_type_t type, void* field_ptr, size_t field_size);


/**
 * @brief deserializes a json primitive value and stores it in the field pointed by the binding, the binding must be initialized before calling this function
 * 
 * @param json  the JSON object to deserialize from
 * @param binding  the binding to use for deserialization, must be initialized before calling this function
 * @return int  0 on success, 1 if an error occurred during deserialization, -1 if an error occurred
 */
int json_primitive_binding_deserialize(const cJSON* json, json_primitive_binding_t* binding);



#endif // JSON_PRIMITIVES_BINDING_H
