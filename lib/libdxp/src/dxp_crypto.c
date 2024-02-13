#include "../include/dxp/dxp_common.h"

#include "../include/dxp/dxp_crypto.h"

dxp_digest_context *dxp_digest_new_context(void) { return EVP_MD_CTX_new(); }

int dxp_digest_init(dxp_digest_context **digest_context, dxp_digest algo)
{
    __DXP_ASSERT_NULL_RET(digest_context, __DXP_STATUS_FAILURE);
    __DXP_ASSERT_NULL_RET(*digest_context, __DXP_STATUS_FAILURE);

    /* Load the human readable error strings for libcrypto */
    /* ERR_load_crypto_strings(); */

    /* Load all digest and cipher algos */
    /* OpenSSL_add_all_algorithms(); */

    if (EVP_DigestInit_ex(*digest_context, algo, NULL) != 1)
        return __DXP_STATUS_FAILURE;

    return __DXP_STATUS_SUCCESS;
}

int dxp_digest_update(dxp_digest_context **digest_context, const void *message,
                      size_t message_len)
{
    __DXP_ASSERT_NULL_RET(digest_context, __DXP_STATUS_FAILURE);
    __DXP_ASSERT_NULL_RET(*digest_context, __DXP_STATUS_FAILURE);

    if (EVP_DigestUpdate(*digest_context, message, message_len) != 1)
        return __DXP_STATUS_FAILURE;

    return __DXP_STATUS_SUCCESS;
}

int dxp_digest_final(dxp_digest_context **digest_context, dxp_digest algo,
                     unsigned char **digest, unsigned int *digest_len)
{
    __DXP_ASSERT_NULL_RET(digest_context, __DXP_STATUS_FAILURE);
    __DXP_ASSERT_NULL_RET(*digest_context, __DXP_STATUS_FAILURE);

    if ((*digest = OPENSSL_malloc(EVP_MD_size(algo))) == NULL)
        return __DXP_STATUS_FAILURE;

    if (EVP_DigestFinal_ex(*digest_context, *digest, digest_len) != 1)
        return __DXP_STATUS_FAILURE;

    return __DXP_STATUS_SUCCESS;
}

void dxp_digest_cleanup(dxp_digest_context **digest_context)
{
    EVP_MD_CTX_free(*digest_context);

    /* Remove all digests and ciphers */
    EVP_cleanup();

    /* Prevent leaks when make use of BIO (low level API) */
    CRYPTO_cleanup_all_ex_data();

    /* Remove error strings */
    ERR_free_strings();
}

int dxp_digest_message(const unsigned char *message, size_t message_len,
                       dxp_digest algo, unsigned char **digest,
                       unsigned int *digest_len)
{
    dxp_digest_context *digest_context;

    if ((digest_context = dxp_digest_new_context()) == NULL)
        return __DXP_STATUS_FAILURE;

    if (dxp_digest_init(&digest_context, algo) != __DXP_STATUS_SUCCESS)
        return __DXP_STATUS_FAILURE;

    if (dxp_digest_update(&digest_context, message, message_len) !=
        __DXP_STATUS_SUCCESS)
        return __DXP_STATUS_FAILURE;

    if (dxp_digest_final(&digest_context, algo, digest, digest_len) !=
        __DXP_STATUS_FAILURE)
        return __DXP_STATUS_FAILURE;

    dxp_digest_cleanup(&digest_context);

    return __DXP_STATUS_SUCCESS;
}

void dxp_digest_print(unsigned char *digest, size_t digest_len, bool newline)
{
    for (int i = 0; i < digest_len; i++)
        printf("%02x", digest[i]);

    if (newline == true)
        printf("\n");
}
