/*
 *
 *    <COPYRIGHT>
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *      This file specifies types and utility interfaces for managing and
 *      working with CHIP TLV.
 *
 */

#ifndef CHIPTLVUTILITIES_HPP
#define CHIPTLVUTILITIES_HPP

#include <stddef.h>
#include <stdint.h>

#include <CHIPError.h>
#include <CHIPTLV.h>

namespace chip {

namespace TLV {

/**
 *   @namespace chip::TLV::Utilities
 *
 *   @brief
 *     This namespace includes types and utility interfaces for managing and
 *     working with CHIP TLV.
 *
 */
namespace Utilities {

typedef CHIP_ERROR (*IterateHandler)(const TLVReader &aReader, size_t aDepth, void *aContext);

extern CHIP_ERROR Iterate(const TLVReader &aReader, IterateHandler aHandler, void *aContext);
extern CHIP_ERROR Iterate(const TLVReader &aReader, IterateHandler aHandler, void *aContext, const bool aRecurse);

extern CHIP_ERROR Count(const TLVReader &aReader, size_t &aCount);
extern CHIP_ERROR Count(const TLVReader &aReader, size_t &aCount, const bool aRecurse);

extern CHIP_ERROR Find(const TLVReader &aReader, const uint64_t &aTag, TLVReader &aResult);
extern CHIP_ERROR Find(const TLVReader &aReader, const uint64_t &aTag, TLVReader &aResult, const bool aRecurse);

extern CHIP_ERROR Find(const TLVReader &aReader, IterateHandler aHandler, void *aContext, TLVReader &aResult);
extern CHIP_ERROR Find(const TLVReader &aReader, IterateHandler aHandler, void *aContext, TLVReader &aResult, const bool aRecurse);
} // namespace Utilities

} // namespace TLV

} // namespace chip

#endif // CHIPTLVUTILITIES_HPP