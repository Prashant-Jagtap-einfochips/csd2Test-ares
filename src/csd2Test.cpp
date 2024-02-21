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
	{	//#00 - Data Mute
		1,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_MUTE,
	},
	{
		//#01 - Data Mute
		0,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_MUTE,
	},
	{
		//#02 - Data Mute
		1,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_MUTE,
	},
	{
		//#03 - Data Mute
		0,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_MUTE,
	},
	{
		//#04 - Gain 0x5000
		20480,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_GAIN,
	},
	{
		//#05 - Gain 0x500
		1280,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_GAIN,
	},
	{
		//#06 - Gain 0x5000
		20480,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_GAIN,
	},
	{
		//#07 - Gain 0x500
		1280,
		MODULE_TAG_DATA_MODULE,
		PARAM_ID_DATA_MODULE_GAIN,
	},
	{	//#08 - Control Mute
		1,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_MUTE,
	},
	{
		//#09 - Control Mute
		0,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_MUTE,
	},
	{
		//#10 - Control Mute
		1,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_MUTE,
	},
	{
		//#11 - Control Mute
		0,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_MUTE,
	},
	{
		//#12 - Gain 0x5000
		20480,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_GAIN,
	},
	{
		//#13 - Gain 0x500
		1280,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_GAIN,
	},
	{
		//#14 - Gain 0x5000
		20480,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_GAIN,
	},
	{
		//#15 - Gain 0x500
		1280,
		MODULE_TAG_CONTROL_MODULE,
		PARAM_ID_CONTROL_MODULE_GAIN,
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

	uint32_t param_payload = tconfig[index].gainValue;

	printf(" Setting Configuration Parameters as below: \n");
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
		printf(" Set Param Value is : 0x%x \n", param_cfg.u.tagged_param.data);
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
		printf(" param_cfg.u.tagged_param.data is : %x \n", param_cfg.u.tagged_param.data);
		printf(" param_cfg.u.tagged_param.param_id is : %x \n", param_cfg.u.tagged_param.param_id);
		printf(" param_cfg.u.tagged_param.data_sz is : %x \n", param_cfg.u.tagged_param.data_sz);
	}

	printf("\n\n********************** Test %d End *****************************\n\n", index);
}
