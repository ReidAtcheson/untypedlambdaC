#include <stdlib.h>
#include <string.h>
#include "purelambda.h"
#include "examples.h"
tagged_term_t lambda_identity(){


  tagged_term_t tmp = 
  {
    .term = {.variable={.name="x"}},
    .tag  = var
  };

  tagged_term_t* term = (tagged_term_t*)malloc(sizeof(tagged_term_t));
  memcpy(term,&tmp,sizeof(tagged_term_t));



  tagged_term_t out = 
  {
    .term = {.Lx_t = {.x={.name="x"}, .t = (struct tagged_term_t*)term}},

    .tag = abst
  };


  return out;

}

tagged_term_t iterated_identities(){
  tagged_term_t tmp = 
  {
    .term = {.variable={.name="x"}},
    .tag  = var
  };

  tagged_term_t* term = (tagged_term_t*)malloc(sizeof(tagged_term_t));
  memcpy(term,&tmp,sizeof(tagged_term_t));



  tagged_term_t out = 
  {
    .term = {.Lx_t = {.x={.name="x"}, .t = (struct tagged_term_t*)term}},

    .tag = abst
  };


  tagged_term_t tmp2 = 
  {
    .term = {.variable={.name="y"}},
    .tag  = var
  };

  tagged_term_t* term2 = (tagged_term_t*)malloc(sizeof(tagged_term_t));
  memcpy(term2,&tmp2,sizeof(tagged_term_t));



  tagged_term_t out2 = 
  {
    .term = {.Lx_t = {.x={.name="y"}, .t = (struct tagged_term_t*)term2}},

    .tag = abst
  };

  tagged_term_t* out22 = (tagged_term_t*)malloc(sizeof(tagged_term_t));
  memcpy(out22,&out2,sizeof(tagged_term_t));
  tagged_term_t* out11 = (tagged_term_t*)malloc(sizeof(tagged_term_t));
  memcpy(out11,&out,sizeof(tagged_term_t));



  tagged_term_t out3 = 
  {
    .term = {.t1_t2 = {.t1 = (struct tagged_term_t*)out22, .t2 = (struct tagged_term_t*)out11}},
    .tag = app
  };





  return out3;


}



