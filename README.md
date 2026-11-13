# autosar-architect — BCE Exterior Light (AUTOSAR)

Implementation and unit-test environment for the **BCE 2024 (Body & Comfort ECU)
Exterior Light** application, described with AUTOSAR 4.2.2 arxml models and
verified with a generated **Test RTE** (GMock based) produced by the BMW
**ArUnit** headless generator.

Original SWC code and AUTOSAR descriptions by Abderrahmen Hammami
(Primatec Engineering — see `specification/BCE_2024_specification.pdf`).

---

## 1. Repository layout

```
apps/                     Hand-written AUTOSAR software components (SWCs)
  light/lce/swc_lce_com_manager/   SwcLceComManager (rte gateway SWC)
  light/lce/swc_lce_master/        SwcLceMaster (light function decision SWC)
    arxml/components/    AUTOSAR component type description
    arxml/interfaces/    AUTOSAR sender/receiver interfaces + data types
    include/, src/       SWC C++ code + RTE entry points
    test/gtest/          GMock unit tests (built against the test RTE)
bceutil/                  ArUnit headless code generator (Eclipse/Equinox)
  Scripts/generateTestRte.sh|.bat   RTE generation entry points
  Scripts/ArUnit/arunit.sh          Java launcher for the generator
  Config/GMockGenerator.config      per-SWC generation configuration
  Ar4Spec/, Autosar/                AUTOSAR platform / standard type packs
AutosarModel/             List of arxml files fed to the generator
test_rte/generated/       Generated test RTE (ArUnit output, committed)
lib/gtest/                Vendored googletest / googlemock
specification/            BCE exterior light specification (PDF)
test_rte/rte_platform/    Hand-maintained RTE platform headers (Rte.h)
.github/workflows/ci.yml  CI/CD pipeline (GitHub Actions)
Dockerfile                Pinned toolchain image (JDK 8 + build tools)
Makefile                  Convenience targets (build / test / rte / docker-*)
```

## 2. AUTOSAR model

### SwcLceComManager (package `primatec/light/lceComManager`)

Receives data from external ECUs (LIN/CAN) and forwards the light control
signals to the light slave managers (FLSM/RLSM) — see spec sections 5–7.

| Port | Direction | Interface | Data elements |
|---|---|---|---|
| `comCTR_EL_F` | provided (P) | `IComCTR_EL_F` | `CTR_FN_DR`, `CTR_FN_POS`, `CTR_FN_PAR` |
| `comCTR_EL_R` | provided (P) | `IComCTR_EL_R` | `CTR_FN_DR`, `CTR_FN_POS`, `CTR_FN_PAR` |
| `comLight_Ctrl_Inputs` | required (R) | `IComLight_Ctrl_Inputs` | `ST_LP_LIN` (LCU status) |
| `comBrightness_Rain_Sensor` | required (R) | `IComBrightness_Rain_Sensor` | `ST_RB_LIN` (BRS status) |
| `comCar_State` | required (R) | `IComCar_State` | `VEH_ST` (PWF state) |
| `comMotor_Speed` | required (R) | `IComMotor_Speed` | `Motor_Speed` |

Behavior: init runnable + 10 ms timing event
(`RTERunnable_SwcLceComManager_RunComMngr_10msTask`) reading all four input
ports and writing both `CTR_EL_F` / `CTR_EL_R` control messages.

### SwcLceMaster (package `primatec/light/lceMaster`)

Decides whether the exterior light functions shall be activated based on the
control signals produced by `SwcLceComManager`.

| Port | Direction | Interface | Data elements |
|---|---|---|---|
| `comCTR_EL_F` | required (R) | `IComCTR_EL_F` | `CTR_FN_DR`, `CTR_FN_POS`, `CTR_FN_PAR` |
| `comCTR_EL_R` | required (R) | `IComCTR_EL_R` | `CTR_FN_DR`, `CTR_FN_POS`, `CTR_FN_PAR` |

Behavior: init runnable + 10 ms timing event
(`RTERunnable_SwcLceMaster_RunMaster_10msTask`) reading the six control
signals.

All data elements are AUTOSAR `uint8` base types
(`/AUTOSAR_Platform/BaseTypes/uint8`).

## 3. Milestone 1 — errors found and fixed

