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

