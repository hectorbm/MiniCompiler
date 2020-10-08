#include "../Symbols_Table/symbols_table.h"

#define MAXTYPELEN 5
char * check_typos(SyntaxTree *st);

static char * BOOL = "bool";
static char * INT = "int";
static char * NA = "NA";