#include "util.h"

ERL_NIF_TERM error(ErlNifEnv *env, const char* message) {
  ERL_NIF_TERM atom_error = enif_make_atom(env, "error");
  return enif_make_tuple2(env, atom_error, enif_make_string(env, message, ERL_NIF_LATIN1));
}

ERL_NIF_TERM ok(ErlNifEnv *env, ERL_NIF_TERM result) {
  ERL_NIF_TERM atom_ok = enif_make_atom(env, "ok");
  return enif_make_tuple2(env, atom_ok, result);
}
