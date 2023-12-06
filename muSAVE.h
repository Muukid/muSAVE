/*
muSAVE.h - Muukid
Public domain single-file C library for generating readable assembly versions of SPIR-V binary code.
No warranty implied; use at your own risk.

Licensed under MIT License or public domain, whichever you prefer.
More explicit license information at the end of file.

@TODO make VS compatible
*/

#ifndef MUSAVE_H
#define MUSAVE_H

#ifdef __cplusplus
extern "C" { // }
#endif

/* basics */

#define MUSAVE_VERSION_MAJOR 1
#define MUSAVE_VERSION_MINOR 0
#define MUSAVE_VERSION_PATCH 0

#ifndef MUDEF
	#ifdef MU_STATIC
		#define MUDEF static
	#else
		#define MUDEF extern
	#endif
#endif

/* C standard library dependencies */

#if !defined(mu_print) || !defined(mu_printf)
    #ifdef MUCOSA_NO_PRINT
        #ifndef mu_print
            #define mu_print(msg)
        #endif
        #ifndef mu_printf
            #define mu_printf(msg, ...)
        #endif
    #else
        #include <stdio.h>
        #ifndef mu_print
            #define mu_print printf
        #endif
        #ifndef mu_printf
            #define mu_printf printf
        #endif
    #endif
#endif

#if !defined(int8_m)      || \
	!defined(uint8_m)     || \
	!defined(int16_m)     || \
	!defined(uint16_m)    || \
	!defined(int32_m)     || \
	!defined(uint32_m)    || \
	!defined(int64_m)     || \
	!defined(uint64_m)    || \
	!defined(MU_SIZE_MAX)
	
	#include <stdint.h>
	
	#ifndef int8_m
		#define int8_m int8_t
	#endif
	#ifndef uint8_m
		#define uint8_m uint8_t
	#endif
	#ifndef int16_m
		#define int16_m int16_t
	#endif
	#ifndef uint16_m
		#define uint16_m uint16_t
	#endif
	#ifndef int32_m
		#define int32_m int32_t
	#endif
	#ifndef uint32_m
		#define uint32_m uint32_t
	#endif
	#ifndef int64_m
		#define int64_m int64_t
	#endif
	#ifndef uint64_m
		#define uint64_m uint64_t
	#endif

	#ifndef MU_SIZE_MAX
		#define MU_SIZE_MAX SIZE_MAX
	#endif

#endif

#ifndef mu_memcpy
	#include <string.h>
	#define mu_memcpy memcpy
#endif

/* mus v3.1.0 header */

#ifndef MUS_H
	#define MUS_H

	#define MUS_VERSION_MAJOR 3
	#define MUS_VERSION_MINOR 1
	#define MUS_VERSION_PATCH 0

	#ifndef MUDEF
	    #ifdef MU_STATIC
	        #define MUDEF static
	    #else
	        #define MUDEF extern
	    #endif
	#endif

	#if !defined(int64_m)

	    #include <stdint.h>

	    #ifndef int64_m
	        #define int64_m int64_t
	    #endif

	#endif

	#ifndef size_m
	    #include <stddef.h>
	    #define size_m size_t
	#endif

	#ifndef wchar_m
	    #include <wchar.h>
	    #define wchar_m wchar_t
	#endif

	#ifndef MU_NULL
	    #define MU_NULL 0
	#endif

	#ifndef MU_BOOL
	    #define MU_BOOL
	    typedef enum { MU_FALSE, MU_TRUE } muBool;
	#endif

	typedef enum { MU_STRING_TYPE_CHAR, MU_STRING_TYPE_WCHAR } muStringType;
	typedef struct {
	    char* s;
	    wchar_m* ws;
	    muStringType type;
	    size_m size;
	    size_m len;
	} muString;

	/* muString */

	MUDEF size_m mu_string_strlen(muString s);

	MUDEF muString mu_string_create (char* s);
	MUDEF muString mu_wstring_create(wchar_m* ws);

	MUDEF muString mu_string_destroy(muString str);

	MUDEF muString mu_string_size_check(muString str, size_m size);

	MUDEF muString mu_string_delete(muString str, size_m beg, size_m end);

	MUDEF muString mu_string_insert (muString str, char* insert,    size_m i);
	MUDEF muString mu_wstring_insert(muString str, wchar_m* insert, size_m i);

	MUDEF muString mu_string_insert_integer (muString str, int64_m n, size_m i);
	MUDEF muString mu_wstring_insert_integer(muString str, int64_m n, size_m i);

	MUDEF muString mu_string_insert_float (muString str, double n, size_m max_decimals, size_m i);
	MUDEF muString mu_wstring_insert_float(muString str, double n, size_m max_decimals, size_m i);

	MUDEF muString mu_string_replace (muString str, char* find,    char* replace,    size_m beg, size_m end);
	MUDEF muString mu_wstring_replace(muString str, wchar_m* find, wchar_m* replace, size_m beg, size_m end);

	MUDEF muString mu_string_to_lowercase(muString str, size_m beg, size_m end);
	MUDEF muString mu_string_to_uppercase(muString str, size_m beg, size_m end);

	/* string */

	MUDEF muBool mu_here (char* str,    char* check,    size_m i);
	MUDEF muBool mu_where(wchar_m* str, wchar_m* check, size_m i);

	MUDEF muBool mu_has (char* str,    char* find,    size_m beg, size_m end);
	MUDEF muBool mu_whas(wchar_m* str, wchar_m* find, size_m beg, size_m end);

	/* character conversion */

	MUDEF int mu_wstring_to_string(char* dest,    wchar_m* src, size_m dest_len);
	MUDEF int mu_string_to_wstring(wchar_m* dest, char* src,    size_m dest_len);

	/* uppercase/lowercase */

	MUDEF char    mu_char_to_lowercase (char c);
	MUDEF wchar_m mu_wchar_to_lowercase(wchar_m c);

	MUDEF char    mu_char_to_uppercase (char c);
	MUDEF wchar_m mu_wchar_to_uppercase(wchar_m c);

	MUDEF muBool mu_char_is_lowercase (char c);
	MUDEF muBool mu_wchar_is_lowercase(wchar_m c);

	MUDEF muBool mu_char_is_uppercase (char c);
	MUDEF muBool mu_wchar_is_uppercase(wchar_m c);

	/* numbers */

	MUDEF int   mu_integer_to_string (int64_m n, char* dest,    size_m dest_len);
	MUDEF int   mu_integer_to_wstring(int64_m n, wchar_m* dest, size_m dest_len);

	MUDEF int   mu_float_to_string (double n, size_m max_decimals, char* dest,    size_m dest_len);
MUDEF int   mu_float_to_wstring(double n, size_m max_decimals, wchar_m* dest, size_m dest_len);

#endif /* MUS_H */

/* defines */

#ifndef muResult
	#define muResult muBool
	#define MU_FAILURE MU_FALSE
	#define MU_SUCCESS MU_TRUE
#endif

#ifndef MU_NULL_PTR
	#define MU_NULL_PTR 0
#endif

#define MU_SPIRV_MAX_DEFAULT_OPERAND_COUNT 16
#define MU_SPIRV_INSTRUCTION_COUNT 512

/* enums */

enum muSPIRVType {
	MU_SPIRV_NO_TYPE=0,
	MU_SPIRV_UINT32,
	MU_SPIRV_STRING,
	MU_SPIRV_LITERAL_VALUE,
	MU_SPIRV_OPCODE,

	MU_SPIRV_ID_TARGET,
	MU_SPIRV_ID_TYPE,
	MU_SPIRV_ID_RESULT,
	MU_SPIRV_ID_RESULT_TYPE,
	MU_SPIRV_ID_STRING,
	MU_SPIRV_ID_OPERAND,

	MU_SPIRV_INDEFINITE,

	MU_SPIRV_SIGN,

	// enums
	MU_SPIRV_SOURCE_LANGUAGE,
	MU_SPIRV_EXECUTION_MODEL,
	MU_SPIRV_ADDRESSING_MODEL,
	MU_SPIRV_MEMORY_MODEL,
	MU_SPIRV_EXECUTION_MODE,
	MU_SPIRV_STORAGE_CLASS,
	MU_SPIRV_DIM,
	MU_SPIRV_SAMPLER_ADDRESSING_MODE,
	MU_SPIRV_SAMPLER_FILTER_MODE,
	MU_SPIRV_IMAGE_FORMAT,
	MU_SPIRV_IMAGE_CHANNEL_ORDER,
	MU_SPIRV_IMAGE_CHANNEL_DATA_TYPE,
	MU_SPIRV_IMAGE_OPERANDS,
	MU_SPIRV_FP_FAST_MATH_MODE,
	MU_SPIRV_FP_ROUNDING_MODE,
	MU_SPIRV_LINKAGE_TYPE,
	MU_SPIRV_ACCESS_QUALIFIER,
	MU_SPIRV_FUNCTION_PARAMETER_ATTRIBUTE,
	MU_SPIRV_DECORATION,
	MU_SPIRV_BUILTIN,
	MU_SPIRV_SELECTION_CONTROL,
	MU_SPIRV_LOOP_CONTROL,
	MU_SPIRV_FUNCTION_CONTROL,
	MU_SPIRV_MEMORY_SEMANTICS,
	MU_SPIRV_MEMORY_OPERANDS,
	MU_SPIRV_SCOPE,
	MU_SPIRV_GROUP_OPERATION,
	MU_SPIRV_KERNEL_ENQUEUE_FLAGS,
	MU_SPIRV_KERNEL_PROFILING_INFO,
	MU_SPIRV_CAPABILITY,
	MU_SPIRV_RESERVED_RAY_FLAGS,
	MU_SPIRV_RESERVED_RAY_QUERY_INTERSECTION,
	MU_SPIRV_RESERVED_RAY_QUERY_COMMITTED_TYPE,
	MU_SPIRV_RESERVED_RAY_QUERY_CANDIDATE_TYPE,
	MU_SPIRV_RESERVED_FRAGMENT_SHADING_RATE,
	MU_SPIRV_RESERVED_FP_DENORM_MODE,
	MU_SPIRV_RESERVED_FP_OPERATION_MODE,
	MU_SPIRV_QUANTIZATION_MODE,
	MU_SPIRV_OVERFLOW_MODE,
	MU_SPIRV_PACKED_VECTOR_FORMAT
};
typedef enum muSPIRVType muSPIRVType;

enum muSPIRVDataType {
	MU_SPIRV_UNKNOWN=0,
	MU_SPIRV_INT,
	MU_SPIRV_FLOAT,
	MU_SPIRV_BOOL,
	MU_SPIRV_OTHER
};
typedef enum muSPIRVDataType muSPIRVDataType;

/* structs */

struct muSPIRVInstruction {
	const char* name;
	size_m opcode;
	size_m min_word_count;
	muSPIRVType indefinite_type;
	muSPIRVType operands[MU_SPIRV_MAX_DEFAULT_OPERAND_COUNT];
};
typedef struct muSPIRVInstruction muSPIRVInstruction;

struct muSPIRVTypeInfo {
	muSPIRVDataType datatype;
	uint32_m size;
};
typedef struct muSPIRVTypeInfo muSPIRVTypeInfo;

/* variables */

MUDEF muSPIRVInstruction mu_global_SPIRV_instructions[MU_SPIRV_INSTRUCTION_COUNT];

/* functions */

muString mu_spirv_binary_to_assembly(const char* binary, size_m len);

#ifdef __cplusplus
}
#endif

#endif /* MUSAVE_H */


#ifdef MUSAVE_IMPLEMENTATION

