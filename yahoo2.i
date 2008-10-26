%module yahoo2

%{
#include <yahoo2.h>
#define USE_STRUCT_CALLBACKS 1
#include <yahoo2_callbacks.h>
%}

#include <yahoo2.h>

void yahoo_register_callbacks(struct yahoo_callbacks *cb);

