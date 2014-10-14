#include "purelambda.h"
#include "examples.h"

int main(int argc,char** argv){

  tagged_term_t t = lambda_identity();
  print_lambda_term(&t);


  return 0;
}
