MZ=
tail -c[elf_size]>p<$0
chmod +x p
./p "$@"
rm p
exit
