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

#include "Client.h"
#include "Buffer.h"
#include "PendingRequest.h"

#ifdef HAVE_OPENSSL
#include <cbang/openssl/SSLContext.h>
#else
namespace cb {class SSLContext {};}
#endif

using namespace std;
using namespace cb;
using namespace cb::Event;


Client::Client(Base &base, DNSBase &dns) : base(base), dns(dns) {}


Client::Client(Base &base, DNSBase &dns,
               const SmartPointer<SSLContext> &sslCtx) :
  base(base), dns(dns), sslCtx(sslCtx) {}


Client::~Client() {}


SmartPointer<PendingRequest>
Client::call(const URI &uri, unsigned method, const char *data, unsigned length,
             const SmartPointer<HTTPHandler> &cb) {
  SmartPointer<PendingRequest> req = new PendingRequest(*this, uri, method, cb);
  if (data) req->getOutputBuffer().add(data, length);
  return req;
}


SmartPointer<PendingRequest>
Client::call(const URI &uri, unsigned method, const string &data,
             const SmartPointer<HTTPHandler> &cb) {
#ifdef _WIN32
  return call(uri, method, data.c_str(), data.length(), cb);
#else
  return call(uri, method, data.data(), data.length(), cb);
#endif
}


SmartPointer<PendingRequest> Client::call(const URI &uri, unsigned method,
                                          const SmartPointer<HTTPHandler> &cb) {
  return call(uri, method, 0, 0, cb);
}
