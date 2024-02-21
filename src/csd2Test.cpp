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
	{	1024, //Gain Value
		MODULE_TAG_CONTROL_MODULE, //Module Tag of a Module under Test
		PARAM_ID_CONTROL_MODULE, //Param ID of a Parameter to be set
	},
	{
		8192, //Gain Value
		MODULE_TAG_CONTROL_MODULE, //Module Tag of a Module under Test
		PARAM_ID_CONTROL_MODULE, //Param ID of a Parameter to be set
	},
	{
		4196, //Gain Value
		MODULE_TAG_DATA_MODULE, //Module Tag of a Module under Test
		PARAM_ID_DATA_MODULE, //Param ID of a Parameter to be set
	},
	{
		256, //Gain Value
		MODULE_TAG_DATA_MODULE, //Module Tag of a Module under Test
		PARAM_ID_DATA_MODULE, //Param ID of a Parameter to be set
	},
	{
		8192, //Gain Value
		MODULE_TAG_CONTROL_MODULE, //Module Tag of a Module under Test
		PARAM_ID_CONTROL_MODULE, //Param ID of a Parameter to be set
	}
};

void initializeParamConfig(csd2_pp_param_config param_cfg, int index) {

	uint32_t param_payload = index;

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
}


void Test(CSDA_Context CsdContext, int index, int delay){

	csd2_pp_param_config param_cfg;

	initializeParamConfig(param_cfg, index);

	if (CSD2_EOK != csd2_ioctl(CsdContext.handle, CSD2_CMD_PP_CONTROL_SET, &param_cfg, sizeof(param_cfg)))
	{
		printf(" Request csd2_ioctl PP_CONTROL_SET failed.\n");
	}
	else{
		printf(" csd2_ioctl CSD2_CMD_PP_CONTROL_SET Successful.\n");
		printf(" Set Param Value is : 0x%x \n", param_cfg.u.tagged_param.data);
	}

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
}
