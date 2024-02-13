#ifndef __DXP_CRYPTO_H
#define __DXP_CRYPTO_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <stdbool.h>

/* #include <openssl/bio.h> */
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/sha.h>
/* #include <openssl/ssl.h> */
#include <openssl/opensslv.h>

#define MIN_OPENSSL_VERSION 0x30200010L
#if (OPENSSL_VERSION_NUMBER < MIN_OPENSSL_VERSION)
#error "OpenSSL version not met. Check MIN_OPENSSL_VERSION"
#endif

#define DXP_DIGEST_ALGO_SHA256     EVP_sha256()
#define DXP_DIGEST_ALGO_SHA256_LEN SHA256_DIGEST_LENGTH
#define DXP_DIGEST_ALGO_SHA512     EVP_sha512()
#define DXP_DIGEST_ALGO_SHA512_LEN SHA512_DIGEST_LENGTH

    typedef EVP_MD_CTX dxp_digest_context;

    typedef const EVP_MD *dxp_digest;

    dxp_digest_context *dxp_digest_new_context(void);

    int dxp_digest_init(dxp_digest_context **, dxp_digest);

    int dxp_digest_update(dxp_digest_context **, const void *, size_t);

    int dxp_digest_final(dxp_digest_context **, dxp_digest, unsigned char **,
                         unsigned int *);

    void dxp_digest_cleanup(dxp_digest_context **);

    int dxp_digest_message(const unsigned char *, size_t, dxp_digest,
                           unsigned char **, unsigned int *);

    void dxp_digest_print(unsigned char *, size_t, bool);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DXP_CRYPTO_H */
