#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "purelambda.h"


tagged_term_t* normal_order_evaluation(tagged_term_t* tin){
  assert(NULL != tin);
  tagged_term_t* tout = NULL;

  if(is_redex(tin)){
    tout = redex_reduce(tin);
  }
  else{
    switch(tin->tag){
      case var:
        tout = term_copy(tin);
        break;
      case abst:{
        tagged_term_t* tmp = term_construct(abst);
        tmp->term.Lx_t.t = (struct tagged_term_t*) normal_order_evaluation((tagged_term_t*)tin->term.Lx_t.t);
        tmp->term.Lx_t.x = tin->term.Lx_t.x;

        tout = term_copy(tmp);

        term_destruct(tmp);}
        break;
      case app:{
        tagged_term_t* tmp = term_construct(app);
        tmp->term.t1_t2.t1 = (struct tagged_term_t*) normal_order_evaluation((tagged_term_t*)tin->term.t1_t2.t1);
        tmp->term.t1_t2.t2 = (struct tagged_term_t*) normal_order_evaluation((tagged_term_t*)tin->term.t1_t2.t2);

        tout = normal_order_evaluation(tmp);

        term_destruct(tmp);}
        break;
    }
  }


  return tout;


}

tagged_term_t* redex_reduce(tagged_term_t* tin){
  assert(is_redex(tin));

  /*This is essentially a deeper pattern match.*/
  /*In this case we pattern match on a term of form: "(\substvar -> tout) t2" */
  variable_t substvar = ((tagged_term_t*)tin->term.t1_t2.t1)->term.Lx_t.x;
  tagged_term_t* tout = term_copy(
      (tagged_term_t*)((tagged_term_t*)(tin->term.t1_t2.t1))->term.Lx_t.t
      );
  tagged_term_t* t2   = term_copy((tagged_term_t*)tin->term.t1_t2.t2);



  term_var_subst(tout,t2,substvar);







  term_destruct(t2);
  return tout;
}

void term_var_subst(tagged_term_t* tout,tagged_term_t* t2,variable_t substvar){

  switch(tout->tag){
    case var:
      /*If variable matches substvar, replace with term t2.*/
      if(var1_equals_var2(substvar,tout->term.variable)){
        tagged_term_t* tmp = term_copy(t2);
        memcpy(tout,tmp,sizeof(tagged_term_t));
      }
      /*Else do nothing..*/
      break;
    case abst:
      term_var_subst((tagged_term_t*)tout->term.Lx_t.t,t2,substvar);
      break;
    case app:
      term_var_subst((tagged_term_t*)tout->term.t1_t2.t1,t2,substvar);
      term_var_subst((tagged_term_t*)tout->term.t1_t2.t2,t2,substvar);
      break;
  }

}

bool var1_equals_var2(variable_t var1, variable_t var2){
  return !strcmp(var1.name,var2.name);
}

/*A redex is of form: (\x -> t1) t2.*/
bool is_redex(tagged_term_t* t){
  if (app == t->tag){/*Check if outermost term is an application.*/
    if (abst == ((tagged_term_t*)t->term.t1_t2.t1)->tag){ /*If it is, check if left term of application is an abstraction.*/
      return true; /*If both cases are true above, input term is a redex.*/
    }
  }
  return false;
}

tagged_term_t* term_copy(tagged_term_t* tin){
  assert(NULL != tin);

  tagged_term_t* tout = term_construct(tin->tag);

  switch(tin->tag){
    case var:
      memcpy((void*)tout->term.variable.name,(const void*)tin->term.variable.name,MAX_VAR_LEN);
      break;
    case abst:
      tout->term.Lx_t.x = tin->term.Lx_t.x;
      tout->term.Lx_t.t = (struct tagged_term_t*)term_copy((tagged_term_t*)tin->term.Lx_t.t);
      break;
    case app:
      tout->term.t1_t2.t1 = (struct tagged_term_t*)term_copy((tagged_term_t*)tin->term.t1_t2.t1);
      tout->term.t1_t2.t2 = (struct tagged_term_t*)term_copy((tagged_term_t*)tin->term.t1_t2.t2);
      break;
  }

  return tout;
}




tagged_term_t* term_construct(term_tag_t type){
  tagged_term_t* t = (tagged_term_t*) malloc(sizeof(tagged_term_t));
  t->tag = type;
  return t;
}


void term_destruct(tagged_term_t* t){
  assert(NULL != t);
  switch(t->tag){
    case var:
      /*Nothing to be done.*/
      break;
    case abst:
      term_destruct((tagged_term_t*)t->term.Lx_t.t);
      break;
    case app:
      term_destruct((tagged_term_t*)t->term.t1_t2.t1);
      term_destruct((tagged_term_t*)t->term.t1_t2.t2);
      break;
  }
  free(t);
}



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
