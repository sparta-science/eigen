#ifndef EIGEN_UTIL_H
#define EIGEN_UTIL_H

#include "erl_nif.h"

typedef struct {
  ErlNifResourceType* matrix3d_type;
} Context;

ERL_NIF_TERM error(ErlNifEnv *, const char* message);
ERL_NIF_TERM ok(ErlNifEnv *, ERL_NIF_TERM result);

#endif