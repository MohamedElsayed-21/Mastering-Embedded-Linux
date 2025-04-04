# Raspberry Pi 4 U-Boot and Kernel Customization Documentation

This documentation provides a step-by-step guide for setting up the toolchain, customizing U-Boot, building the Linux kernel, and creating a minimal root filesystem (RFS) for Raspberry Pi 4.

## 1. Toolchain

### Overview:

The toolchain is essential for cross-compiling software for target architectures. It includes a compiler, linker, and libraries. Different toolchains are available depending on the target architecture (e.g., ARM, x86).

### Setting Up the Toolchain:

Install the required dependencies:

```bash
sudo apt-get install autoconf automake bison bzip2 cmake flex g++ gawk gcc gettext git gperf help2man libncurses5-dev libstdc++6 libtool libtool-bin make patch python3-dev rsync texinfo unzip wget xz-utils
```

Clone, configure, build, and install crosstool-NG:

```bash
git clone https://github.com/crosstool-ng/crosstool-ng.git
cd crosstool-ng
./bootstrap
./configure --prefix=${PWD}
make
make install
export PATH:$PATH:~/x-tools/aarch64-rpi4-linux-gnu/bin
```

### Finding and Building a Toolchain:

Use crosstool-NG to build a toolchain for Raspberry Pi 4:

```bash
bin/ct-ng distclean
bin/ct-ng list-samples
bin/ct-ng aarch64-rpi4-linux-gnu
bin/ct-ng menuconfig
bin/ct-ng build
```

## 2. Bootloader (U-Boot)

### Overview:

The bootloader initializes hardware, loads the kernel, and passes control to it. U-Boot is widely used for embedded systems due to its flexibility and support for multiple platforms.

### Installing Dependencies:

```bash
sudo apt-get install gparted qemu-system device-tree-compiler libgnutls28-dev
```

### Building U-Boot:

Clone the U-Boot repository and configure it for Raspberry Pi 4:

```bash
git clone git://git.denx.de/u-boot.git
cd u-boot
make rpi_4_defconfig
make CROSS_COMPILE=aarch64-rpi4-linux-gnu-
```

### Adding the Header for Compatibility with start.elf:

Download Raspberry Pi tools:

```bash
git clone https://github.com/raspberrypi/tools --depth 1
```

Run the `imagetool-uncompressed.py` script:

```bash
sudo apt update 
sudo apt install python2
python2 ./tools/mkimage/imagetool-uncompressed.py ~/Documents/Mastering_Embedded_Linux/3-Manual-customization/u-boot/u-boot
```

## 3. Kernel

### Overview:

