# Automated builds

This project uses GitHub Actions to build the Qt desktop GUI.

- `build-windows.yml` builds a Windows x64 Release, deploys the Qt runtime with `windeployqt`, and uploads `tr4mpass-windows-x64.zip`.
- `build-linux.yml` builds the Linux x64 application and uploads the executable.
- `build-matrix.yml` performs a Linux Debug build on pull requests as a fast compilation check.

Use **Actions → Build Windows Qt Application → Run workflow** to manually start a Windows build.
