@setlocal
@if "%_echo%"=="" echo off

echo Verifying that the Test PCA Certificate is installed...
set __certinstalled=
for /f %%i in ('tfindcer -a"Microsoft Test PCA" -s ca -S ^| findstr /c:"87382E1E D9544D41 ECD4F68C 374E477D 113CF497"') do (
    set __certinstalled=1
)

if defined __certinstalled goto :eof
echo Test PCA does NOT appear to be installed yet.  Installing now...

@rem Install test pca certificate.
certmgr -add %RazzleToolPath%\testpca.cer -r localMachine -s ca

echo Check again to see if Test PCA Certificate is installed...
set __certinstalled=
for /f %%i in ('tfindcer -a"Microsoft Test PCA" -s ca -S ^| findstr /c:"87382E1E D9544D41 ECD4F68C 374E477D 113CF497"') do (
    set __certinstalled=1
)

if defined __certinstalled echo Test PCA installed successfully&&goto :eof
echo Test PCA Certificate still not installed.  You may have to do this manually.  Simply
echo log on as a local administrator and issue the following command:
echo
echo certmgr -add %RazzleToolPath%\testpca.cer -r localMachine -s ca

endlocal
