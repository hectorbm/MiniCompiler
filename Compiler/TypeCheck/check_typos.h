#include "../SymbolsTable/symbols_table.h"

#define MAXTYPELEN 5
char * typeCheck(SyntaxTree *st);

static char * BOOL = "bool";
static char * INT = "int";
static char * NA = "NA";