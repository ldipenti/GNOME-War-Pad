#!/usr/bin/perl -w
#
#  Display contents of a XYPLAN.DAT file
#
#  Usage: perl plcat.pl gamedir\xyplan.dat
#
#  This will output all X,Ys of all planets. You can then use a
#  program like GNUPLOT to plot these, or import it into a
#  spreadsheet.
#

use strict;
use vars qw{ @list $data };

my $file = shift @ARGV or die "usage: $0 filename";

# read file
open FILE, "< $file" or die "$file: $!";
binmode FILE;
for (1..500) {
  read FILE, $data, 6;
  push @list, $data;
}
close FILE;

# print it out
for (1..500) {
  my ($x, $y, $o) = unpack "v3", $list[$_-1];
#  printf "%3d: (%d, %d)\n", $_, $x, $y;
  printf "%d, %d\n", $x, $y;
}
