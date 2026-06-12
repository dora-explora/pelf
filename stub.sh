MZ=
tail -c+$size_of_exe>p<$0
chmod +x p
./p $@&rm p
exit
