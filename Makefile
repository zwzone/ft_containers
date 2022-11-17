CCW		:= c++ -Wall -Wextra -Werror -std=c++98
SRC		:= test.cpp
PRG		:= test

all : ${PRG}

${PRG} : ${SRC}
	${CCW} ${SRC} -o ${PRG}

clean :
	rm -f ${PRG}

re : clean all

.PHONY: clean
