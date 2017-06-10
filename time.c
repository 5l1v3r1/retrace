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
#include "rtr-time.h"

char *RETRACE_IMPLEMENTATION(ctime_r)(const time_t *timep, char *buf)
{
	real_ctime_r = RETRACE_GET_REAL(ctime_r);

	char *r = real_ctime_r (timep, buf);

	trace_printf(1, "ctime_r(\"%u\", \"%s\");\n", timep ? timep : 0, buf);
	return r;
}

RETRACE_REPLACE(ctime_r)

char *RETRACE_IMPLEMENTATION(ctime)(const time_t *timep)
{
	real_ctime = RETRACE_GET_REAL(ctime);

	char *r = real_ctime(timep);

	trace_printf(1, "ctime(\"%u\") [return: %s];\n", timep ? timep : 0, r);

	return r;
}

RETRACE_REPLACE(ctime)

int RETRACE_IMPLEMENTATION(gettimeofday)(struct timeval *tv, struct timezone *tz)
{
        real_gettimeofday = RETRACE_GET_REAL(gettimeofday);

        int ret = real_gettimeofday(tv, tz);
        if (ret == 0)
                trace_printf(1, "gettimeofday(timeval:[%ld, %ld], timezone:[%d, %d]);\n",
                                tv->tv_sec, tv->tv_usec, tz->tz_minuteswest, tz->tz_dsttime);
        else
                trace_printf(1, "gettimeofday(); -1\n");

        return ret;
}

RETRACE_REPLACE(gettimeofday)
