#ifndef __LIBCOUPLET_HMAC_H__
#define __LIBCOUPLET_HMAC_H__

#include <stdint.h>

#include "sha1.h"

void HMAC_SHA1(const uint8_t *key, size_t key_len,
	       const uint8_t *text, size_t len,
	       uint8_t digest[SHA1_DIGEST_SIZE]);

#endif /* __LIBCOUPLET_HMAC_H__ */
