#ifndef EIGEN_MATRIX3D_H
#define EIGEN_MATRIX3D_H

#include "erl_nif.h"
#include "../util.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

ERL_NIF_TERM matrix3d_empty(ErlNifEnv *, int argc, const ERL_NIF_TERM argv[]);
ERL_NIF_TERM matrix3d_new(ErlNifEnv *, int argc, const ERL_NIF_TERM argv[]);
ERL_NIF_TERM matrix3d_to_list(ErlNifEnv *, int argc, const ERL_NIF_TERM argv[]);

ERL_NIF_TERM matrix3d_add(ErlNifEnv *, int argc, const ERL_NIF_TERM argv[]);
ERL_NIF_TERM matrix3d_div_scalar(ErlNifEnv *, int argc, const ERL_NIF_TERM argv[]);
ERL_NIF_TERM matrix3d_mult_scalar(ErlNifEnv *, int argc, const ERL_NIF_TERM argv[]);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif
