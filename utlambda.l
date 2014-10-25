%{
#include "purelambda.h"
#include "utlambda_yac.h"
%}

%%


[a-z] { tagged_term_t* tmp = term_construct(var); 
memcpy(tmp->term.variable.name,yytext,strlen(yytext)); 
yylval.term_val = tmp;
return VAR;}


"\\" {return LAM;}

"."  {return DOT;}

"(" {return BEGPAR;}

")" {return ENDPAR;}

" " {return WS;}
