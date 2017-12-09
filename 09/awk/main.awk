BEGIN {
    FS="";
} 

{
    score     = 0; /* the score (part 1) */
    garbage   = 0; /* number of garbage characters (part 2) */
    open      = 0; /* currently open groups */
    ingarbage = 0; /* garbage mode indicator */

    for (i = 1; i <= NF; i++) {
        if ($i == "!") {
            /* skip next */
            i++;
        } else if (ingarbage) { 
            if ($i == ">") {
                /* end garbage mode */
                ingarbage = 0;
            } else {
                /* count garbage (for part 2) */
                garbage++;
            }
        } else if ($i == "{") {
            open++;
            score += open;
        } else if ($i == "}") {
            open--;
        } else if ($i == "<") {
            /* start garbage mode */
            ingarbage = 1;
        }
    }
    print "score", score;
    print "garbage", garbage
}
