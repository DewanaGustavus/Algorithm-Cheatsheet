for((i = 1; i<=100; ++i)); do # nge loop
    echo $i # tc ke-i
    ./generator.exe > countertc # bikin tc
    ./bruteforce.exe < countertc > outbrute # redirect tc ke stdin, redirect stdout ke file
    ./solution.exe < countertc > outsol
    diff -w outbrute outsol || break # compare hasil
done
echo finished # kalo finish berarti AC