The kernel is the core of the operating system. It interacts with hardware and manages system resources. Different kernel versions cater to various hardware, features, and performance requirements. For more details, refer to the official Raspberry Pi kernel documentation: [Raspberry Pi Linux Kernel Documentation](https://www.raspberrypi.com/documentation/computers/linux_kernel.html).

### Dependencies:

```bash
sudo apt install libncurses5-dev flex bison subversion libssl-dev
sudo apt-get install qemu-system device-tree-compiler
sudo apt install bc libncurses5-dev
```

### Cloning and Configuring the Kernel:

Clone the Raspberry Pi Linux repository:

```bash
git clone --depth=1 https://github.com/raspberrypi/linux
```

Use `menuconfig` to select configuration options:

```bash
cd linux
KERNEL=kernel8
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- bcm2711_defconfig
make ARCH=arm64 menuconfig
```

`menuconfig` reads `KConfig` files and outputs `.config`, which defines the build options.

In `menuconfig`, ensure the following options are enabled (**built-in**, `[ * ]` not `<M>`):

- **`CONFIG_SERIAL_AMBA_PL011`** = **y**
  - Found under:
    `Device Drivers → Character devices → Serial drivers → ARM AMBA PL011 serial port support`
- **`CONFIG_SERIAL_AMBA_PL011_CONSOLE`** = **y**
  - This option typically appears next to or under the PL011 driver option.
  - Allows using `ttyAMA0` as a console.
- **`CONFIG_DEVTMPFS`** and **`CONFIG_DEVTMPFS_MOUNT`** = **y**
  - Found under:
    `Device Drivers → Generic Driver Options`
- **`CONFIG_BLK_DEV_INITRD`** = **y**
  - Under “General setup” or “Device Drivers” depending on your kernel version.
- (Optional) **Early Console** support, such as `CONFIG_EARLY_PRINTK` or `CONFIG_EARLYCON` if available.

### Building the Kernel:

To build the kernel, you can either run the following single command for general output or follow the specific commands below if you need particular types of outputs:

1\. General Command:

```bash
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- Image modules dtbs
```

If successful, the kernel image will be in:

```
arch/arm64/boot/Image
```

You can verify it’s really an ARM64 kernel:

```bash
file arch/arm64/boot/Image
# Should say: "Linux kernel ARM64 boot executable Image, little-endian..."
```

Alternatively, for specific output types, use the following commands:

2\. Specific Outputs:

- **vmlinux** :
  ```bash
  make -j4 ARCH=arm64 CROSS_COMPILE=aarch64-rpi4-linux-gnu-
  ```
- **zImage** :
  ```bash
  make -j4 ARCH=arm64 CROSS_COMPILE=aarch64-rpi4-linux-gnu- Image
  ```
- **uImage** :
  ```bash
  make -j4 ARCH=arm64 CROSS_COMPILE=aarch64-rpi4-linux-gnu- LOADADDR=0x80008000 uImage
  ```

During the build process, `Kbuild` reads the `.config` file to determine build options and integrates them as macros into the source code.

### Booting the Kernel with QEMU:

```bash
qemu-system-aarch64 -M virt -cpu cortex-a53 -m 1G -kernel Image -append "console=ttyAMA0" -nographic
```

## 4. Root Filesystem (RFS)

### Overview:

The root filesystem provides the basic tools and libraries required for the system to boot and operate. BusyBox simplifies this by providing a suite of Unix utilities in a single binary.



### Create a directory to assemble initramfs contents:

```bash
mkdir -p rootfs/{bin,sbin,proc,sys,usr/bin,usr/sbin}

```

### Merging Sysroot with Root Filesystem:

Use `rsync` to merge:

```bash
rsync -avh path/to/sysroot rootfs/
```
### Building BusyBox:

Clone and checkout a stable version of BusyBox:

```bash
git clone git://busybox.net/busybox.git
cd busybox
git checkout 1_36_stable
```

### Install BusyBox to a minimal root filesystem:

```bash
make ARCH=arm64 CROSS_COMPILE=aarch64-rpi4-linux-gnu- menuconfig
#make sure that you disable the (Network -> tc)if you face any issue with it .

make ARCH=arm64 CROSS_COMPILE=aarch64-rpi4-linux-gnu- install 
```

### Creating Initramfs:

```bash
cd rootfs
find . -print0 | cpio --null -ov --format=newc > initramfs.cpio
gzip initramfs.cpio
```

### Boot Kernel with Initramfs:

```bash
qemu-system-aarch64 -M virt -cpu cortex-a53 -m 1G -kernel Image -append "console=ttyAMA0 earlycon=pl011,0x9000000 rdinit=/bin/sh" -initrd <initramfs> -nographic
```
Explanation of Flags

- **`-M virt`**: Use QEMU’s “virt” platform, an emulated machine for 64-bit ARM.
- **`-cpu cortex-a57`**: Emulated CPU type (other valid choices exist, like `cortex-a53`).
- **`-m 1G`**: Allocate 1 GB of RAM to the guest.
- **`-nographic`**: Use the serial console in the terminal (no GUI window).
- **`-kernel ...`**: Path to our newly built ARM64 kernel.
- **`-initrd ...`**: Path to your initramfs CPIO.
- **`-append "console=ttyAMA0 earlycon=pl011,0x9000000 rdinit=/bin/sh"`**:
  - `console=ttyAMA0` instructs the kernel to use the PL011 UART as its main console.
  - `earlycon=pl011,0x9000000` enables early boot messages on the same UART.
  - `rdinit=/bin/sh` sets the root init process to BusyBox’s `sh`.

If everything is correct, you should see kernel boot messages in your terminal and eventually drop to a BusyBox shell prompt. Press **Enter** a couple of times if you see a black screen.


---

This documentation provides a structured guide for customizing U-Boot, building the Linux kernel, and creating an RFS for Raspberry Pi 4. Adjust the steps as needed for your specific project requirements.


