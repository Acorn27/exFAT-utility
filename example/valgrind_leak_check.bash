# create mock exfat image
bash create_image.bash

# move to paren directory
cd ..

# build exfat
bazel build main:exfat

# calling valgrind for leak check
valgrind --leak-check=full bazel-bin/main/exfat -i images/exfat.img -o images/exfat_clone.img -c

#clean up
cd example
bash cleanup_image.bash
