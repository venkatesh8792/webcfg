/*
 * Copyright 2020 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include "webcfg.h"
#include "http.h"

/*----------------------------------------------------------------------------*/
/*                                   Macros                                   */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                               Data Structures                              */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                            File Scoped Variables                           */
/*----------------------------------------------------------------------------*/
pthread_mutex_t periodicsync_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t periodicsync_condition=PTHREAD_COND_INITIALIZER;

/*----------------------------------------------------------------------------*/
/*                             Function Prototypes                            */
/*----------------------------------------------------------------------------*/
int handleHttpResponse(long response_code, char *webConfigData, int retry_count, int index, char* transaction_uuid);
void *WebConfigTask();
/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/

/* See webcfg.h for details. */
void webcfg_init()
{
	int err = 0;
	pthread_t threadId;

	err = pthread_create(&threadId, NULL, WebConfigTask, NULL);
	if (err != 0) 
	{
		WebConfigLog("Error creating WebConfigTask thread :[%s]\n", strerror(err));
	}
	else
	{
		WebConfigLog("WebConfigTask Thread created Successfully\n");
	}
}

void *WebConfigTask()
{
	pthread_detach(pthread_self());
	int index=0;//, i=0;
	/*int ret = 0;
	int json_status=-1;
	int rv=0, rc=0;
        struct timeval tp;
        struct timespec ts;
        time_t t;
	int count=0;
	int wait_flag=0;
	int forced_sync=0, syncIndex = 0;
        int value =Get_PeriodicSyncCheckInterval();
*/
	//start webconfig notification thread.
	/*initWebConfigNotifyTask();

	while(1)
	{
		if(forced_sync)
		{*/
			//trigger sync only for particular index
			/*WebConfigLog("Trigger Forced sync for index %d\n", syncIndex);
			processWebconfigSync(syncIndex, (int)status);
			WebConfigLog("reset forced_sync and syncIndex after sync\n");
			forced_sync = 0;
			syncIndex = 0;
			WebConfigLog("reset ForceSyncCheck after sync\n");
			setForceSyncCheck(index, false, "", 0);
		}
		else if(!wait_flag)
		{*/
			//iterate through all entries in Device.X_RDK_WebConfig.ConfigFile.[i].URL to check if the current stored version of each configuration document matches the latest version on the cloud.

			/*count = getConfigNumberOfEntries();
			WebConfigLog("count returned from getConfigNumberOfEntries:%d\n", count);

			for(i = 0; i < count; i++)
			{
				index = getInstanceNumberAtIndex(i);
				WebConfigLog("index returned from getInstanceNumberAtIndex:%d\n", index);
				if(index != 0)
				{*/
					processWebconfigSync(index);
				/*}
			}
		}

		pthread_mutex_lock (&periodicsync_mutex);
		gettimeofday(&tp, NULL);
		ts.tv_sec = tp.tv_sec;
		ts.tv_nsec = tp.tv_usec * 1000;
		ts.tv_sec += value;

		if (g_shutdown)
		{
			WebConfigLog("g_shutdown is %d, proceeding to kill webconfig thread\n", g_shutdown);
			pthread_mutex_unlock (&periodicsync_mutex);
			break;
		}
		value=Get_PeriodicSyncCheckInterval();
		WebConfigLog("PeriodicSyncCheckInterval value is %d\n",value);
		if(value == 0)
		{
			WebcfgDebug("B4 periodicsync_condition pthread_cond_wait\n");
			pthread_cond_wait(&periodicsync_condition, &periodicsync_mutex);
			rv =0;
		}
		else
		{
			WebcfgDebug("B4 periodicsync_condition pthread_cond_timedwait\n");
			rv = pthread_cond_timedwait(&periodicsync_condition, &periodicsync_mutex, &ts);
		}

		if(!rv && !g_shutdown)
		{
			time(&t);
			BOOL ForceSyncEnable;
			char* ForceSyncTransID = NULL;*/

			// Iterate through all indexes to check which index needs ForceSync
			/*count = getConfigNumberOfEntries();
			WebConfigLog("count returned is:%d\n", count);

			for(i = 0; i < count; i++)
			{
				WebcfgDebug("B4 getInstanceNumberAtIndex for i %d\n", i);
				index = getInstanceNumberAtIndex(i);
				WebcfgDebug("getForceSyncCheck for index %d\n", index);
				getForceSyncCheck(index,&ForceSyncEnable, &ForceSyncTransID);
				WebcfgDebug("ForceSyncEnable is %d\n", ForceSyncEnable);
				if(ForceSyncTransID !=NULL)
				{
					if(ForceSyncEnable)
					{
						wait_flag=0;
						forced_sync = 1;
						syncIndex = index;
						WebConfigLog("Received signal interrupt to getForceSyncCheck at %s\n",ctime(&t));
						WAL_FREE(ForceSyncTransID);
						break;
					}
					WebConfigLog("ForceSyncEnable is false\n");
					WAL_FREE(ForceSyncTransID);
				}
			}
			WebConfigLog("forced_sync is %d\n", forced_sync);
			if(!forced_sync)
			{
				wait_flag=1;
				value=Get_PeriodicSyncCheckInterval();
				WebConfigLog("Received signal interrupt to change the sync interval to %d\n",value);
			}
		}
		else if (rv == ETIMEDOUT && !g_shutdown)
		{
			time(&t);
			wait_flag=0;
			WebConfigLog("Periodic Sync Interval %d sec and syncing at %s\n",value,ctime(&t));
		}
		else if(g_shutdown)
		{
			WebConfigLog("Received signal interrupt to RFC disable. g_shutdown is %d, proceeding to kill webconfig thread\n", g_shutdown);
			pthread_mutex_unlock (&periodicsync_mutex);
			break;
		}
		pthread_mutex_unlock(&periodicsync_mutex);

	}
	if(NotificationThreadId)
	{
		ret = pthread_join (NotificationThreadId, NULL);
		if(ret ==0)
		{
			WebConfigLog("pthread_join returns success\n");
		}
		else
		{
			WebConfigLog("Error joining thread\n");
		}
	}*/
	WebConfigLog("B4 pthread_exit\n");
	pthread_exit(0);
	WebcfgDebug("After pthread_exit\n");
	return NULL;
}



