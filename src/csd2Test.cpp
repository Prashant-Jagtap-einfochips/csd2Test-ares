#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>

#include "csd2_ioctl.h"
#include "csd2_media_format.h"
#include "csd2_status.h"
#include "csd2_types.h"
#include "csd2.h"
#include "mmdefs.h"
#include "kvh2xml.h"
#include "csd2Test.h"
#include "testConfig.h"

testConfig tconfig[MAX_TEST] = {
	{
	    "Data Module Enable",
		1,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_ENABLE,
	},
	{
		"Control Module Enable",
		1,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_ENABLE,
	},
	{
		"Data Module Mute",
		1,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_MUTE,
	},
	{
		"Data Module UnMute",
		0,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_MUTE,
	},
	{
		"Data Module Disable",
		0,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_ENABLE,
	},
	{
		"Neg - Data Module Mute",
		1,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_MUTE,
	},
	{
		"Neg - Data Module UnMute",
		0,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_MUTE,
	},
	{
		"Data Module Enable",
		1,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_ENABLE,
	},
	{
		"Setting Data Module Gain 0x5000",
		20480,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_GAIN,
	},
	{
		"Setting Data Module Gain 0x500",
		1280,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_GAIN,
	},
	{
		"Data Module Disable",
		0,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_ENABLE,
	},
	{
		"Setting Data Module Gain 0x5000",
		20480,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_GAIN,
	},
	{
		"Setting Data Module Gain 0x500",
		1280,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_GAIN,
	},
	{
		"Data Module Enable",
		1,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_ENABLE,
	},
	{
		"Control Module Mute",
		1,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_MUTE,
	},
	{
		"Control Module UnMute",
		0,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_MUTE,
	},
	{
		"Control Module Disable",
		0,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_ENABLE,
	},
	{
		"Neg - Control Module Mute",
		1,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_MUTE,
	},
	{
		"Neg - Control Module UnMute",
		0,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_MUTE,
	},
	{
		"Control Module Enable",
		1,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_ENABLE,
	},
	{
		"Setting Control Module Gain 0x5000",
		20480,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_GAIN,
	},
	{
		"Setting Control Module Gain 0x500",
		1280,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_GAIN,
	},
	{
		"Control Module Enable",
		1,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_ENABLE,
	},
	{
		"Neg - Setting Control Module Gain 0x5000",
		20480,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_GAIN,
	},
	{
		"Neg - Setting Control Module Gain 0x500",
		1280,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_GAIN,
	},
	{
		"Control Module Enable",
		1,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_ENABLE,
	}
};

testCoeff tcoeff[MAX_COEFF_TEST] = {
	{
		"Setting Coeff to 0x7F",
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_COEFF,
	}
};

#if 0
void initializeParamConfig(struct csd2_pp_param_config *param_cfg, int index) {

	uint32_t param_payload = tconfig[index].gainValue;

	printf(" param_payload is : 0x%x \n", param_payload);

	struct csd2_key_value kvp[5] = {
				{STREAMRX, PCM_DEEP_BUFFER},
				{INSTANCE, INSTANCE_1},
				{VMID, PVM},
				{DEVICEPP_RX, DEVICEPP_RX_AUDIO_MBDRC},
				{DEVICERX, MEDIA_SPKR}};

	param_cfg->gkv.num_kvs = 5;

	param_cfg->gkv.kv = kvp;

	param_cfg->tag = tconfig[index].moduleTag;

	printf(" param_cfg.tag is : 0x%x \n", param_cfg->tag);

	param_cfg->is_persist = FALSE;

	param_cfg->mode = CSD2_PP_CFG_MODE_TAGGED_PARAM;

	// Parameter ID of the parameter whose value need to set
	param_cfg->u.tagged_param.param_id = tconfig[index].paramId;
	printf(" param_cfg.u.tagged_param.param_id is : 0x%x \n", param_cfg->u.tagged_param.param_id);

	param_cfg->u.tagged_param.data = (&param_payload);

	param_cfg->u.tagged_param.data_sz = sizeof(param_payload) + 4;
}
#endif


