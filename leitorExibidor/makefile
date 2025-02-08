all: main.c reader.o header.o bytecode.o attribute.o output.o instructions.o arithmetic.o conversions.o array.o interpreter.o stores.o loads.o stackops.o
	gcc -m32 ./*.o ./main.c -o main.exe -lm

reader.o: reader.c reader.h types.h
	gcc -m32 -c reader.c -o reader.o

header.o: header.c header.h types.h reader.h
	gcc -m32 -c header.c -o header.o

bytecode.o: bytecode.c bytecode.h types.h reader.h instructions.h
	gcc -m32 -c bytecode.c -o bytecode.o

attribute.o: attribute.c attribute.h types.h reader.h
	gcc -m32 -c attribute.c -o attribute.o

instructions.o: instructions.c instructions.h types.h arithmetic.h
	gcc -m32 -c instructions.c -o instructions.o

output.o: output.c output.h types.h reader.h bytecode.h header.h
	gcc -m32 -c output.c -o output.o

arithmetic.o: arithmetic.c arithmetic.h types.h instructions.h conversions.h
	gcc -m32 -c arithmetic.c -lm -o arithmetic.o
	
conversions.o: conversions.c conversions.h instructions.h
	gcc -m32 -c conversions.c -o conversions.o

array.o: array.c array.h types.h instructions.h
	gcc -m32 -c array.c -o array.o

interpreter.o: interpreter.c interpreter.h types.h instructions.h
	gcc -m32 -c interpreter.c -o interpreter.o

stores.o: stores.c stores.h types.h instructions.h
	gcc -m32 -c stores.c -o stores.o

loads.o: loads.c loads.h types.h instructions.h
	gcc -m32 -c loads.c -o loads.o

stackops.o: stackops.c stackops.h types.h instructions.h
	gcc -m32 -c stackops.c -o stackops.o

clean:
	rm -rf *.exe ./**/*.o *.o out.txt
