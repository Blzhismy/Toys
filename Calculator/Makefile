.PHONY:clean check

#---- Compiler Methods ---------------------------------------------------------#
WARNOPT= -Wall                   \
		 -Wno-return-type        \
		 -Wno-unused-variable    \
		 -Wno-attributes         \
		 -Werror=uninitialized   \
		 -Wno-reorder            \
		 -Werror=non-virtual-dtor
OPTIMIZE= -O3 
DBGOPT= -g3
CC= g++
STANDARD= -std=c++14
CFLAGS= $(WARNOPT) $(OPTIMIZE) $(DBGOPT) $(SYSTEM_LINK) $(STANDARD)
#---------------------------------------------------------------------------#


#----- File-Resources ------------------------------------------------------#
ITEM_NAME=main
#SRC_POSTFIX=$(shell ls *.cpp &> /dev/null && printf .cpp || printf .c) 
SRC_POSTFIX=.cpp
SRC=$(shell ls *$(SRC_POSTFIX) 2> /dev/null)
OBJ=$(patsubst %$(SRC_POSTFIX),%.o,$(SRC))
LIB=$(shell echo $(SRC) | sed -n 's@$(ITEM_NAME)$(SRC_POSTFIX)@@p' )
HEADIF=$(patsubst %.cpp,%.h,$(LIB))
HEAD=$(shell for H in $(HEADIF); do ls $$H 2>/dev/null; done) 

BIN=$(ITEM_NAME)$(shell echo $(SRC_POSTFIX) | grep '.cpp' &> /dev/null && echo .exe)
#---------------------------------------------------------------------------#


#----- Dependency And Methods ----------------------------------------------#
all:$(BIN)

$(BIN):$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o:%$(SRC_POSTFIX) 
	$(CC) $(CFLAGS) -c $< -o $@
#---------------------------------------------------------------------------#


check:
	echo "SRC_POSTFIX = $(SRC_POSTFIX)"
	echo "SRC = $(SRC)"
	echo "OBJ = $(OBJ)"
	echo "HEADIF = $(HEADIF)"
	echo "HEAD = $(HEAD)"
	echo "BIN = $(BIN)"

clean:
	rm -f $(BIN) $(OBJ)

