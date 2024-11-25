%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gpp_interpreter.tab.h"
extern int inFunction;
%}


%%

        /* operators */
[+]           { return(OP_PLUS);}
[/]           { return(OP_DIV);}
[)]           { return(OP_CP);}
[-]           { return(OP_MINUS);}
[*]           { return(OP_MULT);}
[(]           { return(OP_OP);}
[,]           { }




        /* keywords */
and           {     }
or            {       }
not           {      }
exit          {  return KW_EXIT; }
if            {       }
def           {inFunction = 1; return KW_DEF; }
for           {     }
concat        {   }
append        {   }
set           {printf("KW_SET\n"); return KW_SET; }
less          {     }
true          { printf("KW_TRUE\n");    }
equal         {    }
list          {     }
display       { printf("KW_DISPLAY\n"); }
nil           {      }   
load          { printf("KW_LOAD\n");    }
false         { printf("KW_FALSE\n");   }


        /* literal comment identifier */
[0-9]+b[0-9]+           {strcpy(yylval.string, yytext); return VALUEF;}

[;]{2}.*                {}

[a-zA-Z][a-zA-Z0-9]*    {  strcpy(yylval.name, yytext);  return IDENTIFIER;}

[ \t\n]+                { /* ignore tab, whitespace and newline */ ;}

[0-9]+[a-zA-Z]+         { printf("SYNTAX_ERROR an identifier should start with a letter.\n");}

.                       { if((int)yytext[0] != 13) { /* don't print carriage return */
                            printf("SYNTAX_ERROR %s cannot be tokenized\n", yytext);
                          }
                        }

%%
/* */
int yywrap() {}
