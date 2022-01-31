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


#include "check.h"
#include "error.h"
#include <string.h>

bool dc_check_not_null(struct dc_error *err, const void *ptr)
{
    if(ptr == NULL)
    {
        DC_ERROR_RAISE_CHECK(err);

        return false;
    }

    return true;
}

bool dc_check_null(struct dc_error *err, const void *ptr)
{
    if(ptr != NULL)
    {
        DC_ERROR_RAISE_CHECK(err);

        return false;
    }

    return true;
}

bool dc_check_greater_than_int(struct dc_error *err, int a, int b)
{
    if(a <= b)
    {
        DC_ERROR_RAISE_CHECK(err);

        return false;
    }

    return true;
}

bool dc_check_less_than_int(struct dc_error *err, int a, int b)
{
    if(a >= b)
    {
        DC_ERROR_RAISE_CHECK(err);

        return false;
    }

    return true;
}

bool dc_check_equals_int(struct dc_error *err, int a, int b)
{
    if(a != b)
    {
        DC_ERROR_RAISE_CHECK(err);

        return false;
    }

    return true;
}

bool dc_check_equals_string(struct dc_error *err, const char *a, const char *b)
{
    if(strcmp(a, b) != 0)
    {
        DC_ERROR_RAISE_CHECK(err);

        return false;
    }

    return true;
}

bool dc_check_not_equals_int(struct dc_error *err, int a, int b)
{
    if(a == b)
    {
        DC_ERROR_RAISE_CHECK(err);

        return false;
    }

    return true;
}

bool dc_check_not_equals_string(struct dc_error *err, const char *a, const char *b)
{
    if(strcmp(a, b) == 0)
    {
        DC_ERROR_RAISE_CHECK(err);

        return false;
    }

    return true;
}
