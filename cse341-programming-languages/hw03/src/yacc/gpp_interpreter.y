%{ 
 //definitions
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>

 char* divideFractions(char* frac1, char* frac2);
 char* multiplyFractions(char* frac1, char* frac2);
 char* subtractFractions(char* frac1, char* frac2);
 char* addFractions(char* frac1, char* frac2);
 
 int calculateGCD(int x, int y);
 void reduceFraction(int *num, int *den);

typedef struct variable {
    char name[20];
    char value[20];
} variable;

// 100 variables
 variable variables[100];
 int variable_count = 0;

// function prototype
typedef struct function {
    char func_name[20];
    char exp_type[20];
} function;

// 100 functions
 function functions[100];
 int function_count = 0;

 int inFunction = 0; // flag to check if we are in a function => for scoping

// symbol table functions
void insertVariable(char* name, char* value);
char* findVariableValue(char* name);
void updateVariableValue (char* name, char* value);
%}

// rules
%union{
char string [20]; // valuef
char name [20]; // identifier
char symbol;
}

/* keywords */
%token <string> KW_EXIT
%token <string> KW_DEF
%token <string> KW_SET

/* operators */
%token <symbol> OP_OP
%token <symbol> OP_CP 
%token <symbol> OP_PLUS
%token <symbol> OP_MINUS
%token <symbol> OP_MULT
%token <symbol> OP_DIV

/* identifier */
%token <name> IDENTIFIER

/* value */
%token <string> VALUEF

%type <string> EXP


// rules
%% 

START:
    EXP START
    | FUNCTION START
    | OP_OP KW_EXIT OP_CP         { printf("Exiting...\n"); exit(0); }
    | SET START
    |
    ;   
