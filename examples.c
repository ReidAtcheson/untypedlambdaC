#include <stdlib.h>
#include <string.h>
#include "purelambda.h"
#include "examples.h"
tagged_term_t lambda_identity(){


  tagged_term_t tmp = 
  {
    .term = {.variable={.debrujin=1}},
    .tag  = var
  };

  tagged_term_t* term = (tagged_term_t*)malloc(sizeof(tagged_term_t));
  memcpy(term,&tmp,sizeof(tagged_term_t));



  tagged_term_t out = 
  {
    .term = {.Lx_t = {.x={.debrujin=1}, .t = (struct tagged_term_t*)term}},

    .tag = abst
  };


  return out;

}



