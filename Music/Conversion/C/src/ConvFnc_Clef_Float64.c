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
#include "ConvFnc_Clef_Float64.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* USERCODE-END:PreProcessor                                                                                          */

extern uint8 MaskParamBuffer[];
extern uint8 ImplParamBuffer[];
extern uint8 SaveFncDataBuffer[];

/** Implementation parameter data structure */
typedef struct {
    int32 clef_info;
} CLEF_FLOAT64_IMPL_PARAM;

/** clef enumeration */
typedef enum {
    CLEF_TREBLE = 0,
    CLEF_BASS = 1,
    CLEF_ALTO = 2,
    CLEF_TENOR = 3
} tclef;

/** sharp enumeration */
typedef enum {
    SHARP_NONE = 0
} tsharp;

/** flat enumeration */
typedef enum {
    FLAT_NONE = 0
} tflat;

/** tempo enumeration */
typedef enum {
    TEMPO_LARGO = 0,
    TEMPO_ADAGIO = 1,
    TEMPO_ANDANTE = 2,
    TEMPO_MODERATO = 3,
    TEMPO_ALLEGRO = 4,
    TEMPO_VIVACE = 5
} ttempo;

/** Private prototypes */
static uint8 convertM2I(const CLEF_FLOAT64_MASK_PARAM *maskParam, CLEF_FLOAT64_IMPL_PARAM *impParam, float_CoT ts);

/**
 * @brief Converts Mask parameters to Implementation parameters.
 *
 * @param[in] maskParam Mask parameters
 * @param[out] impParam Implementation parameters
 * @param[in] ts Block sample time
 *
 * @return Error: zero on success, not zero in case of conversion error
 */
static uint8 convertM2I(const CLEF_FLOAT64_MASK_PARAM *maskParam, CLEF_FLOAT64_IMPL_PARAM *impParam, float_CoT ts)
{
    uint8 error = (uint8)0;
/* USERCODE-BEGIN:Conversion                                                                                          */
#error CONVERSION-ON-TARGET CURRENTLY NOT SUPPORTED / MASK-TO-IMPLEMENTATION CONVERSION MISSING
/* USERCODE-END:Conversion                                                                                            */
    return (error);
}

/**
 * @brief Load block mask parameter data.
 *
 * @param[in] maskParam Mask parameter data structure
 * @param[out] data Data
 * @param[out] dataLen Data length
 * @param[in] maxSize Maximum Service data length
 *
 * @return Error: zero on success, not zero in case of load- or conversion error
 */
uint8 Clef_Float64_LoadMP(const CLEF_FLOAT64_MASK_PARAM *maskParam, uint8 data[], uint16* dataLen, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)12 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(maskParam->clef);
        data[1] = (uint8)(maskParam->sharp);
        data[2] = (uint8)(maskParam->flat);
        data[3] = (uint8)(maskParam->tempo);
        data[4] = (uint8)((*(uint64*)&(maskParam->ts_fact)) & 0x00000000000000FF);
        data[5] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 8) & 0x00000000000000FF);
        data[6] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 16) & 0x00000000000000FF);
        data[7] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 24) & 0x00000000000000FF);
        data[8] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 32) & 0x00000000000000FF);
        data[9] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 40) & 0x00000000000000FF);
        data[10] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 48) & 0x00000000000000FF);
        data[11] = (uint8)((*(uint64*)&(maskParam->ts_fact) >> 56) & 0x00000000000000FF);
        *dataLen = (uint16)12;
    }
    return (error);
}

/**
 * @brief Save block mask parameter data.
 *
 * @param[in] block Pointer to block structure
 * @param[out] maskParam Mask parameter data structure
 * @param[in] data Data
 * @param dataLen Length of mask parameter data stream
 *
 * @return Error: zero on success, not zero in case of save- or conversion error
 */
uint8 Clef_Float64_SaveMP(CLEF_FLOAT64 *block, CLEF_FLOAT64_MASK_PARAM *maskParam, const uint8 data[], uint16 dataLen)
{
    uint8 error = (uint8)0;

    if (dataLen != (uint16)12)
    {
        error = (uint8)1;
    }
    else
    {
        uint64 tmp64;
        float_CoT block_ts;
        CLEF_FLOAT64_IMPL_PARAM *implParam = (CLEF_FLOAT64_IMPL_PARAM*)ImplParamBuffer;

        /** - Cache old mask parameters */
        memcpy(MaskParamBuffer, maskParam, sizeof(*maskParam));

        /** - Save new mask parameters */
        maskParam->clef = data[0];
        maskParam->sharp = data[1];
        maskParam->flat = data[2];
        maskParam->tempo = data[3];
        tmp64 = (uint64)data[4] + \
            ((uint64)data[5] << 8) + ((uint64)data[6] << 16) + \
            ((uint64)data[7] << 24) + ((uint64)data[8] << 32) + \
            ((uint64)data[9] << 40) + ((uint64)data[10] << 48) + \
            ((uint64)data[11] << 56);
        maskParam->ts_fact = (float64)(*(float64*)&tmp64);

        /** - Get Block Sample Time */
        block_ts = maskParam->ts_fact * getModelSampleTime();
        /** - Convert mask parameters to implementation parameters */
        error = convertM2I(maskParam, implParam, block_ts);

        /** - Prepare implementation parameters for save function */
        SaveFncDataBuffer[0] = (uint8)(implParam->clef_info & 0x000000FF);
        SaveFncDataBuffer[1] = (uint8)((implParam->clef_info >> 8) & 0x000000FF);
        SaveFncDataBuffer[2] = (uint8)((implParam->clef_info >> 16) & 0x000000FF);
        SaveFncDataBuffer[3] = (uint8)((implParam->clef_info >> 24) & 0x000000FF);

        /** - Execute save function of block */
        error = Clef_Float64_Save(block, SaveFncDataBuffer, 4);

        /** - Check for errors during execution of save function */
        if (error != 0)
        {
            /* Restore old mask parameter */
            memcpy(maskParam, MaskParamBuffer, sizeof(*maskParam));
        }

    }
    return (error);
}

/**
 * @brief Initializes Implementation parameters from Mask parameters.
 *
 * @param[out] block Block
 * @param[in] maskParam Mask parameters
 *
 * @return Error: zero on success, not zero in case of initialization error
 */
uint8 Clef_Float64_InitMP(CLEF_FLOAT64 *block, const CLEF_FLOAT64_MASK_PARAM *maskParam)
{
    uint8 error = (uint8)0;
    float_CoT block_ts;

    CLEF_FLOAT64_IMPL_PARAM *implParam = (CLEF_FLOAT64_IMPL_PARAM*)ImplParamBuffer;

    /** - Get Block Sample Time */
    block_ts = maskParam->ts_fact * getModelSampleTime();
    /** - Convert mask parameters to implementation parameters */
    error = convertM2I(maskParam, implParam, block_ts);

    /** - Prepare implementation parameters for save function */
    SaveFncDataBuffer[0] = (uint8)(implParam->clef_info & 0x000000FF);
    SaveFncDataBuffer[1] = (uint8)((implParam->clef_info >> 8) & 0x000000FF);
    SaveFncDataBuffer[2] = (uint8)((implParam->clef_info >> 16) & 0x000000FF);
    SaveFncDataBuffer[3] = (uint8)((implParam->clef_info >> 24) & 0x000000FF);

    /** - Execute save function of block */
    error = Clef_Float64_Save(block, SaveFncDataBuffer, 4);

    return (error);
}
