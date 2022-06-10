// SPDX-License-Identifier: GPL-2.0
/*
 * Crypto acceleration support for Rockchip Crypto V3
 *
 * Copyright (c) 2022, Rockchip Electronics Co., Ltd
 *
 * Author: Lin Jinhan <troy.lin@rock-chips.com>
 *
 */

#include "rk_crypto_core.h"
#include "rk_crypto_v3.h"
#include "rk_crypto_v3_reg.h"

static const char * const crypto_v3_rsts[] = {
	 "crypto-rst",
};

static struct rk_crypto_algt *crypto_v3_algs[] = {
	 &rk_v3_ecb_sm4_alg,		 /* ecb(sm4) */
	 &rk_v3_cbc_sm4_alg,		 /* cbc(sm4) */
	 &rk_v3_xts_sm4_alg,		 /* xts(sm4) */
	 &rk_v3_cfb_sm4_alg,		 /* cfb(sm4) */
	 &rk_v3_ofb_sm4_alg,		 /* ofb(sm4) */
	 &rk_v3_ctr_sm4_alg,		 /* ctr(sm4) */

	 &rk_v3_ecb_aes_alg,		 /* ecb(aes) */
	 &rk_v3_cbc_aes_alg,		 /* cbc(aes) */
	 &rk_v3_xts_aes_alg,		 /* xts(aes) */
	 &rk_v3_cfb_aes_alg,		 /* cfb(aes) */
	 &rk_v3_ofb_aes_alg,		 /* ofb(aes) */
	 &rk_v3_ctr_aes_alg,		 /* ctr(aes) */

	 &rk_v3_ecb_des_alg,		 /* ecb(des) */
	 &rk_v3_cbc_des_alg,		 /* cbc(des) */
	 &rk_v3_cfb_des_alg,		 /* cfb(des) */
	 &rk_v3_ofb_des_alg,		 /* ofb(des) */

	 &rk_v3_ecb_des3_ede_alg,	 /* ecb(des3_ede) */
	 &rk_v3_cbc_des3_ede_alg,	 /* cbc(des3_ede) */
	 &rk_v3_cfb_des3_ede_alg,	 /* cfb(des3_ede) */
	 &rk_v3_ofb_des3_ede_alg,	 /* ofb(des3_ede) */

	 &rk_v3_ahash_sha1,		 /* sha1 */
	 &rk_v3_ahash_sha224,		 /* sha224 */
	 &rk_v3_ahash_sha256,		 /* sha256 */
	 &rk_v3_ahash_sha384,		 /* sha384 */
	 &rk_v3_ahash_sha512,		 /* sha512 */
	 &rk_v3_ahash_md5,		 /* md5 */
	 &rk_v3_ahash_sm3,		 /* sm3 */

	 &rk_v3_hmac_sha1,		 /* hmac(sha1) */
	 &rk_v3_hmac_sha256,		 /* hmac(sha256) */
	 &rk_v3_hmac_sha512,		 /* hmac(sha512) */
	 &rk_v3_hmac_md5,		 /* hmac(md5) */
	 &rk_v3_hmac_sm3,		 /* hmac(sm3) */

	 /* Shared v2 version implementation */
	 &rk_v2_asym_rsa,		 /* rsa */
};

int rk_hw_crypto_v3_init(struct device *dev, void *hw_info)
{
	int err = 0;
	struct rk_hw_crypto_v3_info *info =
		(struct rk_hw_crypto_v3_info *)hw_info;

	info->desc = dma_alloc_coherent(dev,
					sizeof(struct crypto_lli_desc),
					&info->desc_dma,
					GFP_KERNEL);
	if (!info->desc) {
		err = -ENOMEM;
		goto end;
	}

end:
	return err;
}

void rk_hw_crypto_v3_deinit(struct device *dev, void *hw_info)
{
	struct rk_hw_crypto_v3_info *info =
		(struct rk_hw_crypto_v3_info *)hw_info;

	if (info && info->desc)
		dma_free_coherent(dev, sizeof(struct crypto_lli_desc),
				  info->desc, info->desc_dma);
}

const char * const *rk_hw_crypto_v3_get_rsts(uint32_t *num)
{
	*num = ARRAY_SIZE(crypto_v3_rsts);

	return crypto_v3_rsts;
}

struct rk_crypto_algt **rk_hw_crypto_v3_get_algts(uint32_t *num)
{
	*num = ARRAY_SIZE(crypto_v3_algs);

	return crypto_v3_algs;
}
