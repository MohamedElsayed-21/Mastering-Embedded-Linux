
# in the past they use this variable to make the systemd as a init manager . 
# it is exist in meta/conf/distro/include/init-manager-systemd.inc
# install systemd  as init manager 
#DISTRO_FEATURES:append=" systemd " 
# select systemd as init manager 
#VIRTUAL-RUNTIME_init_manager="systemd"
#VIRTUAL-RUNTIME_initscripts="systemd-compat-units"
# select busybox-mdev as device manager 
#VIRTUAL-RUNTIME_dev_manager="busybox-mdev"


# just use this variable . 
INIT_MANAGER = "systemd"
