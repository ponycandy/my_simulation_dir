@echo off
echo Deleting .exp, .ilk, and .pdb files in the parent directory...

cd ..
del /q *.exp
del /q *.ilk
del /q *.pdb

echo Deletion complete.
pause