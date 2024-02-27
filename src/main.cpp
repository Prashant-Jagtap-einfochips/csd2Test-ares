#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>

#include "csd2_media_format.h"
#include "csd2_status.h"
#include "csd2_types.h"
#include "csd2.h"
#include "mmdefs.h"
#include "kvh2xml.h"
#include "CSD2Test.h"
#include "testConfig.h"

int main(int argc, char *argv[]) {

	struct csd2_init_data init_param;

	enum csd2_module_type type = CSD2_MODULE_TYPE_PP_CONTROL;

	struct csd2_graph_info gi = {1, CSD2_STREAM_PP_TYPE};

	struct csd2_open_config opencfg = {CSD2_OPEN_OP_RW, &gi};

	uint32_t size = sizeof(opencfg);

	uint32_t value = 0;

	int32_t retVal, idx;

	CSDA_Context CsdContext{};

#if 0
	if (argc != 2) {
		printf("Please provide exactly one integer argument.\n");
		return 1;
	}

	int gain = atoi(argv[1]);
	printf("The integer value entered is: %d\n", gain);
#endif

	if (CSD2_EOK != (value = csd2_init(&init_param)))
	{
		printf(" csd2_init failed %d. \n", value);
		retVal = -1;
	}
	else if (CSD2_EOK != (value = csd2_open(type, &opencfg, size, &(CsdContext.handle))))
	{
		printf(" csd2_open failed %d. \n", value);
		retVal = -1;
	}
	else
	{
		printf(" csd2_open initialized Successfully.: %d \n", CsdContext.handle);
	}


#if 0
	for (idx = 0; idx < MAX_TEST; idx++){
		Test(CsdContext, idx, 10);
		printf ("\n\n\n");
	}
#endif

	TestCoeff(CsdContext, 0, 10);

#if 0
	struct csd2_key_value kvp[5] = {
				{STREAMRX, PCM_DEEP_BUFFER},
				{INSTANCE, INSTANCE_1},
				{VMID, PVM},
				{DEVICEPP_RX, DEVICEPP_RX_AUDIO_MBDRC},
				{DEVICERX, MEDIA_SPKR}};

	csd2_pp_param_config param_cfg = {0};

	param_cfg.gkv.num_kvs = 5;

	param_cfg.gkv.kv = kvp;

	param_cfg.tag = 0xC0000020;

	printf(" param_cfg.tag is : 0x%x \n", param_cfg.tag);

	param_cfg.is_persist = FALSE;

	param_cfg.mode = CSD2_PP_CFG_MODE_TAGGED_PARAM;

	// Parameter ID of the parameter whose value need to set
	param_cfg.u.tagged_param.param_id = 0x08001232;
	printf(" param_cfg.u.tagged_param.param_id is : 0x%x \n", param_cfg.u.tagged_param.param_id);

	param_cfg.u.tagged_param.data = &gain;

	param_cfg.u.tagged_param.data_sz = sizeof(int) + 4;

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
#endif

	csd2_close(CsdContext.handle);
	csd2_deinit();

	return retVal;
}
