#!/usr/bin/perl

use warnings;
use strict;
use 5.020;

my @INPUT_FILE = @ARGV;

sub translate_sel {
    my @sel  = @_;
    my @data = split( '\|', $sel[0] );
    my $recode_type;
    if ( $data[3] =~ /OEM\srecord\s([0-9,a-f]{2})/gm ) {
        given ($1) {
            when ('c0') { $data[3] = "Dump MSR"; }
            when ('c1') { $data[3] = "CPLD Error Record"; }
            when ('c2') { $data[3] = "Boot up event"; }
        }
        @data;
    }
    else {
        @sel;
    }

}

open( my $fh, '<', @INPUT_FILE )
  or die "can not open the file";

while ( my $sel = <$fh> ) {
    my @data        = split( '\|', $sel );
    my $recode_type = '';
    my $recode_data = '';
    print &translate_sel($sel);

}

exit(0);
