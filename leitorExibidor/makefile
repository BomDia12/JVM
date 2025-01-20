all: main.c reader.o header.o bytecode.o attribute.o output.o instructions.o
	gcc ./*.o ./main.c -o main.exe

reader.o: reader.c reader.h types.h
	gcc -c reader.c -o reader.o

header.o: header.c header.h types.h reader.h
	gcc -c header.c -o header.o

bytecode.o: bytecode.c bytecode.h types.h reader.h instructions.h
	gcc -c bytecode.c -o bytecode.o

attribute.o: attribute.c attribute.h types.h reader.h
	gcc -c attribute.c -o attribute.o

instructions.o: instructions.c instructions.h types.h
	gcc -c instructions.c -o instructions.o

output.o: output.c output.h types.h reader.h bytecode.h header.h
	gcc -c output.c -o output.o

clean:
	rm -rf *.exe ./**/*.o *.o out.txt
