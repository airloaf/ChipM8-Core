CC := g++

CHIPM8_INCLUDE := include
BOOST_LIBRARY := libs/boost_1_72_0

TESTS_SRC := tests/Memory/Reading.cpp tests/Bus/RegisterMemory.cpp

bin/Chip8.a: objs/Bus.o objs/Memory.o
	ar rvs $@ $^

objs/Bus.o: src/Bus/Bus.cpp
	$(CC) -I ${CHIPM8_INCLUDE} -c $^ -o $@

objs/Memory.o: src/Devices/Memory.cpp
	$(CC) -I ${CHIPM8_INCLUDE} -c $^ -o $@

test: tests/TestRunner.cpp bin/Chip8.a
	$(CC) -I ${BOOST_LIBRARY} -I ${CHIPM8_INCLUDE} $(TESTS_SRC) $^ -o $@
	./test

.PHONY: clean

clean:
	rm objs/*.o
	rm bin/*.a
	rm test
