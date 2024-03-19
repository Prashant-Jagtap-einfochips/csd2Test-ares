#ifndef CSD2_TEST_H
#define CSD2_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#define DATA_SIZE                            2048

#define MODULE_TAG_DATA_MODULE               0xC0000020
#define PARAM_ID_DATA_MODULE_MUTE            0x08001232
#define PARAM_ID_DATA_MODULE_GAIN            0x08001175
#define PARAM_ID_DATA_MODULE_ENABLE          0x08001026
#define PARAM_ID_DATA_MODULE_COEFF           0x0800122E

#define MODULE_TAG_CONTROL_MODULE            0xC0000021
#define PARAM_ID_CONTROL_MODULE_MUTE         0x08001230
#define PARAM_ID_CONTROL_MODULE_GAIN         0x08001176
#define PARAM_ID_CONTROL_MODULE_ENABLE       0x08001020
#define PARAM_ID_CONTROL_MODULE_COEFF        0x0800122F

typedef struct CsdContext
{
    //CSDA_Cfg* params;
	// Module Tag of the Module under test.
    const uint32_t dstId; // = MODULE_TAG_CONTROL_MODULE;

    uint32_t handle;
} CSDA_Context;

void initializeParamConfig(struct csd2_pp_param_config*, int);

void TestCtrls(CSDA_Context, int, int);

void TestCoeffs(CSDA_Context, int, int);

void SetCoeffs(CSDA_Context, int, int, uint8_t*);

void SetMuteUnmute(CSDA_Context CsdContext, unsigned int, unsigned int, int);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* CSD2_TEST_H */
