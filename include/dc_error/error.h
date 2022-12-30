#ifndef LIBDC_ERROR_ERROR_H
#define LIBDC_ERROR_ERROR_H

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


#include <errno.h>
#include <stdbool.h>
#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif


#ifndef __STDC_LIB_EXT1__
typedef int errno_t;
#endif


/**
 * Error states.
 */
typedef enum
{
    DC_ERROR_NONE = 0, /**< There is no error */
    DC_ERROR_CHECK,    /**< The error is due to a failed check */
    DC_ERROR_ERRNO,    /**< The error is due to errno being set */
    DC_ERROR_SYSTEM, /**< The error is from a library call that doesn't set errno
                    */
    DC_ERROR_USER,   /**< The error is from a non-standard function */
}
        dc_error_type;

struct dc_error;

struct dc_error *dc_error_create(bool report);

/**
 *
 * @param err
 * @param report
 */
void dc_error_init(struct dc_error *err, bool report);

/**
 *
 * @param err
 * @return
 */
bool dc_error_is_reporting(struct dc_error *err);

/**
 *
 * @param err
 * @param on
 */
void dc_error_set_reporting(struct dc_error *err, bool on);

const char *dc_error_get_message(const struct dc_error *err);

/**
 *
 * @param err
 */
void dc_error_reset(struct dc_error *err);

/**
 *
 * @param err
 */
void dc_error_default_error_reporter(const struct dc_error *err);

/**
 *
 * @param err
 * @param file_name
 * @param function_name
 * @param line_number
 */
void dc_error_check(struct dc_error *err, const char *file_name,
                    const char *function_name, size_t line_number);

/**
 *
 * @param err
 * @param file_name
 * @param function_name
 * @param line_number
 * @param err_code
 */
void dc_error_errno(struct dc_error *err, const char *file_name,
                    const char *function_name, size_t line_number,
                    errno_t err_code);

/**
 *
 * @param err
 * @param file_name
 * @param function_name
 * @param line_number
 * @param msg
 * @param err_code
 */
void dc_error_system(struct dc_error *err, const char *file_name,
                     const char *function_name, size_t line_number,
                     const char *msg, int err_code);

/**
 *
 * @param err
 * @param file_name
 * @param function_name
 * @param line_number
 * @param msg
 * @param err_code
 */
void dc_error_user(struct dc_error *err, const char *file_name,
                   const char *function_name, size_t line_number,
                   const char *msg, int err_code);

/**
 *
 * @param err
 * @return
 */
bool dc_error_has_error(const struct dc_error *err);

/**
 *
 * @param err
 * @return
 */
bool dc_error_has_no_error(const struct dc_error *err);

/**
 *
 * @param err
 * @param code
 * @return
 */
bool dc_error_is_errno(const struct dc_error *err, errno_t code);

errno_t dc_errno_get_errno(const struct dc_error *err);

#define DC_ERROR_RAISE_CHECK(err)                                              \
  dc_error_check((err), __FILE__, __func__, __LINE__)
#define DC_ERROR_RAISE_ERRNO(err, code)                                        \
  dc_error_errno((err), __FILE__, __func__, __LINE__, (code))
#define DC_ERROR_RAISE_SYSTEM(err, msg, code)                                  \
  dc_error_system((err), __FILE__, __func__, __LINE__, (msg), (code))
#define DC_ERROR_RAISE_USER(err, msg, code)                                    \
  dc_error_user((err), __FILE__, __func__, __LINE__, (msg), (code))


#ifdef __cplusplus
}
#endif


#endif // LIBDC_ERROR_ERROR_H
