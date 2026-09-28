# tr4mpass Qt Desktop UI

This is a clean Qt Widgets desktop interface separated from the existing low-level device/bypass implementation.

## Build with Qt Creator

1. Open the repository folder in Qt Creator.
2. Select the root `CMakeLists.txt`.
3. Configure a Qt 6 kit (Qt 5 is also accepted by the CMake project).
4. Build the `tr4mpass-gui` target.

The GUI intentionally exposes only non-destructive inspection, local diagnostics, activity, feedback, settings and presentation controls. It does not invoke activation-lock bypass or exploit routines.
