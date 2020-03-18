/* mbed Microcontroller Library
 * Copyright (c) 2019, Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "cy_iperf_rtc.h"
#include "cyhal_rtc.h"
#include "mktime.h"
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

static cyhal_rtc_t cy_rtc;

void rtc_init(void)
{
    if (CY_RSLT_SUCCESS != cyhal_rtc_init(&cy_rtc)) {
        printf("Error in cyhal_rtc_init \n");
    }
}

void rtc_free(void)
{
    cyhal_rtc_free(&cy_rtc);
}

int rtc_isenabled(void)
{
    return cyhal_rtc_is_enabled(&cy_rtc) ? 1 : 0;
}

time_t rtc_read(void)
{
    struct tm rtc_time;
    if (CY_RSLT_SUCCESS != cyhal_rtc_read(&cy_rtc, &rtc_time)) {
    	printf("Error in cyhal_rtc_read \n");
    }
    time_t seconds;
    if (!_rtc_maketime(&rtc_time, &seconds, RTC_FULL_LEAP_YEAR_SUPPORT)) {
    	printf("Error in rtc_maketime \n");
    }
    return seconds;
}

void rtc_write(time_t t)
{
    struct tm rtc_time;
    if (!_rtc_localtime(t, &rtc_time, RTC_FULL_LEAP_YEAR_SUPPORT)) {
    	printf("Error in rtc_localtime \n");
    }
    if (CY_RSLT_SUCCESS != cyhal_rtc_write(&cy_rtc, &rtc_time)) {
    	printf("Error in cyhal_rtc_write \n");
    }
}

#ifdef __cplusplus
}
#endif
