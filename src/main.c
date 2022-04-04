#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lz4.h"
#include "lz4hc.h"

int main(void)
{
    void *inbuf = NULL;
    size_t sz = 0x8000;
    size_t len = 0;
    while(1)
    {
        sz *= 2;
        inbuf = realloc(inbuf, sz);
        if(!inbuf)
        {
            fprintf(stderr, "realloc: %s\n", strerror(errno));
            return -1;
        }
        size_t want = sz - len;
        size_t have = fread((char*)inbuf + len, 1, sz - len, stdin);
        len += have;
        if(have < want)
        {
            if(feof(stdin))
            {
                break;
            }
            fprintf(stderr, "fread: %s\n", strerror(errno));
            return -1;
        }
    }

    if(len > LZ4_MAX_INPUT_SIZE)
    {
        fprintf(stderr, "Input too large\n");
        return -1;
    }

    size_t outsz = LZ4_COMPRESSBOUND(len);
    void *outbuf = malloc(outsz);
    if(!outbuf)
    {
        fprintf(stderr, "malloc: %s\n", strerror(errno));
        return -1;
    }

    int outlen = LZ4_compress_HC(inbuf, outbuf, (int)len, (int)outsz, LZ4HC_CLEVEL_MAX);
    if(!outlen)
    {
        fprintf(stderr, "lz4 error\n");
        return -1;
    }

    size_t written = fwrite(outbuf, 1, outlen, stdout);
    if(written != outlen)
    {
        fprintf(stderr, "fwrite: %s\n", strerror(errno));
        return -1;
    }

    fprintf(stderr, "Compressed 0x%zx bytes to 0x%llx bytes\n", len, (unsigned long long)outlen);
    return 0;
}
