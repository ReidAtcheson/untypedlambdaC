%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "purelambda.h"

void yyerror(const char* s);

extern int yylex(void);
extern int yyparse(void);
extern FILE* yyin;

static tagged_term_t* exp_tree;

%}

%union{
  tagged_term_t* term_val;
}

%token VAR
%token LAM
%token DOT
%token BEGPAR
%token ENDPAR
%token WS

%type <term_val> term


%%

out: term {exp_tree = $<term_val>1}


term: 
    VAR {$$ = $<term_val>1;}
    | BEGPAR LAM VAR DOT term ENDPAR{ tagged_term_t* tmp = term_construct(abst);
                                      tmp->term.Lx_t.x = ($<term_val>3)->term.variable;
                                      tmp->term.Lx_t.t = (struct tagged_term_t*) $<term_val>5;
                                      $<term_val>$ = tmp;
                                    }
    | term WS term{
                    tagged_term_t* tmp = term_construct(app);
                    tmp->term.t1_t2.t1  = (struct tagged_term_t*) $<term_val>1;
                    tmp->term.t1_t2.t2  = (struct tagged_term_t*) $<term_val>3;
                    $<term_val>$ = tmp;
                  }



%%


void yyerror(const char* s){
	printf("Parse error: %s\n",s);
}

tagged_term_t* parse_lambda_exp(const char* filename){
	yyin=fopen(filename,"r");
	if(!yyin){
		fprintf(stderr,"Failed to open .msh file\n");
		return NULL;
	}
	do{
		yyparse();
	}while(!feof(yyin));
	return term_copy(exp_tree);
}
