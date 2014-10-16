#ifndef PURELAMBDA_H_
#define PURELAMBDA_H_


typedef enum{
  var,/*Variable.*/
  abst,/*Abstraction.*/
  app/*Application.*/
}term_tag_t;


typedef struct{
  char name[256];
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



#endif
