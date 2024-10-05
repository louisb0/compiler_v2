make
./bin $1
as -32 result.asm -o result.o
gcc -m32 -no-pie -o result result.o
rm result.o

./result
