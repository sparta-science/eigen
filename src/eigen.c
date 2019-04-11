#include "erl_nif.h"

#include "eigen.h"

static ERL_NIF_TERM hello(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    return enif_make_string(env, "Hello world!", ERL_NIF_LATIN1);
}

static ErlNifFunc nif_functions[] =
{
    {"hello", 0, hello, 0}
};

ERL_NIF_INIT(Elixir.Eigen.NIFs, nif_functions, NULL, NULL, NULL, NULL)