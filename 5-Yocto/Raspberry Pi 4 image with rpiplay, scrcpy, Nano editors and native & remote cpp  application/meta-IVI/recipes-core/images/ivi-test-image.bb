require  recipes-core/images/rpi-test-image.bb

# if you use :append -you have to use it in conf only- you have to leave blank space after `"` and don't leave space before and after `=` .
#  vice versa in `+=`- in recipes you can use both options :append and += -  you will leave blank space before and after it and not necssary to leave one after `"`

inherit audio
inherit qt-features
inherit network-features

# this feature  alreadey existed in (rpi-test-image.bb --> rpi-base.inc so you don't need to add it again)
# MACHINE_FEATURES += "wifi bluetooth alsa"

IMAGE_INSTALL:append=" vsomeip nano c-helloworld cpp-helloworld appssl can-utils scrcpy"

IMAGE_FEATURES += "ssh-server-openssh debug-tweaks tools-debug x11 tools-sdk"



# Set the root filesystem size
# IMAGE_ROOTFS_SIZE = "16384"
# To run custom commands after the root filesystem is created.
# ROOTFS_POSTPROCESS_COMMAND += "my_custom_script.sh"