void Test(CSDA_Context CsdContext, int index, int delay){

	struct csd2_pp_param_config param_cfg = {0};

	uint32_t param_payload = tconfig[index].data;

	printf(" Configuration: %s\n", tconfig[index].des);
	printf(" param_payload is : 0x%x \n", param_payload);

	struct csd2_key_value kvp[5] = {
				{STREAMRX, PCM_DEEP_BUFFER},
				{INSTANCE, INSTANCE_1},
				{VMID, PVM},
				{DEVICEPP_RX, DEVICEPP_RX_AUDIO_MBDRC},
				{DEVICERX, MEDIA_SPKR}};

	param_cfg.gkv.num_kvs = 5;

	param_cfg.gkv.kv = kvp;

	param_cfg.tag = tconfig[index].moduleTag;

	printf(" param_cfg.tag is : 0x%x \n", param_cfg.tag);

	param_cfg.is_persist = FALSE;

	param_cfg.mode = CSD2_PP_CFG_MODE_TAGGED_PARAM;

	// Parameter ID of the parameter whose value need to set
	param_cfg.u.tagged_param.param_id = tconfig[index].paramId;
	printf(" param_cfg.u.tagged_param.param_id is : 0x%x \n", param_cfg.u.tagged_param.param_id);

	param_cfg.u.tagged_param.data = (&param_payload);

	param_cfg.u.tagged_param.data_sz = sizeof(param_payload) + 4;

	printf("\n\n********************** Test %d Start *****************************\n\n", index);

	sleep(delay);

	if (CSD2_EOK != csd2_ioctl(CsdContext.handle, CSD2_CMD_PP_CONTROL_SET, &param_cfg, sizeof(param_cfg)))
	{
		printf(" Request csd2_ioctl PP_CONTROL_SET failed.\n");
	}
	else{
		printf(" csd2_ioctl CSD2_CMD_PP_CONTROL_SET Successful.\n");
		printf(" Set Param Value is : 0x%d \n", (int*)(param_cfg.u.tagged_param.data));
	}

	sleep(delay);

	if (CSD2_EOK != csd2_ioctl(CsdContext.handle,
								   CSD2_CMD_PP_CONTROL_GET,
								   &param_cfg,
								   sizeof(param_cfg)))
	{
		printf(" Request csd2_ioctl PP_CONTROL_GET failed.\n");
	}
	else{
		printf(" csd2_ioctl CSD2_CMD_PP_CONTROL_GET Successful.\n");
		printf(" param_cfg.gkv.num_kvs is : %x \n", param_cfg.gkv.num_kvs);
		printf(" param_cfg.tag is : %x \n", param_cfg.tag);
		printf(" param_cfg.is_persist is : %x \n", param_cfg.is_persist);
		printf(" param_cfg.mode is : %x \n", param_cfg.mode);
		printf(" param_cfg.u.tagged_param.data is : %d \n", (int*)(param_cfg.u.tagged_param.data));
		printf(" param_cfg.u.tagged_param.param_id is : %x \n", param_cfg.u.tagged_param.param_id);
		printf(" param_cfg.u.tagged_param.data_sz is : %x \n", param_cfg.u.tagged_param.data_sz);
	}

	printf("\n\n********************** Test %d End *****************************\n\n", index);
}

void TestCoeff(CSDA_Context CsdContext, int index, int delay){

	struct csd2_pp_param_config param_cfg = {0};
#if 0
	uint8_t* param_payload = 0;

	param_payload = (uint8_t*)malloc(4096);
	if(NULL == param_payload) {
		printf("NOt able to allocate space for param_payload\n");
		return;
	}

	memset(param_payload, 0x7F, 4096);
#endif
	uint8_t param_payload = 0x7F;

	printf(" Configuration: %s\n", tcoeff[index].des);
	//printf(" param_payload is : 0x%x \n", param_payload);

	struct csd2_key_value kvp[5] = {
				{STREAMRX, PCM_DEEP_BUFFER},
				{INSTANCE, INSTANCE_1},
				{VMID, PVM},
				{DEVICEPP_RX, DEVICEPP_RX_AUDIO_MBDRC},
				{DEVICERX, MEDIA_SPKR}};

	param_cfg.gkv.num_kvs = 5;

	param_cfg.gkv.kv = kvp;

	param_cfg.tag = tcoeff[index].moduleTag;

	printf(" param_cfg.tag is : 0x%x \n", param_cfg.tag);

	param_cfg.is_persist = FALSE;

	param_cfg.mode = CSD2_PP_CFG_MODE_TAGGED_PARAM;

	// Parameter ID of the parameter whose value need to set
	param_cfg.u.tagged_param.param_id = tcoeff[index].paramId;
	printf(" param_cfg.u.tagged_param.param_id is : 0x%x \n", param_cfg.u.tagged_param.param_id);

	param_cfg.u.tagged_param.data = &param_payload;

	param_cfg.u.tagged_param.data_sz = 1 + 4;

	printf("\n\n********************** Test %d Start *****************************\n\n", index);

	sleep(delay);

	if (CSD2_EOK != csd2_ioctl(CsdContext.handle, CSD2_CMD_PP_CONTROL_SET, &param_cfg, sizeof(param_cfg)))
	{
		printf(" Request csd2_ioctl PP_CONTROL_SET failed.\n");
	}
	else{
		printf(" csd2_ioctl CSD2_CMD_PP_CONTROL_SET Successful.\n");
		printf(" Set Param Value is : 0x%d \n", (int*)(param_cfg.u.tagged_param.data));
	}

	sleep(delay);
	param_cfg.u.tagged_param.data_sz = 0;

	if (CSD2_EOK != csd2_ioctl(CsdContext.handle,
								   CSD2_CMD_PP_CONTROL_GET,
								   &param_cfg,
								   sizeof(param_cfg)))
	{
		printf(" Request csd2_ioctl PP_CONTROL_GET failed.\n");
	}
	else{
		printf(" csd2_ioctl CSD2_CMD_PP_CONTROL_GET Successful.\n");
		printf(" param_cfg.gkv.num_kvs is : %x \n", param_cfg.gkv.num_kvs);
		printf(" param_cfg.tag is : %x \n", param_cfg.tag);
		printf(" param_cfg.is_persist is : %x \n", param_cfg.is_persist);
		printf(" param_cfg.mode is : %x \n", param_cfg.mode);
		printf(" param_cfg.u.tagged_param.data is : %d \n", (int*)(param_cfg.u.tagged_param.data));
		printf(" param_cfg.u.tagged_param.param_id is : %x \n", param_cfg.u.tagged_param.param_id);
		printf(" param_cfg.u.tagged_param.data_sz is : %x \n", param_cfg.u.tagged_param.data_sz);
	}

	printf("\n\n********************** Test %d End *****************************\n\n", index);

	//free(param_payload);
}
