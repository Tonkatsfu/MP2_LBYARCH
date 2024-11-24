nasm -f win64 mp2asm.asm
gcc -c mp2c.c -o mp2c.obj -m64
gcc mp2c.obj mp2asm.obj -o mp2.exe -m64
mp2.exe < specsInput.txt
