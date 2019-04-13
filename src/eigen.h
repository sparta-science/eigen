#ifndef INCLUDED_EIGEN_H
#define INCLUDED_EIGEN_H

#include "erl_nif.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static ERL_NIF_TERM add(ErlNifEnv *, int argc, const ERL_NIF_TERM argv[]);

static ERL_NIF_TERM matrix3d_new(ErlNifEnv *, int argc, const ERL_NIF_TERM argv[]);
static ERL_NIF_TERM matrix3d_random(ErlNifEnv *, int argc, const ERL_NIF_TERM argv[]);
static ERL_NIF_TERM matrix3d_test(ErlNifEnv *, int argc, const ERL_NIF_TERM argv[]);
static ERL_NIF_TERM matrix3d_to_list(ErlNifEnv *, int argc, const ERL_NIF_TERM argv[]);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif
