all: main.c reader.o header.o bytecode.o attributes.o output.o
	gcc ./*.o ./main.c -o main.exe

reader.o: reader.c reader.h types.h
	gcc -c reader.c -o reader.o

header.o: header.c header.h types.h reader.h
	gcc -c header.c -o header.o

bytecode.o: bytecode.c bytecode.h types.h reader.h instructions.h
	gcc -c bytecode.c -o bytecode.o

attributes.o: attributes.c attributes.h types.h reader.h
	gcc -c attributes.c -o attributes.o

clean:
	rm -rf *.exe ./**/*.o *.o
