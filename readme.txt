1. It is a minimal micropython for XMOS SOC stack extracted from the root Micropython stack available on https://github.com/micropython/micropython.
2. The files have been modified based on the raised warnings and syntactical issues during the compilation. Many additional definitions are to avoid the pointer compatibility issues. 
3. The folder structure also changed, moved all the unused source codes and libraries to excluded folder.
4. If the excluded folder doesn't exist in this version, check the previous version. It has been removed in this version to reduce the overall project folder's size.
5. At present, the main code files are inside the port/minimal. Later on, it might get changed according to the required folder structure.