#ifdef __cplusplus
extern "C" { // }
#endif

#define MUS_IMPLEMENTATION
/* mus v3.1.0 implementation */

#ifdef MUS_IMPLEMENTATION

	#if !defined(mu_malloc)    || \
	    !defined(mu_free)      || \
	    !defined(mu_realloc)   || \
	    !defined(mu_mbstowcs)  || \
	    !defined(mu_mbsrtowcs) || \
	    !defined(mu_wcstombs)  || \
	    !defined(mu_wcsrtombs)

	    #include <stdlib.h>
	    #ifndef mu_malloc
	        #define mu_malloc malloc
	    #endif
	    #ifndef mu_free
	        #define mu_free free
	    #endif
	    #ifndef mu_realloc
	        #define mu_realloc realloc
	    #endif
	    #ifndef mu_mbstowcs
	        #define mu_mbstowcs mbstowcs
	    #endif
	    #ifndef mu_mbsrtowcs
	        #define mu_mbsrtowcs mbsrtowcs
	    #endif
	    #ifndef mu_wcstombs
	        #define mu_wcstombs wcstombs
	    #endif
	    #ifndef mu_wcsrtombs
	        #define mu_wcsrtombs wcsrtombs
	    #endif
	#endif

	#if !defined(mu_strlen) || !defined(mu_wstrlen)
	    #ifndef mu_strlen
	        #include <string.h>
	        #define mu_strlen strlen
	    #endif
	    #ifndef mu_wstrlen
	        #include <wchar.h>
	        #define mu_wstrlen wcslen
	    #endif
	#endif

	#if !defined(mu_snprintf)

	    #include <stdio.h>

	    #ifndef mu_snprintf
	        #define mu_snprintf snprintf
	    #endif

	#endif

	// not sure if multi-byte state being null is fully safe

	MUDEF int mu_wstring_to_string(char* dest, wchar_m* src, size_m dest_len) {
	    if (dest == MU_NULL) return (size_m)mu_wcsrtombs(MU_NULL, (const wchar_m**)&src, 1, MU_NULL);
	    return (size_m)mu_wcstombs(dest, src, dest_len);
	}
	MUDEF int mu_string_to_wstring(wchar_m* dest, char* src, size_m dest_len) {
	    if (dest == MU_NULL) return (size_m)mu_mbsrtowcs(MU_NULL, (const char**)&src, 1, MU_NULL);
	    return (size_m)mu_mbstowcs(dest, src, dest_len);
	}

	MUDEF size_m mu_string_strlen(muString s) {
	    return s.len;
	}

	MUDEF muString mu_string_create(char* s) {
	    muString str;
	    str.len = mu_strlen(s);
	    str.size = (sizeof(char) * (str.len)) * 2;
	    str.s = mu_malloc(str.size);
	    str.ws = 0;
	    str.type = MU_STRING_TYPE_CHAR;
	    for (size_m i = 0; i < str.len; i++) {
	        str.s[i] = s[i];
	    }
	    str.s[str.len] = '\0';
	    return str;
	}
	MUDEF muString mu_wstring_create(wchar_m* ws) {
	    muString str;
	    str.len = mu_wstrlen(ws);
	    str.size = (sizeof(wchar_m) * (str.len)) * 2;
	    str.ws = mu_malloc(str.size);
	    str.s = 0;
	    str.type = MU_STRING_TYPE_WCHAR;
	    for (size_m i = 0; i < str.len; i++) {
	        str.ws[i] = ws[i];
	    }
	    str.ws[str.len] = '\0';
	    return str;
	}

	MUDEF muString mu_string_destroy(muString str) {
	    if (str.s) mu_free(str.s);
	    str.s = 0;
	    if (str.ws) mu_free(str.ws);
	    str.ws = 0;
	    return str;
	}

	MUDEF muString mu_string_size_check(muString str, size_m size) {
	    muBool resized = MU_FALSE;
	    while (str.size < size) {
	        str.size *= 2;
	        resized = MU_TRUE;
	    }
	    if (resized == MU_TRUE) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s = mu_realloc(str.s, str.size);
	        } else {
	            str.ws = mu_realloc(str.ws, str.size);
	        }
	    }
	    return str;
	}

	MUDEF muBool mu_here(char* str, char* check, size_m i) {
	    if (str[i] != check[0]) return MU_FALSE;
	    size_m check_len = mu_strlen(check);
	    size_m str_len = mu_strlen(str);
	    for (size_m j = 0; j < check_len; j++) {
	        if (i+j >= str_len || str[i+j] != check[j]) {
	            return MU_FALSE;
	        }
	    }
	    return MU_TRUE;
	}
	MUDEF muBool mu_where(wchar_m* str, wchar_m* check, size_m i) {
	    if (str[i] != check[0]) return MU_FALSE;
	    size_m check_len = mu_wstrlen(check);
	    size_m str_len = mu_wstrlen(str);
	    for (size_m j = 0; j < check_len; j++) {
	        if (i+j >= str_len || str[i+j] != check[j]) {
	            return MU_FALSE;
	        }
	    }
	    return MU_TRUE;
	}

	MUDEF muBool mu_has(char* str, char* find, size_m beg, size_m end) {
	    size_m find_len = mu_strlen(find);
	    for (size_m i = beg; i + find_len < end; i++) {
	        muBool found = MU_TRUE;
	        for (size_m j = 0; j < find_len; j++) {
	            if (str[i+j] != find[j]) found = MU_FALSE;
	        }
	        if (found == MU_TRUE) return MU_TRUE;
	    }
	    return MU_FALSE;
	}
	MUDEF muBool mu_whas(wchar_m* str, wchar_m* find, size_m beg, size_m end) {
	    size_m find_len = mu_wstrlen(find);
	    for (size_m i = beg; i + find_len < end; i++) {
	        muBool found = MU_TRUE;
	        for (size_m j = 0; j < find_len; j++) {
	            if (str[i+j] != find[j]) found = MU_FALSE;
	        }
	        if (found == MU_TRUE) return MU_TRUE;
	    }
	    return MU_FALSE;
	}

	MUDEF muString mu_string_delete(muString str, size_m beg, size_m end) {
	    for (size_m i = end; i < mu_string_strlen(str) + 1; i++) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s[i-(end-beg)] = str.s[i];
	        } else {
	            str.ws[i-(end-beg)] = str.ws[i];
	        }
	    }
	    str.len -= (end - beg);
	    return str;
	}

	MUDEF muString mu_string_insert(muString str, char* insert, size_m i) {
	    if (str.type == MU_STRING_TYPE_WCHAR) {
	        size_m size = mu_string_to_wstring(MU_NULL, insert, 0);
	        wchar_m* insert_w = mu_malloc(size * sizeof(wchar_m));
	        mu_string_to_wstring(insert_w, insert, size);
	        str = mu_wstring_insert(str, insert_w, i);
	        mu_free(insert_w);
	        return str;
	    }
	    size_m insert_len = mu_strlen(insert);
	    str = mu_string_size_check(str, sizeof(char) * (mu_string_strlen(str) + insert_len + 1));
	    for (size_m j = mu_strlen(str.s); i < j+1; j--) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s[j+insert_len] = str.s[j];
	        } else {
	            str.ws[j+insert_len] = str.ws[j];
	        }
	    }
	    for (size_m j = 0; j < insert_len; j++) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s[i+j] = insert[j];
	        } else {
	            str.ws[i+j] = insert[j];
	        }
	    }
	    str.len += insert_len;
	    return str;
	}
	MUDEF muString mu_wstring_insert(muString str, wchar_m* insert, size_m i) {
	    if (str.type == MU_STRING_TYPE_CHAR) {
	        size_m size = mu_wstring_to_string(MU_NULL, insert, 0);
	        char* insert_c = mu_malloc(size * sizeof(char));
	        mu_wstring_to_string(insert_c, insert, size);
	        str = mu_string_insert(str, insert_c, i);
	        mu_free(insert_c);
	        return str;
	    }
	    size_m insert_len = mu_wstrlen(insert);
	    str = mu_string_size_check(str, sizeof(wchar_m) * (mu_string_strlen(str) + insert_len + 1));
	    for (size_m j = mu_string_strlen(str); i < j+1; j--) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s[j+insert_len] = str.s[j];
	        } else {
	            str.ws[j+insert_len] = str.ws[j];
	        }
	    }
	    for (size_m j = 0; j < insert_len; j++) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s[i+j] = insert[j];
	        } else {
	            str.ws[i+j] = insert[j];
	        }
	    }
	    str.len += insert_len;
	    return str;
	}

	MUDEF muString mu_string_insert_integer(muString str, int64_m n, size_m i) {
	    size_m len = mu_integer_to_string(n, MU_NULL, 0);
	    len++;
	    char* s = mu_malloc(len * sizeof(char));
	    mu_integer_to_string(n, s, len);
	    s[len-1] = 0;
	    str = mu_string_insert(str, s, i);
	    mu_free(s);
	    return str;
	}
	MUDEF muString mu_wstring_insert_integer(muString str, int64_m n, size_m i) {
	    size_m len = mu_integer_to_wstring(n, MU_NULL, 0);
	    len++;
	    wchar_m* s = mu_malloc(len * sizeof(wchar_m));
	    mu_integer_to_wstring(n, s, len);
	    s[len-1] = 0;
	    str = mu_wstring_insert(str, s, i);
	    mu_free(s);
	    return str;
	}

	MUDEF muString mu_string_insert_float(muString str, double n, size_m max_decimals, size_m i) {
	    size_m len = mu_float_to_string(n, max_decimals, MU_NULL, 0);
	    len++;
	    char* s = mu_malloc(len * sizeof(char));
	    mu_float_to_string(n, max_decimals, s, len);
	    s[len-1] = 0;
	    str = mu_string_insert(str, s, i);
	    mu_free(s);
	    return str;
	}
	MUDEF muString mu_wstring_insert_float(muString str, double n, size_m max_decimals, size_m i) {
	    size_m len = mu_float_to_wstring(n, max_decimals, MU_NULL, 0);
	    len++;
	    wchar_m* s = mu_malloc(len * sizeof(wchar_m));
	    mu_float_to_wstring(n, max_decimals, s, len);
	    s[len-1] = 0;
	    str = mu_wstring_insert(str, s, i);
	    mu_free(s);
	    return str;
	}

	MUDEF muString mu_string_replace(muString str, char* find, char* replace, size_m beg, size_m end) {
	    if (str.type == MU_STRING_TYPE_WCHAR) {
	        size_m find_size = mu_string_to_wstring(MU_NULL, find, 0);
	        size_m replace_size = mu_string_to_wstring(MU_NULL, replace, 0);
	        wchar_m* find_w = mu_malloc(find_size * sizeof(wchar_m));
	        wchar_m* replace_w = mu_malloc(replace_size * sizeof(wchar_m));
	        mu_string_to_wstring(find_w, find, find_size);
	        mu_string_to_wstring(replace_w, replace, replace_size);
	        str = mu_wstring_replace(str, find_w, replace_w, beg, end);
	        mu_free(find_w);
	        mu_free(replace_w);
	        return str;
	    }
	    size_m find_len = mu_strlen(find);
	    size_m replace_len = mu_strlen(replace);
	    size_m len_dif = find_len - replace_len;
	    if (replace_len > find_len) len_dif = replace_len - find_len;
	    for (size_m i = beg; i < end + 1 && i < mu_string_strlen(str); i++) {
	        if (mu_here(str.s, find, i) == MU_TRUE) {
	            str = mu_string_delete(str, i, i + find_len);
	            if (replace_len > 0) {
	                str = mu_string_insert(str, replace, i);
	            }
	            end -= len_dif;
	        }
	    }
	    str.len = mu_strlen(str.s);
	    return str;
	}
	MUDEF muString mu_wstring_replace(muString str, wchar_m* find, wchar_m* replace, size_m beg, size_m end) {
	    if (str.type == MU_STRING_TYPE_CHAR) {
	        size_m find_size = mu_wstring_to_string(MU_NULL, find, 0);
	        size_m replace_size = mu_wstring_to_string(MU_NULL, replace, 0);
	        char* find_c = mu_malloc(find_size * sizeof(char));
	        char* replace_c = mu_malloc(replace_size * sizeof(char));
	        mu_wstring_to_string(find_c, find, find_size);
	        mu_wstring_to_string(replace_c, replace, replace_size);
	        str = mu_string_replace(str, find_c, replace_c, beg, end);
	        mu_free(find_c);
	        mu_free(replace_c);
	        return str;
	    }
	    size_m find_len = mu_wstrlen(find);
	    size_m replace_len = mu_wstrlen(replace);
	    size_m len_dif = find_len - replace_len;
	    if (replace_len > find_len) len_dif = replace_len - find_len;
	    for (size_m i = beg; i < end + 1 && i < mu_string_strlen(str); i++) {
	        if (mu_where(str.ws, find, i) == MU_TRUE) {
	            str = mu_string_delete(str, i, i + find_len);
	            if (replace_len > 0) {
	                str = mu_wstring_insert(str, replace, i);
	            }
	            end -= len_dif;
	        }
	    }
	    str.len = mu_wstrlen(str.ws);
	    return str;
	}

	MUDEF muString mu_string_to_lowercase(muString str, size_m beg, size_m end) {
	    for (size_m i = beg; i < str.len && i < end + 1; i++) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s[i] = mu_char_to_lowercase(str.s[i]);
	        } else {
	            str.ws[i] = mu_wchar_to_lowercase(str.ws[i]);
	        }
	    }
	    return str;
	}
	MUDEF muString mu_string_to_uppercase(muString str, size_m beg, size_m end) {
	    for (size_m i = beg; i < str.len && i < end + 1; i++) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s[i] = mu_char_to_uppercase(str.s[i]);
	        } else {
	            str.ws[i] = mu_wchar_to_uppercase(str.ws[i]);
	        }
	    }
	    return str;
	}

	// did this manually because C standards suck
	// last updated 16 September 2023, covers 0 -> 65533
	// https://en.wikipedia.org/wiki/List_of_Unicode_characters
	// https://www.ssec.wisc.edu/~tomw/java/unicode.html

	MUDEF char mu_char_to_lowercase(char c) {
	    if (c >= 65 && c <= 90) c += 32;
	    return c;
	}
	MUDEF wchar_m mu_wchar_to_lowercase(wchar_m c) {
	    if (
	    // latin alphabet
	        (c >= 65 && c <= 90) ||
	    // latin-1 supplement
	        (c >= 192 && c <= 222 && c != 215) ||
	    // greek and coptic
	        (c >= 913 && c <= 939) ||
	    // cyrillic
	        (c >= 0x0410 && c <= 0x042F) ||
	    // halfwidth and fullwidth forms
	        (c >= 65313 && c <= 65338)
	    ) {
	        return c + 32;
	    } else if (
	    // latin extended-a
	        (
	            (c >= 256 && c <= 310 && c % 2 == 0) || 
	            (c >= 313 && c <= 327 && c % 2 != 0) ||
	            (c >= 330 && c <= 376 && c % 2 == 0) ||
	            (c >= 377 && c <= 381 && c % 2 != 0)
	        ) ||
	    // latin extended-b
	        (
	            (c >= 461 && c <= 475 && c % 2 != 0) ||
	            (c >= 478 && c <= 494 && c % 2 == 0) ||
	            (c >= 504 && c <= 542 && c % 2 == 0) ||
	            (c >= 546 && c <= 562 && c % 2 == 0) ||
	            (c >= 582 && c <= 590 && c % 2 == 0)
	        ) ||
	    // greek and coptic
	        (
	            (c >= 984 && c <= 1006 && c % 2 == 0)
	        ) ||
	    // cyrillic
	        (
	            (c >= 0x0460 && c <= 0x0480 && c % 2 == 0) ||
	            (c >= 0x048A && c <= 0x04BE && c % 2 == 0) ||
	            (c >= 0x04C1 && c <= 0x04CD && c % 2 != 0) ||
	            (c >= 0x04D0 && c <= 0x04FE && c % 2 == 0) ||
	            // cyrillic supplement
	            (c >= 0x0500 && c <= 0x052E && c % 2 == 0)
	        ) ||
	    // latin extended additional
	        (
	            (c >= 7680 && c <= 7828 && c % 2 == 0) ||
	            (c >= 7840 && c <= 7928 && c % 2 == 0)
	        )
	    ) {
	        return c + 1;
	    } else if (
	    // cyrillic
	        (
	            (c >= 0x0400 && c <= 0x040F)
	        )
	    ) {
	        return c + 80;
	    } else if (
	    // armenian
	        (
	            (c >= 0x0530 && c <= 0x0558)
	        ) ||
	    // georgian
	        (
	            (c >= 0x10A0 && c <= 0x10CF)
	        )
	    ) {
	        return c + 48;
	    } else if (
	    // greek extended
	        (
	            (c >= 7944 && c <= 7951) || (c >= 7960 && c <= 7965) || (c >= 7976 && c <= 7983) || (c >= 7992 && c <= 7999) ||
	            (c >= 8008 && c <= 8013) || (c >= 8025 && c <= 8031) || (c >= 8040 && c <= 8047) || (c >= 8072 && c <= 8079) ||
	            (c >= 8088 && c <= 8095) || (c >= 8104 && c <= 8111) || (c >= 8120 && c <= 8124)
	        )
	    ) {
	        return c - 8;
	    } else if (
	    // enclosed alphanumerics
	        (
	            (c >= 9398 && c <= 9423)
	        )
	    ) {
	        return c + 26;
	    }
	    switch (c) {
	    default: break;
	    // odd latin extended-b / ipa extensions
	    case 386: case 388: case 391: case 395: case 401: case 408: case 416: case 418: case 420: case 423: case 428: case 431: 
	    case 435: case 437: case 440: case 444: case 453: case 456: case 459: case 498: case 500: case 571: case 577: return c+1; break;
	    case 384: return 579; break;
	    case 385: return 595; break;
	    case 390: return 596; break;
	    case 393: return 598; break;
	    case 394: return 599; break;
	    case 398: return 600; break;
	    case 399: return 601; break;
	    case 400: return 603; break;
	    case 403: return 608; break;
	    case 404: return 611; break;
	    case 406: return 617; break;
	    case 407: return 616; break;
	    case 412: return 623; break;
	    case 413: return 626; break;
	    case 425: return 643; break;
	    case 430: return 648; break;
	    case 433: return 650; break;
	    case 434: return 641; break;
	    case 439: return 658; break;
	    case 452: return 454; break;
	    case 455: return 457; break;
	    case 458: return 460; break;
	    case 497: return 499; break;
	    case 544: return 414; break;
	    case 573: return 410; break;
	    case 579: return 384; break;
	    case 580: return 649; break;
	    case 581: return 652; break;

	    // odd greek and coptic
	    case 880: case 882: case 886: case 1015: case 1018: return c+1; break;
	    case 895: return 1011; break;
	    case 904: case 905: case 906: return c+37; break;
	    case 908: case 910: case 911: return c+64; break;
	    case 975: return 983; break;
	    case 1012: return 977; break;
	    case 1017: return 1010; break;
	    case 1021: case 1022: case 1023: return c-130; break;

	    // odd greek extended
	    // this is so unsorted it makes my room look like a masterpiece
	    case 8136: case 8137: case 8138: case 8139: return c-86; break;
	    case 8140: return 8131; break;
	    case 8152: return 8144; break;
	    case 8153: return 8145; break;
	    case 8154: case 8155: return c-100; break;
	    case 8168: return 8160; break;
	    case 8169: return 8161; break;
	    case 8170: return 8058; break;
	    case 8171: return 8059; break;
	    case 8172: return 8165; break;
	    case 8184: case 8185: return c-128; break;
	    case 8187: return 8061; break;
	    }
	    return c;
	}
	MUDEF char mu_char_to_uppercase(char c) {
	    if (c >= 97 && c <= 122) c -= 32;
	    return c;
	}
	MUDEF wchar_m mu_wchar_to_uppercase(wchar_m c) {
	    if (
	    // latin alphabet
	        (c >= 97 && c <= 122) ||
	    // latin-1 supplement
	        (c >= 224 && c <= 255 && c != 247) ||
	    // greek and coptic
	        (c >= 945 && c <= 971) ||
	    // cyrillic
	        (c >= (0x0410 + 32) && c <= (0x042F + 32)) ||
	    // halfwidth and fullwidth forms
	        (c >= (65313 + 32) && c <= (65338 + 32))
	    ) {
	        return c - 32;
	    } else if (
	    // latin extended-a
	        (
	            (c >= 257 && c <= 311 && c % 2 != 0) || 
	            (c >= 312 && c <= 328 && c % 2 == 0) ||
	            (c >= 329 && c <= 375 && c % 2 != 0) ||
	            (c >= 378 && c <= 382 && c % 2 == 0)
	        ) ||
	    // latin extended-b
	        (
	            (c >= 462 && c <= 476 && c % 2 == 0) ||
	            (c >= 479 && c <= 495 && c % 2 != 0) ||
	            (c >= 505 && c <= 543 && c % 2 != 0) ||
	            (c >= 547 && c <= 563 && c % 2 != 0) ||
	            (c >= 583 && c <= 591 && c % 2 != 0)
	        ) ||
	    // greek and coptic
	        (
	            (c >= 985 && c <= 1007 && c % 2 != 0)
	        ) ||
	    // cyrillic
	        (
	            (c >= 0x0461 && c <= 0x0481 && c % 2 != 0) ||
	            (c >= 0x048B && c <= 0x04BF && c % 2 != 0) ||
	            (c >= 0x04C2 && c <= 0x04CE && c % 2 == 0) ||
	            (c >= 0x04D1 && c <= 0x04FF && c % 2 != 0) ||
	            // cyrillic supplement
	            (c >= 0x0501 && c <= 0x052F && c % 2 != 0)
	        ) ||
	    // latin extended additional
	        (
	            (c >= 7681 && c <= 7829 && c % 2 != 0) ||
	            (c >= 7841 && c <= 7929 && c % 2 != 0)
	        )
	    ) {
	        return c - 1;
	    } else if (
	    // cyrillic
	        (
	            (c >= (0x0400+80) && c <= (0x040F+80))
	        )
	    ) {
	        return c - 80;
	    } else if (
	    // armenian
	        (
	            (c >= (0x0530+48) && c <= (0x0558+48))
	        ) ||
	    // georgian
	        (
	            (c >= (0x10A0+48) && c <= (0x10CF+48))
	        )
	    ) {
	        return c - 48;
	    } else if (
	    // greek extended
	        (
	            (c >= (7944-8) && c <= (7951-8)) || (c >= (7960-8) && c <= (7965-8)) || (c >= (7976-8) && c <= (7983-8)) || (c >= (7992-8) && c <= (7999-8)) ||
	            (c >= (8008-8) && c <= (8013-8)) || (c >= (8025-8) && c <= (8031-8)) || (c >= (8040-8) && c <= (8047-8)) || (c >= (8072-8) && c <= (8079-8)) ||
	            (c >= (8088-8) && c <= (8095-8)) || (c >= (8104-8) && c <= (8111-8)) || (c >= (8120-8) && c <= (8124-8))
	        )
	    ) {
	        return c + 8;
	    } else if (
	    // enclosed alphanumerics
	        (
	            (c >= (9398+26) && c <= (9423+26))
	        )
	    ) {
	        return c - 26;
	    }
	    switch (c) {
	    default: break;
	    // odd latin extended-b / ipa extensions
	    case 387: case 389: case 392: case 396: case 402: case 409: case 417: case 419: case 421: case 424: case 429: case 432: 
	    case 436: case 438: case 441: case 445: case 453: case 456: case 459: case 498: case 501: case 572: case 578: return c-1; break;
	    case 579: return 384; break;
	    case 595: return 385; break;
	    case 596: return 390; break;
	    case 598: return 393; break;
	    case 599: return 394; break;
	    case 600: return 398; break;
	    case 601: return 399; break;
	    case 603: return 400; break;
	    case 608: return 403; break;
	    case 611: return 404; break;
	    case 617: return 406; break;
	    case 616: return 407; break;
	    case 623: return 412; break;
	    case 626: return 413; break;
	    case 643: return 425; break;
	    case 648: return 430; break;
	    case 650: return 433; break;
	    case 641: return 434; break;
	    case 658: return 439; break;
	    case 454: return 452; break;
	    case 457: return 455; break;
	    case 460: return 458; break;
	    case 499: return 497; break;
	    case 414: return 544; break;
	    case 410: return 573; break;
	    case 384: return 579; break;
	    case 649: return 580; break;
	    case 652: return 581; break;

	    // odd greek and coptic
	    case 881: case 883: case 887: case 1016: case 1019: return c-1; break;
	    case 1011: return 895; break;
	    case 941: case 942: case 943: return c-37; break;
	    case 972: case 974: case 975: return c-64; break;
	    case 983: return 975; break;
	    case 977: return 1012; break;
	    case 1010: return 1017; break;
	    case 891: case 892: case 893: return c+130; break;

	    // odd greek extended
	    // this is so unsorted it makes my room look like a masterpiece
	    case 8050: case 8051: case 8052: case 8053: return c+86; break;
	    case 8131: return 8140; break;
	    case 8144: return 8152; break;
	    case 8145: return 8153; break;
	    case 8054: case 8055: return c+100; break;
	    case 8160: return 8168; break;
	    case 8161: return 8169; break;
	    case 8058: return 8170; break;
	    case 8059: return 8171; break;
	    case 8165: return 8172; break;
	    case 8056: case 8057: return c+128; break;
	    case 8061: return 8187; break;
	    }
	    return c;
	}

	// these funcs aren't entirely necessary
	MUDEF muBool mu_char_is_lowercase(char c) {
	    return c != mu_char_to_uppercase(c);
	}
	MUDEF muBool mu_wchar_is_lowercase(wchar_m c) {
	    return c != mu_wchar_to_uppercase(c);
	}
	MUDEF muBool mu_char_is_uppercase(char c) {
	    return c != mu_char_to_lowercase(c);
	}
	MUDEF muBool mu_wchar_is_uppercase(wchar_m c) {
	    return c != mu_wchar_to_lowercase(c);
	}

	MUDEF int mu_integer_to_string(int64_m n, char* dest, size_m dest_len) {
	    if (dest == MU_NULL) return mu_snprintf(MU_NULL, 0, "%ld", (long)n);
	    return mu_snprintf(dest, dest_len+1, "%ld", (long)n);
	}

	// would like to not have to convert here, but snwprintf isn't standard
	MUDEF int mu_integer_to_wstring(int64_m n, wchar_m* dest, size_m dest_len) {
	    if (dest == MU_NULL) return mu_snprintf(MU_NULL, 0, "%ld", (long)n);
	    size_m len = mu_integer_to_string(n, MU_NULL, 0);
	    char* s = mu_malloc(len * sizeof(char));
	    mu_integer_to_string(n, s, len);
	    for (size_m i = 0; i < dest_len; i++) {
	        dest[i] = (wchar_m)s[i];
	    }
	    free(s);
	    return 0;
	}

	MUDEF int mu_float_to_string(double n, size_m max_decimals, char* dest, size_m dest_len) {
	    if (max_decimals >= 10) max_decimals = 9;
	    char format[7] = "%0.0lf\0";
	    format[3] = '0' + max_decimals;
	    if (dest == MU_NULL) return mu_snprintf(MU_NULL, 0, format, n);
	    return mu_snprintf(dest, dest_len+1, format, n);
	}

	MUDEF int mu_float_to_wstring(double n, size_m max_decimals, wchar_m* dest, size_m dest_len) {
	    size_m len = mu_float_to_string(n, max_decimals, MU_NULL, 0);
	    if (dest == MU_NULL) return len;
	    char* s = mu_malloc(len * sizeof(char));
	    mu_float_to_string(n, max_decimals, s, len);
	    for (size_m i = 0; i < dest_len; i++) {
	        dest[i] = (wchar_m)s[i];
	    }
	    mu_free(s);
	    return 0;
}

