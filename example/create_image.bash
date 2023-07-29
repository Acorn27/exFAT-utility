#!/bin/bash

#Set the desired image's name and location
image_name="exfat.img"
image_folder="images"
image_location="."         # create image folder in current directory instead of insde example folder
mount_point="image_directory"

#Create and Navigate to the image foler
mkdir "$image_location/$image_folder"
cd "$image_location/$image_folder"

# Step 4: Create a blank image file
# /dev/zero is a special file that provides an endless stream of null bytes when read
# in the context of creating exfat image, dev/zero help create a blank file filled with zero
# bs (block size): size of each blokc. M stand for megabyte.
# count: total number of blocks to be read
# in this context, bs * count = size of created image (1M * 256 = 256 megabyte = 1/4 gygabyte)
# source: https://www.gnu.org/software/coreutils/manual/html_node/dd-invocation.html#dd-invocation
dd if=/dev/zero of="$image_name" bs=1M count=256

# Step 5: Format the image file with exFAT filesystem
sudo mkfs.exfat "$image_name"

# Step 6: Create a mount point directory
mkdir "$mount_point"

# Step 7: Mount the exFAT image
sudo mount -o loop "$image_name" "$mount_point"

# Additional information and instructions
echo "exFAT image created and mounted successfully."
echo "You can access the contents at: $image_folder/$mount_point"

