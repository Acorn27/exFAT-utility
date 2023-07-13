#check create_image.bash
image_name="exfat.img"
image_folder="images"
mount_point="image_directory"

# un mount image
sudo umount ../"$image_folder"/"$mount_point"

# clean up image and mounted folder
rm -rf ../"$image_folder"/"$mount_point"
rm ../"$image_folder"/"$image_name"
rmdir ../"$image_folder"

# Additional information and instructions
echo "exFAT image unmounted and removed successfully."
echo "Keep up with the good habit!"