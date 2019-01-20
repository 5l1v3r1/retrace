#!/bin/sh

# retrace configuration var
RTR_CONF_VAR=`cat ../retrace.conf.example`

./strinject.sh
LC_ALL="POSIX" retrace ./setlocale
retrace ./exec
retrace ./env
retrace ./exit
retrace ./file
retrace ./fork
retrace ./getaddrinfo
./httpredirect.sh
retrace ./id
retrace ./malloc
retrace ./pipe
retrace ./sock
retrace ./sock_srv
retrace ./str
retrace ./time
retrace ./dlopen
retrace ./dir
retrace ./popen
retrace ./char
retrace ./perror
retrace ./printf
retrace ./scanf
retrace ./char
retrace ./trace
retrace ./log
retrace ./writev
retrace ./readv
export RETRACE_CONFIG_VAR="${RTR_CONF_VAR}"
retrace ./config
retrace --config ../retrace.conf.example ./config

if [[ "$OSTYPE" == "darwin"* ]]; then
RETRACE_v2=../src/v2/.libs/libretrace_v2.dylib
if [ -f $RETRACE_v2 ]; then
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./env
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./exit
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./file
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./fork
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./getaddrinfo
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./id
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./malloc
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./pipe
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./sock
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./sock_srv
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./str
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./time
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./dlopen
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./dir
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./popen
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./char
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./perror
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./printf
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./scanf
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./char
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./trace
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./log
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./writev
DYLD_INSERT_LIBRARIES=$RETRACE_v2 ./readv
fi
else
RETRACE_v2=../src/v2/.libs/libretrace_v2.so
if [ -f $RETRACE_v2 ]; then
LD_PRELOAD=$RETRACE_v2 ./exec
LD_PRELOAD=$RETRACE_v2 ./env
LD_PRELOAD=$RETRACE_v2 ./exit
LD_PRELOAD=$RETRACE_v2 ./file
LD_PRELOAD=$RETRACE_v2 ./fork
LD_PRELOAD=$RETRACE_v2 ./getaddrinfo
LD_PRELOAD=$RETRACE_v2 ./id
LD_PRELOAD=$RETRACE_v2 ./malloc
LD_PRELOAD=$RETRACE_v2 ./pipe
LD_PRELOAD=$RETRACE_v2 ./sock
LD_PRELOAD=$RETRACE_v2 ./sock_srv
LD_PRELOAD=$RETRACE_v2 ./str
LD_PRELOAD=$RETRACE_v2 ./time
LD_PRELOAD=$RETRACE_v2 ./dlopen
LD_PRELOAD=$RETRACE_v2 ./dir
LD_PRELOAD=$RETRACE_v2 ./popen
LD_PRELOAD=$RETRACE_v2 ./char
LD_PRELOAD=$RETRACE_v2 ./perror
LD_PRELOAD=$RETRACE_v2 ./printf
LD_PRELOAD=$RETRACE_v2 ./scanf
LD_PRELOAD=$RETRACE_v2 ./char
LD_PRELOAD=$RETRACE_v2 ./trace
LD_PRELOAD=$RETRACE_v2 ./log
LD_PRELOAD=$RETRACE_v2 ./writev
LD_PRELOAD=$RETRACE_v2 ./readv
fi
fi
