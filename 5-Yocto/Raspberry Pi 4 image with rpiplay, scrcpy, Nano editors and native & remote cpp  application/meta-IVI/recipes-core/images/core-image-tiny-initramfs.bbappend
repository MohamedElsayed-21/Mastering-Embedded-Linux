python tinyinitrd () {
  # Modify our init file so the user knows we drop to shell prompt on purpose
rm "${IMAGE_ROOTFS}/init"
}


# https://docs.yoctoproject.org/4.0.25/dev-manual/building.html#building-an-initial-ram-filesystem-initramfs-image