/*----------------------------------------------------------------------------*/
/*                             Internal functions                             */
/*----------------------------------------------------------------------------*/
void processWebconfigSync(int index)
{
	int status=0;
	int retry_count=0;
	int r_count=0;
	int configRet = -1;
	char *webConfigData = NULL;
	long res_code;
	int rv=0;
	char *transaction_uuid =NULL;

	WebcfgDebug("========= Start of processWebconfigSync =============\n");
	while(1)
	{
		if(retry_count >3)
		{
			WebConfigLog("retry_count has reached max limit. Exiting.\n");
			retry_count=0;
			break;
		}
		configRet = webcfg_http_request(&webConfigData, r_count, index, status, &res_code, &transaction_uuid);
		if(configRet == 0)
		{
			rv = handleHttpResponse(res_code, webConfigData, retry_count, index, transaction_uuid);
			if(rv ==1)
			{
				WebConfigLog("No retries are required. Exiting..\n");
				break;
			}
		}
		else
		{
			WebConfigLog("Failed to get webConfigData from cloud\n");
		}
		WebConfigLog("webcfg_http_request BACKOFF_SLEEP_DELAY_SEC is %d seconds\n", BACKOFF_SLEEP_DELAY_SEC);
		sleep(BACKOFF_SLEEP_DELAY_SEC);
		retry_count++;
		WebConfigLog("Webconfig retry_count is %d\n", retry_count);
	}
	WebcfgDebug("========= End of processWebconfigSync =============\n");
	return;
}

int handleHttpResponse(long response_code, char *webConfigData, int retry_count, int index, char* transaction_uuid)
{
	return 0;
}

void getConfigURL(char **Url)
{
	*Url = strdup("https://example.com"); //get the url from partners.json

}


