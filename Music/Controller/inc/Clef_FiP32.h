/*
 * Copyright (c) 2019, Strifus
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the "{ORGANIZATION_NAME}" nor
 *     the names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "{ORGANIZATION_NAME}" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef CLEF_FIP32_H
#define CLEF_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(CLEF_FIP32_ISLINKED)
#define CLEF_FIP32_ID ((uint16)48002)

typedef struct {
    uint16          ID;
    bool            *Start;
    int32           AO;
    int32           CO;
    int32           clef_info;
    bool            start_old;
} CLEF_FIP32;

#define CLEF_FIP32_FUNCTIONS { \
    CLEF_FIP32_ID, \
    (void (*)(void*))Clef_FiP32_Update, \
    (void (*)(void*))Clef_FiP32_Init, \
    (tLoadImplementationParameter)Clef_FiP32_Load, \
    (tSaveImplementationParameter)Clef_FiP32_Save, \
    (void* (*)(const void*, uint16))Clef_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Clef_FiP32_Update(CLEF_FIP32 *pTClef_FiP32);
void Clef_FiP32_Init(CLEF_FIP32 *pTClef_FiP32);
uint8 Clef_FiP32_Load(const CLEF_FIP32 *pTClef_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 Clef_FiP32_Save(CLEF_FIP32 *pTClef_FiP32, const uint8 data[], uint16 dataLength);
void* Clef_FiP32_GetAddress(const CLEF_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
