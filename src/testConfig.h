#ifndef TEST_CONFIG_H
#define TEST_CONFIG_H

#include "CSD2Test.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_TEST 16

typedef struct TestConfig
{
	uint32_t gainValue;
	uint32_t moduleTag;
	uint32_t paramId;

} testConfig;

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* TEST_CONFIG_H */