EXP: /* An expression always returns a fraction */
      OP_OP OP_PLUS EXP EXP OP_CP   {
        if(inFunction == 0) {
            char exp3_value[20];
            char exp4_value[20];
            strcpy(exp3_value, $3);
            strcpy(exp4_value, $4);

            // if exp is an identifier like x. handle it.
            for(int i = 0; i < variable_count; i++) {
                if(strcmp(variables[i].name, $3) == 0) {
                    strcpy(exp3_value, variables[i].value);
                }
            }
            for(int i = 0; i < variable_count; i++) {
                if(strcmp(variables[i].name, $4) == 0) {
                    strcpy(exp4_value, variables[i].value);
                }
            }
            char* result = addFractions(exp3_value, exp4_value);
            strcpy($$, result);
            printf("%s\n", $$); 
        }
        else {
            strcpy(functions[function_count].exp_type, "add");
        }
    }                          
    | OP_OP OP_MINUS EXP EXP OP_CP  {
        if(inFunction == 0) {
            char exp3_value[20];
            char exp4_value[20];
            strcpy(exp3_value, $3);
            strcpy(exp4_value, $4);

            // if exp is an identifier like x. handle it.
            for(int i = 0; i < variable_count; i++) {
                if(strcmp(variables[i].name, $3) == 0) {
                    strcpy(exp3_value, variables[i].value);
                }
            }
            for(int i = 0; i < variable_count; i++) {
                if(strcmp(variables[i].name, $4) == 0) {
                    strcpy(exp4_value, variables[i].value);
                }
            }
            char* result = subtractFractions(exp3_value, exp4_value);
            strcpy($$, result);
            printf("%s\n", $$); 
        }
        else {
            strcpy(functions[function_count].exp_type, "subtract");
        }
    }
    | OP_OP OP_MULT EXP EXP OP_CP   {
        if(inFunction == 0) {
            char exp3_value[20];
            char exp4_value[20];
            strcpy(exp3_value, $3);
            strcpy(exp4_value, $4);

            // if exp is an identifier like x. handle it.
            for(int i = 0; i < variable_count; i++) {
                if(strcmp(variables[i].name, $3) == 0) {
                    strcpy(exp3_value, variables[i].value);
                }
            }
            for(int i = 0; i < variable_count; i++) {
                if(strcmp(variables[i].name, $4) == 0) {
                    strcpy(exp4_value, variables[i].value);
                }
            }
            char* result = multiplyFractions(exp3_value, exp4_value);
            strcpy($$, result);
            printf("%s\n", $$); 
        }
        else {
            strcpy(functions[function_count].exp_type, "multiply");
        }
    }
    | OP_OP OP_DIV EXP EXP OP_CP    {
        if(inFunction == 0) {
            char exp3_value[20];
            char exp4_value[20];
            strcpy(exp3_value, $3);
            strcpy(exp4_value, $4);

            // if exp is an identifier like x. handle it.
            for(int i = 0; i < variable_count; i++) {
                if(strcmp(variables[i].name, $3) == 0) {
                    strcpy(exp3_value, variables[i].value);
                }
            }
            for(int i = 0; i < variable_count; i++) {
                if(strcmp(variables[i].name, $4) == 0) {
                    strcpy(exp4_value, variables[i].value);
                }
            }
            char* result = divideFractions(exp3_value, exp4_value);
            strcpy($$, result);
            printf("%s\n", $$); 
        }
        else {
            strcpy(functions[function_count].exp_type, "divide");
        }
    }
    | OP_OP IDENTIFIER EXP          
    | OP_OP IDENTIFIER EXP EXP       
    | OP_OP IDENTIFIER EXP EXP EXP 
    //function part
    | OP_OP IDENTIFIER EXP EXP OP_CP {
        char exp3_value[20];
        char exp4_value[20];
        strcpy(exp3_value, $3);
        strcpy(exp4_value, $4);

        // if exp is an identifier like x. handle it.
        for(int i = 0; i < variable_count; i++) {
            if(strcmp(variables[i].name, $3) == 0) {
                strcpy(exp3_value, variables[i].value);
            }
        }
        for(int i = 0; i < variable_count; i++) {
            if(strcmp(variables[i].name, $4) == 0) {
                strcpy(exp4_value, variables[i].value);
            }
        }

        // calculate the result based on the function's exp_type
        char exp_type[20];
        for(int i = 0; i < function_count; i++) {
            if(strcmp(functions[i].func_name, $2) == 0) {
                strcpy(exp_type, functions[i].exp_type);
            }
        }
        if(strcmp(exp_type, "add") == 0) {
            char* result = addFractions(exp3_value, exp4_value);
            strcpy($$, result);
            printf("%s\n", $$); 
        }
        else if(strcmp(exp_type, "subtract") == 0) {
            char* result = subtractFractions(exp3_value, exp4_value);
            strcpy($$, result);
            printf("%s\n", $$); 
        }
        else if(strcmp(exp_type, "multiply") == 0) {
            char* result = multiplyFractions(exp3_value, exp4_value);
            strcpy($$, result);
            printf("%s\n", $$); 
        }
        else if(strcmp(exp_type, "divide") == 0) {
            char* result = divideFractions(exp3_value, exp4_value);
            strcpy($$, result);
            printf("%s\n", $$); 
        }
    }
    | IDENTIFIER {
        // if the variable exists do nothing else add it to the symbol table
        int exists = 0; 
        for(int i = 0; i < variable_count; i++) {
            if(strcmp(variables[i].name, $1) == 0) {
                exists = 1;
                break;
            }
        }
        if(exists == 0) {
            insertVariable($1, "0b1");
        }
    }                    
    | VALUEF  
    |
    ;

/* 
 Parameter passing by value – Function definition returns a function value – Function application will return the value of the 
 expression evaluated
*/
FUNCTION:
    OP_OP KW_DEF IDENTIFIER EXP OP_CP {
        printf("Function %s defined\n", $3);
    }
    | OP_OP KW_DEF IDENTIFIER IDENTIFIER EXP OP_CP
    {
        printf("Function %s defined\n", $3);
    }
    | OP_OP KW_DEF IDENTIFIER IDENTIFIER IDENTIFIER EXP OP_CP 
    {
        inFunction = 0;
        strcpy(functions[function_count].func_name, $3);
        function_count++;
        printf("Function %s defined\n", $3);
    }
    ;

