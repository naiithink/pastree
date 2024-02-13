#include <string.h>

#include <openssl/sha.h>

#include "../include/dxp/dxp_crypto.h"

int main(int argc, char **argv)
{
    char              *message     = "hello, world";
    const unsigned int message_len = strnlen((const char *) message, PATH_MAX);
    unsigned char     *digest;
    unsigned int       digest_len;
    EVP_MD_CTX        *mdctx = dxp_digest_new_context();

    /* As block */
    dxp_digest_message((const unsigned char *) message, message_len,
                       DXP_DIGEST_ALGO_SHA256, &digest, &digest_len);
    dxp_digest_print(digest, DXP_DIGEST_ALGO_SHA256_LEN, true);

    /* As stream */
    dxp_digest_init(&mdctx, DXP_DIGEST_ALGO_SHA256);
    dxp_digest_update(&mdctx, "hello, ", 7);
    dxp_digest_update(&mdctx, "world", 5);
    dxp_digest_final(&mdctx, DXP_DIGEST_ALGO_SHA256, &digest, &digest_len);
    dxp_digest_cleanup(&mdctx);
    dxp_digest_print(digest, DXP_DIGEST_ALGO_SHA256_LEN, true);

    return EXIT_SUCCESS;
}
