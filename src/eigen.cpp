#include "erl_nif.h"
#include "./util.h"
#include "./eigen/matrix3d.h"

#include <iostream>

static void gc_matrix3d(ErlNifEnv *, void* data);
static int load(ErlNifEnv *, void** priv_data, ERL_NIF_TERM load_info);
static void unload(ErlNifEnv *, void* priv_data);

/***************************
/  Export to Elixir
***************************/

static ErlNifFunc nif_functions[] = {
  {"matrix3d_empty", 0, matrix3d_empty, 0},
  {"matrix3d_new", 1, matrix3d_new, 0},
  {"matrix3d_to_list", 1, matrix3d_to_list, 0},
  {"matrix3d_div_scalar", 2, matrix3d_div_scalar, 0},
  {"matrix3d_mult_scalar", 2, matrix3d_mult_scalar, 0}
};

/***************************
/  NIF lifecycle
***************************/

// TODO: verify that this does not leak memory
static void gc_matrix3d(ErlNifEnv *env, void* data) {
  (void) env;
}

static int load(ErlNifEnv *env, void** priv_data, ERL_NIF_TERM load_info) {
  Context* context = (Context*) enif_alloc(sizeof(Context));

  ErlNifResourceType* matrix3d_type = enif_open_resource_type(
    env,
    NULL,
    "gc_matrix3d",
    gc_matrix3d,
    ERL_NIF_RT_CREATE,
    NULL
  );

  if (matrix3d_type == NULL) return -1;

  context->matrix3d_type = matrix3d_type;
  *priv_data = context;

  return 0;
}

static void unload(ErlNifEnv *env, void* priv_data) {
  priv_data = NULL;
}

ERL_NIF_INIT(Elixir.Eigen.Nif, nif_functions, &load, NULL, NULL, &unload);