#include "erl_nif.h"
#include "tea.h"

static ERL_NIF_TERM tea_encrypt(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]){
	char str[512];
	char key[512];
	unsigned char res[512];
	int strlen = 0;
	int reslen = 0;
	strlen = enif_get_string(env, argv[0], (char*)str, 512, ERL_NIF_LATIN1);
	if (!strlen) {
		return enif_make_tuple2(env, enif_make_atom(env, "error"), enif_make_atom(env, "invalid_str"));
	}
	if (!enif_get_string(env, argv[1], (char*)key, 512, ERL_NIF_LATIN1)) {
		return enif_make_tuple2(env, enif_make_atom(env, "error"), enif_make_atom(env, "invalid_key"));
	}
	symmetry_encrypt(str,strlen,key,res,&reslen);
    return enif_make_string_len(env, (const char*)res,reslen, ERL_NIF_LATIN1);
}

static int
load(ErlNifEnv* env, void** priv, ERL_NIF_TERM info)
{
    return 0;
}

static int
reload(ErlNifEnv* env, void** priv, ERL_NIF_TERM info)
{
    return 0;
}

static int
upgrade(ErlNifEnv* env, void** priv, void** old_priv, ERL_NIF_TERM info)
{
    return 0;
}

static void
unload(ErlNifEnv* env, void* priv)
{
    return;
}

static ErlNifFunc funcs[] =
{
    {"encrypt", 2, tea_encrypt},
};

ERL_NIF_INIT(etea, funcs, &load, &reload, &upgrade, &unload);
