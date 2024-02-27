#ifndef TEST_CONFIG_H
#define TEST_CONFIG_H

#include "CSD2Test.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_TEST 26
#define MAX_COEFF_TEST 1

typedef struct TestConfig
{
	uint8_t  des[50];
	uint32_t data;
	uint32_t moduleTag;
	uint32_t paramId;

} testConfig;

typedef struct TestCoeff
{
	uint8_t  des[50];
	uint32_t moduleTag;
	uint32_t paramId;

} testCoeff;

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* TEST_CONFIG_H */
