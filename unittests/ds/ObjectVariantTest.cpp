// Copyright 2017-2018 zzu_softboy <zzu_softboy@163.com>
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Created by softboy on 2017/09/06.

#include "php/sapi/embed/php_embed.h"
#include "gtest/gtest.h"
#include "zapi/ds/ObjectVariant.h"
#include <iostream>
#include <string>
#include <vector>

using zapi::ds::ObjectVariant;
using zapi::ds::Variant;
using zapi::lang::Type;

TEST(ObjectVariantTest, testStdObject)
{
   ObjectVariant stdObj;
   ASSERT_EQ(stdObj.getRefCount(), 1);
   ASSERT_EQ(stdObj.getUnDerefType(), Type::Object);
   // test copy construct
   ObjectVariant stdObj1(stdObj);
   ASSERT_EQ(stdObj.getRefCount(), 2);
   ASSERT_EQ(stdObj1.getRefCount(), 2);
   ASSERT_EQ(stdObj1.getUnDerefType(), Type::Object);
   {
      ObjectVariant stdObj2(stdObj1);
      ASSERT_EQ(stdObj.getRefCount(), 3);
      ASSERT_EQ(stdObj1.getRefCount(), 3);
      ASSERT_EQ(stdObj2.getRefCount(), 3);
   }
   ASSERT_EQ(stdObj.getRefCount(), 2);
   ASSERT_EQ(stdObj1.getRefCount(), 2);
   Variant gobj(stdObj1);
   ASSERT_EQ(stdObj.getRefCount(), 3);
   ASSERT_EQ(stdObj1.getRefCount(), 3);
   ASSERT_EQ(gobj.getRefCount(), 3);
   stdObj = stdObj1;
   ASSERT_EQ(stdObj.getRefCount(), 3);
   ASSERT_EQ(stdObj1.getRefCount(), 3);
   ASSERT_EQ(gobj.getRefCount(), 3);
   // diffrent object
   ObjectVariant stdObj2;
   ASSERT_EQ(stdObj2.getRefCount(), 1);
   stdObj = stdObj2;
   ASSERT_EQ(stdObj1.getRefCount(), 2);
   ASSERT_EQ(gobj.getRefCount(), 2);
   ASSERT_EQ(stdObj.getRefCount(), 2);
   ASSERT_EQ(stdObj2.getRefCount(), 2);
   
   stdObj = std::move(stdObj2);
   ASSERT_EQ(stdObj.getRefCount(), 1);
   ASSERT_EQ(gobj.getRefCount(), 2);
   ObjectVariant stdObj3(std::move(gobj));
   ASSERT_EQ(stdObj3.getRefCount(), 2);
   
   {
      Variant num(123);
      ObjectVariant stdObj(num);
      ASSERT_EQ(num.getRefCount(), 0);
      ASSERT_EQ(stdObj.getRefCount(), 1);
      ASSERT_EQ(stdObj.getUnDerefType(), Type::Object);
   }
   {
      Variant num("zapi");
      ObjectVariant stdObj(std::move(num));
      ASSERT_EQ(stdObj.getRefCount(), 1);
      ASSERT_EQ(stdObj.getUnDerefType(), Type::Object);
   }
}
