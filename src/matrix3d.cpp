#include "erl_nif.h"

#include "matrix3d.h"
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

/***************************
/  Export to Elixir
***************************/

static ErlNifFunc nif_functions[] = {
  {"matrix3d_empty", 0, matrix3d_empty, 0},
  {"matrix3d_new", 1, matrix3d_new, 0},
  {"matrix3d_to_list", 1, matrix3d_to_list, 0}
};

static ERL_NIF_TERM matrix3d_empty(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  ERL_NIF_TERM result;

  Matrix3d* mtx = (Matrix3d*) enif_alloc_resource(matrix3d_type, sizeof(Matrix3d));

  Matrix3d matrix;
  memcpy(mtx, &matrix, sizeof(Matrix3d));

  result = enif_make_resource(env, mtx);
  enif_release_resource(mtx);

  return result;
}

static ERL_NIF_TERM matrix3d_new(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  if (argc != 1) return enif_make_badarg(env);

  Matrix3d matrix;
  ERL_NIF_TERM result;
  ERL_NIF_TERM list = argv[0];
  ERL_NIF_TERM head, tail, col, coltail;
  int i = 0;
  int j = 0;
  double current;
  unsigned int row_length;

  if (!enif_get_list_length(env, list, &row_length)) return enif_make_badarg(env);

  while(enif_get_list_cell(env, list, &head, &tail)) {
    while(enif_get_list_cell(env, head, &col, &coltail)) {
      if(!enif_get_double(env, col, &current)) return enif_make_badarg(env);
      matrix(i, j) = current;
      j++;
      head = coltail;
    }
    j = 0;
    i++;
    list = tail;
  }

  Matrix3d* mtx = (Matrix3d*) enif_alloc_resource(matrix3d_type, sizeof(Matrix3d));
  memcpy(mtx, &matrix, sizeof(Matrix3d));

  result = enif_make_resource(env, mtx);
  enif_release_resource(mtx);

  return result;
}

static ERL_NIF_TERM matrix3d_to_list(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  if (argc != 1) return enif_make_badarg(env);

  Matrix3d* matrix;
  ERL_NIF_TERM row;
  double* matrix_data;

  if (!enif_get_resource(env, argv[0], matrix3d_type, (void**) &matrix)) return enif_make_badarg(env);

  matrix_data = matrix->data();
  int64_t rows = matrix->rows();
  int64_t cols = matrix->cols();

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

ERL_NIF_INIT(Elixir.Eigen.Matrix3d, nif_functions, &load, NULL, NULL, NULL);