SET:
    OP_OP KW_SET IDENTIFIER EXP OP_CP {
        updateVariableValue($3, $4);
        printf("Variable %s set to %s\n", $3, $4);
    }
    ;

%%

int main() {
    yyparse();
    return 0;
}

int yyerror(char *s) {
    fprintf(stderr, "error: %s\n", s);
    return 0;
}

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}
// Renamed and reordered gcd function
int calculateGCD(int x, int y) {
    int temp;
    while (y != 0) {
        temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

// Renamed and reordered simplify_fraction function
void reduceFraction(int *num, int *den) {
    int gcd = calculateGCD(*num, *den);
    *num /= gcd;
    *den /= gcd;
}

// Renamed variables and function names in add function
char* addFractions(char* fraction1, char* fraction2) {
    int n1, d1, n2, d2;
    sscanf(fraction1, "%db%d", &n1, &d1);
    sscanf(fraction2, "%db%d", &n2, &d2);

    int denomCommon = d1 * d2;
    int numResult = (n1 * d2) + (n2 * d1);

    reduceFraction(&numResult, &denomCommon);

    char* sum = (char*)malloc(20 * sizeof(char));
    if (sum != NULL) {
        sprintf(sum, "%db%d", numResult, denomCommon);
    }
    return sum;
}

// Renamed variables and function names in subtract function
char* subtractFractions(char* fraction1, char* fraction2) {
    int n1, d1, n2, d2;
    sscanf(fraction1, "%db%d", &n1, &d1);
    sscanf(fraction2, "%db%d", &n2, &d2);

    int denomCommon = d1 * d2;
    int numResult = (n1 * d2) - (n2 * d1);

    reduceFraction(&numResult, &denomCommon);

    char* difference = (char*)malloc(20 * sizeof(char));
    if (difference != NULL) {
        sprintf(difference, "%db%d", numResult, denomCommon);
    }
    return difference;
}

// Renamed variables and function names in multiply function
char* multiplyFractions(char* fraction1, char* fraction2) {
    int n1, d1, n2, d2;
    sscanf(fraction1, "%db%d", &n1, &d1);
    sscanf(fraction2, "%db%d", &n2, &d2);

    int numResult = n1 * n2;
    int denomResult = d1 * d2;

    reduceFraction(&numResult, &denomResult);

    char* product = (char*)malloc(20 * sizeof(char));
    if (product != NULL) {
        sprintf(product, "%db%d", numResult, denomResult);
    }
    return product;
}

// Renamed variables and function names in divide function
char* divideFractions(char* fraction1, char* fraction2) {
    int n1, d1, n2, d2;
    sscanf(fraction1, "%db%d", &n1, &d1);
    sscanf(fraction2, "%db%d", &n2, &d2);

    int numResult = n1 * d2;
    int denomResult = d1 * n2;

    reduceFraction(&numResult, &denomResult);

    char* quotient = (char*)malloc(20 * sizeof(char));
    if (quotient != NULL) {
        sprintf(quotient, "%db%d", numResult, denomResult);
    }
    return quotient;
}

// Renamed and reordered symbol table functions
void insertVariable(char* name, char* value) {
    strcpy(variables[variable_count].name, name);
    strcpy(variables[variable_count].value, value);
    variable_count++;
}

char* findVariableValue(char* name) {
    for (int i = 0; i < variable_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].value;
        }
    }
    return "0b1";
}

void updateVariableValue(char* name, char* value) {
    for (int i = 0; i < variable_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            strcpy(variables[i].value, value);
            return;
        }
    }
    insertVariable(name, value);
}
