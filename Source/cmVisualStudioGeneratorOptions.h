/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#ifndef cmVisualStudioGeneratorOptions_h
#define cmVisualStudioGeneratorOptions_h

#include <cmConfigure.h>

#include <iosfwd>
#include <string>

#include "cmGlobalVisualStudioGenerator.h"
#include "cmIDEFlagTable.h"
#include "cmIDEOptions.h"

class cmLocalVisualStudioGenerator;

typedef cmIDEFlagTable cmVS7FlagTable;

class cmVisualStudio10TargetGenerator;

class cmVisualStudioGeneratorOptions : public cmIDEOptions
{
public:
  // Construct an options table for a given tool.
  enum Tool
  {
    Compiler,
    ResourceCompiler,
    MasmCompiler,
    NasmCompiler,
    Linker,
    FortranCompiler,
    CSharpCompiler
  };
  cmVisualStudioGeneratorOptions(cmLocalVisualStudioGenerator* lg, Tool tool,
                                 cmVS7FlagTable const* table,
                                 cmVS7FlagTable const* extraTable = 0,
                                 cmVisualStudio10TargetGenerator* g = 0);

  cmVisualStudioGeneratorOptions(cmLocalVisualStudioGenerator* lg, Tool tool,
                                 cmVisualStudio10TargetGenerator* g = 0);

  // Add a table of flags.
  void AddTable(cmVS7FlagTable const* table);

  // Store options from command line flags.
  void Parse(const char* flags);
  void ParseFinish();

  // Fix the ExceptionHandling option to default to off.
  void FixExceptionHandlingDefault();

  // Store options for verbose builds.
  void SetVerboseMakefile(bool verbose);

  // Check for specific options.
  bool UsingUnicode() const;
  bool UsingSBCS() const;

  bool IsDebug() const;
  bool IsWinRt() const;
  bool IsManaged() const;
  // Write options to output.
  void OutputPreprocessorDefinitions(std::ostream& fout, const char* prefix,
                                     const char* suffix,
                                     const std::string& lang);
  void OutputFlagMap(std::ostream& fout, const char* indent);
  void OutputAdditionalOptions(std::ostream& fout, const char* prefix,
                               const char* suffix);
  void SetConfiguration(const char* config);

private:
  cmLocalVisualStudioGenerator* LocalGenerator;
  cmGlobalVisualStudioGenerator::VSVersion Version;

  std::string Configuration;
  Tool CurrentTool;
  cmVisualStudio10TargetGenerator* TargetGenerator;

  bool FortranRuntimeDebug;
  bool FortranRuntimeDLL;
  bool FortranRuntimeMT;

  virtual void StoreUnknownFlag(const char* flag);
};

#endif
