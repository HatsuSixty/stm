// Copyright 2021 Alexey Kutepov <reximkut@gmail.com>

// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef SV_H_
#define SV_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#ifndef SVDEF
#define SVDEF
#endif // SVDEF

typedef struct {
    size_t count;
    const char *data;
} String_View;

#define SV(cstr_lit) sv_from_parts(cstr_lit, sizeof(cstr_lit) - 1)
#define SV_STATIC(cstr_lit)   \
    {                         \
        sizeof(cstr_lit) - 1, \
        (cstr_lit)            \
    }

#define SV_NULL sv_from_parts(NULL, 0)

// printf macros for String_View
#define SV_Fmt "%.*s"
#define SV_Arg(sv) (int) (sv).count, (sv).data
// USAGE:
//   String_View name = ...;
//   printf("Name: "SV_Fmt"\n", SV_Arg(name));

SVDEF String_View sv_from_parts(const char *data, size_t count);
SVDEF String_View sv_from_cstr(const char *cstr);
SVDEF String_View sv_trim_left(String_View sv);
SVDEF String_View sv_trim_right(String_View sv);
SVDEF String_View sv_trim(String_View sv);
SVDEF String_View sv_take_left_while(String_View sv, bool (*predicate)(char x));
SVDEF String_View sv_chop_by_delim(String_View *sv, char delim);
SVDEF String_View sv_chop_by_sv(String_View *sv, String_View thicc_delim);
SVDEF bool sv_try_chop_by_delim(String_View *sv, char delim, String_View *chunk);
SVDEF String_View sv_chop_left(String_View *sv, size_t n);
SVDEF String_View sv_chop_right(String_View *sv, size_t n);
SVDEF String_View sv_chop_left_while(String_View *sv, bool (*predicate)(char x));
SVDEF bool sv_index_of(String_View sv, char c, size_t *index);
SVDEF bool sv_eq(String_View a, String_View b);
SVDEF bool sv_eq_ignorecase(String_View a, String_View b);
SVDEF bool sv_starts_with(String_View sv, String_View prefix);
SVDEF bool sv_ends_with(String_View sv, String_View suffix);
SVDEF uint64_t sv_to_u64(String_View sv);
SVDEF int sv_to_int(String_View sv);

#endif  // SV_H_
