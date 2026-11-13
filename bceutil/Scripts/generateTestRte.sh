#!/bin/bash
###########################################################################
# Runs ArUnit GMock code generator (Linux version of generateTestRte.bat).
###########################################################################

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR" || exit 254

ARUNIT=ArUnit/arunit.sh

if [ ! -f "$ARUNIT" ]; then
    echo "Generator tool not found: $ARUNIT" 1>&2
    exit 254
fi

INPUT_FILE_LIST_FILE="@../../AutosarModel/AutosarDescriptions.lst"
OUT_DIR=../../test_rte/generated
AUTOSAR_VERSION=40

CONFIG_FILE=../Config/GMockGenerator.config
SWCS=SwcLceComManager,SwcLceMaster
SWCS=${SWCS//\"/}

ARUNIT_OPTIONS="-skipMerge -continueOnError -v $AUTOSAR_VERSION -allTypes -implicitCompositions"
GENERATORS=gmock_ext_config
OUTPUT_PATHS="-gmock_ext_output_path $OUT_DIR"
GENERATOR_OPTIONS="-gmock_ext_config_file $CONFIG_FILE"
COMPONENTS="-components $SWCS"

echo "Starting ArUnit. This may take a minute or two..."
sh "$ARUNIT" -input "$INPUT_FILE_LIST_FILE" -generate $GENERATORS $OUTPUT_PATHS $GENERATOR_OPTIONS $ARUNIT_OPTIONS $COMPONENTS
