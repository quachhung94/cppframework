/*
 * Created on Mon Aug 30 2021
 *
 * Author: HoangNV36
 * Brief: Helper functions to read, write, delete data in secure storage
 *
 * Copyright (c) 2021 Vinfast
 */

#ifndef _SS_HELPER_
#define _SS_HELPER_

#ifdef __cplusplus
extern "C" {
#endif

// #include <ss_impl.h>

/*
 *  @brief: Write data to Secure Storage
 *  @args:
 *      - object_name: Secure Storage id object name
 *      - data, data_size: Input data
 */
bool SSHelper_Write(char *object_name, char *data, uint32_t data_size) {
    (void) object_name;
    (void) data;
    (void) data_size;
    return true;
}

/*
 *  @brief: Get data size of Secure Storage object
 *  @args:
 *      - object_name: Secure Storage id object name
 */
uint32_t SSHelper_GetSize(char *object_name) {
    (void) object_name;
    return 0;
}

/*
 *  @brief: Read data from Secure Storage
 *  @args:
 *      - object_name: Secure Storage id object name
 *      - data, data_size: Output data
 * NOTE: Call this function after get object size by calling SSHelper_GetSize
 * For detail, see "example.cpp"
 */
bool SSHelper_Read(char *object_name, char *data, uint32_t data_size) {
    (void) object_name;
    (void) data;
    (void) data_size;
    return true;
}

/*
 *  @brief: Delete data from Secure Storage
 *  @args:
 *      - object_name: Secure Storage id object name
 */
bool SSHelper_Delete(char *object_name) {
    (void) object_name;
    return true;
}

#ifdef __cplusplus
}
#endif
#endif