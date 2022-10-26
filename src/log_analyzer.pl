#!/usr/bin/env perl

use strict;
use warnings;

my $file = '../test/test.log';
print $file
open my $info, $file or die "Could not open $file: $!";


while ( my $line = <$info> ) {
    print $line;
    last if $. == 10;
}

close $info;
