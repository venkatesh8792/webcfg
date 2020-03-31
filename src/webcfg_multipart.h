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
#ifndef REQUEST_H
#define REQUEST_H

#include <stdint.h>
#include <curl/curl.h>
#include <base64.h>
#define WEBCFG_FREE(__x__) if(__x__ != NULL) { free((void*)(__x__)); __x__ = NULL;} else {printf("Trying to free null pointer\n");}

#ifdef BUILD_YOCTO
#define DEVICE_PROPS_FILE       "/etc/device.properties"
#else
#define DEVICE_PROPS_FILE       "/tmp/device.properties"
#endif

typedef struct
{
    uint32_t  etag;
    char  *name_space;
    char  *data;
    size_t data_size;
} multipartdocs_t;

typedef struct {
    multipartdocs_t *entries;
    size_t   entries_count;
} multipart_t;


int readFromFile(char *filename, char **data, int *len);
int parseMultipartDocument(void *config_data, char *ct , size_t data_size);
void getConfigDocList(char **doc);
void print_tmp_doc_list(size_t mp_count);
void loadInitURLFromFile(char **url);
uint32_t get_global_root();
#endif