#!/usr/bin/perl -w
#
#  Parse KOREx.DAT file to stdout
#
#  Usage: parsekore.pl KOREx.DAT
#
#  The KOREx.DAT file contains: mine fields, ion storms, explosions,
#  Ufos, and additional visual contacts. In particular, it has "true"
#  minefield data for your race: if one of your minefields is not in
#  koreX.dat, it is gone.
#

use strict;

if (@ARGV != 1) { die "usage: $0 koreX.dat\n" }

open FILE, "< $ARGV[0]" or die "$ARGV[0]: $!\n";
binmode FILE;

my $data;

# parse initial junk
read FILE, $data, 102;
parse_junk ($data);

# minefields
read FILE, $data, 500*8;
parse_minefields ($data);

# storms
read FILE, $data, 12*50;
parse_storms ($data);

# bangs
read FILE, $data, 50*4;
parse_bangs ($data);

# ufos
read FILE, $data, 78*100;
parse_ufos ($data, 0);

# avcs
read FILE, $data, 4;
if ($data eq '1120') {
    read FILE, $data, 16;   # skip junk
    read FILE, $data, 4;
    my $count = unpack "V", $data;
    read FILE, $data, 34*$count;
    parse_avcs ($data, 1);
}

close FILE;
exit 0;

sub parse_junk {
    my ($turn, $j1, $sig, $j2) = unpack "vA7A10A*", shift;
    print "=== Header ===\n";
    print "Turn number:   $turn\n";
}

sub parse_minefields {
    my @data = unpack "v*", shift;
    print "=== Minefields ===\n";
    for (1..int(@data/4)) {
         my ($x, $y, $r, $owner) = splice @data, 0, 4;
         if ($owner) {
              print "+ Minefield #$_\n";
              print "  - Location:  ($x, $y)\n";
              print "  - Radius:    $r ly\n";
              if ($owner == 12) {
                  print "  - Owner:     7 (WEB MINE FIELD)\n"
              } else {
                  print "  - Owner:     $owner\n"
              }
         }
    }
}

sub parse_storms {
    my @data = unpack "v*", shift;
    print "=== Ion Storms ===\n";
    for (1..int(@data/6)) {
        my ($x, $y, $r, $volt, $warp, $head) = splice @data, 0, 6;
        if ($volt) {
            print "+ Storm #$_
  - Location:  ($x, $y)
  - Radius:    $r ly
  - Voltage:   $volt MeV
  - Speed:     warp $warp
  - Heading:   $head degrees\n";
        }
    }
}

sub parse_bangs {
    my @data = unpack "v*", shift;
    print "=== Explosions ===\n";
    for (1..int(@data/2)) {
        my ($x, $y) = splice @data, 0, 2;
        if ($x || $y) { print "+ Explosion $_ at ($x, $y)\n"; }
    }
}

sub parse_ufos {
    my $data = shift;
    my $id = shift;
    print "=== Ufos ===\n";
    while (length($data) >= 78) {
        my ($color, $name, $info1, $info2, $x, $y, $warp, $head,
            $psee, $ssee, $r, $type)
          = unpack"vA20A20A20vvvvvvvv", substr($data, 0, 78);
        $data = substr($data, 78);
        if ($color) {
            print "+ Ufo #$_:
  - Type: '$name'
    . '$info1'
    . '$info2'
  - Color:     $color
  - Type Code: $type
  - Location:  ($x, $y)
  - Radius:    $r ly
  - Speed:     warp $warp
  - Heading:   $head degrees
  - Seen from planets in $psee ly distance
  - Seen from ships in $ssee ly distance\n";
         }
    }
}

sub parse_avcs {
    my ($data, $decrypt) = @_;
    while (length($data) >= 34) {
        my ($id, $owner, $warp, $x, $y, $hull, $head, $name) =
            unpack "vvvvvvvA20", substr($data, 0, 34);
        $data = substr($data, 34);
        if ($decrypt) {
            my @asc = map{ord} split//, $name;
            for (0..$#asc) { $asc[$_] ^= (154-$_) }
            $name = join '', map{chr} @asc;
            $name =~ s/\s+$//;
        }
        print "+ Ship #$id:
  - Name:      $name
  - Owner:     $owner
  - Hull Type: $hull
  - Location:  ($x, $y)
  - Speed:     warp $warp\n";
        if ($head != 65535) { print "  - Heading:   $head degrees\n" }
    }
}
