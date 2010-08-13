/*
 * Copyright (C) 2010 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "IDBFactoryBackendImpl.h"

#include "DOMStringList.h"
#include "IDBDatabaseBackendImpl.h"
#include "SecurityOrigin.h"
#include <wtf/Threading.h>
#include <wtf/UnusedParam.h>

#if ENABLE(INDEXED_DATABASE)

namespace WebCore {

PassRefPtr<IDBFactoryBackendImpl> IDBFactoryBackendImpl::create()
{
    return adoptRef(new IDBFactoryBackendImpl);
}

IDBFactoryBackendImpl::IDBFactoryBackendImpl()
{
}

IDBFactoryBackendImpl::~IDBFactoryBackendImpl()
{
}

void IDBFactoryBackendImpl::open(const String& name, const String& description, PassRefPtr<IDBCallbacks> callbacks, PassRefPtr<SecurityOrigin>, Frame*)
{
    RefPtr<IDBDatabaseBackendInterface> databaseBackend;
    IDBDatabaseBackendMap::iterator it = m_databaseBackendMap.find(name);
    if (it == m_databaseBackendMap.end()) {
        // FIXME: What should the version be?  The spec doesn't define it yet.
        databaseBackend = IDBDatabaseBackendImpl::create(name, description, "");
        m_databaseBackendMap.set(name, databaseBackend);
    } else
        databaseBackend = it->second;

    callbacks->onSuccess(databaseBackend.release());
}

} // namespace WebCore

#endif // ENABLE(INDEXED_DATABASE)
