# VulkanPBR

A Vulkan-based physically-based rendering (PBR) framework. Early scaffold — window/context bring-up via GLFW, shaders authored in [Slang](https://github.com/shader-slang/slang).

## Prerequisites

- [Vulkan SDK](https://vulkan.lunarg.com/) — installer sets the `VULKAN_SDK` environment variable used by `Code/CMakeLists.txt`
- CMake 3.20+
- A C++17 compiler (MSVC / Visual Studio 2022 recommended on Windows)

## Third-party dependencies

`ThirdParty/` is not checked into this repo (prebuilt binaries, too large / not source). Download and lay it out as follows, next to `Code/`:

```
VulkanPBR/
├── Code/
└── ThirdParty/
    ├── GLFW/
    │   ├── include/GLFW/...
    │   └── lib/glfw3.lib
    └── slang/
        ├── bin/
        ├── include/
        └── lib/
```

- **GLFW** (this project was built against 3.5.1): download the Windows pre-compiled binaries from the [GLFW downloads page](https://www.glfw.org/download.html), or build from source. Copy `include/` and the `lib-vc2022/` (renamed to `lib/`) folders into `ThirdParty/GLFW/`.
- **Slang**: download a release from the [shader-slang/slang releases page](https://github.com/shader-slang/slang/releases) and extract it into `ThirdParty/slang/`.

## Build

```powershell
cd Code
cmake -B out/build/x64-Debug -S .
cmake --build out/build/x64-Debug
```

Or open `Code/` directly in Visual Studio (CMake project support) and build from there.
