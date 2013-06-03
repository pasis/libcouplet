/* hmac.c
 * libcouplet - fork of libstrophe, XMPP client library
 * HMAC-SHA1 implementation according to RFC2104
 *
 * Copyright (C) 2013 Dmitry Podgorny <pasis.ua@gmail.com>
 *
 *  This software is provided AS-IS with no warranty, either express
 *  or implied.
 *
 *  This software is distributed under license and may not be copied,
 *  modified or distributed except as expressly authorized under the
 *  terms of the license contained in the file LICENSE.txt in this
 *  distribution.
 */

/** @file
 *  HMAC-SHA1 implementation.
 */

#include <stdint.h>
#include <string.h>

#include "sha1.h"
#include "hmac.h"

#define BLOCK_SIZE 64
#if BLOCK_SIZE < SHA1_DIGEST_SIZE
#error BLOCK_SIZE must not be less than SHA1_DIGEST_SIZE
#endif

static const uint64_t ipad = 0x3636363636363636;
static const uint64_t opad = 0x5C5C5C5C5C5C5C5C;

void HMAC_SHA1(const uint8_t *key, size_t key_len,
	       const uint8_t *text, size_t len,
	       uint8_t digest[SHA1_DIGEST_SIZE])
{
	uint64_t key_pad[BLOCK_SIZE / sizeof(uint64_t)];
	uint64_t key_ipad[BLOCK_SIZE / sizeof(uint64_t)];
	uint64_t key_opad[BLOCK_SIZE / sizeof(uint64_t)];
	uint8_t sha_digest[SHA1_DIGEST_SIZE];
	int i;
	SHA1_CTX ctx;

	memset(key_pad, 0, sizeof(key_pad));
	if (key_len <= BLOCK_SIZE) {
		memcpy(key_pad, key, key_len);
	} else {
		/* according to RFC2104 */
		SHA1(key, key_len, (uint8_t *)key_pad);
	}

	for (i = 0; i < (BLOCK_SIZE / sizeof(uint64_t)); i++) {
		key_ipad[i] = key_pad[i] ^ ipad;
		key_opad[i] = key_pad[i] ^ opad;
	}

	SHA1_Init(&ctx);
	SHA1_Update(&ctx, (uint8_t *)key_ipad, BLOCK_SIZE);
	SHA1_Update(&ctx, text, len);
	SHA1_Final(&ctx, sha_digest);

	SHA1_Init(&ctx);
	SHA1_Update(&ctx, (uint8_t *)key_opad, BLOCK_SIZE);
	SHA1_Update(&ctx, sha_digest, SHA1_DIGEST_SIZE);
	SHA1_Final(&ctx, digest);
}

/* TODO: test vectors from RFC 6070 */