* `SwcLceComManager.cpp`
  * duplicate `init()` definition (compile error) — removed
  * `writeOutputs()` contained a truncated statement (`rte_wri`) — implemented
    all six RTE writes (`CTR_EL_F` and `CTR_EL_R`, signals DR/POS/PAR)
  * `readInputs()` only read 2 of the 4 input ports modeled in the arxml —
    now reads all four (LCU, BRS, VEH_ST, Motor_Speed)
* `SwcLceComManager.h` / `SwcLceMaster.h` — used RTE data types without
  including `Rte_Type.h`; added the include and the missing members
  (`vehSt`, `motorSpeed`, master control-signal members)
* `Rte_SwcLceMaster.cpp` — entry point named `..._RunComMngr_10msTask`
  (copy-paste error) — renamed to `..._RunMaster_10msTask`
* **Missing** `IComCTR_EL_R.arxml` — the component referenced it but it was
  never defined, so no `comCTR_EL_R` APIs were generated — created it
* `IComCTR_EL_F.arxml` — three separate `<DATA-ELEMENTS>` blocks (schema
  invalid) — merged into one block with three data elements
* **Missing** `SwcLceMaster.arxml` component description — created (both SWCs
  are now modeled and generatable)
* `AutosarModel/AutosarDescriptions.lst` — Windows backslash paths (did not
  work on Linux); converted to forward slashes and added the new arxml files
* `bceutil/Scripts/generateTestRte.bat` — only generated the RTE for
  `SwcLceComManager`; extended to both SWCs and added a Linux equivalent
  `generateTestRte.sh`
* **Missing** `Rte.h` — included by the generated `Rte_Type.h` but absent;
  added (provides `Std_ReturnType` and standard return values)
* `lib/gtest/CMakeLists.txt` — source paths had a duplicated `lib/gtest/`
  prefix, so the target had no sources; fixed
* Per-SWC `CMakeLists.txt` files (4 files) were empty — implemented

## 4. Milestone 2 — Test RTE generation

The test RTE is generated with the ArUnit headless GMock generator
(`gmock_ext_config`) directly from the arxml model:

```bash
# Linux (requires Java 8 on PATH)
cd bceutil/Scripts
./generateTestRte.sh

# Windows
bceutil\Scripts\generateTestRte.bat
```

Input file list: `AutosarModel/AutosarDescriptions.lst`
Output: `test_rte/generated/` (committed to the repository)

Generated per SWC:

| File | Purpose |
|---|---|
| `Rte_<SWC>.h/.cpp` | RTE port API declarations and mock delegation |
| `Rte_<SWC>_Interface.h` | abstract RTE interface class |
| `Rte_<SWC>_Mock.h/.cpp` | GMock mock of the RTE |
| `Rte_<SWC>_BufferDecorator.*` | captures written/read values for assertions |
| `Rte_<SWC>_TraceDecorator.*` | records RTE calls with timestamps |
| `Rte_<SWC>_CanoeTraceDump.*` | CANoe-compatible trace dump |
| `Rte_<SWC>_Type.h`, `Rte_Type.h` | RTE data types and CDS |
| `<SWC>_FixtureBase.*` | base test fixture (time control + scheduling) |

