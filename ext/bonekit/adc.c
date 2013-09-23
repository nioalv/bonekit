/*

 adc.c
 BoneKit

 Copyright (cc) 2012 Luis Laugga.
 Some rights reserved, all wrongs deserved.

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "adc.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int adc_read(unsigned int ain, char * value, unsigned int length)
{
  int fd, len;
  char filepath[ADC_LEN];
  snprintf(filepath, sizeof(filepath), "%s/in_voltage%d_raw", ADC_DIR, ain); // ie. /sys/bus/iio/devices/iio\:device0/in_voltage0_raw
  
  if((fd = open(filepath, O_RDONLY | O_NONBLOCK)) < 0)
    return -1;
  
  lseek(fd, 0, SEEK_SET);
  read(fd, value, length);
  close(fd);
  
  return 0;
}

int adc_get_value(unsigned int ain, unsigned float * value)
{
  const unsigned int length = 2;
  char buffer[length];
    
  if(adc_read(ain, buffer, length) < 0)
    return -1;
    
  *value = atof(buffer);
    
  return 0;
}