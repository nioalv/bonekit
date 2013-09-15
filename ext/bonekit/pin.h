/*
 
 pin.h
 BoneKit
 
 Copyright (cc) 2012 Luis Laugga.
 Some rights reserved, all wrongs deserved.
 
 Licensed under a Creative Commons Attribution-ShareAlike 3.0 License;
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://creativecommons.org/licenses/by-sa/3.0/
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" basis,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 
*/

#ifndef BONEKIT_PIN_H__
#define BONEKIT_PIN_H__

#ifdef __cplusplus
extern "C" {
#endif

struct pin_s
{
  unsigned _gpio;
};

typedef struct pin_s pin_t;

pin_t * pin_create(unsigned int);
void pin_destroy(pin_t *);
int pin_mode(pin_t *);
void pin_set_mode(pin_t *, int);
int pin_value(pin_t *);
void pin_set_value(pin_t *, int);

#ifdef __cplusplus
}
#endif

#endif