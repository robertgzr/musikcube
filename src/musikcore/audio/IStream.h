//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004-2021 musikcube team
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the author nor the names of other contributors may
//      be used to endorse or promote products derived from this software
//      without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <musikcore/config.h>
#include <musikcore/sdk/IBuffer.h>
#include <musikcore/sdk/IDecoder.h>
#include <musikcore/sdk/IDSP.h>
#include <musikcore/sdk/IDecoderFactory.h>
#include <musikcore/sdk/IOutput.h>

#include <list>

namespace musik { namespace core { namespace audio {

    class IStream {
        public:
            virtual musik::core::sdk::IBuffer* GetNextProcessedOutputBuffer() = 0;
            virtual void OnBufferProcessedByPlayer(musik::core::sdk::IBuffer* buffer) = 0;
            virtual double SetPosition(double seconds) = 0;
            virtual double GetDuration() = 0;
            virtual bool OpenStream(std::string uri, musik::core::sdk::IOutput* output) = 0;
            virtual void Interrupt() = 0;
            virtual int GetCapabilities() = 0;
            virtual bool Eof() = 0;
            virtual void Release() = 0;
    };

    typedef std::shared_ptr<IStream> IStreamPtr;

} } }
