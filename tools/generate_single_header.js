const fs = require("fs");
const readline = require("node:readline");

const filePath = "../include/ompcapi.h";

const events = require("../apidocs/events.json");

const files = fs
  .readdirSync("../src/Impl", { recursive: true })
  .filter((file) => {
    return file.endsWith("APIs.cpp");
  });

const entityTypes = [
  "Player",
  "Vehicle",
  "Menu",
  "TextDraw",
  "TextLabel",
  "Object",
  "PlayerObject",
  "PlayerTextLabel3D",
  "PlayerTextDraw",
  "Class",
  "GangZone",
  "Pickup",
];

const predefinedTypes = `#ifndef OMPCAPI_H
#define OMPCAPI_H

#include <stdbool.h>
#include <stdint.h>

#ifndef CAPI_COMPONENT_BUILD
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <Windows.h>
#define LIBRARY_OPEN(path) LoadLibrary(path)
#define LIBRARY_GET_ADDR(lib, symbol) GetProcAddress((HMODULE)lib, symbol)
#else
#include <dlfcn.h>
#define LIBRARY_OPEN(path) dlopen(path, RTLD_LAZY | RTLD_LOCAL)
#define LIBRARY_GET_ADDR dlsym
#endif
#endif

// Events

enum EventPriorityType
{
	EventPriorityType_Highest,
	EventPriorityType_FairlyHigh,
	EventPriorityType_Default,
	EventPriorityType_FairlyLow,
	EventPriorityType_Lowest,
};

struct EventArgs_Common
{
	uint8_t size;
	void** list;
};

typedef bool (*EventCallback_Common)(struct EventArgs_Common* args);

// Components

struct ComponentVersion
{
	uint8_t major; ///< MAJOR version when you make incompatible API changes
	uint8_t minor; ///< MINOR version when you add functionality in a backwards compatible manner
	uint8_t patch; ///< PATCH version when you make backwards compatible bug fixes
	uint16_t prerel; ///< PRE-RELEASE version
};

typedef void (*ComponentOnInitCallback)();
typedef void (*ComponentOnReadyCallback)();
typedef void (*ComponentOnResetCallback)();
typedef void (*ComponentOnFreeCallback)();
typedef void (*ComponentOnLoadCallback)(void* core);

struct CAPIStringView
{
	unsigned int len;
	char* data;
};

#ifndef CAPI_COMPONENT_BUILD

`;

fs.writeFileSync(filePath, predefinedTypes);

fs.appendFileSync(
  filePath,
  entityTypes
    .map((type) => {
      return `typedef void* ${type};\n`;
    })
    .join("")
);

const APIs = {};

const convertTypeNames = (type) => {
  if (type === "StringCharPtr") {
    return "const char*";
  } else if (type === "objectPtr") {
    return "void*";
  } else if (type === "voidPtr") {
    return "void*";
  } else if (type === "OutputStringViewPtr") {
    return "struct CAPIStringView*";
  } else {
    return type;
  }
};

files.forEach(async (file, index) => {
  const data = fs.createReadStream("../src/Impl/" + file);
  const lines = readline.createInterface({
    input: data,
    crlfDelay: Infinity,
  });

  for await (const line of lines) {
    if (line.startsWith("OMP_CAPI(")) {
      const v0 = line.replace("OMP_CAPI(", "");
      const name_full = v0.split(", ")[0];
      const group = name_full.split("_")[0];
      const name = name_full.split("_")[1];

      if (APIs[group] === undefined) {
        APIs[group] = [];
      }

      const v1 = v0.split(", ")[1];
      const ret = v1.substring(0, v1.indexOf("("));
      const v2 = v0.replace(`OMP_CAPI(${name}, ${ret}`, "");
      const params = v2
        .substring(v2.indexOf("(") + 1, v2.indexOf(")"))
        .split(", ")
        .map((param) => {
          const name = param.split(" ")[1];
          const type = param.split(" ")[0];

          if (name === undefined) {
            return undefined;
          }

          return {
            name,
            type: convertTypeNames(type),
          };
        });

      APIs[group].push({
        ret: convertTypeNames(ret),
        name,
        params: params.length === 1 && params[0] === undefined ? [] : params,
      });
    }
  }

  if (index == files.length - 1) {
    generateFunctions(APIs);

    fs.appendFileSync(filePath, `\n#endif\n\n#endif /* OMPCAPI_H */\n`);
  }
});

const generateFunctions = (apis) => {
  const entries = Object.entries(apis);
  entries.forEach(([group, funcs], index) => {
    fs.appendFileSync(filePath, `\n\n// ${group} function type definitions\n`);
    funcs.forEach((func) => {
      fs.appendFileSync(
        filePath,
        `typedef ${func.ret} (*${group}_${func.name}_t)(${func.params
          .map((param) => `${param.type} ${param.name}`)
          .join(", ")});\n`
      );
    });
  });

  generateEvents(events);

  entries.forEach(([group, funcs], index) => {
    fs.appendFileSync(
      filePath,
      `\n// ${group} functions\nstruct ${group}_t {\n`
    );
    funcs.forEach((func) => {
      fs.appendFileSync(
        filePath,
        `    ${group}_${func.name}_t ${func.name};\n`
      );
    });
    fs.appendFileSync(filePath, `};\n`);
  });

  fs.appendFileSync(
    filePath,
    `\n// All APIs
struct OMPAPI_t {
`
  );

  entries.forEach(([group, funcs], index) => {
    fs.appendFileSync(filePath, `    struct ${group}_t ${group};\n`);
  });

  fs.appendFileSync(filePath, `};\n`);

  fs.appendFileSync(
    filePath,
    `
static void omp_initialize_capi(struct OMPAPI_t* ompapi) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    void* capi_lib = LIBRARY_OPEN("./components/$CAPI.dll");
#else
    void* capi_lib = LIBRARY_OPEN("./components/$CAPI.so");
#endif
`
  );

  entries.forEach(([group, funcs], index) => {
    fs.appendFileSync(filePath, `\n    // Retrieve ${group} functions\n`);
    funcs.forEach((func) => {
      fs.appendFileSync(
        filePath,
        `    ompapi->${group}.${func.name} = (${group}_${func.name}_t)LIBRARY_GET_ADDR(capi_lib, "${group}_${func.name}");\n`
      );
    });
  });
  fs.appendFileSync(filePath, `\n    return;\n};\n`);
};

const generateEvents = (events_) => {
  const entries = Object.entries(events_);
  entries.forEach(([group, events], index) => {
    fs.appendFileSync(
      filePath,
      `\n\n// ${group} event type and arguments definitions`
    );
    events.forEach((event) => {
      fs.appendFileSync(
        filePath,
        `
struct EventArgs_${event.name} {
    uint8_t size;
    struct {
${event.args.map((param) => `        ${param.type}* ${param.name};`).join("\n")}
    } *list;
};
typedef bool (*EventCallback_${event.name})(struct EventArgs_${event.name} args);\n`
      );
    });
  });
  fs.appendFileSync(filePath, `\n`);
};

// generateEvents(events);

/*
 const structBegin = `struct ${group} {\n`;
    fs.appendFileSync(filePath, structBegin);
    funcs.forEach(func => {
      fs.appendFileSync(filePath, structBegin);
    })
      */
