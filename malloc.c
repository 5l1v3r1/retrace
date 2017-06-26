/*
 * Copyright (c) 2017, [Ribose Inc](https://www.ribose.com).
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "common.h"
#include "malloc.h"

#include <stdlib.h>

static int init_rand = 0;

void *RETRACE_IMPLEMENTATION(malloc)(size_t bytes)
{
        void *p;
	double fail_chance = 0;

	if (rtr_get_config_single("memoryfuzzing", ARGUMENT_TYPE_DOUBLE, ARGUMENT_TYPE_END, &fail_chance)) {
		long int random_value;

		if (!init_rand) {
			srand (time(NULL));
			init_rand = 1;
		}

		random_value = rand();

		if (random_value <= (RAND_MAX * fail_chance)) {
			trace_printf(1, "malloc(%d); [redirecting: NULL]\n", bytes);

			return NULL;
		}
	}

        p = real_malloc(bytes);

        trace_printf(1, "malloc(%d); [%p]\n", bytes, p);

        return p;
}

RETRACE_REPLACE(malloc, void *, (size_t bytes), (bytes))

void RETRACE_IMPLEMENTATION(free)(void *mem)
{
	trace_printf(1, "free(%p);\n", mem);

	real_free(mem);
}

RETRACE_REPLACE(free, void, (void *mem), (mem))

void *RETRACE_IMPLEMENTATION(calloc)(size_t nmemb, size_t size)
{
        void *p;
	double fail_chance = 0;

	if (rtr_get_config_single("memoryfuzzing", ARGUMENT_TYPE_DOUBLE, ARGUMENT_TYPE_END, &fail_chance)) {
		long int random_value;

		if (!init_rand) {
			srand (time(NULL));
			init_rand = 1;
		}

		random_value = rand();

		if (random_value <= (RAND_MAX * fail_chance)) {
			trace_printf(1, "calloc(%d, %d); [redirecting: NULL]\n", nmemb, size);

			return NULL;
		}
	}

        p = real_calloc(nmemb, size);

        trace_printf(1, "calloc(%d, %d); [%p]\n", nmemb, size, p);

        return p;
}

RETRACE_REPLACE(calloc, void *, (size_t nmemb, size_t size), (nmemb, size))

void *RETRACE_IMPLEMENTATION(realloc)(void *ptr, size_t size)
{
        void *p;
	double fail_chance;

	if (size > 0 && rtr_get_config_single("memoryfuzzing", ARGUMENT_TYPE_DOUBLE, ARGUMENT_TYPE_END, &fail_chance)) {
		long int random_value;

		if (!init_rand) {
			srand (time(NULL));
			init_rand = 1;
		}

		random_value = rand();

		if (random_value <= (RAND_MAX * fail_chance)) {
			trace_printf(1, "realloc(%p, %d); [redirecting: NULL]\n", ptr, size);

			return NULL;
		}
	}


        p = real_realloc(ptr, size);

        trace_printf(1, "realloc(%p, %d); [%p]\n", ptr, size, p);

        return p;
}

RETRACE_REPLACE(realloc, void *, (void *ptr, size_t size), (ptr, size))
