CC := g++

CHIPM8_INCLUDE := include
BOOST_LIBRARY := libs/boost_1_72_0

SRC := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)

OBJS := $(SRC:.cpp=.o)

TESTS_SRC := $(wildcard tests/*.cpp) $(wildcard tests/*/*.cpp)

bin/Chip8.a: ${OBJS}
	ar rvs $@ $^

%.o: %.cpp
	$(CC) -I ${CHIPM8_INCLUDE} -c $^ -o $@


test: ${TESTS_SRC} bin/Chip8.a
	$(CC) -I ${BOOST_LIBRARY} -I ${CHIPM8_INCLUDE} $^ -o $@
	./test

.PHONY: clean

clean:
	rm ${OBJS}
	rm bin/*.a
	rm test
