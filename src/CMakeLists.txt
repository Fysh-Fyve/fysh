add_library (
	compyle
	Compyler/Compyler.cc
	Compyler/Compyler.h
	Compyler/Expressions.cc
	Compyler/Statements.cc
	Compyler/Variable.h
)

add_library (
	common
	Lexer/Fysh/Fysh.cc
	Lexer/Fysh/Fysh.h
	Lexer/Fysh/Species.h
	Lexer/FyshChar.h
	Lexer/Lexer.cc
	Lexer/Lexer.h
	Parser/AST/AST.cc
	Parser/AST/AST.h
	Parser/AST/Box.h
	Parser/Parser.cc
	Parser/Parser.h
)
