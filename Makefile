.PHONY: all clean

all: lz4hc

lz4hc: src/main.c lz4/lib/lz4.c lz4/lib/lz4hc.c lz4/lib/lz4.h lz4/lib/lz4hc.h
	$(CC) -o $@ src/main.c lz4/lib/lz4.c lz4/lib/lz4hc.c -Wall -O3 -Ilz4/lib $(CFLAGS)

lz4/lib/%:
	git submodule update --init --recursive

clean:
	rm -f lz4hc
