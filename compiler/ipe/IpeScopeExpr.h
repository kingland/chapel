/*
 * Copyright 2004-2015 Cray Inc.
 * Other additional copyright holders may be indicated within.
 *
 * The entirety of this work is licensed under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License.
 *
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

#ifndef _IPE_SCOPE_EXPR_H_
#define _IPE_SCOPE_EXPR_H_

#include "IpeScope.h"

class IpeScopeExpr : public IpeScope
{
public:
                           IpeScopeExpr(IpeScope* parent);
  virtual                 ~IpeScopeExpr();

  virtual const char*      name()                                     const;

  virtual void             extend(Symbol*  sym,
                                  IpeValue defaultValue,
                                  IpeVars* vars);

  virtual void             envPush();
  virtual void             envPop();

protected:
  virtual const char*      type()                                     const;
  virtual void             describeHeader(int offset)                 const;

private:
                           IpeScopeExpr();
};

#endif
