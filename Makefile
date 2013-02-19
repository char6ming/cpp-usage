VPATH			= ./

TEST_BIN		= test_cpp_usage

TEST_BIN_SRCS		= test_miscellaneous.cpp
SOURCES			= $(TEST_BIN_SRCS)
OBJECTS			= $(SOURCES:.c=.o)
GEN_BINS		= $(TEST_BIN)

CFLAGS			+= -Wall -I$(VPATH)
#4 debug
CFLAGS			+= -D__DEBUG__ -g
#4 GNU OS
CFLAGS			+= -D_GNU_SOURCE
LDFLAGS			+= -L$(VPATH)
LDFLAGS			+= -lpthread

.PHONY:         all clean

all:            $(GEN_BINS)

clean:
	rm -f $(GEN_BINS)

$(TEST_BIN):	$(TEST_BIN_SRCS:.c=.o)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(TEST_BIN)

