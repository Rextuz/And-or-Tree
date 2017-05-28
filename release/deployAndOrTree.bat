set deploy_path=C:\Projects\Qt\build-And-or_tree-template-Desktop_Qt_5_5_1_MinGW_32bit-Release\deploy
set mingw_path=e:\Programs\Qt\5.5\mingw492_32\bin\

cd %mingw_path%
e:

set PATH=%mingw_path%
windeployqt %deploy_path%
copy "libgcc_s_dw2-1.dll" %deploy_path%
copy "libstdc++-6.dll" %deploy_path%
copy "libwinpthread-1.dll" %deploy_path%