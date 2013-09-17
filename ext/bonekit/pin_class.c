/*
 
 pin_class.c
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

#include "pin_class.h"

#include "ruby.h"
#include "gpio.h"
#include "pin.h"

VALUE cBoneKit_Pin;

static void Pin_free(pin_t * ptr)
{
  if(ptr == NULL)
      return;

  pin_destroy(ptr);
}

static VALUE Pin_alloc(VALUE class)
{
    pin_t * ptr = pin_alloc();
  
    VALUE self = Data_Wrap_Struct(class, 0, Pin_free, ptr);
    return self;
}

/*
 * call-seq:
 *  initialize(pin, mode=Input) -> Pin
 *
 * Returns a new Pin object with default value of 0
 * @param [Integer] pin the pin number
 * @param [Integer] mode the pin mode to be used (Input or Output)
 */
static VALUE Pin_initialize(int argc, VALUE* argv, VALUE self)
{
  if (argc > 2 || argc == 0)  // there should only be 1 or 2 arguments
    rb_raise(rb_eArgError, "wrong number of arguments (%d for 0..1)", argc);
  
  pin_t * ptr;
  Data_Get_Struct(self, pin_t, ptr);
  
  pin_init(ptr, NUM2UINT(argv[0]));
  
  int mode = INPUT;
  
  if(argc == 2)
    mode = NUM2INT(argv[1]);

  pin_set_mode(ptr, mode);
  
  return self;
}

/*
 * call-seq:
 *  value -> integer
 *
 * Reads the value from the pin.
 */
static VALUE Pin_value(VALUE self)
{
  pin_t * ptr;
  Data_Get_Struct(self, pin_t, ptr);
  
  return INT2NUM(pin_value(ptr));
}

/*
 * call-seq:
 *  value=(value) -> integer
 *
 * Write the value to the pin. The pin mode must be set to Output.
 * Possible values: High, Low.
 */
static VALUE Pin_set_value(VALUE self, VALUE value)
{
  pin_t * ptr;
  Data_Get_Struct(self, pin_t, ptr);
  pin_set_value(ptr, NUM2INT(value));
  
  return value;
}

/*
 * call-seq:
 *  mode -> integer
 *
 * Returns the mode of the pin.
 * Possible modes: Input, Output.
 */
static VALUE Pin_mode(VALUE self)
{
  pin_t * ptr;
  Data_Get_Struct(self, pin_t, ptr);
  return INT2NUM(pin_mode(ptr));
}

/*
 * call-seq:
 *  mode=(mode) -> integer
 *
 * Sets the mode of the pin.
 * Possible modes: Input, Output.
 */
static VALUE Pin_set_mode(VALUE self, VALUE value)
{
  pin_t * ptr;
  Data_Get_Struct(self, pin_t, ptr);
  pin_set_mode(ptr, NUM2INT(value));
  
  return value;
}

void BoneKit_Pin_class_init()
{
  cBoneKit_Pin = rb_define_class("Pin", rb_cObject);
  
  rb_define_alloc_func(cBoneKit_Pin, Pin_alloc);
  
  rb_define_method(cBoneKit_Pin, "initialize", Pin_initialize, -1);
  rb_define_method(cBoneKit_Pin, "value", Pin_value, 0);
  rb_define_method(cBoneKit_Pin, "value=", Pin_set_value, 1);
  rb_define_method(cBoneKit_Pin, "mode", Pin_mode, 0);
  rb_define_method(cBoneKit_Pin, "mode=", Pin_set_mode, 1);
  
  rb_define_global_const("High", INT2NUM(HIGH));
  rb_define_global_const("Low", INT2NUM(LOW));
  rb_define_global_const("Input", INT2NUM(INPUT));
  rb_define_global_const("Output", INT2NUM(OUTPUT));
}
