#!/usr/bin/env bash

# Exit immediately if any command below fails.
set -e

make


echo "Generating a test_files directory.."
mkdir -p test_files
rm -f test_files/*


echo "Generating test files.."
printf "Hello, World!\n" > test_files/ascii.input
printf "Hello, World!" > test_files/ascii2.input
printf "Hello,\x00World!\n" > test_files/data.input
printf "" > test_files/empty.input
### TODO: Generate more test files ###

# ASCII
printf "1234" > test_files/ascii3.input
printf "Punctuation !?;:()[]{}n" > test_files/ascii4.input
printf "Titte bUh\n" > test_files/ascii5.input
printf "William er Dum\n" > test_files/ascii6.input
printf "ABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n0123456789\n" > test_files/ascii7.input
printf "Jeg er traet af at lave testfiler\n" > test_files/ascii8.input
printf "09876543245678901213120398475621736821974872149841728974812947128947128947128471298471247891\n" > test_files/ascii9.input
printf "h\n\n\nn\nh\n\n\nn\nh\n\n\nn\nh\n\n\nn\nh\n\n\nn\n" > test_files/ascii10.input
printf "http://www.example.com\n" > test_files/ascii11.input
printf "sidste test fil\n" > test_files/ascii12.input
printf "Du er verdens bedste TA hvis du giver os maaaax points\n ps tak på forhånd\n" > test_files/ascii13.input

# UTF-8
printf "Hello, Wörld!\n" > test_files/utf8.input
printf "Hello, Wørld!\n" > test_files/utf82.input
printf "Hello, 世界!\n" > test_files/utf83.input
printf "Hello, 世界!\n" > test_files/utf84.input
printf "😀 emoji\n" > test_files/utf85.input
printf "🍝🐥🐜🍆🍑\n" > test_files/utf86.input
printf "¡Hola señor!\n" > test_files/utf87.input
printf "ÆØÅ æøå i en sætning\n" > test_files/utf88.input
printf "JägerBomben\n" > test_files/utf89.input
printf "Smörrebröd\n" > test_files/utf810.input
printf "Café\n" > test_files/utf811.input
printf "Rödgröd med flöde\n" > test_files/utf812.input

# ISO-8859-1
printf "Sm\xF8rrebr\xF8d\n" > test_files/iso1.input   
printf "Caf\xE9\n" > test_files/iso2.input
printf "R\xF8dgr\xF8d med fl\xF8de\n" > test_files/iso3.input
printf "Fu\xDFball\n" > test_files/iso4.input
printf "a\xC5rhus\n" > test_files/iso05.input 
printf "Mix: \xE6\xF8\xE5 / \xC6\xD8\xC5\n" > test_files/iso6.input 
printf "P\xE5 l\xF8rdag skal vi feste hele natten\n" > test_files/iso7.input
printf "T\xE6nk at det ikke er sommer mere!\n" > test_files/iso8.input
printf "1234567890\xE6\xF8\xE5\xC6\xD8\xC5!?\n" > test_files/iso9.input
printf "Gr\xFC\xDF Gott\n" > test_files/iso10.input 
printf "Se\xF1or Pi\xF1ata\n" > test_files/iso11.input
printf "Cr\xE8me br\xFBl\xE9e\n" > test_files/iso12.input 

# Data
printf "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F" > test_files/data2.input
printf "\xFF\xFE\xFD\xFC\xFB\xFA\xF9\xF8\xF7\xF6\xF5\xF4\xF3\xF2\xF1\xF0" > test_files/data3.input
printf "\xDE\xAD\xBE\xEF" > test_files/data4.input
printf "\xBA\xAD\xF0\x0D" > test_files/data5.input
printf "\xCA\xFE\xBA\xBE" > test_files/data6.input
printf "\x00\xFF\x7F\x80" > test_files/data7.input
printf "\xAD\xBE\xEF\xDE" > test_files/data8.input
printf "\xDE\xAD\xC0\xDE" > test_files/data9.input
printf "\xFE\xED\xFA\xCE" > test_files/data10.input
printf "\xBE\xEF\xCA\xFE" > test_files/data11.input
printf "\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xAA\xBB\xCC\xDD\xEE\xFF" > test_files/data12.input









echo "Running the tests.."
exitcode=0
for f in test_files/*.input
do
  echo ">>> Testing ${f}.."
  file    ${f} | sed -e 's/ASCII text.*/ASCII text/' \
                         -e 's/UTF-8 Unicode text.*/UTF-8 Unicode text/' \
                         -e 's/ISO-8859 text.*/ISO-8859 text/' \
                         -e 's/writable, regular file, no read permission/cannot determine (Permission denied)/' \
                         > "${f}.expected"
  ./file  "${f}" > "${f}.actual"

  if ! diff -u "${f}.expected" "${f}.actual"
  then
    echo ">>> Failed :-("
    exitcode=1
  else
    echo ">>> Success :-)"
  fi
done
exit $exitcode
