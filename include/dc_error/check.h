#ifndef LIBDC_ERROR_CHECK_H
#define LIBDC_ERROR_CHECK_H


/*
 * Copyright 2021-2022 D'Arcy Smith.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "error.h"


#ifdef __cplusplus
extern "C" {
#endif


#define DC_CHECK_NOT_NULL(err, ptr) dc_check_not_null((err), (ptr))
#define DC_CHECK_NULL(err, ptr) dc_check_null((err), (ptr))
#define DC_CHECK_GREATER_THAN(err, a, b) dc_check_greater_than((err), (a), (b))
#define DC_CHECK_LESS_THAN(err, a, b) dc_check_less_than((err), (a), b)
#define DC_CHECK_EQUALS(err, a, b)                                             \
  _Generic((err), (a, b), \
      char *: dc_check_equals_string,                       \
      default: dc_check_equals_int                          \
    )(a, b)
#define DC_CHECK_NOT_EQUALS(err, a, b)                                         \
  _Generic((err), (a, b), \
      char *: dc_check_not_equals_string,                       \
      default: dc_check_not_equals_int                          \
    )(a, b)

/**
 *
 * @param err
 * @param ptr
 * @return
 */
bool dc_check_not_null(struct dc_error *err, const void *ptr);

/**
 *
 * @param err
 * @param ptr
 * @return
 */
bool dc_check_null(struct dc_error *err, const void *ptr);

/**
 *
 * @param err
 * @param a
 * @param b
 * @return
 */
bool dc_check_greater_than_int(struct dc_error *err, int a, int b);

/**
 *
 * @param err
 * @param a
 * @param b
 * @return
 */
bool dc_check_less_than_int(struct dc_error *err, int a, int b);

/**
 *
 * @param err
 * @param a
 * @param b
 * @return
 */
bool dc_check_equals_int(struct dc_error *err, int a, int b);

/**
 *
 * @param err
 * @param a
 * @param b
 * @return
 */
bool dc_check_equals_string(struct dc_error *err, const char *a, const char *b);

/**
 *
 * @param err
 * @param a
 * @param b
 * @return
 */
bool dc_check_not_equals_int(struct dc_error *err, int a, int b);

/**
 *
 * @param err
 * @param a
 * @param b
 * @return
 */
bool dc_check_not_equals_string(struct dc_error *err, const char *a,
                                const char *b);


#ifdef __cplusplus
}
#endif


#endif // LIBDC_ERROR_CHECK_H
