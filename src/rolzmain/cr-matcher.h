/*
 * Copyright (C) 2011-2012 by Zhang Li <RichSelian at gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#ifndef HEADER_CR_MATCHER_H
#define HEADER_CR_MATCHER_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* rolz parameters */
#define M_rolz_buckets          262144
#define M_rolz_indices          64
#define M_rolz_indices_short    16
#define M_rolz_minlength        5
#define M_rolz_maxlength        255

extern int flexible_parsing;
extern int using_ctx4;

typedef struct matcher_t {
    uint32_t m_context;
    struct {
        uint32_t m_head;
        uint32_t m_item[M_rolz_indices];
        uint8_t  m_hash[M_rolz_indices];
    }* m_table;

    uint32_t m_short_table[256][M_rolz_indices_short];
    uint8_t  m_short_context;
} matcher_t;

typedef struct matcher_ret_t {
    uint32_t m_idx;
    uint32_t m_len;
} matcher_ret_t;

int matcher_init(matcher_t* matcher);
int matcher_free(matcher_t* matcher);
int matcher_update(matcher_t* matcher, unsigned char* data, uint32_t pos, int encode);
int matcher_getpos(matcher_t* matcher, uint32_t idx);

matcher_ret_t matcher_lookup(matcher_t* matcher, unsigned char* data, uint32_t pos);

#endif
