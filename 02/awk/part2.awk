{
    for (i=1; i<=NF; i++) {
        for (j=i+1; j<=NF; j++) {
            if ($i % $j == 0) {
                sum += $i / $j;
            } else if ($j % $i == 0) {
                sum += $j / $i;
            }
        }
    }
}
END {
    print sum;
}
