#ifndef CSD2_TEST_H
#define CSD2_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#define MODULE_TAG_CONTROL_MODULE       0xC0000020
#define MODULE_TAG_DATA_MODULE          0xC0000020

#define PARAM_ID_CONTROL_MODULE         0x08001232
#define PARAM_ID_DATA_MODULE            0x08001176

typedef struct CsdContext
{
    //CSDA_Cfg* params;
	// Module Tag of the Module under test.
    const uint32_t dstId = MODULE_TAG_CONTROL_MODULE;

    uint32_t handle;
} CSDA_Context;

void initializeParamConfig(struct csd2_pp_param_config, int);

void Test(CSDA_Context, int, int);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* CSD2_TEST_H */