`Rte.h` (RTE base header with `Std_ReturnType`) is hand-maintained in
`test_rte/rte_platform/` — deliberately **outside** the generator output
directory so that regeneration (or ArUnit's `-clean_output` flag) can never
delete it.

Generation is **reproducible**: regenerating from the current model produces
byte-identical output to the committed files. The generation scripts apply a
post-processing patch because ArUnit emits `std::numeric_limits` usages
without the `<limits>` include.

Toolchain notes:
* The generator requires **Java 8** (2021-era Eclipse Equinox tooling).
* The committed OSGi storage tables under `bceutil/Scripts/ArUnit/configuration/`
  were regenerated from a corrupt Windows state; if you ever hit
  `java.io.IOException: ReliableFile is corrupt`, delete
  `configuration/org.eclipse.osgi/.manager/.fileTable*` and rerun — Equinox
  rebuilds them.

## 5. Milestone 3 — build and test

Requires CMake ≥ 3.10 and a C++14 compiler.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
ctest --test-dir build --output-on-failure
```

Targets:

| Target | Content |
|---|---|
| `lib_gtest` | vendored googletest + googlemock |
| `test_rte` | generated test RTE for both SWCs |
| `swc_lce_com_manager` / `swc_lce_master` | SWC static libraries |
| `swc_lce_com_manager_test` / `swc_lce_master_test` | GMock test executables |

## 6. Milestone 4 — verification and CI/CD

### Verification performed

1. **SWC code correctness** — clean-room build of all targets from scratch.
2. **RTE generation** — both SWCs generated by the real ArUnit toolchain
   (`Generating code for 2 SWCs... Code Generator finished successfully`).
3. **RTE correctness/reproducibility** — fresh regeneration is byte-identical
   to the committed output; the RTE APIs match exactly the `Rte_Read_*` /
   `Rte_Write_*` calls used by the SWC code (verified for all 16 port APIs).
4. **Runtime behavior** — unit tests run the SWCs through the generated
   fixture and assert the RTE data flow (reads propagate to SWC members,
   writes propagate to the RTE buffers, scheduling every 10 ms).

Current suite (all passing):

* `SwcLceComManagerTest` — forwards control signals on both `CTR_EL_F`/`CTR_EL_R`,
  reads all four inputs, 10 ms scheduling (not before t=10, twice within 20 ms)
* `SwcLceMasterTest` — reads the six control signals, 10 ms scheduling

### GitHub Actions (`.github/workflows/ci.yml`)

Two jobs run on every push/PR to `main`:

| Job | What it does |
|---|---|
| `build-and-test` | CMake configure → build → `ctest` |
| `rte-generation` | Installs JDK 8 (Temurin), regenerates the test RTEs from the model with ArUnit, then `git diff --exit-code -- test_rte/generated` fails the build if the committed RTEs are out of date with the model |

### Makefile / Docker

```bash
make build    # CMake configure + build
make test     # build + ctest
make rte      # regenerate the test RTEs (needs Java 8 locally)
make clean    # remove the build directory

make docker-test    # build + unit tests inside the pinned container
make docker-rte     # regenerate the test RTEs inside the container
```

The `Dockerfile` pins the full toolchain (Eclipse Temurin JDK 8, CMake,
GCC) so the 2021-era ArUnit generator and the build can be reproduced on
any machine without installing Java 8 locally. The containerized
regeneration was verified to produce byte-identical output to the
committed RTEs.

## 7. Functional behavior (per BCE specification)

Implemented so far (plumbing verified by tests):

* `SwcLceComManager::run10ms()` — reads LCU status (`ST_LP_LIN`), BRS status
  (`ST_RB_LIN`), vehicle state (`VEH_ST`) and motor speed (`Motor_Speed`),
  then forwards the driving/position/parking control signals (`CTR_FN_DR`,
  `CTR_FN_POS`, `CTR_FN_PAR`) on both CAN messages `CTR_EL_F` (front light
  slave manager) and `CTR_EL_R` (rear light slave manager).
* `SwcLceMaster::run10ms()` — reads the six control signals; the
  activation/deactivation decision logic (spec activation tables) is still a
  placeholder and can be implemented against the generated fixture tests.

## 8. Architect's roadmap (recommended next steps)

Deliberately **not** done so far, in priority order:

1. **System composition arxml** — the model currently has no
   `COMPOSITION-SW-COMPONENT-TYPE` with assembly connectors
   (`SwcLceComManager.comCTR_EL_F` → `SwcLceMaster.comCTR_EL_F`, etc.). Add
   it together with the Master decision logic, enable the composition in the
   generator (`-implicitCompositions` is already set), and add integration
   tests that connect both SWCs through the generated RTE.
2. **Master decision logic** — implement the activation/deactivation tables
   from the specification (driving/position/parking light, battery rescue
   mode, unsafe vehicle state handling).
3. **AUTOSAR schema validation in CI** — `xmllint` the arxml files against
   `autosar_4-2-2.xsd` (the xsd is currently not vendored in the repo).
4. **Windows CI job** — the `.bat` workflow exists; a `windows-latest`
   build job would guard MSVC compatibility (the vendored gtest already
   carries the `_VARIADIC_MAX` workaround).
5. **LICENSE** — the repository has no license file; the owner should pick
   one (the SWC code carries Primatec Engineering attribution).
