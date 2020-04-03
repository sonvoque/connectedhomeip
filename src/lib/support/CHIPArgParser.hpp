/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    Copyright (c) 2017 Nest Labs, Inc.
 *    All rights reserved.
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
 *      Support functions for parsing command-line arguments.
 *
 */

#ifndef CHIPARGPARSER_H_
#define CHIPARGPARSER_H_

#include <core/CHIPCore.h>

#if CHIP_CONFIG_ENABLE_ARG_PARSER

#include <stdio.h>
#include <stdlib.h>

namespace chip {
namespace ArgParser {

struct OptionSet;

/**
 * A function that can be called to handle a set of command line options.
 */
typedef bool (*OptionHandlerFunct)(const char * progName, OptionSet * optSet, int id, const char * name, const char * arg);

/**
 * A function that can be called to handle any remaining, non-option command line arguments.
 */
typedef bool (*NonOptionArgHandlerFunct)(const char * progName, int argc, char * argv[]);

/**
 * Defines the argument requirements for a command line option.
 */
enum OptionArgumentType
{
    kNoArgument       = 0,
    kArgumentRequired = 1,
    kArgumentOptional = 2,
};

/**
 * Defines a command line option.
 */
struct OptionDef
{
    const char * Name;          /**< Long name for the option */
    OptionArgumentType ArgType; /**< An enumerated value specifying whether the option takes an argument */
    uint16_t Id;                /**< An integer id for the option.  If the value falls in the range of
                                     graphical ASCII characters the value is also used as the short name
                                     for the option. */
};

/**
 * Defines a group of logically-related and reusable command line options.
 */
struct OptionSet
{
    OptionHandlerFunct OptionHandler; /**< Pointer to function for processing individual options */
    OptionDef * OptionDefs;           /**< NULL terminated list of option definitions structures. */
    const char * HelpGroupName;       /**< Group name under which options appear in help output */
    const char * OptionHelp;          /**< Help text describing options */
};

/**
 * An OptionSet where the handler is a virtual function.
 */
class OptionSetBase : public OptionSet
{
public:
    OptionSetBase();
    virtual bool HandleOption(const char * progName, OptionSet * optSet, int id, const char * name, const char * arg) = 0;

private:
    static bool CallHandleFunct(const char * progName, OptionSet * optSet, int id, const char * name, const char * arg);
};

extern bool ParseArgs(const char * progName, int argc, char * argv[], OptionSet * optSets[]);
extern bool ParseArgs(const char * progName, int argc, char * argv[], OptionSet * optSets[],
                      NonOptionArgHandlerFunct nonOptArgHandler);
extern bool ParseArgs(const char * progName, int argc, char * argv[], OptionSet * optSets[],
                      NonOptionArgHandlerFunct nonOptArgHandler, bool ignoreUnknown);

extern bool ParseArgsFromString(const char * progName, const char * argStr, OptionSet * optSets[]);
extern bool ParseArgsFromString(const char * progName, const char * argStr, OptionSet * optSets[],
                                NonOptionArgHandlerFunct nonOptArgHandler);
extern bool ParseArgsFromString(const char * progName, const char * argStr, OptionSet * optSets[],
                                NonOptionArgHandlerFunct nonOptArgHandler, bool ignoreUnknown);

extern bool ParseArgsFromEnvVar(const char * progName, const char * varName, OptionSet * optSets[]);
extern bool ParseArgsFromEnvVar(const char * progName, const char * varName, OptionSet * optSets[],
                                NonOptionArgHandlerFunct nonOptArgHandler);
extern bool ParseArgsFromEnvVar(const char * progName, const char * varName, OptionSet * optSets[],
                                NonOptionArgHandlerFunct nonOptArgHandler, bool ignoreUnknown);

extern void PrintOptionHelp(OptionSet * optionSets[], FILE * s);

extern void (*PrintArgError)(const char * msg, ...);
extern void DefaultPrintArgError(const char * msg, ...);

// Utility functions for parsing common argument value types.
extern bool ParseBoolean(const char * str, bool & output);
extern bool ParseInt(const char * str, uint8_t & output);
extern bool ParseInt(const char * str, uint16_t & output);
extern bool ParseInt(const char * str, int32_t & output);
extern bool ParseInt(const char * str, uint32_t & output);
extern bool ParseInt(const char * str, uint64_t & output);
extern bool ParseInt(const char * str, int32_t & output, int base);
extern bool ParseInt(const char * str, uint32_t & output, int base);
extern bool ParseInt(const char * str, uint64_t & output, int base);
extern bool ParseIPAddress(const char * str, chip::Inet::IPAddress & output);
extern bool ParseNodeId(const char * str, uint64_t & nodeId);
extern bool ParseFabricId(const char * str, uint64_t & fabricId, bool allowReserved = false);
extern bool ParseSubnetId(const char * str, uint16_t & subnetId);
extern bool ParseHexString(const char * hexStr, uint32_t strLen, uint8_t * outBuf, uint32_t outBufSize, uint32_t & outDataLen);

extern OptionSet ** gActiveOptionSets;

/**
 * Common OptionSet for handling informational options (--help, --version).
 *
 */
class HelpOptions : public OptionSetBase
{
public:
    const char * AppName;  /**< The name of the command-line application. */
    const char * AppUsage; /**< A short string depicting the application's command-line syntax. */
    const char * AppVersion;
    const char * AppDesc; /**< A description of the application's purpose/behavior. */

    HelpOptions(const char * appName, const char * appUsage, const char * appVersion);
    HelpOptions(const char * appName, const char * appUsage, const char * appVersion, const char * appDesc);

    void PrintBriefUsage(FILE * s);
    void PrintLongUsage(OptionSet * optSets[], FILE * s);
    void PrintVersion(FILE * s);

    virtual bool HandleOption(const char * progName, OptionSet * optSet, int id, const char * name, const char * arg);
};

} // namespace ArgParser
} // namespace chip

#endif // CHIP_CONFIG_ENABLE_ARG_PARSER

#endif // NLARGPARSER_H_
