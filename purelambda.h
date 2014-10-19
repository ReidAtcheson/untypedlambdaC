#ifndef PURELAMBDA_H_
#define PURELAMBDA_H_

#define MAX_VAR_LEN 256

#include <stdbool.h>


typedef enum{
  var,/*Variable.*/
  abst,/*Abstraction.*/
  app/*Application.*/
}term_tag_t;


typedef struct{
  char name[MAX_VAR_LEN];
}variable_t;

typedef struct{
  variable_t x;
  struct tagged_term_t* t;
}abstraction_t;

typedef struct{
  struct tagged_term_t* t1;
  struct tagged_term_t* t2;
}application_t;


typedef union{
  variable_t variable;
  abstraction_t Lx_t;
  application_t t1_t2;
} term_t;

typedef struct{
  term_t term;
  term_tag_t tag;
} tagged_term_t;




void print_lambda_term(tagged_term_t* t);
void print_abstraction(abstraction_t Lx_t);
void print_application(application_t t1_t2);
void print_variable(variable_t x);


tagged_term_t* redex_reduce(tagged_term_t* t);
void term_var_subst(tagged_term_t* tout,tagged_term_t* t2,variable_t substvar);
bool var1_equals_var2(variable_t var1, variable_t var2);
bool is_redex(tagged_term_t* t);


tagged_term_t* term_copy(tagged_term_t* t);
tagged_term_t* term_construct(term_tag_t type);
void term_destruct(tagged_term_t* t);




#endif
