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


#include "dc_error/error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dc_error
{
    char *message;
    const char *file_name;
    const char *function_name;
    size_t line_number;
    dc_error_type type;

    void (*reporter)(const struct dc_error *err);

    union
    {
        errno_t errno_code;
        int err_code;
    };
};

static void setup_error(struct dc_error *err, dc_error_type type, const char *file_name, const char *function_name,
                        size_t line_number, const char *msg);

struct dc_error *dc_error_create(bool report)
{
    struct dc_error *err;

    err = malloc(sizeof(struct dc_error));

    if(err != NULL)
    {
        dc_error_init(err, report);
    }

    return err;
}

void dc_error_init(struct dc_error *err, bool report)
{
    memset(err, 0, sizeof(struct dc_error));

    if(report)
    {
        err->reporter = dc_error_default_error_reporter;
    }
}

void dc_error_reset(struct dc_error *err)
{
    if(err->message)
    {
        free(err->message);
        err->message = NULL;
    }

    dc_error_init(err, err->reporter);
}

bool dc_error_is_reporting(struct dc_error *err)
{
    return err->reporter != NULL;
}

void dc_error_set_reporting(struct dc_error *err, bool on)
{
    if(on)
    {
        err->reporter = dc_error_default_error_reporter;
    }
    else
    {
        err->reporter = NULL;
    }
}

void dc_error_default_error_reporter(const struct dc_error *err)
{
    if(err->type == DC_ERROR_ERRNO)
    {
        // NOLINTNEXTLINE(cert-err33-c)
        fprintf(stderr, "ERROR: %s : %s : @ %zu : %d : %s\n", err->file_name, err->function_name, err->line_number,
                err->errno_code, err->message);
    }
    else
    {
        // NOLINTNEXTLINE(cert-err33-c)
        fprintf(stderr, "ERROR: %s : %s : @ %zu : %d : %s\n", err->file_name, err->function_name, err->line_number,
                err->err_code, err->message);
    }
}

static void setup_error(struct dc_error *err, dc_error_type type, const char *file_name, const char *function_name,
                        size_t line_number, const char *msg)
{
    char *saved_msg;

    saved_msg = malloc(strlen(msg) + 1);

    if(saved_msg)
    {
        strcpy(saved_msg, msg);
    }

    err->type = type;
    err->file_name = file_name;
    err->function_name = function_name;
    err->line_number = line_number;
    err->message = saved_msg;
}

void dc_error_check(struct dc_error *err, const char *file_name, const char *function_name, size_t line_number)
{
    const char *msg;

    // TODO: fix this, message should be passed in
    msg = "failed check";
    setup_error(err, DC_ERROR_CHECK, file_name, function_name, line_number, msg);
    err->errno_code = -1;

    if(err->reporter)
    {
        err->reporter(err);
    }
}

void dc_error_errno(struct dc_error *err, const char *file_name, const char *function_name, size_t line_number,
                    errno_t err_code)
{
    char *msg;

    msg = strerror(err_code);   // NOLINT(concurrency-mt-unsafe)
    msg = strdup(msg);
    setup_error(err, DC_ERROR_ERRNO, file_name, function_name, line_number, msg);
    err->errno_code = err_code; // NOLINT(clang-analyzer-unix.Malloc)

    if(err->reporter)
    {
        err->reporter(err);
    }
}

void dc_error_system(struct dc_error *err, const char *file_name, const char *function_name, size_t line_number,
                     const char *msg, int err_code)
{
    setup_error(err, DC_ERROR_SYSTEM, file_name, function_name, line_number, msg);
    err->err_code = err_code;

    if(err->reporter)
    {
        err->reporter(err);
    }
}

void dc_error_user(struct dc_error *err, const char *file_name, const char *function_name, size_t line_number,
                   const char *msg, int err_code)
{
    setup_error(err, DC_ERROR_USER, file_name, function_name, line_number, msg);
    err->err_code = err_code;

    if(err->reporter)
    {
        err->reporter(err);
    }
}

inline bool dc_error_has_error(const struct dc_error *err)
{
    return err->type != DC_ERROR_NONE;
}

inline bool dc_error_has_no_error(const struct dc_error *err)
{
    return err->type == DC_ERROR_NONE;
}

inline bool dc_error_is_errno(const struct dc_error *err, errno_t code)
{
    return (err->type == DC_ERROR_ERRNO) && (err->errno_code == code);
}
