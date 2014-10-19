#include <stdio.h>
#include "purelambda.h"
#include "examples.h"

int main(int argc,char** argv){

  tagged_term_t t = lambda_identity();
  tagged_term_t* t2 = term_copy(&t);
  print_lambda_term(&t);
  printf("\n");
  print_lambda_term(t2);
  printf("\n");


  if(is_redex(t2)){
    printf("Is redex\n");
  }
  else{
    printf("Is not redex\n");
  }



  term_destruct(t2);
  return 0;
}
