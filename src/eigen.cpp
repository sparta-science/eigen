#include "erl_nif.h"

#include "eigen.h"
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;
using namespace std;

static ErlNifResourceType* matrix3d_type;

/***************************
/  PRIVATE headers
***************************/

static void gc_matrix3d(ErlNifEnv *, void* data);
static int load(ErlNifEnv *, void** priv_data, ERL_NIF_TERM load_info);
static ERL_NIF_TERM matrix3d_to_term(ErlNifEnv *, Matrix3d);

/***************************
/  Export to Elixir
***************************/

static ErlNifFunc nif_functions[] = {
  {"add", 2, add, 0},
  {"matrix3d_new", 0, matrix3d_new, 0},
  {"matrix3d_random", 0, matrix3d_random, 0},
  {"matrix3d_test", 0, matrix3d_test, 0},
  {"matrix3d_to_list", 1, matrix3d_to_list, 0}
};


static ERL_NIF_TERM add(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  ErlNifSInt64 first, second;

  (void)(argc);

  if (!enif_get_int64(env, argv[0], &first)) return enif_make_badarg(env);
  if (!enif_get_int64(env, argv[1], &second)) return enif_make_badarg(env);

  return enif_make_int(env, first + second);
}

static ERL_NIF_TERM matrix3d_new(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  ERL_NIF_TERM result;

  Matrix3d* mtx = (Matrix3d*) enif_alloc_resource(matrix3d_type, sizeof(Matrix3d));

  Matrix3d matrix;

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  matrix(2, 2) = 9;

  memcpy(mtx, &matrix, sizeof(Matrix3d));

  result = enif_make_resource(env, mtx);
  enif_release_resource(mtx);

  return result;
}

static ERL_NIF_TERM matrix3d_random(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  Matrix3d m = Matrix3d::Random();

  return matrix3d_to_term(env, m);
}

static ERL_NIF_TERM matrix3d_test(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  Matrix3d m;

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 4;
  m(1, 1) = 5;
  m(1, 2) = 6;
  m(2, 0) = 7;
  m(2, 1) = 8;
  m(2, 2) = 9;

  return matrix3d_to_term(env, m);
}

static ERL_NIF_TERM matrix3d_to_list(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  if (argc != 1) return enif_make_badarg(env);

  Matrix3d* matrix;
  if (!enif_get_resource(env, argv[0], matrix3d_type, (void**) &matrix)) return enif_make_badarg(env);

  return matrix3d_to_term(env, *matrix);
}

static ERL_NIF_TERM matrix3d_to_term(ErlNifEnv* env, Matrix3d m) {
  ERL_NIF_TERM row;
  double* matrix_data;

  matrix_data = m.data();
  int64_t rows = m.rows();
  int64_t cols = m.cols();

  ERL_NIF_TERM result = enif_make_list(env, 0);

  for (int64_t i = cols - 1; i >= 0; i--) {
    row = enif_make_list(env, 0);

    for (int64_t j = rows - 1; j >= 0 ; j--) {
      row = enif_make_list_cell(env, enif_make_double(env, matrix_data[j*rows + i]), row);
    }
    result = enif_make_list_cell(env, row, result);
  }

  return result;
}

/***************************
/  NIF lifecycle
***************************/

// TODO: verify that this does not leak memory
static void gc_matrix3d(ErlNifEnv *env, void* data) {
  (void) env;
}


static int load(ErlNifEnv *env, void** priv_data, ERL_NIF_TERM load_info) {
  ErlNifResourceType* rt = enif_open_resource_type(
    env,
    NULL,
    "gc_matrix3d",
    &gc_matrix3d,
    ERL_NIF_RT_CREATE,
    NULL
  );

  if (rt == NULL) return -1;

  matrix3d_type = rt;

  return 0;
}

ERL_NIF_INIT(Elixir.Eigen.NIFs, nif_functions, &load, NULL, NULL, NULL);