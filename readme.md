# Nile

## Develop

Below we assume that the following environment variables are set:

- `VULKAN_SDK` should point to the sdk home, e.g. `~/VulkanSDK/1.3.296.0/macOS`.

### MacOS

When generating the project, and when running the executable, some environment variables need to be set.

Set them yourself or use `./scripts/env-macos.sh` to set them:
```shell
source ./scripts/env-macos.sh
```

### Build

Generate project
```shell
cmake -H. -Bbuild
```

Build
```shell
cmake --build build -- -j 4
```

Alternatively, to build in debug mode:
```shell
cmake --build build --config Debug -- -j 4
```

### Run

```shell
./out/bin/nile_app
```