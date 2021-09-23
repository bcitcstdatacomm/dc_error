#ifndef LIBDC_ERROR_ERROR_H
#define LIBDC_ERROR_ERROR_H


#include <errno.h>
#include <stdbool.h>
#include <stddef.h>


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
    DC_ERROR_SYSTEM,   /**< The error is from a library call that doesn't set errno */
    DC_ERROR_USER,     /**< The error is from a non-standard function */
} dc_error_type;

/**
 *
 */
struct dc_error
{
    char *message;                /**< the message for the error, dynamically allocated */
    const char *file_name;        /**< the file name that the error happened in */
    const char *function_name;    /**< the function name that the error happened in */
    size_t line_number;           /**< the line number that the error happened on */
    dc_error_type type;           /**< type type of error */
    void (*reporter)(const struct dc_error *err);

    union
    {
        errno_t errno_code; /**< the value of errno, if the type is DC_ERROR_ERRNO */
        int err_code;       /**< type value of the error, if the type is not DC_ERROR_ERRNO */
    };
};


/**
 *
 * @param err
 */
void dc_error_init(struct dc_error *err, void (*reporter)(const struct dc_error *err));

/**
 *
 * @param err
 */
void dc_error_reset(struct dc_error *err);

/**
 *
 * @param env
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


#define DC_ERROR_RAISE_CHECK(err)                                              \
  dc_error_check((err), __FILE__, __func__, __LINE__)
#define DC_ERROR_RAISE_ERRNO(err, code)                                        \
  dc_error_errno((err), __FILE__, __func__, __LINE__, (code))
#define DC_ERROR_RAISE_SYSTEM(err, msg, code)                                  \
  dc_error_system((err), __FILE__, __func__, __LINE__, (msg), (code))
#define DC_ERROR_RAISE_USER(err, msg, code)                                    \
  dc_error_user((err), __FILE__, __func__, __LINE__, (msg), (code))


#endif // LIBDC_ERROR_ERROR_H
