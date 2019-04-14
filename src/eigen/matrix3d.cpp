#include "../util.h"
#include "matrix3d.h"

#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;
using namespace std;

/***************************
/  Init
***************************/

ERL_NIF_TERM matrix3d_empty(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  ERL_NIF_TERM result;

  Context* context = (Context*) enif_priv_data(env);
  Matrix3d* mtx = (Matrix3d*) enif_alloc_resource(context->matrix3d_type, sizeof(Matrix3d));

  Matrix3d matrix;
  memcpy(mtx, &matrix, sizeof(Matrix3d));

  result = enif_make_resource(env, mtx);
  enif_release_resource(mtx);

return ok(env, result);
}

ERL_NIF_TERM matrix3d_new(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  if (argc != 1) return enif_make_badarg(env);

  Matrix3d matrix;
  ERL_NIF_TERM result;
  ERL_NIF_TERM list = argv[0];
  ERL_NIF_TERM head, tail, col, coltail;
  int i = 0;
  int j = 0;
  double current;
  unsigned int row_length;

  if (!enif_get_list_length(env, list, &row_length)) return error(env, "unable to find length of list");

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

  Context* context = (Context*) enif_priv_data(env);
  Matrix3d* mtx = (Matrix3d*) enif_alloc_resource(context->matrix3d_type, sizeof(Matrix3d));
  memcpy(mtx, &matrix, sizeof(Matrix3d));

  result = enif_make_resource(env, mtx);
  enif_release_resource(mtx);

  return ok(env, result);
}

ERL_NIF_TERM matrix3d_to_list(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  if (argc != 1) return enif_make_badarg(env);

  Matrix3d* matrix;
  ERL_NIF_TERM row;
  double* matrix_data;

  Context* context = (Context*) enif_priv_data(env);
  if (!enif_get_resource(env, argv[0], context->matrix3d_type, (void**) &matrix)) return error(env, "unable to reference pointer");

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

  return ok(env, result);
}

/***************************
/  Maths
***************************/

ERL_NIF_TERM matrix3d_div_scalar(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  if (argc != 2) return enif_make_badarg(env);

  Matrix3d* matrix;
  double multiplier;

  Context* context = (Context*) enif_priv_data(env);
  if (!enif_get_resource(env, argv[0], context->matrix3d_type, (void**) &matrix)) return error(env, "unable to reference pointer");
  if(!enif_get_double(env, argv[1], &multiplier)) return error(env, "divisor must be a float");

  Matrix3d new_matrix = *matrix / multiplier;

  Matrix3d* mtx = (Matrix3d*) enif_alloc_resource(context->matrix3d_type, sizeof(Matrix3d));
  memcpy(mtx, &new_matrix, sizeof(Matrix3d));

  ERL_NIF_TERM result = enif_make_resource(env, mtx);
  enif_release_resource(mtx);

  return ok(env, result);
}

ERL_NIF_TERM matrix3d_mult_scalar(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  if (argc != 2) return enif_make_badarg(env);

  Matrix3d* matrix;
  double multiplier;

  Context* context = (Context*) enif_priv_data(env);
  if (!enif_get_resource(env, argv[0], context->matrix3d_type, (void**) &matrix)) return error(env, "unable to reference pointer");
  if(!enif_get_double(env, argv[1], &multiplier)) return error(env, "multiplier must be a float");

  Matrix3d new_matrix = *matrix * multiplier;

  Matrix3d* mtx = (Matrix3d*) enif_alloc_resource(context->matrix3d_type, sizeof(Matrix3d));
  memcpy(mtx, &new_matrix, sizeof(Matrix3d));

  ERL_NIF_TERM result = enif_make_resource(env, mtx);
  enif_release_resource(mtx);

  return ok(env, result);
}
