CC=gcc

compiler:  compile.o SyntaxTree/syntax_tree.o LexYacc/y.tab.o LexYacc/lex.yy.o SymbolsTable/symbols_table.o TypeCheck/check_typos.o CodeGenerator/code_generator.o

		$(CC) -o compile compile.o SyntaxTree/syntax_tree.o LexYacc/y.tab.o LexYacc/lex.yy.o SymbolsTable/symbols_table.o TypeCheck/check_typos.o CodeGenerator/code_generator.o