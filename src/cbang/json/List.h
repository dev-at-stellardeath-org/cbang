/******************************************************************************\

          This file is part of the C! library.  A.K.A the cbang library.

              Copyright (c) 2003-2015, Cauldron Development LLC
                 Copyright (c) 2003-2015, Stanford University
                             All rights reserved.

        The C! library is free software: you can redistribute it and/or
        modify it under the terms of the GNU Lesser General Public License
        as published by the Free Software Foundation, either version 2.1 of
        the License, or (at your option) any later version.

        The C! library is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
        Lesser General Public License for more details.

        You should have received a copy of the GNU Lesser General Public
        License along with the C! library.  If not, see
        <http://www.gnu.org/licenses/>.

        In addition, BSD licensing may be granted on a case by case basis
        by written permission from at least one of the copyright holders.
        You may request written permission by emailing the authors.

                For information regarding this software email:
                               Joseph Coffland
                        joseph@cauldrondevelopment.com

\******************************************************************************/

#ifndef CBANG_JSON_LIST_H
#define CBANG_JSON_LIST_H

#include "Value.h"

#include <vector>


namespace cb {
  namespace JSON {
    class List : public Value, public std::vector<ValuePtr> {
      typedef std::vector<ValuePtr> Super_T;

      bool simple;

    public:
      List() : simple(true) {}

      // From std::vector<ValuePtr>
      using std::vector<ValuePtr>::operator[];

      // From Value
      ValueType getType() const {return JSON_LIST;}
      ValuePtr copy(bool deep = false) const;
      bool isSimple() const {return simple;}
      using Value::getList;
      List &getList() {return *this;}
      const List &getList() const {return *this;}
      unsigned size() const {return std::vector<ValuePtr>::size();}
      const ValuePtr &get(unsigned i) const
      {return std::vector<ValuePtr>::at(i);}
      void appendNull();
      void appendBoolean(bool value);
      void append(double value);
      void append(const std::string &value);
      void append(const ValuePtr &value);
      void write(Sink &sink) const;
    };
  }
}

#endif // CBANG_JSON_LIST_H
