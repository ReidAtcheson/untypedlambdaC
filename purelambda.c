#include <stdio.h>
#include <assert.h>
#include "purelambda.h"



void print_lambda_term(tagged_term_t* t){
  assert(NULL != t);


  switch(t->tag){
    case var:
      printf("(");
      print_variable(t->term.variable);
      printf(")");
      break;
    case abst:
      printf("(");
      print_abstraction(t->term.Lx_t);
      printf(")");
      break;
    case app:
      printf("(");
      print_application(t->term.t1_t2);
      printf(")");
      break;
  }


}


void print_abstraction(abstraction_t Lx_t){
  printf("\\");
  print_variable(Lx_t.x);
  printf("->");
  print_lambda_term((tagged_term_t*)Lx_t.t);
}


void print_application(application_t t1_t2){
  print_lambda_term((tagged_term_t*)t1_t2.t1);
  printf(" ");
  print_lambda_term((tagged_term_t*)t1_t2.t2);
}


void print_variable(variable_t x){
  printf("%s",x.name);
}