#endif /* MUS_IMPLEMENTATION */

/* instruction map */

muSPIRVInstruction mu_global_SPIRV_instructions[MU_SPIRV_INSTRUCTION_COUNT] = {
	{ "OpNop",                                     0,   1,  0,                       { 0 } },
	{ "OpUndef",                                   1,   3,  0,                       { MU_SPIRV_ID_TYPE, MU_SPIRV_ID_RESULT, 0 } },
	{ "OpSourceContinued",                         2,   2,  0,                       { MU_SPIRV_STRING, 0 } },
	{ "OpSource",                                  3,   3,  0,                       { MU_SPIRV_SOURCE_LANGUAGE, MU_SPIRV_UINT32, MU_SPIRV_ID_STRING, MU_SPIRV_STRING, 0 } },
	{ "OpSourceExtension",                         4,   2,  0,                       { MU_SPIRV_STRING, 0 } },
	{ "OpName",                                    5,   3,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_STRING, 0 } },
	{ "OpMemberName",                              6,   4,  0,                       { MU_SPIRV_ID_TYPE, MU_SPIRV_UINT32, MU_SPIRV_STRING, 0 } },
	{ "OpString",                                  7,   3,  0,                       { MU_SPIRV_ID_RESULT, MU_SPIRV_STRING, 0 } },
	{ "OpLine",                                    8,   4,  0,                       { MU_SPIRV_ID_STRING, MU_SPIRV_UINT32, MU_SPIRV_UINT32, 0 } },
	// No 9
	{ "OpExtension",                               10,  2,  0,                       { MU_SPIRV_STRING, 0 } },
	{ "OpExtInstImport",                           11,  3,  0,                       { MU_SPIRV_ID_RESULT, MU_SPIRV_STRING, 0 } },
	{ "OpExtInst",                                 12,  5,  MU_SPIRV_ID_OPERAND,     { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_UINT32, 0 } },
	// No 13
	{ "OpMemoryModel",                             14,  3,  0,                       { MU_SPIRV_ADDRESSING_MODEL, MU_SPIRV_MEMORY_MODEL, 0 } },
	{ "OpEntryPoint",                              15,  4,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_EXECUTION_MODEL, MU_SPIRV_ID_TARGET, MU_SPIRV_STRING, 0 } },
	{ "OpExecutionMode",                           16,  3,  MU_SPIRV_EXECUTION_MODE, { MU_SPIRV_ID_TARGET, MU_SPIRV_EXECUTION_MODE, 0 } },
	{ "OpCapability",                              17,  2,  0,                       { MU_SPIRV_CAPABILITY, 0 } },
	// No 18
	{ "OpTypeVoid",                                19,  2,  0,                       { MU_SPIRV_ID_RESULT, 0 } },
	{ "OpTypeBool",                                20,  2,  0,                       { MU_SPIRV_ID_RESULT, 0 } },
	{ "OpTypeInt",                                 21,  4,  0,                       { MU_SPIRV_ID_RESULT, MU_SPIRV_UINT32, MU_SPIRV_SIGN, 0 } },
	{ "OpTypeFloat",                               22,  3,  0,                       { MU_SPIRV_ID_RESULT, MU_SPIRV_UINT32, 0 } },
	{ "OpTypeVector",                              23,  4,  0,                       { MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_UINT32, 0 } },
	{ "OpTypeMatrix",                              24,  4,  0,                       { MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_UINT32, 0 } },
	{ "OpTypeImage",                               25,  9,  0,                       { MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_DIM, MU_SPIRV_UINT32, MU_SPIRV_UINT32, MU_SPIRV_UINT32, MU_SPIRV_UINT32, MU_SPIRV_IMAGE_FORMAT, MU_SPIRV_ACCESS_QUALIFIER, 0 } },
	{ "OpTypeSampler",                             26,  2,  0,                       { MU_SPIRV_ID_RESULT, 0 } },
	{ "OpTypeSampledImage",                        27,  3,  0,                       { MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpTypeArray",                               28,  4,  0,                       { MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpTypeRuntimeArray",                        29,  3,  0,                       { MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpTypeStruct",                              30,  2,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT, 0 } },
	{ "OpTypeOpaque",                              31,  3,  0,                       { MU_SPIRV_ID_RESULT, MU_SPIRV_ID_STRING, 0 } },
	{ "OpTypePointer",                             32,  4,  0,                       { MU_SPIRV_ID_RESULT, MU_SPIRV_STORAGE_CLASS, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpTypeFunction",                            33,  3,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpTypeEvent",                               34,  2,  0,                       { MU_SPIRV_ID_RESULT, 0 } },
	{ "OpTypeDeviceEvent",                         35,  2,  0,                       { MU_SPIRV_ID_RESULT, 0 } },
	{ "OpTypeReserveId",                           36,  2,  0,                       { MU_SPIRV_ID_RESULT, 0 } },
	{ "OpTypeQueue",                               37,  2,  0,                       { MU_SPIRV_ID_RESULT, 0 } },
	{ "OpTypePipe",                                38,  3,  0,                       { MU_SPIRV_ID_RESULT, MU_SPIRV_ACCESS_QUALIFIER, 0 } },
	{ "OpTypeForwardPointer",                      39,  3,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_STORAGE_CLASS, 0 } },
	// No 40
	{ "OpConstantTrue",                            41,  3,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, 0 } },
	{ "OpConstantFalse",                           42,  3,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, 0 } },
	{ "OpConstant",                                43,  4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_LITERAL_VALUE, 0 } },
	{ "OpConstantComposite",                       44,  3,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, 0 } },
	{ "OpConstantSampler",                         45,  6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_SAMPLER_ADDRESSING_MODE, MU_SPIRV_UINT32, MU_SPIRV_SAMPLER_FILTER_MODE, 0 } },
	{ "OpConstantNull",                            46,  3,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, 0 } },
	// No 47
	{ "OpSpecConstantTrue",                        48,  3,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, 0 } },
	{ "OpSpecConstantFalse",                       49,  3,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, 0 } },
	{ "OpSpecConstant",                            50,  4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_LITERAL_VALUE, 0 } },
	{ "OpSpecConstantComposite",                   51,  3,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, 0 } },
	{ "OpSpecConstantOp",                          52,  4,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_OPCODE, 0 } },
	// No 53
	{ "OpFunction",                                54,  5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_FUNCTION_CONTROL, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFunctionParameter",                       55,  3,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, 0 } },
	{ "OpFunctionEnd",                             56,  1,  0,                       { 0 } },
	{ "OpFunctionCall",                            57,  4,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	// No 58
	{ "OpVariable",                                59,  4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_STORAGE_CLASS, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpImageTexelPointer",                       60,  6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpLoad",                                    61,  4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_MEMORY_OPERANDS, 0 } },
	{ "OpStore",                                   62,  3,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_MEMORY_OPERANDS, 0 } },
	{ "OpCopyMemory",                              63,  3,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_MEMORY_OPERANDS, MU_SPIRV_MEMORY_OPERANDS, 0 } },
	{ "OpCopyMemorySized",                         64,  4,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_MEMORY_OPERANDS, MU_SPIRV_MEMORY_OPERANDS, 0 } },
	{ "OpAccessChain",                             65,  4,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpInBoundsAccessChain",                     66,  4,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpPtrAccessChain",                          67,  5,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpArrayLength",                             68,  5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_UINT32, 0 } },
	{ "OpGenericPtrMemSemantics",                  69,  4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpInBoundsPtrAccessChain",                  70,  5,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpDecorate",                                71,  3,  MU_SPIRV_DECORATION,     { MU_SPIRV_ID_TARGET, 0 } },
	{ "OpMemberDecorate",                          72,  4,  MU_SPIRV_DECORATION,     { MU_SPIRV_ID_TARGET, MU_SPIRV_UINT32, 0 } },
	{ "OpDecorationGroup",                         73,  2,  0,                       { MU_SPIRV_ID_RESULT, 0 } },
	{ "OpGroupDecorate",                           74,  2,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupMemberDecorate",                     75,  2,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_TARGET, 0 } },
	// No 76
	{ "OpVectorExtractDynamic",                    77,  5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpVectorInsertDynamic",                     78,  6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpVectorShuffle",                           79,  5,  MU_SPIRV_UINT32,         { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpCompositeConstruct",                      80,  3,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, 0 } },
	{ "OpCompositeExtract",                        81,  4,  MU_SPIRV_UINT32,         { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpCompositeInsert",                         82,  5,  MU_SPIRV_UINT32,         { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpCopyObject",                              83,  4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpTranspose",                               84,  4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	// No 85
	{ "OpSampledImage",                            86,  5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpImageSampleImplicitLod",                  87,  5,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageSampleExplicitLod",                  88,  7,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageSampleDrefImplicitLod",              89,  6,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageSampleDrefExplicitLod",              90,  8,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageSampleProjImplicitLod",              91,  5,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageSampleProjExplicitLod",              92,  7,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageSampleProjDrefImplicitLod",          93,  6,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageSampleProjDrefExplicitLod",          94,  8,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageFetch",                              95,  5,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageGather",                             96,  6,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageDrefGather",                         97,  6,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageRead",                               98,  5,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageWrite",                              99,  4,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImage",                                   100, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpImageQueryFormat",                        101, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpImageQueryOrder",                         102, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpImageQuerySizeLod",                       103, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpImageQuerySize",                          104, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpImageQueryLod",                           105, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpImageQueryLevels",                        106, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpImageQuerySamples",                       107, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	// No 108
	{ "OpConvertFToU",                             109, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpConvertFToS",                             110, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpConvertSToF",                             111, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpConvertUToF",                             112, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpUConvert",                                113, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpSConvert",                                114, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFConvert",                                115, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpQuantizeToF16",                           116, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpConvertPtrToU",                           117, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpSatConvertSToU",                          118, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpSatConvertUToS",                          119, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpConvertUToPtr",                           120, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpPtrCastToGeneric",                        121, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGenericCastToPtr",                        122, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGenericCastToPtrExplicit",                123, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_STORAGE_CLASS, 0 } },
	{ "OpBitcast",                                 124, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	// No 125
	{ "OpSNegate",                                 126, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFNegate",                                 127, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpIAdd",                                    128, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFAdd",                                    129, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpISub",                                    130, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFSub",                                    131, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpIMul",                                    132, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFMul",                                    133, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpUDiv",                                    134, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpSDiv",                                    135, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFDiv",                                    136, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpUMod",                                    137, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpSRem",                                    138, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpSMod",                                    139, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFRem",                                    140, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFMod",                                    141, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpVectorTimesScalar",                       142, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpMatrixTimesScalar",                       143, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpVectorTimesMatrix",                       144, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpMatrixTimesVector",                       145, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpMatrixTimesMatrix",                       146, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpOuterProduct",                            147, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpDot",                                     148, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpIAddCarry",                               149, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpISubBorrow",                              150, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpUMulExtended",                            151, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpSMulExtended",                            152, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	// No 153
	{ "OpAny",                                     154, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAll",                                     155, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpIsNan",                                   156, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpIsInf",                                   157, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpIsFinite",                                158, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpIsNormal",                                159, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpSignBitSet",                              160, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpLessOrGreater",                           161, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpOrdered",                                 162, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpUnordered",                               163, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpLogicalEqual",                            164, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpLogicalNotEqual",                         165, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpLogicalOr",                               166, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpLogicalAnd",                              167, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpLogicalNot",                              168, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpSelect",                                  169, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpIEqual",                                  170, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpINotEqual",                               171, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpUGreaterThan",                            172, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpSGreaterThan",                            173, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpUGreaterThanEqual",                       174, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpSGreaterThanEqual",                       175, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpULessThan",                               176, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpSLessThan",                               177, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpULessThanEqual",                          178, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpSLessThanEqual",                          179, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFOrdEqual",                               180, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFUnordEqual",                             181, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFOrdNotEqual",                            182, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFUnordNotEqual",                          183, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFOrdLessThan",                            184, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFUnordLessThan",                          185, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFOrdGreaterThan",                         186, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFUnordGreaterThan",                       187, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFOrdLessThanEqual",                       188, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFUnordLessThanEqual",                     189, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFOrdGreaterThanEqual",                    190, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFUnordGreaterThanEqual",                  191, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	// No 192
	// No 193
	{ "OpShiftRightLogical",                       194, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpShiftRightArithmetic",                    195, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpShiftLeftLogical",                        196, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpBitwiseOr",                               197, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpBitwiseXor",                              198, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpBitwiseAnd",                              199, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpNot",                                     200, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpBitFieldInsert",                          201, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpBitFieldSExtract",                        202, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpBitFieldUExtract",                        203, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpBitReverse",                              204, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpBitCount",                                205, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	// No 206
	{ "OpDPdx",                                    207, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpDPdy",                                    208, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFwidth",                                  209, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpDPdxFine",                                210, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpDPdyFine",                                211, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFwidthFine",                              212, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpDPdxCoarse",                              213, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpDPdyCoarse",                              214, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpFwidthCoarse",                            215, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	// No 216
	// No 217
	{ "OpEmitVertex",                              218, 1,  0,                       { 0 } },
	{ "OpEndPrimitive",                            219, 1,  0,                       { 0 } },
	{ "OpEmitStreamVertex",                        220, 2,  0,                       { MU_SPIRV_ID_TARGET, 0 } },
	{ "OpEndStreamPrimitive",                      221, 2,  0,                       { MU_SPIRV_ID_TARGET, 0 } },
	// No 222
	// No 223
	{ "OpControlBarrier",                          224, 4,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpMemoryBarrier",                           225, 3,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	// No 226
	{ "OpAtomicLoad",                              227, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAtomicStore",                             228, 5,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAtomicExchange",                          229, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAtomicCompareExchange",                   230, 9,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAtomicCompareExchangeWeak",               231, 9,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAtomicIIncrement",                        232, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAtomicIDecrement",                        233, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAtomicIAdd",                              234, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAtomicISub",                              235, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAtomicSMin",                              236, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAtomicUMin",                              237, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAtomicSMax",                              238, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAtomicUMax",                              239, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAtomicAnd",                               240, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAtomicOr",                                241, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAtomicXor",                               242, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	// No 243
	// No 244
	{ "OpPhi",                                     245, 3,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, 0 } },
	{ "OpLoopMerge",                               246, 4,  MU_SPIRV_LOOP_CONTROL,   { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_LOOP_CONTROL, 0 } },
	{ "OpSelectionMerge",                          247, 3,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_SELECTION_CONTROL, 0 } },
	{ "OpLabel",                                   248, 2,  0,                       { MU_SPIRV_ID_RESULT, 0 } },
	{ "OpBranch",                                  249, 2,  0,                       { MU_SPIRV_ID_TARGET, 0 } },
	{ "OpBranchConditional",                       250, 4,  MU_SPIRV_UINT32,         { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpSwitch",                                  251, 3,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpKill",                                    252, 1,  0,                       { 0 } },
	{ "OpReturn",                                  253, 1,  0,                       { 0 } },
	{ "OpReturnValue",                             254, 2,  0,                       { MU_SPIRV_ID_TARGET, 0 } },
	{ "OpUnreachable",                             255, 1,  0,                       { 0 } },
	{ "OpLifetimeStart",                           256, 3,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_UINT32, 0 } },
	{ "OpLifetimeStop",                            257, 3,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_UINT32, 0 } },
	// No 258
	{ "OpGroupAsyncCopy",                          259, 9,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupWaitEvents",                         260, 4,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupAll",                                261, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupAny",                                262, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupBroadcast",                          263, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupIAdd",                               264, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupFAdd",                               265, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupFMin",                               266, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupUMin",                               267, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupSMin",                               268, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupFMax",                               269, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupUMax",                               270, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupSMax",                               271, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, 0 } },
	// No 272
	// No 273
	{ "OpReadPipe",                                274, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpWritePipe",                               275, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpReservedReadPipe",                        276, 9,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpReservedWritePipe",                       277, 9,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpReserveReadPipePackets",                  278, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpReserveWritePipePackets",                 279, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpCommitReadPipe",                          280, 5,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpCommitWritePipe",                         281, 5,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpIsValidReserveId",                        282, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGetNumPipePackets",                       283, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGetMaxPipePackets",                       284, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupReserveReadPipePackets",             285, 8,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupReserveWritePipePackets",            286, 8,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupCommitReadPipe",                     287, 6,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupCommitWritePipe",                    288, 6,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	// No 289
	// No 290
	{ "OpEnqueueMarker",                           291, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpEnqueueKernel",                           292, 13, MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGetKernelNDrangeSubGroupCount",           293, 8,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGetKernelNDrangeMaxSubGroupSize",         294, 8,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGetKernelWorkGroupSize",                  295, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGetKernelPreferredWorkGroupSizeMultiple", 296, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpRetainEvent",                             297, 2,  0,                       { MU_SPIRV_ID_TARGET, 0 } },
	{ "OpReleaseEvent",                            298, 2,  0,                       { MU_SPIRV_ID_TARGET, 0 } },
	{ "OpCreateUserEvent",                         299, 3,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, 0 } },
	{ "OpIsValidEvent",                            300, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpSetUserEventStatus",                      301, 3,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpCaptureEventProfilingInfo",               302, 4,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGetDefaultQueue",                         303, 3,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, 0 } },
	{ "OpBuildNDRange",                            304, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpImageSparseSampleImplicitLod",            305, 5,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageSparseSampleExplicitLod",            306, 7,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpImageSparseSampleDrefImplicitLod",        307, 6,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageSparseSampleDrefExplicitLod",        308, 8,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpImageSparseSampleProjImplicitLod",        309, 5,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageSparseSampleProjExplicitLod",        310, 7,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpImageSparseSampleProjDrefImplicitLod",    311, 6,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageSparseSampleProjDrefExplicitLod",    312, 8,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpImageSparseFetch",                        313, 5,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageSparseGather",                       314, 6,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageSparseDrefGather",                   315, 6,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpImageSparseTexelsResident",               316, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpNoLine",                                  317, 1,  0,                       { 0 } },
	{ "OpAtomicFlagTestAndSet",                    318, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpAtomicFlagClear",                         319, 4,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpImageSparseRead",                         320, 5,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_IMAGE_OPERANDS, 0 } },
	{ "OpSizeOf",                                  321, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpTypePipeStorage",                         322, 2,  0,                       { MU_SPIRV_ID_RESULT, 0 } },
	{ "OpConstantPipeStorage",                     323, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_UINT32, MU_SPIRV_UINT32, MU_SPIRV_UINT32, 0 } },
	{ "OpCreatePipeFromPipeStorage",               324, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGetKernelLocalSizeForSubgroupCount",      325, 8,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGetKernelMaxNumSubgroups",                326, 7,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpTypeNamedBarrier",                        327, 2,  0,                       { MU_SPIRV_ID_RESULT, 0 } },
	{ "OpNamedBarrierInitialize",                  328, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpMemoryNamedBarrier",                      329, 4,  0,                       { MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpModuleProcessed",                         330, 2,  0,                       { MU_SPIRV_STRING, 0 } },
	{ "OpExecutionModeId",                         331, 3,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_TARGET, MU_SPIRV_EXECUTION_MODE, 0 } },
	{ "OpDecorateId",                              332, 3,  MU_SPIRV_ID_TARGET,      { MU_SPIRV_ID_TARGET, MU_SPIRV_DECORATION, 0 } },
	{ "OpGroupNonUniformElect",                    333, 4,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformAll",                      334, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformAny",                      335, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformAllEqual",                 336, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformBroadcast",                337, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformBroadcastFirst",           338, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformBallot",                   339, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformInverseBallot",            340, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformBallotBitExtract",         341, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformBallotBitCount",           342, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformBallotFindLSB",            343, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformBallotFindMSB",            344, 5,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformShuffle",                  345, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformShuffleXor",               346, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformShuffleUp",                347, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformShuffleDown",              348, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformIAdd",                     349, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformFAdd",                     350, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformIMul",                     351, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformFMul",                     352, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformSMin",                     353, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformUMin",                     354, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformFMin",                     355, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformSMax",                     356, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformUMax",                     357, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformFMax",                     358, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformBitwiseAnd",               359, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformBitwiseOr",                360, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformBitwiseXor",               361, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformLogicalAnd",               362, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformLogicalOr",                363, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformLogicalXor",               364, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_GROUP_OPERATION, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformQuadBroadcast",            365, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	{ "OpGroupNonUniformQuadSwap",                 366, 6,  0,                       { MU_SPIRV_ID_RESULT_TYPE, MU_SPIRV_ID_RESULT, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, MU_SPIRV_ID_TARGET, 0 } },
	// No 367 -> 399

	0
};

/* useful functions */

// @TODO improve the speed of this function
size_m muSAVE_get_instruction_index(uint16_m opcode) {
	for (size_m i = 0; i < MU_SPIRV_INSTRUCTION_COUNT; i++) {
		if (mu_global_SPIRV_instructions[i].opcode == opcode) {
			return i;
		}
	}
	return MU_SIZE_MAX;
}

uint32_m muSAVE_get_word(const char* b) {
	const unsigned char* ub = (const unsigned char*)b;
	return ub[0] + (ub[1] << 8) + (ub[2] << 16) + (ub[3] << 24);
}
uint32_m muSAVE_get_word_be(const char* b) {
	const unsigned char* ub = (const unsigned char*)b;
	return (ub[0] << 24) + (ub[1] << 16) + (ub[2] << 8) + ub[3];
}
uint16_m muSAVE_get_halfword(const char* b) {
	const unsigned char* ub = (const unsigned char*)b;
	return ub[0] + (ub[1] << 8);
}

muString muSAVE_insert_type_info(muString str, const char* binary, size_m len, uint32_m id, unsigned char* data, size_m datalen) {
	for (size_m i = 20; i < len;) {
		uint16_m instruction = muSAVE_get_halfword(&binary[i]);
		uint16_m step = muSAVE_get_halfword(&binary[i+2]);
		size_m j = muSAVE_get_instruction_index(instruction);
		if (j != MU_SIZE_MAX) {
			/*MU_SPIRV_BASSERT(
				(mu_global_SPIRV_instructions[j].indefinite_type == 0 && step == mu_global_SPIRV_instructions[j].min_word_count) || 
				(mu_global_SPIRV_instructions[j].indefinite_type != 0)
			)*/
			switch (mu_global_SPIRV_instructions[j].opcode) {
				default: { } break;
				// bool
				case 20: {
					if (muSAVE_get_word(&binary[i+4]) == id) {
						for (size_m k = 0; k < datalen; k++) {
							if (data[k] != 0) {
								str = mu_string_insert(str, "True", mu_string_strlen(str));
								return str;
							}
						}
						str = mu_string_insert(str, "False", mu_string_strlen(str));
						return str;
					}
				} break;
				// int (this code is pretty messy but it gets the job done)
				case 21: {
					switch (datalen) {
						default: {
							if (muSAVE_get_word(&binary[i+4]) == id) {
								str = mu_string_insert(str, "UnknownValue", mu_string_strlen(str));
								return str;
							}
						} break;
						case 1: {
							if (muSAVE_get_word(&binary[i+4]) == id) {
								if (muSAVE_get_word(&binary[i+12]) == 0) {
									str = mu_string_insert_integer(str, *(uint8_m*)data, mu_string_strlen(str));
								} else if (muSAVE_get_word(&binary[i+12]) == 1) {
									str = mu_string_insert_integer(str, *(int8_m*)data, mu_string_strlen(str));
								} else {
									str = mu_string_insert(str, "UnknownValue", mu_string_strlen(str));
								}
								return str;
							}
						} break;
						case 2: {
							if (muSAVE_get_word(&binary[i+4]) == id) {
								if (muSAVE_get_word(&binary[i+12]) == 0) {
									str = mu_string_insert_integer(str, *(uint16_m*)data, mu_string_strlen(str));
								} else if (muSAVE_get_word(&binary[i+12]) == 1) {
									str = mu_string_insert_integer(str, *(int16_m*)data, mu_string_strlen(str));
								} else {
									str = mu_string_insert(str, "UnknownValue", mu_string_strlen(str));
								}
								return str;
							}
						} break;
						case 4: {
							if (muSAVE_get_word(&binary[i+4]) == id) {
								if (muSAVE_get_word(&binary[i+12]) == 0) {
									str = mu_string_insert_integer(str, *(uint32_m*)data, mu_string_strlen(str));
								} else if (muSAVE_get_word(&binary[i+12]) == 1) {
									str = mu_string_insert_integer(str, *(int32_m*)data, mu_string_strlen(str));
								} else {
									str = mu_string_insert(str, "UnknownValue", mu_string_strlen(str));
								}
								return str;
							}
						} break;
						case 8: {
							if (muSAVE_get_word(&binary[i+4]) == id) {
								if (muSAVE_get_word(&binary[i+12]) == 0) {
									str = mu_string_insert_integer(str, *(uint64_m*)data, mu_string_strlen(str));
								} else if (muSAVE_get_word(&binary[i+12]) == 1) {
									str = mu_string_insert_integer(str, *(int64_m*)data, mu_string_strlen(str));
								} else {
									str = mu_string_insert(str, "UnknownValue", mu_string_strlen(str));
								}
								return str;
							}
						} break;
					}
				} break;
				case 22: {
					if (muSAVE_get_word(&binary[i+4]) == id) {
 						if (muSAVE_get_word(&binary[i+8]) == 32) {
							float fdata = 0.f;
							if (datalen <= 4) {
								mu_memcpy(&fdata, data, datalen);
							}
							str = mu_string_insert_float(str, fdata, 4, mu_string_strlen(str));
						} else if (datalen == 8) {
							double ddata = 0.f;
							if (datalen <= 8) {
								mu_memcpy(&ddata, data, datalen);
							}
							str = mu_string_insert_float(str, ddata, 8, mu_string_strlen(str));
						} else {
							str = mu_string_insert(str, "UnknownValue", mu_string_strlen(str));
						}
						return str;
					}
				} break;
			}
		}

		// step forward
		i += step * 4;
	}

	str = mu_string_insert(str, "UnknownValue", mu_string_strlen(str));
	return str;
}

muString muSAVE_insert_instruction_by_type(muString str, muSPIRVType type, const char* binary, size_m binarylen, size_m i, size_m* k, size_m step, uint32_m* latest_result_target, size_m* beg_str_i);

/* enum name functions */

	muString muSAVE_insert_SourceLanguage(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownSourceLanguage", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "ESSL", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "GLSL", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "OpenGL_C", mu_string_strlen(str)); break;
			case 4: return mu_string_insert(str, "OpenGL_CPP", mu_string_strlen(str)); break;
			case 5: return mu_string_insert(str, "HLSL", mu_string_strlen(str)); break;
			case 6: return mu_string_insert(str, "CPP_for_OpenCL", mu_string_strlen(str)); break;
			case 7: return mu_string_insert(str, "SYCL", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_ExecutionModel(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownExecutionModel", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "Vertex", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "TessellationControl", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "TessellationEvaluation", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "Geometry", mu_string_strlen(str)); break;
			case 4: return mu_string_insert(str, "Fragment", mu_string_strlen(str)); break;
			case 5: return mu_string_insert(str, "GLCompute", mu_string_strlen(str)); break;
			case 6: return mu_string_insert(str, "Kernel", mu_string_strlen(str)); break;
			case 5267: return mu_string_insert(str, "Task", mu_string_strlen(str)); break;
			case 5268: return mu_string_insert(str, "Mesh", mu_string_strlen(str)); break;
			case 5313: return mu_string_insert(str, "RayGeneration", mu_string_strlen(str)); break;
			case 5314: return mu_string_insert(str, "Intersection", mu_string_strlen(str)); break;
			case 5315: return mu_string_insert(str, "AnyHit", mu_string_strlen(str)); break;
			case 5316: return mu_string_insert(str, "ClosestHit", mu_string_strlen(str)); break;
			case 5317: return mu_string_insert(str, "Miss", mu_string_strlen(str)); break;
			case 5318: return mu_string_insert(str, "Callable", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_AddressingModel(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownAddressingModel", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "Logical", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "Physical32", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "Physical64", mu_string_strlen(str)); break;
			case 5348: return mu_string_insert(str, "PhysicalStorageBuffer64", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_MemoryModel(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownMemoryModel", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "Simple", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "GLSL450", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "OpenCL", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "Vulkan", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_ExecutionMode(muString str, muSPIRVType type, const char* binary, size_m binarylen, size_m i, size_m* k, size_m step, uint32_m* latest_result_target, size_m* beg_str_i) {
		switch (muSAVE_get_word(&binary[i+4+((*k*4))])) {
			default: return mu_string_insert(str, "UnknownExecutionMode", mu_string_strlen(str)); break;
			case 0: {
				str = mu_string_insert(str, "Invocations ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 1: return mu_string_insert(str, "SpacingEqual", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "SpacingFractionalEven", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "SpacingFractionalOdd", mu_string_strlen(str)); break;
			case 4: return mu_string_insert(str, "VertexOrderCw", mu_string_strlen(str)); break;
			case 5: return mu_string_insert(str, "VertexOrderCcw", mu_string_strlen(str)); break;
			case 6: return mu_string_insert(str, "PixelCenterInteger", mu_string_strlen(str)); break;
			case 7: return mu_string_insert(str, "OriginUpperLeft", mu_string_strlen(str)); break;
			case 8: return mu_string_insert(str, "OriginLowerLeft", mu_string_strlen(str)); break;
			case 9: return mu_string_insert(str, "EarlyFragmentTests", mu_string_strlen(str)); break;
			case 10: return mu_string_insert(str, "PointMode", mu_string_strlen(str)); break;
			case 11: return mu_string_insert(str, "Xfb", mu_string_strlen(str)); break;
			case 12: return mu_string_insert(str, "DepthReplacing", mu_string_strlen(str)); break;
			case 14: return mu_string_insert(str, "DepthGreater", mu_string_strlen(str)); break;
			case 15: return mu_string_insert(str, "DepthLess", mu_string_strlen(str)); break;
			case 16: return mu_string_insert(str, "DepthUnchanged", mu_string_strlen(str)); break;
			case 17: {
				str = mu_string_insert(str, "LocalSize ", mu_string_strlen(str));
				*k += 1;
				str = muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
				str = mu_string_insert(str, " ", mu_string_strlen(str));
				*k += 1;
				str = muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
				str = mu_string_insert(str, " ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 18: {
				str = mu_string_insert(str, "LocalSizeHint ", mu_string_strlen(str));
				*k += 1;
				str = muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
				str = mu_string_insert(str, " ", mu_string_strlen(str));
				*k += 1;
				str = muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
				str = mu_string_insert(str, " ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 19: return mu_string_insert(str, "InputPoints", mu_string_strlen(str)); break;
			case 20: return mu_string_insert(str, "InputLines", mu_string_strlen(str)); break;
			case 21: return mu_string_insert(str, "InputLinesAdjacency", mu_string_strlen(str)); break;
			case 22: return mu_string_insert(str, "Triangles", mu_string_strlen(str)); break;
			case 23: return mu_string_insert(str, "InputTrianglesAdjacency", mu_string_strlen(str)); break;
			case 24: return mu_string_insert(str, "Quads", mu_string_strlen(str)); break;
			case 25: return mu_string_insert(str, "Isolines", mu_string_strlen(str)); break;
			case 26: {
				str = mu_string_insert(str, "OutputVertices ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 27: return mu_string_insert(str, "OutputPoints", mu_string_strlen(str)); break;
			case 28: return mu_string_insert(str, "OutputLineStrip", mu_string_strlen(str)); break;
			case 29: return mu_string_insert(str, "OutputTriangleStrip", mu_string_strlen(str)); break;
			// @TODO figure this out
			case 30: return mu_string_insert(str, "VecTypeHint", mu_string_strlen(str)); break;
			case 31: return mu_string_insert(str, "ContractionOff", mu_string_strlen(str)); break;
			case 33: return mu_string_insert(str, "Initializer", mu_string_strlen(str)); break;
			case 34: return mu_string_insert(str, "Finalizer", mu_string_strlen(str)); break;
			case 35: {
				str = mu_string_insert(str, "SubgroupSize ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 36: {
				str = mu_string_insert(str, "SubgroupsPerWorkgroup ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 37: {
				str = mu_string_insert(str, "SubgroupsPerWorkgroupId ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_ID_TARGET, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 38: {
				str = mu_string_insert(str, "LocalSizeId ", mu_string_strlen(str));
				*k += 1;
				str = muSAVE_insert_instruction_by_type(str, MU_SPIRV_ID_TARGET, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
				str = mu_string_insert(str, " ", mu_string_strlen(str));
				*k += 1;
				str = muSAVE_insert_instruction_by_type(str, MU_SPIRV_ID_TARGET, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
				str = mu_string_insert(str, " ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_ID_TARGET, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 39: {
				str = mu_string_insert(str, "LocalSizeHintId ", mu_string_strlen(str));
				*k += 1;
				str = muSAVE_insert_instruction_by_type(str, MU_SPIRV_ID_TARGET, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
				str = mu_string_insert(str, " ", mu_string_strlen(str));
				*k += 1;
				str = muSAVE_insert_instruction_by_type(str, MU_SPIRV_ID_TARGET, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
				str = mu_string_insert(str, " ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_ID_TARGET, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 4421: return mu_string_insert(str, "SubgroupUniformControlFlow", mu_string_strlen(str)); break;
			case 4446: return mu_string_insert(str, "PostDepthCoverage", mu_string_strlen(str)); break;
			case 4459: {
				str = mu_string_insert(str, "DenormPreserve ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 4460: {
				str = mu_string_insert(str, "DenormFlushToZero ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 4461: {
				str = mu_string_insert(str, "SignedZeroInfNanPreserve ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 4462: {
				str = mu_string_insert(str, "RoundingModeRTE ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 4463: {
				str = mu_string_insert(str, "RoundingModeRTZ ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5017: return mu_string_insert(str, "EarlyAndLateFragmentTests", mu_string_strlen(str)); break;
			case 5027: return mu_string_insert(str, "StencilRefReplacing", mu_string_strlen(str)); break;
			case 5079: return mu_string_insert(str, "StencilRefUnchangedFront", mu_string_strlen(str)); break;
			case 5080: return mu_string_insert(str, "StencilRefGreaterFront", mu_string_strlen(str)); break;
			case 5081: return mu_string_insert(str, "StencilRefLessFront", mu_string_strlen(str)); break;
			case 5082: return mu_string_insert(str, "StencilRefUnchangedBack", mu_string_strlen(str)); break;
			case 5083: return mu_string_insert(str, "StencilRefGreaterBack", mu_string_strlen(str)); break;
			case 5084: return mu_string_insert(str, "StencilRefLessBack", mu_string_strlen(str)); break;
			case 5269: return mu_string_insert(str, "OutputLines", mu_string_strlen(str)); break;
			case 5270: {
				str = mu_string_insert(str, "OutputPrimitives ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5289: return mu_string_insert(str, "DerivativeGroupQuads", mu_string_strlen(str)); break;
			case 5290: return mu_string_insert(str, "DerivativeGroupLinear", mu_string_strlen(str)); break;
			case 5298: return mu_string_insert(str, "OutputTriangles", mu_string_strlen(str)); break;
			case 5366: return mu_string_insert(str, "PixelInterlockOrdered", mu_string_strlen(str)); break;
			case 5367: return mu_string_insert(str, "PixelInterlockUnordered", mu_string_strlen(str)); break;
			case 5368: return mu_string_insert(str, "SampleInterlockOrdered", mu_string_strlen(str)); break;
			case 5369: return mu_string_insert(str, "SampleInterlockUnordered", mu_string_strlen(str)); break;
			case 5370: return mu_string_insert(str, "ShadingRateInterlockOrdered", mu_string_strlen(str)); break;
			case 5371: return mu_string_insert(str, "ShadingRateInterlockUnordered", mu_string_strlen(str)); break;
			case 5618: {
				str = mu_string_insert(str, "SharedLocalMemorySize ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5620: {
				str = mu_string_insert(str, "RoundingModeRTP ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5621: {
				str = mu_string_insert(str, "RoundingModeRTN ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5622: {
				str = mu_string_insert(str, "FloatingPointModeALT ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5623: {
				str = mu_string_insert(str, "FloatingPointModeIEEE ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5893: {
				str = mu_string_insert(str, "MaxWorkgroupSize ", mu_string_strlen(str));
				*k += 1;
				str = muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
				str = mu_string_insert(str, " ", mu_string_strlen(str));
				*k += 1;
				muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
				str = mu_string_insert(str, " ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5894: {
				str = mu_string_insert(str, "MaxWorkDim ", mu_string_strlen(str));
				*k += 1;
				// Might be some weird half of bits width and other half height, doesn't really matter
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5895: return mu_string_insert(str, "NoGlobalOffset", mu_string_strlen(str)); break;
			case 5896: {
				str = mu_string_insert(str, "NumSIMDWorkitems ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5903: {
				str = mu_string_insert(str, "SchedulerTargetFmaxMhz ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 6417: {
				str = mu_string_insert(str, "NamedBarrierCount ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
		}
	}

	muString muSAVE_insert_StorageClass(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownStorageClass", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "UniformConstant", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "Input", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "Uniform", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "Output", mu_string_strlen(str)); break;
			case 4: return mu_string_insert(str, "Workgroup", mu_string_strlen(str)); break;
			case 5: return mu_string_insert(str, "CrossWorkgroup", mu_string_strlen(str)); break;
			case 6: return mu_string_insert(str, "Private", mu_string_strlen(str)); break;
			case 7: return mu_string_insert(str, "Function", mu_string_strlen(str)); break;
			case 8: return mu_string_insert(str, "Generic", mu_string_strlen(str)); break;
			case 9: return mu_string_insert(str, "PushConstant", mu_string_strlen(str)); break;
			case 10: return mu_string_insert(str, "AtomicCounter", mu_string_strlen(str)); break;
			case 11: return mu_string_insert(str, "Image", mu_string_strlen(str)); break;
			case 12: return mu_string_insert(str, "StorageBuffer", mu_string_strlen(str)); break;
			case 5328: return mu_string_insert(str, "CallableData", mu_string_strlen(str)); break;
			case 5329: return mu_string_insert(str, "IncomingCallableData", mu_string_strlen(str)); break;
			case 5338: return mu_string_insert(str, "RayPayload", mu_string_strlen(str)); break;
			case 5339: return mu_string_insert(str, "HitAttribute", mu_string_strlen(str)); break;
			case 5342: return mu_string_insert(str, "IncomingRayPayload", mu_string_strlen(str)); break;
			case 5343: return mu_string_insert(str, "ShaderRecordBuffer", mu_string_strlen(str)); break;
			case 5349: return mu_string_insert(str, "PhysicalStorageBuffer", mu_string_strlen(str)); break;
			case 5605: return mu_string_insert(str, "CodeSection", mu_string_strlen(str)); break;
			case 5936: return mu_string_insert(str, "DeviceOnly", mu_string_strlen(str)); break;
			case 5937: return mu_string_insert(str, "HostOnly", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_Dim(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownDim", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "1D", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "2D", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "3D", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "Cube", mu_string_strlen(str)); break;
			case 4: return mu_string_insert(str, "Rect", mu_string_strlen(str)); break;
			case 5: return mu_string_insert(str, "Buffer", mu_string_strlen(str)); break;
			case 6: return mu_string_insert(str, "SubpassData", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_SamplerAddressingMode(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownSamplerAddressingMode", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "None", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "ClampToEdge", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "Clamp", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "Repeat", mu_string_strlen(str)); break;
			case 4: return mu_string_insert(str, "RepeatMirrored", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_SamplerFilterMode(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownSamplerFilterMode", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "Nearest", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "Linear", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_ImageFormat(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownImageFormat", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "Unknown", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "Rgba32f", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "Rgba16f", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "R32f", mu_string_strlen(str)); break;
			case 4: return mu_string_insert(str, "Rgba8", mu_string_strlen(str)); break;
			case 5: return mu_string_insert(str, "Rgba8Snorm", mu_string_strlen(str)); break;
			case 6: return mu_string_insert(str, "Rg32f", mu_string_strlen(str)); break;
			case 7: return mu_string_insert(str, "Rg16f", mu_string_strlen(str)); break;
			case 8: return mu_string_insert(str, "R11fG11fB10f", mu_string_strlen(str)); break;
			case 9: return mu_string_insert(str, "R16f", mu_string_strlen(str)); break;
			case 10: return mu_string_insert(str, "Rgba16", mu_string_strlen(str)); break;
			case 11: return mu_string_insert(str, "Rgb10A2", mu_string_strlen(str)); break;
			case 12: return mu_string_insert(str, "Rg16", mu_string_strlen(str)); break;
			case 13: return mu_string_insert(str, "Rg8", mu_string_strlen(str)); break;
			case 14: return mu_string_insert(str, "R16", mu_string_strlen(str)); break;
			case 15: return mu_string_insert(str, "R8", mu_string_strlen(str)); break;
			case 16: return mu_string_insert(str, "Rgba16Snorm", mu_string_strlen(str)); break;
			case 17: return mu_string_insert(str, "Rg16Snorm", mu_string_strlen(str)); break;
			case 18: return mu_string_insert(str, "Rg8Snorm", mu_string_strlen(str)); break;
			case 19: return mu_string_insert(str, "R16Snorm", mu_string_strlen(str)); break;
			case 20: return mu_string_insert(str, "R8Snorm", mu_string_strlen(str)); break;
			case 21: return mu_string_insert(str, "Rgba32i", mu_string_strlen(str)); break;
			case 22: return mu_string_insert(str, "Rgba16i", mu_string_strlen(str)); break;
			case 23: return mu_string_insert(str, "Rgba8i", mu_string_strlen(str)); break;
			case 24: return mu_string_insert(str, "R32i", mu_string_strlen(str)); break;
			case 25: return mu_string_insert(str, "Rg32i", mu_string_strlen(str)); break;
			case 26: return mu_string_insert(str, "Rg16i", mu_string_strlen(str)); break;
			case 27: return mu_string_insert(str, "Rg8i", mu_string_strlen(str)); break;
			case 28: return mu_string_insert(str, "R16i", mu_string_strlen(str)); break;
			case 29: return mu_string_insert(str, "R8i", mu_string_strlen(str)); break;
			case 30: return mu_string_insert(str, "Rgba32ui", mu_string_strlen(str)); break;
			case 31: return mu_string_insert(str, "Rgba16ui", mu_string_strlen(str)); break;
			case 32: return mu_string_insert(str, "Rgba8ui", mu_string_strlen(str)); break;
			case 33: return mu_string_insert(str, "R32ui", mu_string_strlen(str)); break;
			case 34: return mu_string_insert(str, "Rgb10a2ui", mu_string_strlen(str)); break;
			case 35: return mu_string_insert(str, "Rg32ui", mu_string_strlen(str)); break;
			case 36: return mu_string_insert(str, "Rg16ui", mu_string_strlen(str)); break;
			case 37: return mu_string_insert(str, "Rg8ui", mu_string_strlen(str)); break;
			case 38: return mu_string_insert(str, "R16ui", mu_string_strlen(str)); break;
			case 39: return mu_string_insert(str, "R8ui", mu_string_strlen(str)); break;
			case 40: return mu_string_insert(str, "R64ui", mu_string_strlen(str)); break;
			case 41: return mu_string_insert(str, "R64i", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_ImageChannelOrder(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownImageChannelOrder", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "R", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "A", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "RG", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "RA", mu_string_strlen(str)); break;
			case 4: return mu_string_insert(str, "RGB", mu_string_strlen(str)); break;
			case 5: return mu_string_insert(str, "RGBA", mu_string_strlen(str)); break;
			case 6: return mu_string_insert(str, "BGRA", mu_string_strlen(str)); break;
			case 7: return mu_string_insert(str, "ARGB", mu_string_strlen(str)); break;
			case 8: return mu_string_insert(str, "Intensity", mu_string_strlen(str)); break;
			case 9: return mu_string_insert(str, "Luminance", mu_string_strlen(str)); break;
			case 10: return mu_string_insert(str, "Rx", mu_string_strlen(str)); break;
			case 11: return mu_string_insert(str, "RGx", mu_string_strlen(str)); break;
			case 12: return mu_string_insert(str, "RGBx", mu_string_strlen(str)); break;
			case 13: return mu_string_insert(str, "Depth", mu_string_strlen(str)); break;
			case 14: return mu_string_insert(str, "DepthStencil", mu_string_strlen(str)); break;
			case 15: return mu_string_insert(str, "sRGB", mu_string_strlen(str)); break;
			case 16: return mu_string_insert(str, "sRGBx", mu_string_strlen(str)); break;
			case 17: return mu_string_insert(str, "sRGBA", mu_string_strlen(str)); break;
			case 18: return mu_string_insert(str, "sBGRA", mu_string_strlen(str)); break;
			case 19: return mu_string_insert(str, "ABGR", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_ImageChannelDataType(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownImageChannelDataType", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "SnormInt8", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "SnormInt16", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "UnormInt8", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "UnormInt16", mu_string_strlen(str)); break;
			case 4: return mu_string_insert(str, "UnormShort565", mu_string_strlen(str)); break;
			case 5: return mu_string_insert(str, "UnormShort555", mu_string_strlen(str)); break;
			case 6: return mu_string_insert(str, "UnormInt101010", mu_string_strlen(str)); break;
			case 7: return mu_string_insert(str, "SignedInt8", mu_string_strlen(str)); break;
			case 8: return mu_string_insert(str, "SignedInt16", mu_string_strlen(str)); break;
			case 9: return mu_string_insert(str, "SignedInt32", mu_string_strlen(str)); break;
			case 10: return mu_string_insert(str, "UnsignedInt8", mu_string_strlen(str)); break;
			case 11: return mu_string_insert(str, "UnsignedInt16", mu_string_strlen(str)); break;
			case 12: return mu_string_insert(str, "UnsignedInt32", mu_string_strlen(str)); break;
			case 13: return mu_string_insert(str, "HalfFloat", mu_string_strlen(str)); break;
			case 14: return mu_string_insert(str, "Float", mu_string_strlen(str)); break;
			case 15: return mu_string_insert(str, "UnormInt24", mu_string_strlen(str)); break;
			case 16: return mu_string_insert(str, "UnormInt101010_2", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_ImageOperands(muString str, uint32_m n) {
		muBool found_any = MU_FALSE;
		if (n & 0x1) {
			str = mu_string_insert(str, "Bias", mu_string_strlen(str));
			found_any = MU_TRUE;
		}
		if (n & 0x2) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "Lod", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|Lod", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x4) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "Grad", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|Grad", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x8) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "ConstOffset", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|ConstOffset", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x10) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "Offset", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|Offset", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x20) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "ConstOffsets", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|ConstOffsets", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x40) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "Sample", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|Sample", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x80) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "MinLod", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|MinLod", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x100) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "MakeTexelAvailable", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|MakeTexelAvailable", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x200) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "MakeTexelVisible", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|MakeTexelVisible", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x400) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "NonPrivateTexel", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|NonPrivateTexel", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x800) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "VolatileTexel", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|VolatileTexel", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x1000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "SignExtend", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|SignExtend", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x2000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "ZeroExtend", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|ZeroExtend", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x4000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "Nontemporal", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|Nontemporal", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x10000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "Offsets", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|Offsets", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}

		if (found_any == MU_FALSE) {
			str = mu_string_insert(str, "None", mu_string_strlen(str));
		}
		return str;
	}

	muString muSAVE_insert_FPFastMathMode(muString str, uint32_m n) {
		muBool found_any = MU_FALSE;
		if (n & 0x1) {
			str = mu_string_insert(str, "NotNaN", mu_string_strlen(str));
			found_any = MU_TRUE;
		}
		if (n & 0x2) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "NotInf", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|NotInf", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x4) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "NSZ", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|NSZ", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x8) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "AllowRecip", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|AllowRecip", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x10) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "Fast", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|Fast", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x10000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "AllowContractFast", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|AllowContractFast", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x20000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "AllowReassoc", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|AllowReassoc", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}

		if (found_any == MU_FALSE) {
			str = mu_string_insert(str, "None", mu_string_strlen(str));
		}
		return str;
	}

	muString muSAVE_insert_FPRoundingMode(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownFPRoundingMode", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "RTE", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "RTZ", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "RTP", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "RTN", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_LinkageType(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownLinkageType", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "Export", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "Import", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "LinkOnceODR", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_AccessQualifier(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownAccessQualifier", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "ReadOnly", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "WriteOnly", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "ReadWrite", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_FunctionParameterAttribute(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownFunctionParameterAttribute", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "Zext", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "Sext", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "ByVal", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "Sret", mu_string_strlen(str)); break;
			case 4: return mu_string_insert(str, "NoAlias", mu_string_strlen(str)); break;
			case 5: return mu_string_insert(str, "NoCapture", mu_string_strlen(str)); break;
			case 6: return mu_string_insert(str, "NoWrite", mu_string_strlen(str)); break;
			case 7: return mu_string_insert(str, "NoReadWrite", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_BuiltIn(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownBuiltIn", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "Position", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "PointSize", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "ClipDistance", mu_string_strlen(str)); break;
			case 4: return mu_string_insert(str, "CullDistance", mu_string_strlen(str)); break;
			case 5: return mu_string_insert(str, "VertexId", mu_string_strlen(str)); break;
			case 6: return mu_string_insert(str, "InstanceId", mu_string_strlen(str)); break;
			case 7: return mu_string_insert(str, "PrimitiveId", mu_string_strlen(str)); break;
			case 8: return mu_string_insert(str, "InvocationId", mu_string_strlen(str)); break;
			case 9: return mu_string_insert(str, "Layer", mu_string_strlen(str)); break;
			case 10: return mu_string_insert(str, "ViewportIndex", mu_string_strlen(str)); break;
			case 11: return mu_string_insert(str, "TessLevelOuter", mu_string_strlen(str)); break;
			case 12: return mu_string_insert(str, "TessLevelInner", mu_string_strlen(str)); break;
			case 13: return mu_string_insert(str, "TessCoord", mu_string_strlen(str)); break;
			case 14: return mu_string_insert(str, "PatchVertices", mu_string_strlen(str)); break;
			case 15: return mu_string_insert(str, "FragCoord", mu_string_strlen(str)); break;
			case 16: return mu_string_insert(str, "PointCoord", mu_string_strlen(str)); break;
			case 17: return mu_string_insert(str, "FrontFacing", mu_string_strlen(str)); break;
			case 18: return mu_string_insert(str, "SampleId", mu_string_strlen(str)); break;
			case 19: return mu_string_insert(str, "SamplePosition", mu_string_strlen(str)); break;
			case 20: return mu_string_insert(str, "SampleMask", mu_string_strlen(str)); break;
			case 22: return mu_string_insert(str, "FragDepth", mu_string_strlen(str)); break;
			case 23: return mu_string_insert(str, "HelperInvocation", mu_string_strlen(str)); break;
			case 24: return mu_string_insert(str, "NumWorkgroups", mu_string_strlen(str)); break;
			case 25: return mu_string_insert(str, "WorkgroupSize", mu_string_strlen(str)); break;
			case 26: return mu_string_insert(str, "WorkgroupId", mu_string_strlen(str)); break;
			case 27: return mu_string_insert(str, "LocalInvocationId", mu_string_strlen(str)); break;
			case 28: return mu_string_insert(str, "GlobalInvocationId", mu_string_strlen(str)); break;
			case 29: return mu_string_insert(str, "LocalInvocationIndex", mu_string_strlen(str)); break;
			case 30: return mu_string_insert(str, "WorkDim", mu_string_strlen(str)); break;
			case 31: return mu_string_insert(str, "GlobalSize", mu_string_strlen(str)); break;
			case 32: return mu_string_insert(str, "EnqueuedWorkgroupSize", mu_string_strlen(str)); break;
			case 33: return mu_string_insert(str, "GlobalOffset", mu_string_strlen(str)); break;
			case 34: return mu_string_insert(str, "GlobalLinearId", mu_string_strlen(str)); break;
			case 36: return mu_string_insert(str, "SubgroupSize", mu_string_strlen(str)); break;
			case 37: return mu_string_insert(str, "SubgroupMaxSize", mu_string_strlen(str)); break;
			case 38: return mu_string_insert(str, "NumSubgroups", mu_string_strlen(str)); break;
			case 39: return mu_string_insert(str, "NumEnqueuedSubgroups", mu_string_strlen(str)); break;
			case 40: return mu_string_insert(str, "SubgroupId", mu_string_strlen(str)); break;
			case 41: return mu_string_insert(str, "SubgroupLocalInvocationId", mu_string_strlen(str)); break;
			case 42: return mu_string_insert(str, "VertexIndex", mu_string_strlen(str)); break;
			case 43: return mu_string_insert(str, "InstanceIndex", mu_string_strlen(str)); break;
			case 4416: return mu_string_insert(str, "SubgroupEqMask", mu_string_strlen(str)); break;
			case 4417: return mu_string_insert(str, "SubgroupGeMask", mu_string_strlen(str)); break;
			case 4418: return mu_string_insert(str, "SubgroupGtMask", mu_string_strlen(str)); break;
			case 4419: return mu_string_insert(str, "SubgroupLeMask", mu_string_strlen(str)); break;
			case 4420: return mu_string_insert(str, "SubgroupLtMask", mu_string_strlen(str)); break;
			case 4424: return mu_string_insert(str, "BaseVertex", mu_string_strlen(str)); break;
			case 4425: return mu_string_insert(str, "BaseInstance", mu_string_strlen(str)); break;
			case 4426: return mu_string_insert(str, "DrawIndex", mu_string_strlen(str)); break;
			case 4432: return mu_string_insert(str, "PrimitiveShadingRate", mu_string_strlen(str)); break;
			case 4438: return mu_string_insert(str, "DeviceIndex", mu_string_strlen(str)); break;
			case 4440: return mu_string_insert(str, "ViewIndex", mu_string_strlen(str)); break;
			case 4444: return mu_string_insert(str, "ShadingRate", mu_string_strlen(str)); break;
			case 4992: return mu_string_insert(str, "BaryCoordNoPersp", mu_string_strlen(str)); break;
			case 4993: return mu_string_insert(str, "BaryCoordNoPerspCentroid", mu_string_strlen(str)); break;
			case 4994: return mu_string_insert(str, "BaryCoordNoPerspSample", mu_string_strlen(str)); break;
			case 4995: return mu_string_insert(str, "BaryCoordSmooth", mu_string_strlen(str)); break;
			case 4996: return mu_string_insert(str, "BaryCoordSmoothCentroid", mu_string_strlen(str)); break;
			case 4997: return mu_string_insert(str, "BaryCoordSmoothSample", mu_string_strlen(str)); break;
			case 4998: return mu_string_insert(str, "BaryCoordPullModel", mu_string_strlen(str)); break;
			case 5014: return mu_string_insert(str, "FragStencilRef", mu_string_strlen(str)); break;
			case 5253: return mu_string_insert(str, "ViewportMask", mu_string_strlen(str)); break;
			case 5257: return mu_string_insert(str, "SecondaryPosition", mu_string_strlen(str)); break;
			case 5258: return mu_string_insert(str, "SecondaryViewportMask", mu_string_strlen(str)); break;
			case 5261: return mu_string_insert(str, "PositionPerView", mu_string_strlen(str)); break;
			case 5262: return mu_string_insert(str, "ViewportMaskPerView", mu_string_strlen(str)); break;
			case 5264: return mu_string_insert(str, "FullyCovered", mu_string_strlen(str)); break;
			case 5274: return mu_string_insert(str, "TaskCount", mu_string_strlen(str)); break;
			case 5275: return mu_string_insert(str, "PrimitiveCount", mu_string_strlen(str)); break;
			case 5276: return mu_string_insert(str, "PrimitiveIndices", mu_string_strlen(str)); break;
			case 5277: return mu_string_insert(str, "ClipDistancePerView", mu_string_strlen(str)); break;
			case 5278: return mu_string_insert(str, "CullDistancePerView", mu_string_strlen(str)); break;
			case 5279: return mu_string_insert(str, "LayerPerView", mu_string_strlen(str)); break;
			case 5280: return mu_string_insert(str, "MeshViewCount", mu_string_strlen(str)); break;
			case 5281: return mu_string_insert(str, "MeshViewIndices", mu_string_strlen(str)); break;
			case 5286: return mu_string_insert(str, "BaryCoord", mu_string_strlen(str)); break;
			case 5287: return mu_string_insert(str, "BaryCoordNoPersp", mu_string_strlen(str)); break;
			case 5292: return mu_string_insert(str, "FragSize", mu_string_strlen(str)); break;
			case 5293: return mu_string_insert(str, "FragInvocationCount", mu_string_strlen(str)); break;
			case 5319: return mu_string_insert(str, "LaunchId", mu_string_strlen(str)); break;
			case 5320: return mu_string_insert(str, "LaunchSize", mu_string_strlen(str)); break;
			case 5321: return mu_string_insert(str, "WorldRayOrigin", mu_string_strlen(str)); break;
			case 5322: return mu_string_insert(str, "WorldRayDirection", mu_string_strlen(str)); break;
			case 5323: return mu_string_insert(str, "ObjectRayOrigin", mu_string_strlen(str)); break;
			case 5324: return mu_string_insert(str, "ObjectRayDirection", mu_string_strlen(str)); break;
			case 5325: return mu_string_insert(str, "RayTmin", mu_string_strlen(str)); break;
			case 5326: return mu_string_insert(str, "RayTmax", mu_string_strlen(str)); break;
			case 5327: return mu_string_insert(str, "InstanceCustomIndex", mu_string_strlen(str)); break;
			case 5330: return mu_string_insert(str, "ObjectToWorld", mu_string_strlen(str)); break;
			case 5331: return mu_string_insert(str, "WorldToObject", mu_string_strlen(str)); break;
			case 5332: return mu_string_insert(str, "HitT", mu_string_strlen(str)); break;
			case 5333: return mu_string_insert(str, "HitKind", mu_string_strlen(str)); break;
			case 5334: return mu_string_insert(str, "CurrentRayTime", mu_string_strlen(str)); break;
			case 5351: return mu_string_insert(str, "IncomingRayFlags", mu_string_strlen(str)); break;
			case 5352: return mu_string_insert(str, "RayGeometryIndex", mu_string_strlen(str)); break;
			case 5374: return mu_string_insert(str, "WarpsPerSM", mu_string_strlen(str)); break;
			case 5375: return mu_string_insert(str, "SMCount", mu_string_strlen(str)); break;
			case 5376: return mu_string_insert(str, "WarpID", mu_string_strlen(str)); break;
			case 5377: return mu_string_insert(str, "SMID", mu_string_strlen(str)); break;
			case 6021: return mu_string_insert(str, "CullMask", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_ReservedFPDenormMode(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownReservedFPDenormMode", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "Preserve", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "FlushToZero", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_Decoration(muString str, muSPIRVType type, const char* binary, size_m binarylen, size_m i, size_m* k, size_m step, uint32_m* latest_result_target, size_m* beg_str_i) {
		switch (muSAVE_get_word(&binary[i+4+((*k*4))])) {
			default: return mu_string_insert(str, "UnknownDecoration", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "RelaxedPrecision", mu_string_strlen(str)); break;
			case 1: {
				str = mu_string_insert(str, "SpecId ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 2: return mu_string_insert(str, "Block", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "BufferBlock", mu_string_strlen(str)); break;
			case 4: return mu_string_insert(str, "RowMajor", mu_string_strlen(str)); break;
			case 5: return mu_string_insert(str, "ColMajor", mu_string_strlen(str)); break;
			case 6: {
				str = mu_string_insert(str, "ArrayStride ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 7: {
				str = mu_string_insert(str, "MatrixStride ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 8: return mu_string_insert(str, "GLSLShared", mu_string_strlen(str)); break;
			case 9: return mu_string_insert(str, "GLSLPacked", mu_string_strlen(str)); break;
			case 10: return mu_string_insert(str, "CPacked", mu_string_strlen(str)); break;
			case 11: {
				str = mu_string_insert(str, "BuiltIn ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_BuiltIn(str, muSAVE_get_word(&binary[i+4+((*k*4))]));
			} break;
			case 13: return mu_string_insert(str, "NoPerspective", mu_string_strlen(str)); break;
			case 14: return mu_string_insert(str, "Flat", mu_string_strlen(str)); break;
			case 15: return mu_string_insert(str, "Patch", mu_string_strlen(str)); break;
			case 16: return mu_string_insert(str, "Centroid", mu_string_strlen(str)); break;
			case 17: return mu_string_insert(str, "Sample", mu_string_strlen(str)); break;
			case 18: return mu_string_insert(str, "Invariant", mu_string_strlen(str)); break;
			case 19: return mu_string_insert(str, "Restrict", mu_string_strlen(str)); break;
			case 20: return mu_string_insert(str, "Aliased", mu_string_strlen(str)); break;
			case 21: return mu_string_insert(str, "Volatile", mu_string_strlen(str)); break;
			case 22: return mu_string_insert(str, "Constant", mu_string_strlen(str)); break;
			case 23: return mu_string_insert(str, "Coherent", mu_string_strlen(str)); break;
			case 24: return mu_string_insert(str, "NonWritable", mu_string_strlen(str)); break;
			case 25: return mu_string_insert(str, "NonReadable", mu_string_strlen(str)); break;
			case 26: return mu_string_insert(str, "Uniform", mu_string_strlen(str)); break;
			case 27: {
				str = mu_string_insert(str, "UniformId ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_ID_TARGET, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 28: return mu_string_insert(str, "SaturatedConversion", mu_string_strlen(str)); break;
			case 29: {
				str = mu_string_insert(str, "Stream ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 30: {
				str = mu_string_insert(str, "Location ", mu_string_strlen(str));
				*k += 1;
				// Might be StorageClass... docs don't phrase it clearly, making uint32 to be safe
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 31: {
				str = mu_string_insert(str, "Component ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 32: {
				str = mu_string_insert(str, "Index ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 33: {
				str = mu_string_insert(str, "Binding ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 34: {
				str = mu_string_insert(str, "DescriptorSet ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 35: {
				str = mu_string_insert(str, "Offset ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 36: {
				str = mu_string_insert(str, "XfbBuffer ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 37: {
				str = mu_string_insert(str, "XfbStride ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 38: {
				str = mu_string_insert(str, "FuncParamAttr ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_FunctionParameterAttribute(str, muSAVE_get_word(&binary[i+4+((*k*4))]));
			} break;
			case 39: {
				str = mu_string_insert(str, "FPRoundingMode ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_FPRoundingMode(str, muSAVE_get_word(&binary[i+4+((*k*4))]));
			} break;
			case 40: {
				str = mu_string_insert(str, "FPFastMathMode ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_FPFastMathMode(str, muSAVE_get_word(&binary[i+4+((*k*4))]));
			} break;
			case 41: {
				str = mu_string_insert(str, "LinkageAttributes ", mu_string_strlen(str));
				*k += 1;
				str = muSAVE_insert_instruction_by_type(str, MU_SPIRV_STRING, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
				*k += 1;
				str = mu_string_insert(str, " ", mu_string_strlen(str));
				return muSAVE_insert_LinkageType(str, muSAVE_get_word(&binary[i+4+((*k*4))]));
			} break;
			case 42: return mu_string_insert(str, "NoContraction", mu_string_strlen(str)); break;
			case 43: {
				str = mu_string_insert(str, "InputAttachmentIndex ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 44: {
				str = mu_string_insert(str, "Alignment ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 45: {
				str = mu_string_insert(str, "MaxByteOffset ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 46: {
				str = mu_string_insert(str, "AlignmentId ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_ID_TARGET, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 47: {
				str = mu_string_insert(str, "MaxByteOffsetId ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_ID_TARGET, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 4469: return mu_string_insert(str, "NoSignedWrap", mu_string_strlen(str)); break;
			case 4470: return mu_string_insert(str, "NoUnsignedWrap", mu_string_strlen(str)); break;
			case 4999: return mu_string_insert(str, "ExplicitInterp", mu_string_strlen(str)); break;
			case 5248: return mu_string_insert(str, "OverrideCoverage", mu_string_strlen(str)); break;
			case 5250: return mu_string_insert(str, "Passthrough", mu_string_strlen(str)); break;
			case 5252: return mu_string_insert(str, "ViewportRelative", mu_string_strlen(str)); break;
			case 5256: {
				str = mu_string_insert(str, "SecondaryViewportRelative ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5271: return mu_string_insert(str, "PerPrimitive", mu_string_strlen(str)); break;
			case 5272: return mu_string_insert(str, "PerView", mu_string_strlen(str)); break;
			case 5273: return mu_string_insert(str, "PerTask", mu_string_strlen(str)); break;
			case 5285: return mu_string_insert(str, "PerVertex", mu_string_strlen(str)); break;
			case 5300: return mu_string_insert(str, "NonUniform", mu_string_strlen(str)); break;
			case 5355: return mu_string_insert(str, "RestrictPointer", mu_string_strlen(str)); break;
			case 5356: return mu_string_insert(str, "AliasedPointer", mu_string_strlen(str)); break;
			case 5398: return mu_string_insert(str, "BindlessSampler", mu_string_strlen(str)); break;
			case 5399: return mu_string_insert(str, "BindlessImage", mu_string_strlen(str)); break;
			case 5400: return mu_string_insert(str, "BoundSampler", mu_string_strlen(str)); break;
			case 5401: return mu_string_insert(str, "BoundImage", mu_string_strlen(str)); break;
			case 5599: {
				str = mu_string_insert(str, "SIMTCall ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5602: return mu_string_insert(str, "ReferencedIndirectly", mu_string_strlen(str)); break;
			case 5607: {
				str = mu_string_insert(str, "Clobber ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5608: return mu_string_insert(str, "SideEffects", mu_string_strlen(str)); break;
			case 5624: return mu_string_insert(str, "VectorComputeVariable", mu_string_strlen(str)); break;
			case 5625: {
				str = mu_string_insert(str, "FuncParamIOKind ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5626: return mu_string_insert(str, "VectorComputeFunction", mu_string_strlen(str)); break;
			case 5627: return mu_string_insert(str, "StackCall", mu_string_strlen(str)); break;
			case 5628: {
				str = mu_string_insert(str, "GlobalVariableOffset ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5634: {
				str = mu_string_insert(str, "CounterBuffer ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_ID_TARGET, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5635: {
				str = mu_string_insert(str, "UserSemantic ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_STRING, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5636: {
				str = mu_string_insert(str, "UserType ", mu_string_strlen(str));
				*k += 1;
				// Might be a string or number, undefined in spec... guessing string.
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_STRING, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5822: {
				str = mu_string_insert(str, "FunctionRoundingMode ", mu_string_strlen(str));
				*k += 1;
				str = muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
				*k += 1;
				str = mu_string_insert(str, " ", mu_string_strlen(str));
				return muSAVE_insert_FPRoundingMode(str, muSAVE_get_word(&binary[i+4+((*k*4))]));
			} break;
			case 5823: {
				str = mu_string_insert(str, "FunctionDenormMode ", mu_string_strlen(str));
				*k += 1;
				str = muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
				*k += 1;
				str = mu_string_insert(str, " ", mu_string_strlen(str));
				return muSAVE_insert_ReservedFPDenormMode(str, muSAVE_get_word(&binary[i+4+((*k*4))]));
			} break;
			case 5825: return mu_string_insert(str, "Register", mu_string_strlen(str)); break;
			// @TODO handle operands for the rest of these (they're reserved and I'm lazy rn)
			case 5826: {
				str = mu_string_insert(str, "Memory ", mu_string_strlen(str));
				*k += 1;
				// "memory type" assuming uint32
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5827: {
				str = mu_string_insert(str, "Numbanks ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5828: {
				str = mu_string_insert(str, "Bankwidth ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5829: {
				str = mu_string_insert(str, "MaxPrivateCopies ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5830: return mu_string_insert(str, "Singlepump", mu_string_strlen(str)); break;
			case 5831: return mu_string_insert(str, "Doublepump", mu_string_strlen(str)); break;
			case 5832: {
				str = mu_string_insert(str, "MaxReplicates ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5833: return mu_string_insert(str, "SimpleDualPort", mu_string_strlen(str)); break;
			case 5834: {
				str = mu_string_insert(str, "Merge ", mu_string_strlen(str));
				*k += 1;
				str = muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
				str = mu_string_insert(str, " ", mu_string_strlen(str));
				*k += 1;
				// "merge type" assuming uint32
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5835: {
				str = mu_string_insert(str, "BankBits ", mu_string_strlen(str));
				*k += 1;
				// "bank bits" assuming uint32
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5836: {
				str = mu_string_insert(str, "ForcePow2Depth ", mu_string_strlen(str));
				*k += 1;
				// "force key" assuming uint32
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5899: return mu_string_insert(str, "BurstCoalesce", mu_string_strlen(str)); break;
			case 5900: {
				str = mu_string_insert(str, "CacheSize ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5901: return mu_string_insert(str, "DontStaticallyCoalesce", mu_string_strlen(str)); break;
			case 5902: {
				str = mu_string_insert(str, "Prefetch ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5905: return mu_string_insert(str, "StallEnable", mu_string_strlen(str)); break;
			case 5907: return mu_string_insert(str, "FuseLoopsInFunction", mu_string_strlen(str)); break;
			case 5914: {
				str = mu_string_insert(str, "AliasScope ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_ID_TARGET, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5915: {
				str = mu_string_insert(str, "NoAlias ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_ID_TARGET, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5921: {
				str = mu_string_insert(str, "BufferLocation ", mu_string_strlen(str));
				*k += 1;
				// "<id> ..." versus "Literal ... ID"
				// ???? Assuming uint32
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 5944: {
				str = mu_string_insert(str, "IOPipeStorage ", mu_string_strlen(str));
				*k += 1;
				// Same issue with this one
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 6080: {
				str = mu_string_insert(str, "FunctionFloatingPointMode ", mu_string_strlen(str));
				*k += 1;
				str = muSAVE_insert_instruction_by_type(str, MU_SPIRV_UINT32, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
				str = mu_string_insert(str, " ", mu_string_strlen(str));
				*k += 1;
				return muSAVE_insert_instruction_by_type(str, MU_SPIRV_RESERVED_FP_OPERATION_MODE, binary, binarylen, i, k, step, latest_result_target, beg_str_i);
			} break;
			case 6085: return mu_string_insert(str, "SingleElementVector", mu_string_strlen(str)); break;
			case 6087: return mu_string_insert(str, "VectorComputeCallableFunction", mu_string_strlen(str)); break;
			case 6140: return mu_string_insert(str, "MediaBlockIO", mu_string_strlen(str)); break;
		}
	}

	// pretty sure this is actually incorrect
	muString muSAVE_insert_SelectionControl(muString str, uint32_m n) {
		muBool found_any = MU_FALSE;
		if (n & 0x1) {
			str = mu_string_insert(str, "Flatten", mu_string_strlen(str));
			found_any = MU_TRUE;
		}
		if (n & 0x2) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "DontFlatten", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|DontFlatten", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}

		if (found_any == MU_FALSE) {
			str = mu_string_insert(str, "None", mu_string_strlen(str));
		}
		return str;
	}

	muString muSAVE_insert_LoopControl(muString str, uint32_m n) {
		muBool found_any = MU_FALSE;
		if (n & 0x1) {
			str = mu_string_insert(str, "Unroll", mu_string_strlen(str));
			found_any = MU_TRUE;
		}
		if (n & 0x2) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "DontUnroll", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|DontUnroll", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x4) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "DependencyInfinite", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|DependencyInfinite", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x8) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "DependencyLength", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|DependencyLength", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x10) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "MinIterations", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|MinIterations", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x20) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "MaxIterations", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|MaxIterations", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x40) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "IterationMultiple", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|IterationMultiple", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x80) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "PeelCount", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|PeelCount", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x100) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "PartialCount", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|PartialCount", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x10000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "InitiationInterval", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|InitiationInterval", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x20000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "MaxConcurrency", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|MaxConcurrency", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x40000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "DependencyArray", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|DependencyArray", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x80000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "PipelineEnable", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|PipelineEnable", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x100000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "LoopCoalesce", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|LoopCoalesce", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x200000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "MaxInterleaving", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|MaxInterleaving", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x400000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "SpeculatedIterations", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|SpeculatedIterations", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x800000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "NoFusion", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|NoFusion", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}

		if (found_any == MU_FALSE) {
			str = mu_string_insert(str, "None", mu_string_strlen(str));
		}
		return str;
	}

	muString muSAVE_insert_FunctionControl(muString str, uint32_m n) {
		muBool found_any = MU_FALSE;
		if (n & 0x1) {
			str = mu_string_insert(str, "Inline", mu_string_strlen(str));
			found_any = MU_TRUE;
		}
		if (n & 0x2) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "DontInline", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|DontInline", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x4) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "Pure", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|Pure", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x8) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "Const", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|Const", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x10000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "OptNone", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|OptNone", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}

		if (found_any == MU_FALSE) {
			str = mu_string_insert(str, "None", mu_string_strlen(str));
		}
		return str;
	}

	muString muSAVE_insert_MemorySemantics(muString str, uint32_m n) {
		muBool found_any = MU_FALSE;
		if (n & 0x2) {
			str = mu_string_insert(str, "Acquire", mu_string_strlen(str));
			found_any = MU_TRUE;
		}
		if (n & 0x4) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "Release", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|Release", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x8) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "AcquireRelease", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|AcquireRelease", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x10) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "SequentiallyConsistent", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|SequentiallyConsistent", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x40) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "UniformMemory", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|UniformMemory", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x80) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "SubgroupMemory", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|SubgroupMemory", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x100) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "WorkgroupMemory", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|WorkgroupMemory", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x200) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "CrossWorkgroupMemory", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|CrossWorkgroupMemory", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x400) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "AtomicCounterMemory", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|AtomicCounterMemory", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x800) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "ImageMemory", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|ImageMemory", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x1000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "OutputMemory", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|OutputMemory", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x2000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "MakeAvailable", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|MakeAvailable", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x4000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "MakeVisible", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|MakeVisible", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x8000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "Volatile", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|Volatile", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}

		if (found_any == MU_FALSE) {
			str = mu_string_insert(str, "None(Relaxed)", mu_string_strlen(str));
		}
		return str;
	}

	muString muSAVE_insert_MemoryOperands(muString str, uint32_m n) {
		muBool found_any = MU_FALSE;
		if (n & 0x1) {
			str = mu_string_insert(str, "Volatile", mu_string_strlen(str));
			found_any = MU_TRUE;
		}
		if (n & 0x2) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "Aligned", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|Aligned", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x4) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "Nontemporal", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|Nontemporal", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x8) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "MakePointerAvailable", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|MakePointerAvailable", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x10) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "MakePointerVisible", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|MakePointerVisible", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x20) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "NonPrivatePointer", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|NonPrivatePointer", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x10000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "AliasScopeMask", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|AliasScopeMask", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x20000) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "NoAliasMask", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|NoAliasMask", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}

		if (found_any == MU_FALSE) {
			str = mu_string_insert(str, "None", mu_string_strlen(str));
		}
		return str;
	}

	muString muSAVE_insert_Scope(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownScope", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "CrossDevice", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "Device", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "Workgroup", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "Subgroup", mu_string_strlen(str)); break;
			case 4: return mu_string_insert(str, "Invocation", mu_string_strlen(str)); break;
			case 5: return mu_string_insert(str, "QueueFamily", mu_string_strlen(str)); break;
			case 6: return mu_string_insert(str, "ShaderCall", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_GroupOperation(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownGroupOperation", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "Reduce", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "InclusiveScan", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "ExclusiveScan", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "ClusteredReduce", mu_string_strlen(str)); break;
			case 6: return mu_string_insert(str, "PartitionedReduce", mu_string_strlen(str)); break;
			case 7: return mu_string_insert(str, "PartitionedInclusiveScan", mu_string_strlen(str)); break;
			case 8: return mu_string_insert(str, "PartitionedExclusiveScan", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_KernelEnqueueFlags(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownKernelEnqueueFlags", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "NoWait", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "WaitKernel", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "WaitWorkGroup", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_KernelProfilingInfo(muString str, uint32_m n) {
		muBool found_any = MU_FALSE;
		if (n & 0x1) {
			str = mu_string_insert(str, "CmdExecTime", mu_string_strlen(str));
			found_any = MU_TRUE;
		}

		if (found_any == MU_FALSE) {
			str = mu_string_insert(str, "None", mu_string_strlen(str));
		}
		return str;
	}

	muString muSAVE_insert_Capability(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownCapability", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "Matrix", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "Shader", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "Geometry", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "Tessellation", mu_string_strlen(str)); break;
			case 4: return mu_string_insert(str, "Addresses", mu_string_strlen(str)); break;
			case 5: return mu_string_insert(str, "Linkage", mu_string_strlen(str)); break;
			case 6: return mu_string_insert(str, "Kernel", mu_string_strlen(str)); break;
			case 7: return mu_string_insert(str, "Vector16", mu_string_strlen(str)); break;
			case 8: return mu_string_insert(str, "Float16Buffer", mu_string_strlen(str)); break;
			case 9: return mu_string_insert(str, "Float16", mu_string_strlen(str)); break;
			case 10: return mu_string_insert(str, "Float64", mu_string_strlen(str)); break;
			case 11: return mu_string_insert(str, "Int64", mu_string_strlen(str)); break;
			case 12: return mu_string_insert(str, "Int64Atomics", mu_string_strlen(str)); break;
			case 13: return mu_string_insert(str, "ImageBasic", mu_string_strlen(str)); break;
			case 14: return mu_string_insert(str, "ImageReadWrite", mu_string_strlen(str)); break;
			case 15: return mu_string_insert(str, "ImageMipmap", mu_string_strlen(str)); break;
			case 17: return mu_string_insert(str, "Pipes", mu_string_strlen(str)); break;
			case 18: return mu_string_insert(str, "Groups", mu_string_strlen(str)); break;
			case 19: return mu_string_insert(str, "DeviceEnqueue", mu_string_strlen(str)); break;
			case 20: return mu_string_insert(str, "LiteralSampler", mu_string_strlen(str)); break;
			case 21: return mu_string_insert(str, "AtomicStorage", mu_string_strlen(str)); break;
			case 22: return mu_string_insert(str, "Int16", mu_string_strlen(str)); break;
			case 23: return mu_string_insert(str, "TessellationPointSize", mu_string_strlen(str)); break;
			case 24: return mu_string_insert(str, "GeometryPointSize", mu_string_strlen(str)); break;
			case 25: return mu_string_insert(str, "ImageGatherExtended", mu_string_strlen(str)); break;
			case 27: return mu_string_insert(str, "StorageImageMultisample", mu_string_strlen(str)); break;
			case 28: return mu_string_insert(str, "UniformBufferArrayDynamicIndexing", mu_string_strlen(str)); break;
			case 29: return mu_string_insert(str, "SampledImageArrayDynamicIndexing", mu_string_strlen(str)); break;
			case 30: return mu_string_insert(str, "StorageBufferArrayDynamicIndexing", mu_string_strlen(str)); break;
			case 31: return mu_string_insert(str, "StorageImageArrayDynamicIndexing", mu_string_strlen(str)); break;
			case 32: return mu_string_insert(str, "ClipDistance", mu_string_strlen(str)); break;
			case 33: return mu_string_insert(str, "CullDistance", mu_string_strlen(str)); break;
			case 34: return mu_string_insert(str, "ImageCubeArray", mu_string_strlen(str)); break;
			case 35: return mu_string_insert(str, "SampleRateShading", mu_string_strlen(str)); break;
			case 36: return mu_string_insert(str, "ImageRect", mu_string_strlen(str)); break;
			case 37: return mu_string_insert(str, "SampledRect", mu_string_strlen(str)); break;
			case 38: return mu_string_insert(str, "GenericPointer", mu_string_strlen(str)); break;
			case 39: return mu_string_insert(str, "Int8", mu_string_strlen(str)); break;
			case 40: return mu_string_insert(str, "InputAttachment", mu_string_strlen(str)); break;
			case 41: return mu_string_insert(str, "SparseResidency", mu_string_strlen(str)); break;
			case 42: return mu_string_insert(str, "MinLod", mu_string_strlen(str)); break;
			case 43: return mu_string_insert(str, "Sampled1D", mu_string_strlen(str)); break;
			case 44: return mu_string_insert(str, "Image1D", mu_string_strlen(str)); break;
			case 45: return mu_string_insert(str, "SampledCubeArray", mu_string_strlen(str)); break;
			case 46: return mu_string_insert(str, "SampledBuffer", mu_string_strlen(str)); break;
			case 47: return mu_string_insert(str, "ImageBuffer", mu_string_strlen(str)); break;
			case 48: return mu_string_insert(str, "ImageMSArray", mu_string_strlen(str)); break;
			case 49: return mu_string_insert(str, "StorageImageExtendedFormats", mu_string_strlen(str)); break;
			case 50: return mu_string_insert(str, "ImageQuery", mu_string_strlen(str)); break;
			case 51: return mu_string_insert(str, "DerivativeControl", mu_string_strlen(str)); break;
			case 52: return mu_string_insert(str, "InterpolationFunction", mu_string_strlen(str)); break;
			case 53: return mu_string_insert(str, "TransformFeedback", mu_string_strlen(str)); break;
			case 54: return mu_string_insert(str, "GeometryStreams", mu_string_strlen(str)); break;
			case 55: return mu_string_insert(str, "StorageImageReadWithoutFormat", mu_string_strlen(str)); break;
			case 56: return mu_string_insert(str, "StorageImageWriteWithoutFormat", mu_string_strlen(str)); break;
			case 57: return mu_string_insert(str, "MultiViewport", mu_string_strlen(str)); break;
			case 58: return mu_string_insert(str, "SubgroupDispatch", mu_string_strlen(str)); break;
			case 59: return mu_string_insert(str, "NamedBarrier", mu_string_strlen(str)); break;
			case 60: return mu_string_insert(str, "PipeStorage", mu_string_strlen(str)); break;
			case 61: return mu_string_insert(str, "GroupNonUniform", mu_string_strlen(str)); break;
			case 62: return mu_string_insert(str, "GroupNonUniformVote", mu_string_strlen(str)); break;
			case 63: return mu_string_insert(str, "GroupNonUniformArithmetic", mu_string_strlen(str)); break;
			case 64: return mu_string_insert(str, "GroupNonUniformBallot", mu_string_strlen(str)); break;
			case 65: return mu_string_insert(str, "GroupNonUniformShuffle", mu_string_strlen(str)); break;
			case 66: return mu_string_insert(str, "GroupNonUniformShuffleRelative", mu_string_strlen(str)); break;
			case 67: return mu_string_insert(str, "GroupNonUniformClustered", mu_string_strlen(str)); break;
			case 68: return mu_string_insert(str, "GroupNonUniformQuad", mu_string_strlen(str)); break;
			case 69: return mu_string_insert(str, "ShaderLayer", mu_string_strlen(str)); break;
			case 70: return mu_string_insert(str, "ShaderViewportIndex", mu_string_strlen(str)); break;
			case 71: return mu_string_insert(str, "UniformDecoration", mu_string_strlen(str)); break;
			case 4422: return mu_string_insert(str, "FragmentShadingRate", mu_string_strlen(str)); break;
			case 4423: return mu_string_insert(str, "SubgroupBallot", mu_string_strlen(str)); break;
			case 4427: return mu_string_insert(str, "DrawParameters", mu_string_strlen(str)); break;
			case 4428: return mu_string_insert(str, "WorkgroupMemoryExplicitLayout", mu_string_strlen(str)); break;
			case 4429: return mu_string_insert(str, "WorkgroupMemoryExplicitLayout8BitAccess", mu_string_strlen(str)); break;
			case 4430: return mu_string_insert(str, "WorkgroupMemoryExplicitLayout16BitAccess", mu_string_strlen(str)); break;
			case 4431: return mu_string_insert(str, "SubgroupVote", mu_string_strlen(str)); break;
			case 4433: return mu_string_insert(str, "StorageBuffer16BitAccess", mu_string_strlen(str)); break;
			case 4434: return mu_string_insert(str, "UniformAndStorageBuffer16BitAccess", mu_string_strlen(str)); break;
			case 4435: return mu_string_insert(str, "StoragePushConstant16", mu_string_strlen(str)); break;
			case 4436: return mu_string_insert(str, "StorageInputOutput16", mu_string_strlen(str)); break;
			case 4437: return mu_string_insert(str, "DeviceGroup", mu_string_strlen(str)); break;
			case 4439: return mu_string_insert(str, "MultiView", mu_string_strlen(str)); break;
			case 4441: return mu_string_insert(str, "VariablePointersStorageBuffer", mu_string_strlen(str)); break;
			case 4442: return mu_string_insert(str, "VariablePointers", mu_string_strlen(str)); break;
			case 4445: return mu_string_insert(str, "AtomicStorageOps", mu_string_strlen(str)); break;
			case 4447: return mu_string_insert(str, "SampleMaskPostDepthCoverage", mu_string_strlen(str)); break;
			case 4448: return mu_string_insert(str, "StorageBuffer8BitAccess", mu_string_strlen(str)); break;
			case 4449: return mu_string_insert(str, "UniformAndStorageBuffer8BitAccess", mu_string_strlen(str)); break;
			case 4450: return mu_string_insert(str, "StoragePushConstant8", mu_string_strlen(str)); break;
			case 4464: return mu_string_insert(str, "DenormPreserve", mu_string_strlen(str)); break;
			case 4465: return mu_string_insert(str, "DenormFlushToZero", mu_string_strlen(str)); break;
			case 4466: return mu_string_insert(str, "SignedZeroInfNanPreserve", mu_string_strlen(str)); break;
			case 4467: return mu_string_insert(str, "RoundingModeRTE", mu_string_strlen(str)); break;
			case 4468: return mu_string_insert(str, "RoundingModeRTZ", mu_string_strlen(str)); break;
			case 4471: return mu_string_insert(str, "RayQueryProvisional", mu_string_strlen(str)); break;
			case 4472: return mu_string_insert(str, "RayQuery", mu_string_strlen(str)); break;
			case 4478: return mu_string_insert(str, "RayTraversalPrimitiveCulling", mu_string_strlen(str)); break;
			case 4479: return mu_string_insert(str, "RayTracing", mu_string_strlen(str)); break;
			case 5008: return mu_string_insert(str, "Float16Image", mu_string_strlen(str)); break;
			case 5009: return mu_string_insert(str, "ImageGatherBiasLod", mu_string_strlen(str)); break;
			case 5010: return mu_string_insert(str, "FragmentMask", mu_string_strlen(str)); break;
			case 5013: return mu_string_insert(str, "StencilExport", mu_string_strlen(str)); break;
			case 5015: return mu_string_insert(str, "ImageReadWriteLod", mu_string_strlen(str)); break;
			case 5016: return mu_string_insert(str, "Int64Image", mu_string_strlen(str)); break;
			case 5055: return mu_string_insert(str, "ShaderClock", mu_string_strlen(str)); break;
			case 5249: return mu_string_insert(str, "SampleMaskOverrideCoverage", mu_string_strlen(str)); break;
			case 5251: return mu_string_insert(str, "GeometryShaderPassthrough", mu_string_strlen(str)); break;
			case 5254: return mu_string_insert(str, "ShaderViewportIndexLayer", mu_string_strlen(str)); break;
			case 5255: return mu_string_insert(str, "ShaderViewportMask", mu_string_strlen(str)); break;
			case 5259: return mu_string_insert(str, "ShaderStereoView", mu_string_strlen(str)); break;
			case 5260: return mu_string_insert(str, "PerViewAttributes", mu_string_strlen(str)); break;
			case 5265: return mu_string_insert(str, "FragmentFullyCovered", mu_string_strlen(str)); break;
			case 5266: return mu_string_insert(str, "MeshShading", mu_string_strlen(str)); break;
			case 5282: return mu_string_insert(str, "ImageFootprint", mu_string_strlen(str)); break;
			case 5284: return mu_string_insert(str, "FragmentBarycentric", mu_string_strlen(str)); break;
			case 5288: return mu_string_insert(str, "ComputeDerivativeGroupQuads", mu_string_strlen(str)); break;
			case 5291: return mu_string_insert(str, "FragmentDensity", mu_string_strlen(str)); break;
			case 5297: return mu_string_insert(str, "GroupNonUniformPartitioned", mu_string_strlen(str)); break;
			case 5301: return mu_string_insert(str, "ShaderNonUniform", mu_string_strlen(str)); break;
			case 5302: return mu_string_insert(str, "RuntimeDescriptorArray", mu_string_strlen(str)); break;
			case 5303: return mu_string_insert(str, "InputAttachmentArrayDynamicIndexing", mu_string_strlen(str)); break;
			case 5304: return mu_string_insert(str, "UniformTexelBufferArrayDynamicIndexing", mu_string_strlen(str)); break;
			case 5305: return mu_string_insert(str, "StorageTexelBufferArrayDynamicIndexing", mu_string_strlen(str)); break;
			case 5306: return mu_string_insert(str, "UniformBufferArrayNonUniformIndexing", mu_string_strlen(str)); break;
			case 5307: return mu_string_insert(str, "SampledImageArrayNonUniformIndexing", mu_string_strlen(str)); break;
			case 5308: return mu_string_insert(str, "StorageBufferArrayNonUniformIndexing", mu_string_strlen(str)); break;
			case 5309: return mu_string_insert(str, "StorageImageArrayNonUniformIndexing", mu_string_strlen(str)); break;
			case 5310: return mu_string_insert(str, "InputAttachmentArrayNonUniformIndexing", mu_string_strlen(str)); break;
			case 5311: return mu_string_insert(str, "UniformTexelBufferArrayNonUniformIndexing", mu_string_strlen(str)); break;
			case 5312: return mu_string_insert(str, "StorageTexelBufferArrayNonUniformIndexing", mu_string_strlen(str)); break;
			case 5340: return mu_string_insert(str, "RayTracing", mu_string_strlen(str)); break;
			case 5341: return mu_string_insert(str, "RayTracingMotionBlur", mu_string_strlen(str)); break;
			case 5345: return mu_string_insert(str, "VulkanMemoryModel", mu_string_strlen(str)); break;
			case 5346: return mu_string_insert(str, "VulkanMemoryModelDeviceScope", mu_string_strlen(str)); break;
			case 5347: return mu_string_insert(str, "PhysicalStorageBufferAddresses", mu_string_strlen(str)); break;
			case 5350: return mu_string_insert(str, "ComputeDerivativeGroupLinear", mu_string_strlen(str)); break;
			case 5353: return mu_string_insert(str, "RayTracingProvisional", mu_string_strlen(str)); break;
			case 5357: return mu_string_insert(str, "CooperativeMatrix", mu_string_strlen(str)); break;
			case 5363: return mu_string_insert(str, "FragmentShaderSampleInterlock", mu_string_strlen(str)); break;
			case 5372: return mu_string_insert(str, "FragmentShaderShadingRateInterlock", mu_string_strlen(str)); break;
			case 5373: return mu_string_insert(str, "ShaderSMBuiltins", mu_string_strlen(str)); break;
			case 5378: return mu_string_insert(str, "FragmentShaderPixelInterlock", mu_string_strlen(str)); break;
			case 5379: return mu_string_insert(str, "DemoteToHelperInvocation", mu_string_strlen(str)); break;
			case 5390: return mu_string_insert(str, "BindlessTexture", mu_string_strlen(str)); break;
			case 5568: return mu_string_insert(str, "SubgroupShuffle", mu_string_strlen(str)); break;
			case 5569: return mu_string_insert(str, "SubgroupBufferBlockIO", mu_string_strlen(str)); break;
			case 5570: return mu_string_insert(str, "SubgroupImageBlockIO", mu_string_strlen(str)); break;
			case 5579: return mu_string_insert(str, "SubgroupImageMediaBlockIO", mu_string_strlen(str)); break;
			case 5582: return mu_string_insert(str, "RoundToInfinity", mu_string_strlen(str)); break;
			case 5583: return mu_string_insert(str, "FloatingPointMode", mu_string_strlen(str)); break;
			case 5584: return mu_string_insert(str, "IntegerFunctions2", mu_string_strlen(str)); break;
			case 5603: return mu_string_insert(str, "FunctionPointers", mu_string_strlen(str)); break;
			case 5604: return mu_string_insert(str, "IndirectReferences", mu_string_strlen(str)); break;
			case 5606: return mu_string_insert(str, "Asm", mu_string_strlen(str)); break;
			case 5612: return mu_string_insert(str, "AtomicFloat32MinMax", mu_string_strlen(str)); break;
			case 5613: return mu_string_insert(str, "AtomicFloat64MinMax", mu_string_strlen(str)); break;
			case 5616: return mu_string_insert(str, "AtomicFloat16MinMax", mu_string_strlen(str)); break;
			case 5617: return mu_string_insert(str, "VectorCompute", mu_string_strlen(str)); break;
			case 5619: return mu_string_insert(str, "VectorAny", mu_string_strlen(str)); break;
			case 5629: return mu_string_insert(str, "ExpectAssume", mu_string_strlen(str)); break;
			case 5696: return mu_string_insert(str, "SubgroupAvcMotionEstimation", mu_string_strlen(str)); break;
			case 5697: return mu_string_insert(str, "SubgroupAvcMotionEstimationIntra", mu_string_strlen(str)); break;
			case 5698: return mu_string_insert(str, "SubgroupAvcMotionEstimationChroma", mu_string_strlen(str)); break;
			case 5817: return mu_string_insert(str, "VariableLengthArray", mu_string_strlen(str)); break;
			case 5821: return mu_string_insert(str, "FunctionFloatControl", mu_string_strlen(str)); break;
			case 5824: return mu_string_insert(str, "FPGAMemoryAttributes", mu_string_strlen(str)); break;
			case 5837: return mu_string_insert(str, "FPFastMathMode", mu_string_strlen(str)); break;
			case 5844: return mu_string_insert(str, "ArbitraryPrecisionIntegers", mu_string_strlen(str)); break;
			case 5845: return mu_string_insert(str, "ArbitraryPrecisionFloatingPoint", mu_string_strlen(str)); break;
			case 5886: return mu_string_insert(str, "UnstructuredLoopControls", mu_string_strlen(str)); break;
			case 5888: return mu_string_insert(str, "FPGALoopControls", mu_string_strlen(str)); break;
			case 5892: return mu_string_insert(str, "KernelAttributes", mu_string_strlen(str)); break;
			case 5897: return mu_string_insert(str, "FPGAKernelAttributes", mu_string_strlen(str)); break;
			case 5898: return mu_string_insert(str, "FPGAMemoryAccesses", mu_string_strlen(str)); break;
			case 5904: return mu_string_insert(str, "FPGAClusterAttributes", mu_string_strlen(str)); break;
			case 5906: return mu_string_insert(str, "LoopFuse", mu_string_strlen(str)); break;
			case 5910: return mu_string_insert(str, "MemoryAccessAliasing", mu_string_strlen(str)); break;
			case 5920: return mu_string_insert(str, "FPGABufferLocation", mu_string_strlen(str)); break;
			case 5922: return mu_string_insert(str, "ArbitraryPrecisionFixedPoint", mu_string_strlen(str)); break;
			case 5935: return mu_string_insert(str, "USMStorageClasses", mu_string_strlen(str)); break;
			case 5943: return mu_string_insert(str, "IOPipes", mu_string_strlen(str)); break;
			case 5945: return mu_string_insert(str, "BlockingPipes", mu_string_strlen(str)); break;
			case 5948: return mu_string_insert(str, "FPGAReg", mu_string_strlen(str)); break;
			case 6016: return mu_string_insert(str, "DotProductInputAll", mu_string_strlen(str)); break;
			case 6017: return mu_string_insert(str, "DotProductInput4x8Bit", mu_string_strlen(str)); break;
			case 6018: return mu_string_insert(str, "DotProductInput4x8BitPacked", mu_string_strlen(str)); break;
			case 6019: return mu_string_insert(str, "DotProduct", mu_string_strlen(str)); break;
			case 6020: return mu_string_insert(str, "RayCullMask", mu_string_strlen(str)); break;
			case 6025: return mu_string_insert(str, "BitInstructions", mu_string_strlen(str)); break;
			case 6026: return mu_string_insert(str, "GroupNonUniformRotate", mu_string_strlen(str)); break;
			case 6033: return mu_string_insert(str, "AtomicFloat32Add", mu_string_strlen(str)); break;
			case 6034: return mu_string_insert(str, "AtomicFloat64Add", mu_string_strlen(str)); break;
			case 6089: return mu_string_insert(str, "LongConstantComposite", mu_string_strlen(str)); break;
			case 6094: return mu_string_insert(str, "OptNone", mu_string_strlen(str)); break;
			case 6095: return mu_string_insert(str, "AtomicFloat16Add", mu_string_strlen(str)); break;
			case 6114: return mu_string_insert(str, "DebugInfoModule", mu_string_strlen(str)); break;
			case 6141: return mu_string_insert(str, "SplitBarrier", mu_string_strlen(str)); break;
			case 6400: return mu_string_insert(str, "GroupUniformArithmetic", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_ReservedRayFlags(muString str, uint32_m n) {
		muBool found_any = MU_FALSE;
		if (n & 0x1) {
			str = mu_string_insert(str, "Opaque", mu_string_strlen(str));
			found_any = MU_TRUE;
		}
		if (n & 0x2) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "NoOpaque", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|NoOpaque", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x4) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "TerminateOnFirstHit", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|TerminateOnFirstHit", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x8) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "SkipClosestHitShader", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|SkipClosestHitShader", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x10) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "CullBackFacingTriangles", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|CullBackFacingTriangles", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x20) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "CullFrontFacingTriangles", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|CullFrontFacingTriangles", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x40) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "CullOpaque", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|CullOpaque", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x80) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "CullNoOpaque", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|CullNoOpaque", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x100) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "SkipTriangles", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|SkipTriangles", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x200) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "SkipAABBs", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|SkipAABBs", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}

		if (found_any == MU_FALSE) {
			str = mu_string_insert(str, "None", mu_string_strlen(str));
		}
		return str;
	}

	muString muSAVE_insert_ReservedRayQueryIntersection(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownReservedRayQueryIntersection", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "RayQueryCandidateIntersection", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "RayQueryCommittedIntersection", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_ReservedRayQueryCommittedType(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownReservedRayQueryCommittedType", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "RayQueryCommittedIntersectionNone", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "RayQueryCommittedIntersectionTriangle", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "RayQueryCommittedIntersectionGenerated", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_ReservedRayQueryCandidateType(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownReservedRayQueryCandidateType", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "RayQueryCandidateIntersectionTriangle", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "RayQueryCandidateIntersectionAABB", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_ReservedFragmentShadingRate(muString str, uint32_m n) {
		muBool found_any = MU_FALSE;
		if (n & 0x1) {
			str = mu_string_insert(str, "Vertical2Pixels", mu_string_strlen(str));
			found_any = MU_TRUE;
		}
		if (n & 0x2) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "Vertical4Pixels", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|Vertical4Pixels", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x4) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "Horizontal2Pixels", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|Horizontal2Pixels", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}
		if (n & 0x8) {
			if (found_any == MU_FALSE) {
				str = mu_string_insert(str, "Horizontal4Pixels", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, "|Horizontal4Pixels", mu_string_strlen(str));
			}
			found_any = MU_TRUE;
		}

		if (found_any == MU_FALSE) {
			str = mu_string_insert(str, "None", mu_string_strlen(str));
		}
		return str;
	}

	muString muSAVE_insert_ReservedFPOperationMode(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownReservedFPOperationMode", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "IEEE", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "ALT", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_QuantizationMode(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownQuantizationMode", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "TRN", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "TRN_ZERO", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "RND", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "RND_ZERO", mu_string_strlen(str)); break;
			case 4: return mu_string_insert(str, "RND_INF", mu_string_strlen(str)); break;
			case 5: return mu_string_insert(str, "RND_MIN_INF", mu_string_strlen(str)); break;
			case 6: return mu_string_insert(str, "RND_CONV", mu_string_strlen(str)); break;
			case 7: return mu_string_insert(str, "RND_CONV_ODD", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_OverflowMode(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownOverflowMode", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "WRAP", mu_string_strlen(str)); break;
			case 1: return mu_string_insert(str, "SAT", mu_string_strlen(str)); break;
			case 2: return mu_string_insert(str, "SAT_ZERO", mu_string_strlen(str)); break;
			case 3: return mu_string_insert(str, "SAT_SYM", mu_string_strlen(str)); break;
		}
	}

	muString muSAVE_insert_PackedVectorFormat(muString str, uint32_m n) {
		switch (n) {
			default: return mu_string_insert(str, "UnknownPackedVectorFormat", mu_string_strlen(str)); break;
			case 0: return mu_string_insert(str, "PackedVectorFormat4x8Bit", mu_string_strlen(str)); break;
		}
	}

muString muSAVE_insert_instruction_by_type(muString str, muSPIRVType type, const char* binary, size_m binarylen, size_m i, size_m* k, size_m step, uint32_m* latest_result_target, size_m* beg_str_i) {
	switch (type) {

		default: {
			str = mu_string_insert(str, " UnknownType", mu_string_strlen(str));
		} break;

		case MU_SPIRV_UINT32: {
			str = mu_string_insert(str, " ", mu_string_strlen(str));
			str = mu_string_insert_integer(str, muSAVE_get_word(&binary[i+4+((*k*4))]), mu_string_strlen(str)); 
		} break;

		case MU_SPIRV_STRING: { // @TODO make utf-8 compliant (I think it is but still...)
			str = mu_string_insert(str, " \"", mu_string_strlen(str));
			str = mu_string_insert(str, (char*)&binary[i+4+((*k*4))], mu_string_strlen(str));
			str = mu_string_insert(str, "\"", mu_string_strlen(str));
			*k += (mu_strlen(&binary[i+4+(*k*4)])) / 4;
		} break;

		case MU_SPIRV_LITERAL_VALUE: {
			str = mu_string_insert(str, " ", mu_string_strlen(str));
			str = muSAVE_insert_type_info(str, binary, binarylen, *latest_result_target, (unsigned char*)&binary[i+4+((*k*4))], (step-*k)*2);
		} break;

		case MU_SPIRV_OPCODE: {
			size_m ii = muSAVE_get_instruction_index(muSAVE_get_word(&binary[i+4+((*k*4))]));
			if (ii == MU_SIZE_MAX) {
				str = mu_string_insert(str, " UnknownOpcode", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, " ", mu_string_strlen(str));
				str = mu_string_insert(str, (char*)mu_global_SPIRV_instructions[ii].name, mu_string_strlen(str));
			}
		} break;

		case MU_SPIRV_ID_TARGET: {
			str = mu_string_insert(str, " %", mu_string_strlen(str));
			str = mu_string_insert_integer(str, muSAVE_get_word(&binary[i+4+((*k*4))]), mu_string_strlen(str));
		} break;

		case MU_SPIRV_ID_TYPE: {
			str = mu_string_insert(str, " %", mu_string_strlen(str));
			str = mu_string_insert_integer(str, muSAVE_get_word(&binary[i+4+((*k*4))]), mu_string_strlen(str));
		} break;

		case MU_SPIRV_ID_RESULT: {
			str = mu_string_insert(str, "%", *beg_str_i);
			*beg_str_i += 1;
			size_m prevlen = mu_string_strlen(str);
			str = mu_string_insert_integer(str, muSAVE_get_word(&binary[i+4+((*k*4))]), *beg_str_i);
			*beg_str_i += mu_string_strlen(str) - prevlen;
			str = mu_string_insert(str, " = ", *beg_str_i);
			*beg_str_i += 3;
		} break;

		case MU_SPIRV_ID_RESULT_TYPE: { // @TODO print type in parenthesis
			str = mu_string_insert(str, " %", mu_string_strlen(str));
			str = mu_string_insert_integer(str, muSAVE_get_word(&binary[i+4+((*k*4))]), mu_string_strlen(str));
			*latest_result_target = muSAVE_get_word(&binary[i+4+((*k*4))]);
		} break;

		case MU_SPIRV_ID_STRING: {
			str = mu_string_insert(str, " %", mu_string_strlen(str));
			str = mu_string_insert_integer(str, muSAVE_get_word(&binary[i+4+((*k*4))]), mu_string_strlen(str));
		} break;

		case MU_SPIRV_ID_OPERAND: {
			str = mu_string_insert(str, " %", mu_string_strlen(str));
			str = mu_string_insert_integer(str, muSAVE_get_word(&binary[i+4+((*k*4))]), mu_string_strlen(str));
		} break;

		case MU_SPIRV_SIGN: {
			if (muSAVE_get_word(&binary[i+4+((*k*4))]) == 0) {
				str = mu_string_insert(str, " Unsigned", mu_string_strlen(str));
			} else if (muSAVE_get_word(&binary[i+4+((*k*4))]) == 1) {
				str = mu_string_insert(str, " Signed", mu_string_strlen(str));
			} else {
				str = mu_string_insert(str, " UnknownSign", mu_string_strlen(str));
			}
		} break;

		case MU_SPIRV_SOURCE_LANGUAGE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_SourceLanguage(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_EXECUTION_MODEL: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_ExecutionModel(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_ADDRESSING_MODEL: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_AddressingModel(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_MEMORY_MODEL: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_MemoryModel(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_EXECUTION_MODE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_ExecutionMode(str, type, binary, binarylen, i, k, step, latest_result_target, beg_str_i); } break;
		case MU_SPIRV_STORAGE_CLASS: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_StorageClass(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_DIM: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_Dim(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_SAMPLER_ADDRESSING_MODE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_SamplerAddressingMode(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_SAMPLER_FILTER_MODE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_SamplerFilterMode(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_IMAGE_FORMAT: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_ImageFormat(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_IMAGE_CHANNEL_ORDER: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_ImageChannelOrder(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_IMAGE_CHANNEL_DATA_TYPE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_ImageChannelDataType(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_IMAGE_OPERANDS: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_ImageOperands(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_FP_FAST_MATH_MODE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_FPFastMathMode(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_FP_ROUNDING_MODE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_FPRoundingMode(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_LINKAGE_TYPE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_LinkageType(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_ACCESS_QUALIFIER: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_AccessQualifier(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_FUNCTION_PARAMETER_ATTRIBUTE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_FunctionParameterAttribute(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_DECORATION: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_Decoration(str, type, binary, binarylen, i, k, step, latest_result_target, beg_str_i); } break;
		case MU_SPIRV_BUILTIN: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_BuiltIn(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_SELECTION_CONTROL: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_SelectionControl(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_LOOP_CONTROL: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_LoopControl(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_FUNCTION_CONTROL: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_FunctionControl(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_MEMORY_SEMANTICS: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_MemorySemantics(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_MEMORY_OPERANDS: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_MemoryOperands(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_SCOPE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_Scope(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_GROUP_OPERATION: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_GroupOperation(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_KERNEL_ENQUEUE_FLAGS: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_KernelEnqueueFlags(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_KERNEL_PROFILING_INFO: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_KernelProfilingInfo(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_CAPABILITY: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_Capability(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_RESERVED_RAY_FLAGS: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_ReservedRayFlags(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_RESERVED_RAY_QUERY_INTERSECTION: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_ReservedRayQueryIntersection(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_RESERVED_RAY_QUERY_COMMITTED_TYPE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_ReservedRayQueryCommittedType(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_RESERVED_RAY_QUERY_CANDIDATE_TYPE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_ReservedRayQueryCandidateType(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_RESERVED_FRAGMENT_SHADING_RATE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_ReservedFragmentShadingRate(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_RESERVED_FP_DENORM_MODE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_ReservedFPDenormMode(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_RESERVED_FP_OPERATION_MODE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_ReservedFPOperationMode(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_QUANTIZATION_MODE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_ReservedFPOperationMode(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_OVERFLOW_MODE: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_OverflowMode(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
		case MU_SPIRV_PACKED_VECTOR_FORMAT: { str = mu_string_insert(str, " ", mu_string_strlen(str)); str = muSAVE_insert_PackedVectorFormat(str, muSAVE_get_word(&binary[i+4+((*k*4))])); } break;
	}

	return str;
}

/* instruction stuff */

muString muSAVE_insert_instruction(muString str, size_m i, size_m j, uint16_m step, const char* binary, size_m binarylen, muBool print_newline) {
	size_m beg_str_i = mu_string_strlen(str) + 1;
	if (j == MU_SIZE_MAX) {
		if (print_newline) {
			str = mu_string_insert(str, "\nUnknownInstruction", mu_string_strlen(str));
		} else {
			str = mu_string_insert(str, "UnknownInstruction", mu_string_strlen(str));
		}
	} else {
		if (print_newline) {
			str = mu_string_insert(str, "\n", mu_string_strlen(str));
		}
		str = mu_string_insert(str, (char*)mu_global_SPIRV_instructions[j].name, mu_string_strlen(str));
		muBool reached_indefinite = MU_FALSE;
		uint32_m latest_result_target = 0;
		for (size_m k = 0; k < step-1; k++) {
			muSPIRVType type;
			if (reached_indefinite == MU_TRUE) {
				type = mu_global_SPIRV_instructions[j].indefinite_type;
			} else {
				type = mu_global_SPIRV_instructions[j].operands[k];
			}
			if (type == 0) {
				str = mu_string_insert(str, " {", mu_string_strlen(str));
				reached_indefinite = MU_TRUE;
				type = mu_global_SPIRV_instructions[j].indefinite_type;
				//break;
			}
			// handle type printing
			// @TODO handle MU_SPIRV_INSTRUCTION
			str = muSAVE_insert_instruction_by_type(str, type, binary, binarylen, i, &k, step, &latest_result_target, &beg_str_i);
			if (reached_indefinite && k < step-2) {
				str = mu_string_insert(str, ",", mu_string_strlen(str));
			}
		}
		if (reached_indefinite) {
			str = mu_string_insert(str, " }", mu_string_strlen(str));
		}
	}
	return str;
}

/* API-level functions */

const char* mu_global_spirv_binary_to_assembly_error_msg = "[MUSAVE] Failed to convert SPIR-V binary to assembly; SPIR-V binary is incorrect or corrupted.\n";
#define MU_SPIRV_BASSERT(c) {if(!(c)){mu_printf("%s",mu_global_spirv_binary_to_assembly_error_msg);str=mu_string_destroy(str);return empty_str;}}

muString mu_spirv_binary_to_assembly(const char* binary, size_m len) {
	muString empty_str = {0};
	empty_str.s = MU_NULL_PTR;
	empty_str.ws = MU_NULL_PTR;
	
	/* Beginning comment */

	muString str = mu_string_create("; Assembly generated by muSAVE v");
	str = mu_string_insert_integer(str, MUSAVE_VERSION_MAJOR, mu_string_strlen(str));
	str = mu_string_insert(str, ".", mu_string_strlen(str));
	str = mu_string_insert_integer(str, MUSAVE_VERSION_MINOR, mu_string_strlen(str));
	str = mu_string_insert(str, ".", mu_string_strlen(str));
	str = mu_string_insert_integer(str, MUSAVE_VERSION_PATCH, mu_string_strlen(str));
	str = mu_string_insert(str, " with explanation comments off.\n", mu_string_strlen(str));

	/* First words of physical layout */ // @TODO add hex numbers
	MU_SPIRV_BASSERT(len >= 24)

	// Beginning
	str = mu_string_insert(str, "\n; == First words of physical layout ==\n", mu_string_strlen(str));

	// Magic number
	MU_SPIRV_BASSERT(
		binary[0] == 0x03 && binary[1] == 0x02 &&
		binary[2] == 0x23 && binary[3] == 0x07
	)
	str = mu_string_insert(str, "; Magic:     0x07230203 (SPIR-V)\n", mu_string_strlen(str));

	// Version
	str = mu_string_insert(str, "; Version:   v", mu_string_strlen(str));
	str = mu_string_insert_integer(str, binary[6], mu_string_strlen(str));
	str = mu_string_insert(str, ".", mu_string_strlen(str));
	str = mu_string_insert_integer(str, binary[5], mu_string_strlen(str));
	str = mu_string_insert(str, ".", mu_string_strlen(str));
	str = mu_string_insert_integer(str, binary[4], mu_string_strlen(str));
	str = mu_string_insert(str, "\n", mu_string_strlen(str));

	// @TODO Generator

	// Bound
	str = mu_string_insert(str, "; Bound:     ", mu_string_strlen(str));
	str = mu_string_insert_integer(str, muSAVE_get_word(&binary[12]), mu_string_strlen(str));
	str = mu_string_insert(str, "\n", mu_string_strlen(str));

	// @TODO Schema

	/* Instruction list */
	str = mu_string_insert(str, "\n; == Instruction list ==", mu_string_strlen(str));

	for (size_m i = 20; i < len;) {
		// gather info
		MU_SPIRV_BASSERT(i+3 < len)
		uint16_m instruction = muSAVE_get_halfword(&binary[i]);
		uint16_m step = muSAVE_get_halfword(&binary[i+2]);
		MU_SPIRV_BASSERT(step != 0)
		MU_SPIRV_BASSERT(i+step < len)
		size_m j = muSAVE_get_instruction_index(instruction);
		if (j != MU_SIZE_MAX) {
			MU_SPIRV_BASSERT(step >= mu_global_SPIRV_instructions[j].min_word_count);
			/*MU_SPIRV_BASSERT(
				(mu_global_SPIRV_instructions[j].indefinite_type == 0 && step == mu_global_SPIRV_instructions[j].min_word_count) || 
				(mu_global_SPIRV_instructions[j].indefinite_type != 0)
			)*/
		}

		// spit out info
		str = muSAVE_insert_instruction(str, i, j, step, binary, len, MU_TRUE);

		// step forward
		i += step * 4;
	}
	
	return str;
}

#ifdef __cplusplus
}
#endif

#endif /* MUSAVE_IMPLEMENTATION */

/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2023 Hum
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
