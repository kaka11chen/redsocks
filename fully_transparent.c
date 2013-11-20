/* redsocks - transparent TCP-to-proxy redirector
 * Copyright (C) 2007-2011 Leonid Evdokimov <leon@darkk.net.ru>
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License.  You may obtain a copy
 * of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#include "redsocks.h"
#include "fully_transparent.h"

typedef struct fully_transparent_client_t {
    int test;
} fully_transparent_client;

void fully_transparent_client_init(redsocks_client *client)
{
    fully_transparent_client *fully_transparent = (void*)(client + 1);
    fully_transparent->test = 1;
}

static void fully_transparent_write_cb(struct bufferevent *buffev, void *_arg)
{
    redsocks_client *client = _arg;
    redsocks_start_relay(client);
}

relay_subsys fully_transparent_subsys =
{
    .name                 = "fully_transparent",
    .payload_len          = sizeof(fully_transparent_client),
    .instance_payload_len = 0,
    .writecb              = fully_transparent_write_cb,
    .init                 = fully_transparent_client_init,
    .is_fully_transparent = 1
};


/* vim:set tabstop=4 softtabstop=4 shiftwidth=4: */
/* vim:set foldmethod=marker foldlevel=32 foldmarker={,}: */
