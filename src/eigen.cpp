#include "erl_nif.h"

#include "eigen.h"
#include <iostream>

using namespace Eigen;
using namespace std;

static ERL_NIF_TERM matrix3d_random(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  Matrix3d m = Matrix3d::Random();

  return matrix3d_to_term(env, m);
}

static ERL_NIF_TERM matrix3d_test(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
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

static ERL_NIF_TERM matrix3d_to_term(ErlNifEnv* env, Matrix3d m)
{
  ERL_NIF_TERM row;
  double *matrix_data;

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

static ErlNifFunc nif_functions[] =
{
  {"matrix3d_random", 0, matrix3d_random, 0},
  {"matrix3d_test", 0, matrix3d_test, 0}
};

ERL_NIF_INIT(Elixir.Eigen.NIFs, nif_functions, NULL, NULL, NULL, NULL)