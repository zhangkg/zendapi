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
// Created by softboy on 27/07/2017.

#ifndef ZAPI_LANG_FUNCTION_H
#define ZAPI_LANG_FUNCTION_H

#include "zapi/vm/Callable.h"

namespace zapi
{
namespace lang
{

using zapi::lang::internal::ExtensionPrivate;
using zapi::ds::Variant;
class FunctionPrivate;

class ZAPI_DECL_EXPORT Function : public zapi::vm::Callable
{
public:
   Function(const char *name, zapi::ZendCallable callable, const Arguments &arguments = {});
   Function(const char *name, const Arguments &arguments = {});
   Function(const Function &other);
   Function &operator=(const Function &other);
   virtual Variant invoke(Parameters &parameters);
   virtual ~Function();
private:
   ZAPI_DECLARE_PRIVATE(Function)
};

} // lang
} // zapi

#endif //ZAPI_LANG_FUNCTION_H
