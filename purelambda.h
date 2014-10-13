#ifndef PURELAMBDA_H_
#define PURELAMBDA_H_


typedef enum{
  var,/*Variable.*/
  abs,/*Abstraction.*/
  app/*Application.*/
}term_tag_t;


typedef struct{
  int debrujin;
}variable_t;

typedef struct{
  variable_t x;
  struct term_t* t;
}abstraction_t;

typedef struct{
  struct term_t* t1;
  struct term_t* t2;
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


#endif
