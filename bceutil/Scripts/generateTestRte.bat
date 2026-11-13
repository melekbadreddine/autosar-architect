@echo off
rem ###########################################################################
rem # Runs ArUnit GMock code generator.
rem ###########################################################################

rem setlocal

set ARUNIT=ArUnit/arunit.bat

if not exist %ARUNIT% (
echo Generator tool not found: %ARUNIT% 1>&2
exit /b 254
)

set INPUT_FILE_LIST_FILE=@../../AutosarModel/AutosarDescriptions.lst
set OUT_DIR=../../test_rte/generated
set AUTOSAR_VERSION=40

set CONFIG_FILE=../Config/GMockGenerator.config
set SWCS=SwcLceComManager SwcLceMaster
set SWCS=%SWCS:"=%

set ARUNIT_OPTIONS=-skipMerge -continueOnError -v %AUTOSAR_VERSION% -allTypes -implicitCompositions
set GENERATORS=gmock_ext_config
set OUTPUT_PATHS=-gmock_ext_output_path %OUT_DIR%
set GENERATOR_OPTIONS=-gmock_ext_config_file %CONFIG_FILE%
set COMPONENTS=-components %SWCS%

echo Starting ArUnit. This may take a minute or two...
rem echo %ARUNIT% -input "%INPUT_FILE_LIST_FILE%" -generate %GENERATORS% %OUTPUT_PATHS% %CAF_FILE_PATH% %GENERATOR_OPTIONS% %ARUNIT_OPTIONS% %COMPONENTS%
call %ARUNIT% -input "%INPUT_FILE_LIST_FILE%" -generate %GENERATORS% %OUTPUT_PATHS% %GENERATOR_OPTIONS% %ARUNIT_OPTIONS% %COMPONENTS%

if not errorlevel 1 (
    rem ArUnit generates std::numeric_limits usages without including ^<limits^>.
    rem Ensure the include is present so the generated code compiles cleanly.
    powershell -NoProfile -Command "$files = Get-ChildItem '..\..\test_rte\generated\Rte_*_CanoeTraceDump.cpp'; foreach ($f in $files) { $c = Get-Content $f.FullName -Raw; if ($c -notmatch 'include <limits>') { $c = $c -replace '#include <stdexcept>', \"#include <stdexcept>`r`n#include <limits>\"; Set-Content $f.FullName $c; Write-Host ('Patched missing <limits> include: ' + $f.FullName) } }"
)