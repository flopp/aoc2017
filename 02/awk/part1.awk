{
    min=$1; max=$1;
    for (i=2; i<=NF; i++) {
        min = (min < $i ? min : $i);
        max = (max > $i ? max : $i);
    }
    sum += max - min;
}
END {
    print sum;
}
