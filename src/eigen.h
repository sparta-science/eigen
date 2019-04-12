#ifndef INCLUDED_EIGEN_H
#define INCLUDED_EIGEN_H

#include "erl_nif.h"
#include <Eigen/Dense>

using namespace Eigen;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static ERL_NIF_TERM add(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]);
static ERL_NIF_TERM matrix3d_random(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]);
static ERL_NIF_TERM matrix3d_test(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]);
static ERL_NIF_TERM matrix3d_to_term(ErlNifEnv* env, Matrix3d matrix);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif
