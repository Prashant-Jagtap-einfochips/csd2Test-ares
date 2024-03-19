#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <time.h>

#include "csd2_media_format.h"
#include "csd2_status.h"
#include "csd2_types.h"
#include "csd2.h"
#include "mmdefs.h"
#include "kvh2xml.h"
#include "CSD2Test.h"
#include "testConfig.h"

uint8_t param_payload[2048] = {0};
#define BILLION  1000000000L;

int main(int argc, char *argv[]) {

	struct csd2_init_data init_param;

	enum csd2_module_type type = CSD2_MODULE_TYPE_PP_CONTROL;

	struct csd2_graph_info gi = {1, CSD2_STREAM_PP_TYPE};

	struct csd2_open_config opencfg = {CSD2_OPEN_OP_RW, &gi};

	uint32_t size = sizeof(opencfg);

	int32_t retVal;

	CSDA_Context CsdContext{};

	if (CSD2_EOK != (retVal = csd2_init(&init_param)))
	{
		printf(" csd2_init failed %d. \n", retVal);
		retVal = -1;
	}
	else if (CSD2_EOK != (retVal = csd2_open(type, &opencfg, size, &(CsdContext.handle))))
	{
		printf(" csd2_open failed %d. \n", retVal);
		retVal = -1;
	}
	else
	{
		printf(" csd2_open initialized Successfully.: %d \n", CsdContext.handle);
	}

#if 0
	int32_t idx;
    /**************************************************************
		     Regression Testing (Ctrls and Coeffs)
    **************************************************************/
	for (idx = 0; idx < MAX_TEST; idx++){
		TestCtrls(CsdContext, idx, 10);
		printf ("\n\n\n");
	}

	for (idx = 0; idx < MAX_COEFF_TEST; idx++){
	    TestCoeffs(CsdContext, idx, 10);
	}
#endif

#if 0
    struct timespec start, stop;

    double accum;
	/**************************************************************
	     Latency measurement for 200K Coeff to Data CAPI module
	**************************************************************/
	if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
	    perror( "clock gettime" );
	    return EXIT_FAILURE;
	}

	SetCoeffs(CsdContext, 0, 10, 500, &param_payload[0]);

	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
	    perror( "clock gettime" );
	    return EXIT_FAILURE;
	}

	accum = ( stop.tv_sec - start.tv_sec )
	             + (double)( stop.tv_nsec - start.tv_nsec )
	               / (double)BILLION;
	printf("start: %d\nstop: %d \nstart_nsec: %d \nstop_nsec:%d \n",
			start.tv_sec, stop.tv_sec, start.tv_nsec, stop.tv_nsec);
	printf( "Total Time: %lf\n", accum );
#endif

#if 0
	/**************************************************************
	   Latency measurement for 200K Coeff to Control CAPI module
	**************************************************************/
	if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
		perror( "clock gettime" );
		return EXIT_FAILURE;
	}

	SetCoeffs(CsdContext, 1, 10, 500, &param_payload[0]);

	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
		perror( "clock gettime" );
		return EXIT_FAILURE;
	}

	accum = ( stop.tv_sec - start.tv_sec )
				 + (double)( stop.tv_nsec - start.tv_nsec )
				   / (double)BILLION;
	printf("start: %d\nstop: %d \nstart_nsec: %d \nstop_nsec:%d \n",
			start.tv_sec, stop.tv_sec, start.tv_nsec, stop.tv_nsec);
	printf( "Total Time: %lf\n", accum );
#endif

#if 1
	printf("*************** Mute Unmute Test ********************");
	SetMuteUnmute(CsdContext, MODULE_TAG_DATA_MODULE, PARAM_ID_DATA_MODULE_MUTE, 1);

	SetCoeffs(CsdContext, 1, 1, &param_payload[0]);
	sleep(0.1);

	SetMuteUnmute(CsdContext, MODULE_TAG_DATA_MODULE, PARAM_ID_DATA_MODULE_MUTE, 0);
	printf("*************** Mute Unmute Test END ********************");

#endif

	csd2_close(CsdContext.handle);
	csd2_deinit();

	return retVal;
}
