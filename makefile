OBJECTS = cbeast.o lexer.o parser.o interpret.o

cbeast : $(OBJECTS)
	gcc -o cbeast $(OBJECTS)

cbeast.o : headers/cbeast.h
lexer.o : headers/lexer.h headers/tokentypeEnum.h
parser.o : headers/parser.h
interpret.o : headers/interpret.h

.PHONY : clean
clean:
	rm cbeast $(OBJECTS)