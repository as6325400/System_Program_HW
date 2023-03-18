for i in {1,50,500};
do
    for j in {100,4096,8192,16384};
    do
        num=$(($i * 1024))
        dd if=/dev/zero of="./${i}mb_file_for_buffSize${j}" bs=1024 count=$num;
    done
done

for i in 1 2 3 4
do
    num=$((512 * 1024))
    dd if=/dev/zero of="./512mb_file${i}" bs=1024 count=$num
done