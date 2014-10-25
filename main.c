#include <stdio.h>
#include "purelambda.h"
#include "examples.h"
tagged_term_t* parse_lambda_exp(const char* filename);

int main(int argc,char** argv){

  tagged_term_t* in = NULL;
  if(argc==1){
    fprintf(stderr,"Supply filename to lambda expression\n");
    return 1;
  }
  else{
    in = parse_lambda_exp(argv[1]);
  }

  printf("Input lambda expression:\n");
  print_lambda_term(in);
  printf("\n");

  printf("Lambda expression in normal form:\n");
  tagged_term_t* out = normal_order_evaluation(in);
  print_lambda_term(out);
  printf("\n");
  term_destruct(in);
  term_destruct(out);
  return 0;

}
