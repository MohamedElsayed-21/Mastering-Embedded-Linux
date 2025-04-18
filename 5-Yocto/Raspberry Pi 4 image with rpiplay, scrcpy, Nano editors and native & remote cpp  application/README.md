### **Application Requirements**

**Target Hardware:**

* Raspberry Pi 4 (Raspi4)

**Packages:**

* **SSH:** Secure Shell for remote access.
* **WIFI addon:** Support for wireless connectivity.
* **Nano:** Simple text editor.
* **Meta-qt5:** Qt5 layer for developing graphical applications.
* **Community: VSOMEIP:** Middleware for inter-process communication.
    * **Collaboration Project:** Submit your layer on Open-Embedded as part of the Bullet AI project.
* **RPI Play:** For Iphone screen mirroring.
* **Scrcpy:** For andriod screen mirroring.
* **Audio:** Support for audio playback and recording.
* **Native Hello Bullet Application:** A sample remote and local application for testing.

**Image:**

* Image recipe.

**Kernel:**

* Version: 5.15.x

**Distributions:**

* Distribution 1:
    * Includes Meta-qt5.
    * Uses systemd as the init system.

* Distribution 2:
    * Excludes Meta-qt5.
    * Uses sysvinit as the init system.
---
### **1. Setting Up the Environment**

To successfully build a Yocto-based image for the Raspberry Pi 4, follow these steps to set up your development environment.

- **Install Required Dependencies**

Ensure your system has the necessary packages installed. If you are using Ubuntu, you can install them with the following command:
For more details, refer to the official Yocto documentation: [Yocto System Requirements](https://docs.yoctoproject.org/4.0.25/ref-manual/system-requirements.html#ubuntu-and-debian).


```bash
sudo apt install build-essential chrpath cpio debianutils diffstat file gawk gcc git iputils-ping \
libacl1 liblz4-tool locales python3 python3-git python3-jinja2 python3-pexpect python3-pip \
python3-subunit socat texinfo unzip wget xz-utils zstd git inkscape locales make \
python3-saneyaml python3-sphinx-rtd-theme sphinx texlive-latex-extra
```

After installation, ensure that the `en_US.utf8` locale is available by running:

```bash
locale --all-locales | grep en_US.utf8
```

---

### **2. Download and Configure Poky**

Poky is the reference build system for Yocto. To obtain the Poky repository and switch to the desired branch:   [exploring the poky direcotry](https://docs.yoctoproject.org/4.0.25/ref-manual/structure.html#source-directory-structure) 

```bash
git clone https://github.com/yoctoproject/poky.git
cd poky
git switch kirkstone
```

---
### 3. **Initialize the Build Environment**:
   - Run the following command to set up the build environment:
      ```bash
     source poky/oe-init-build-env build-raspberrypi4
      ```
   - This creates a `build` directory and sets up the necessary environment variables.[exploring the build direcotry](https://docs.yoctoproject.org/4.0.25/ref-manual/structure.html#the-build-directory-build) 

---

### **4. Configure Local Build Settings**

Edit `local.conf` in the `build-raspberrypi4/conf/` directory to match the target hardware and improve performance:

```local.conf
MACHINE ?= "raspberrypi4"
DL_DIR ?= "${TOPDIR}/../downloads"
BB_NUMBER_THREADS="5"
PARALLEL_MAKE="-j 5"

hostname:pn-base-files = "Mohamed"
```

 **Explanation of Modifications:**

- `MACHINE`: Defines the target hardware as Raspberry Pi 4.
- `DL_DIR`: Points to the shared `downloads` directory, avoiding redundant downloads.
- `DISTRO`: Custom distribution name, allowing better configuration control.
- `BB_NUMBER_THREADS` & `PARALLEL_MAKE`: Optimize build performance by leveraging multiple CPU cores.
- `hostname:pn-base-files`: Sets the system hostname to "Mohamed".

By following these steps, your Yocto environment is set up efficiently and ready for further customization.

---


### **5. Define the Directory Structure**

For better organization and to avoid modifying the Poky source directly, the following directory structure is used:

```
yocto
├── build-raspberrypi4    # Build directory specific to Raspberry Pi 4
├── downloads             # Shared directory for downloaded source files
├── images                # Output directory for generated images
├── layers                # Custom layers and additional Yocto layers
├── poky                  # Poky source directory (unmodified)
```

##### **Why This Structure?**

- Keeping the `poky` directory separate ensures that upstream changes can be pulled without conflicts.
- The `downloads` directory is shared, preventing redundant downloads when building multiple images.
- Custom layers and meta-layers are placed in `layers`, making it easier to manage and integrate external components.
- Output images are stored in `images`, simplifying access to build artifacts.

--- 


### **6. Fetch and Add Layers**

🔗 [Understanding and Creating Layers in Yocto](https://docs.yoctoproject.org/4.0.25/dev-manual/layers.html#understanding-and-creating-layers)
- **To include additional functionality, fetch and add the required layers:**
   ```bash
   cd layers
   git clone -b kirkstone git://git.yoctoproject.org/meta-raspberrypi.git
   git clone -b kirkstone git://git.openembedded.org/meta-openembedded.git
   git clone -b kirkstone https://github.com/meta-qt5/meta-qt5.git
   ```

- **Check dependencies for Qt5:**

   ```bash
   bitbake-layers layerindex-show-depends meta-qt5
   ```

- **Add the layers to the build system:**

   ```bash
   bitbake-layers add-layer ../layers/meta-raspberrypi
   bitbake-layers add-layer ../layers/meta-openembedded/meta-oe
   bitbake-layers add-layer ../layers/meta-qt5
   ```

These layers provide support for Raspberry Pi 🔗 [meta-raspberrypi Documentation](https://meta-raspberrypi.readthedocs.io/en/latest/)  , additional open-source packages, and Qt5 for graphical applications.
By following these steps, your Yocto environment is set up efficiently and ready for further customization.

- **Edit `bblayers.conf` in the `build-raspberrypi4/conf/` directory :**

   ```bitbake
   BBLAYERS ?= " \
   ${TOPDIR}/../poky/meta \
   ${TOPDIR}/../poky/meta-poky \
   ${TOPDIR}/../poky/meta-yocto-bsp \
   ${TOPDIR}/../layers/meta-raspberrypi \
   ${TOPDIR}/../layers/meta-openembedded/meta-oe \
   ${TOPDIR}/../layers/meta-qt5 \

   ```
**Using `${TOPDIR}/..` in `bblayers.conf` makes paths relative** **to the build directory, providing key benefits:**

1. **Portability:** The setup works across different machines without modifying `bblayers.conf`.  
2. **Reusability:** Multiple build directories (e.g., for different targets) can share the same layers.  
3. **Yocto Best Practices:** Keeps `poky` and `layers` separate from `build`, following Yocto recommendations.  
4. **Avoids Hardcoded Paths:** Prevents issues when moving the project or using different environments.  

--- 

### **7. Create a Custom Software Layer (`meta-IVI`)**  

To add custom features and configurations, we need to create a new Yocto layer.  

- **Generate the Layer Structure**  
Run the following command inside the **build directory** to create a properly structured Yocto layer:  

   ```bash
   bitbake-layers create-layer ../layers/meta-IVI
   ```
   This command generates the necessary directories and metadata files required for a valid Yocto layer.  

- **Add the Layer to BitBake**  
Since `bitbake-layers` only recognizes `bblayers.conf` when executed from inside the build directory, switch to it first and Then, add the newly created layer:  
   ```bash
   cd build-raspberrypi4
   bitbake-layers add-layer ../layers/meta-IVI
   ```

- **Verify `bblayers.conf`**  
After adding the layer, ensure `bblayers.conf` contains an entry for `meta-IVI`, using **relative paths** to maintain flexibility:  

   ```bblayers.conf
   BBLAYERS ?= " 
   ${TOPDIR}/../layers/meta-IVI \
   ```
   **Note:** Always run `bitbake-layers` commands from within the build directory to ensure proper detection of `bblayers.conf`.  


---

### **8. Create Distribution-Specific Layers**  

- **Generate the Layers**  
Run the following commands inside the **build directory** to create the layers:  

   ```bash
   bitbake-layers create-layer ../layers/meta-info-distro
   bitbake-layers create-layer ../layers/meta-audio-distro
   ```

- **Add Layers to BitBake**  
Since `bitbake-layers` only recognizes `bblayers.conf` when run inside the build directory, switch to it first Then, add the layers:  :  



   ```bash
   cd build-raspberrypi4
   bitbake-layers add-layer ../layers/meta-info-distro
   bitbake-layers add-layer ../layers/meta-audio-distro
   ```

- **Verify `bblayers.conf`**  
Ensure `bblayers.conf` includes the new layers using **relative paths**:  

   ```bblayers.conf
   BBLAYERS ?= " \
   ${TOPDIR}/../layers/meta-info-distro \
   ${TOPDIR}/../layers/meta-audio-distro \
   "
   ```

### **9. Create a Custom Distribution Configuration**  
Now, we will define a **custom distribution** for our project. In Yocto, distributions are typically defined in **configuration files** located under `conf/distro/`.  

### 9.1 - infotainment distro

- **Define the Distribution Configuration**  
Inside the new layer, navigate to its `conf/distro/` directory and create a new file called `infotainment.conf`:  

   ```bash
   cd layers
   mkdir -p meta-info-distro/conf/distro 
   touch ./meta-info-distro/conf/distro/infotainment.conf 
   ```

- **Now, open `infotainment.conf` and define your distribution settings:**  

   ```bitbake
   DISTRO="infotainment"
   DISTRO_NAME="MOHAMED-infotainment"
   DISTRO_VERSION="1.0"
   MAINTAINER="mohamedelsayedhussein22@gmail.com"
   # SDK Information.
   SDK_VENDOR = "-mohamedSDK" # دي نرجسية مش اكتر :)
   SDK_VERSION = "${@d.getVar('DISTRO_VERSION').replace('snapshot-${METADATA_REVISION}', 'snapshot')}"
   SDK_VERSION[vardepvalue] = "${SDK_VERSION}"
   SDK_NAME = "${DISTRO}-${TCLIBC}-${SDKMACHINE}-${IMAGE_BASENAME}-${TUNE_PKGARCH}-${MACHINE}"

   # Installation path --> can be changed to ${HOME}-${DISTRO}-${SDK_VERSION}
   SDKPATHINSTALL = "/opt/${DISTRO}/${SDK_VERSION}" 

   INFOTAINMENT_DEFAULT_DISTRO_FEATURES = "largefile opengl ptest wayland multiarch vulkan x11 bluez5 qt5 "
   # ${DISTRO_FEATURES_DEFAULT} exist in  meta/conf/distro/include/default-distrovars.inc -->  DISTRO_FEATURES_DEFAULT ?= "acl alsa argp bluetooth debuginfod ext2 ipv4 ipv6 largefile pcmcia usbgadget usbhost wifi xattr nfs zeroconf pci 3g nfc x11 vfat seccomp"
   
   DISTRO_FEATURES ?= "${DISTRO_FEATURES_DEFAULT} \ 
                     ${INFOTAINMENT_DEFAULT_DISTRO_FEATURES} \
                     userland  pulseaudio   "

   IMAGE_INSTALL:append=" rpi-play "

   # add systemd as init-process 
   require conf/distro/include/systemd.inc

   # prefered version for packages.
   PREFERRED_VERSION_linux-yocto ?= "5.15%"
   PREFERRED_VERSION_linux-yocto-rt ?= "5.15%"

   # Build System configuration.
   LOCALCONF_VERSION="2"

   # add poky sanity bbclass
   INHERIT += "poky-sanity"
   ```
- **Update `local.conf` to Use the infotainment Distribution**  
Modify `build-raspberrypi4/conf/local.conf` and set ` DISTRO ?= "infotainment"`:  

- **Verify the Configuration**  
   - Run the following command to ensure the distribution is recognized:  
    ```bash
      bitbake -e | grep "^DISTRO="
    ```
   If everything is correct, it should print:  
   ```
   DISTRO="infotainment"
   ```
   
- **Enable systemd for Infotainment Distribution**  

   **By default, **Poky uses `sysvinit`** as its **init manager** unless explicitly changed. To switch to **systemd** for the Infotainment distribution, we will include a configuration file.For more details on init managers in Yocto, refer to the official documentation:** 🔗 [Yocto Init Manager Documentation](https://docs.yoctoproject.org/4.0.25/dev-manual/init-manager.html#using-systemd)  

   - **Create the systemd Configuration File**  

      Run the following command inside `meta-IVI`:  
      ```bash
      mkdir -p meta-IVI/conf/distro/include
      touch meta-IVI/conf/distro/include/systemd.inc
      ```
   - **Define systemd as the Init Manager**  
   Edit `meta-IVI/conf/distro/include/systemd.inc` and add the following content:  

      ```systemd.inc
      # In the past, this variable was used to set systemd as the init manager.
      # Select systemd as the init manager
      # VIRTUAL-RUNTIME_init_manager="systemd"
      # VIRTUAL-RUNTIME_initscripts="systemd-compat-units"
      # Select busybox-mdev as the device manager
      # VIRTUAL-RUNTIME_dev_manager="busybox-mdev"
      # It existed in meta/conf/distro/include/init-manager-systemd.inc.

      # Just use this variable to set systemd
      INIT_MANAGER = "systemd"

      # Install systemd as the init manager
      # DISTRO_FEATURES:append=" systemd "
      ```

   - **Include systemd in the Infotainment Distribution**  
   Modify `meta-IVI/conf/distro/infotainment.conf` and add:  

      ```infotainment.conf
      require conf/distro/include/systemd.inc
      ```

---

### 9.2- audio distro

- **Define the Distribution Configuration**  
Inside the new layer, navigate to its `conf/distro/` directory and create a new file called `audio.conf`:  

   ```bash
   cd layers
   mkdir -p  meta-audio-distro/conf/distro
   touch ./meta-audio-distro/conf/distro/audio.conf 
   ```

- **Open `audio.conf` and define the audio-specific settings**:  

   ```bitbake
   require conf/distro/poky.conf

   DISTRO="audio"
   DISTRO_NAME="audio-os "
   DISTRO_VERSION="1.0"

   MAINTAINER="mohamedelsayedhussein22@gmail.com"

   DISTRO_FEATURES:remove = " largefile opengl ptest multiarch vulkan"
   DISTRO_FEATURES:append = " userland pulseaudio bluetooth wifi alsa"
   ```

- **By default,** Poky uses **`sysvinit`** as its **init manager** unless explicitly changed. so there is no addition steps here for fullfill the requirment.


- **Update `local.conf` to Use the New Audio Distribution if neededd**  
Modify `build-raspberrypi4/conf/local.conf` and set `DISTRO ?= "audio"`.  

- **Verify the Configuration**  
   - Check that the distribution is correctly set:  
      ```
      bitbake -e | grep "^DISTRO="
      ```

   -  If everything is correct, it should print:   
      ```
      DISTRO="audio"
      ```

---

### **10. Create the Image Recipe: `ivi-test-image.bb`**  

- **Create the Image Recipe File**  

   ```bash
   mkdir -p layers/meta-IVI/recipes-core/images
   touch layers/meta-IVI/recipes-core/images/ivi-test-image.bb
   ```

- **Add the Following Content to `ivi-test-image.bb`**  

   ```ivi-test-image.bb
   require  recipes-core/images/rpi-test-image.bb

   inherit audio
   inherit qt-features
   inherit network-features

   # "wifi bluetooth alsa"  this MACHINE_FEATURES alreadey existed in (rpi-test-image.bb --> rpi-base.inc so you don't need to add it again)

   IMAGE_INSTALL:append=" vsomeip nano c-helloworld cpp-helloworld appssl can-utils scrcpy"

   IMAGE_FEATURES += "ssh-server-openssh debug-tweaks tools-debug x11 tools-sdk"

   ```

 **Explanation of the Recipe**  

- **`require recipes-core/images/rpi-test-image.bb`**  
- Inherits from `rpi-test-image.bb`, meaning it will have the same base configuration.  
- **`IMAGE_FEATURES`** 🔗 [Image Features yocto documentaion](https://docs.yoctoproject.org/4.0.25/ref-manual/features.html#image-features)  

---

### **11. Creating the First Recipe: for remote cpp hellowrold**  

We are now moving on to creating our first custom recipe for a C++ application. Following the Yocto documentation, we will generate and modify the recipe to meet our project's requirements. in each recipe we will make we will stick into the steps exit in documentaion 🔗 [Yocto Writing a New Recipe Documentation](https://docs.yoctoproject.org/4.0.25/dev-manual/new-recipe.html#writing-a-new-recipe) .

- **Generate the Initial Recipe file**  

   1. **Create a directory for C++ recipes**:  
            ```
            mkdir -p layers/meta-IVI/recipes-cpp/cpp-helloworld
            ```
         **why this structure necessary?**
      - **Following Yocto's Standard Structure**  
         - Each layer contains a `layer.conf` file, which defines how BitBake finds recipe files.  
         - Typically, `BBFILES` is set like this:  
            ```bitbake
            BBFILES += "${LAYERDIR}/recipes-*/*/*.bb"
            ```
             This means Yocto expects `.bb` files to be inside a **subdirectory** within `recipes-*`.  


   2. **Run the following command inside the `meta-IVI/recipes-cpp/cpp-helloworld` layer to create the base recipe:** 
      🔗 [Recpitool Documentation](https://docs.yoctoproject.org/4.0.25/dev-manual/new-recipe.html#creating-the-base-recipe-using-recipetool-create)

         ```bash
         cd layers/meta-IVI/recipes-cpp/cpp-helloworld
         recipetool create -o cpp-helloworld_1.0.bb https://github.com/embeddedlinuxworkshop/y_t1.git
         ```
         This will generate a file named `cpp-helloworld_1.0.bb` with an initial recipe file.  


- **Modify the Recipe**  
After generating the recipe, edit the `cpp-helloworld_1.0.bb` file and apply the following changes:  

   ```bitbake
   # Set the source directory inside the work directory
   S = "${WORKDIR}/git"

   # Define the compilation steps
   do_compile () {
      ${CXX} ${S}/main.cpp -o cpp-app
   }

   # Define installation steps
   do_install () {
      install -d ${D}${bindir}
      install -m 0755 cpp-app ${D}${bindir}
   }

   # Skip package QA checks to avoid errors
   do_package_qa[noexec] = "1"
   ```

---

### **12. Writing a Recipe for a Local Application (`appssl`)**  

this the cpp application , we want to integrate it in our image .
   ```cpp code 

   #include <iostream>
   #include <openssl/sha.h>

   int main() {
      const std::string message = "Hello World";
      
      // Create a buffer to hold the hash
      unsigned char hash[SHA256_DIGEST_LENGTH];
      
      // Compute the SHA256 hash
      SHA256(reinterpret_cast<const unsigned char*>(message.c_str()), message.length(), hash);
      
      // Print the hash in hexadecimal format
      std::cout << "SHA-256 hash of \"" << message << "\" is: ";
      for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
         printf("%02x", hash[i]);
      }
      std::cout << std::endl;
      
      return 0;
   }

   ```

Since `appssl` is a **local application**, we must use `SRC_URI = "file://appssl.cpp"` to fetch the source code from our local machine instead of downloading it from an external repository.

**check this pages from the documentation .**
[Yocto: Fetching Code in Recipes](https://docs.yoctoproject.org/4.0.25/dev-manual/new-recipe.html#fetching-code) and 
[SRC_URI](https://docs.yoctoproject.org/bitbake/2.10/bitbake-user-manual/bitbake-user-manual-ref-variables.html#term-SRC_URI)


- **Folder Structure**  
   We follow the Yocto best practices by creating:  
   ```bash
   mkdir -p layers/meta-IVI/recipes-cpp/appssl/files
   ```
   The folder  Structure be like this :

   ``` terminal output
   recipes-cpp
   ├── appssl
      ├── appssl_1.0.bb
      └── files
          └── appssl.cpp
   ```
   **(The `files/` directory  or  `{BPN}:` → `appssl/` or `${BP} - ${BPN}-${PV}` → `appssl_1.0` ) is necessary for BitBake to recognize and access local source files.**


- **Resolving Dependencies**  
To determine the correct flags for linking against OpenSSL, you can use:  
   ```bash
  $  pkg-config --libs --cflags openssl
   -lssl -lcrypto
   ```
   This helps find the necessary compiler and linker flags.


- **The Package  Recipe**  

   ```bitbake
   DOCUMENTATION = "appssl"
   SUMMARY = "this appssl app is a simple example of a C++ application with dependencies" 

   LICENSE = "CLOSED"  # Since the app is local and proprietary

   PV = "1.0"  # Package version

   SRC_URI = "file://appssl.cpp"  # Fetch source from local files

   S = "${WORKDIR}"  # Set source directory inside the build environment

   DEPENDS = "openssl"  # Declare dependency on OpenSSL

   do_compile () {
      ${CXX} ${LDFLAGS} ${S}/appssl.cpp -lssl -lcrypto -o appssl
   }

   do_install () {
      install -d ${D}${bindir}
      install -m 0755 ${S}/appssl ${D}${bindir}
   }
   ```

 **Explanation of Variables:**
- **`${CXX}`** → Uses the C++ compiler set by Yocto.
- **`${LDFLAGS}`** → Ensures correct linking flags for the build.
- **`-lssl -lcrypto`** → Links against OpenSSL libraries.
- **`${D}${bindir}`** → Installs the compiled binary into `/usr/bin/` inside the target filesystem.
- **Understanding `install` Command**  
   - The `install` command in Linux is used for copying and setting file permissions. To check its options, run:  `man install` 
   - In our case:
      - `install -d` → Creates the destination directory.
      - `install -m 0755` → Copies the file and sets permissions (`rwxr-xr-x`).

---




### **13. Integrating Nano into Yocto**

### Method 1: Using GNU FTP (Nano 7.2)
For more details, visit: [Nano Releases](https://ftp.gnu.org/gnu/nano/).
- Navigate to your layer's `recipes-editors` directory:
   ```bash
   mkdir -p layers/meta-IVI/recipes-editors/nano
   cd layers/meta-IVI/recipes-editors/nano
   ```
- Create a recipe using `recipetool`:
   ```bash
   recipetool create -o nano_1.0.bb https://ftp.gnu.org/gnu/nano/nano-7.2.tar.xz
   ```
- adjst this variable and it will work without any errors`FILES:${PN} += "${datadir}/*"`

- Build Nano using Bitbake:
   ```bash
   bitbake nano
   ```


### Method 2: Using the Official Git Repository (Nano 8.3)
**This method is not recommended** becuse you have to specifiy certain version of any application you will download in your image .but i did it **for learning purposes.**

For more details about the nano, visit: [Nano Git Repository](https://git.savannah.gnu.org/cgit/nano.git/tree/README.hacking).

- Install dependencies required for building Nano from source:
   ```bash
   sudo apt install autoconf automake autopoint gcc gettext git groff make pkg-config texinfo
   ```
- Create a recipe using `recipetool`:
   ```bash
   recipetool create -o nano_1.0.bb git://git.savannah.gnu.org/nano.git
   ```
- Fetch and unpack the source code:
   ```bash
   bitbake -c fetch nano
   bitbake -c unpack nano
   ```
   
- Find the `WORKDIR` path:
   ```bash
   bitbake -e nano | grep -i "^workdir="
   ```
   Navigate to the printed path.

- Run `autogen.sh` to generate the `configure` script:
   ```bash
   ./autogen.sh
   ```
   We performed these two steps separately instead of running `bitbake nano` directly because:  

   1. **Auto-configuration Requirement:**  
      - The source code from `git://git.savannah.gnu.org/nano.git` requires running `./autogen.sh` before `configure` can execute.  
      - `bitbake nano` by default runs the `do_configure` task, which expects a `configure` script to exist. But since `nano` uses `autogen.sh` to generate this script, `do_configure` would fail if we ran `bitbake nano` immediately.  

   2. **Manual Execution of `autogen.sh`:**  
      - After `bitbake -c unpack nano`, we navigate to the work directory and manually run `./autogen.sh` to generate the necessary `configure` script.  
      - This ensures that the `do_configure` step in BitBake will succeed when we finally run `bitbake nano`.  


- Build Nano:
   ```bash
   bitbake nano
   ```

**Automate this steps by**
1. **Patch `autogen.sh`**

   - The patch removes the Gnulib cloning logic from `autogen.sh`. Here's the patch:
   
      ```patch
      diff --git a/autogen.sh b/autogen.sh
      index 541b90ca..906182d8 100755
      --- a/autogen.sh
      +++ b/autogen.sh
      @@ -1,9 +1,6 @@
      #!/bin/sh
      # Generate configure & friends for GIT users.
      
      -gnulib_url="git://git.sv.gnu.org/gnulib.git"
      -gnulib_hash="4631e9b4d5d3bd5ba42864c7001cf3509a00c7b3"
      -
      modules="
         canonicalize-lgpl
         futimens
      @@ -31,17 +28,7 @@ modules="
      "
      
      # Make sure the local gnulib git repo is up-to-date.
      -if [ ! -d "gnulib" ]; then
      -	git clone --depth=2222 ${gnulib_url}
      -fi
      -cd gnulib >/dev/null || exit 1
      -curr_hash=$(git log -1 --format=%H)
      -if [ "${gnulib_hash}" != "${curr_hash}" ]; then
      -	echo "Pulling..."
      -	git pull
      -	git checkout --force ${gnulib_hash}
      -fi
      -cd .. >/dev/null || exit 1
      +
      
      rm -rf lib
      echo "Gnulib-tool..."
      ```

2. **Final Recipe for Nano**
   - Here’s the updated Yocto recipe that incorporates the patch and automates the build process:
      ```nano.bb
      SUMMARY = "GNU nano text editor"
      DESCRIPTION = "GNU nano is a small and simple text editor."
      HOMEPAGE = "https://www.nano-editor.org/"
      LICENSE = "GPL-3.0-only & Unknown"
      LIC_FILES_CHKSUM = "file://COPYING;md5=f27defe1e96c2e1ecd4e0c9be8967949 \
                        file://COPYING.DOC;md5=ad1419ecc56e060eccf8184a87c4285f"
      SRC_URI = "git://git.savannah.gnu.org/git/nano.git;protocol=https;branch=master;name=nano \
               git://git.savannah.gnu.org/git/gnulib.git;protocol=https;branch=master;name=gnulib;destsuffix=git/gnulib \
               file://0001-remove-cloning-gnulib-by-script-autogen.patch"
      SRCREV_nano = "63a7be115a729190fdf612fd5b821ac015f2421e"
      SRCREV_gnulib = "4631e9b4d5d3bd5ba42864c7001cf3509a00c7b3"
      SRCREV_FORMAT = "nano_gnulib"
      PV = "1.0+git${SRCPV}"
      S = "${WORKDIR}/git"
      DEPENDS = "zlib ncurses file"
      inherit gettext pkgconfig autotools
      # Ensure gnulib is available in the source directory
      do_unpack_append() {
         cp -r ${WORKDIR}/git/gnulib ${S}/gnulib
      }
      # Run autogen.sh before configure
      do_autogen() {
         cd ${S}
         ./autogen.sh
      }
      addtask do_autogen before do_configure after do_unpack
      # Configure and build
      do_configure() {
         oe_runconf
      }
      do_build() {
         oe_runmake
      }

      # Disable package QA checks
      do_package_qa[noexec]="1"
      ```

#### **Explanation of the Recipe**
1. **`SRC_URI`**:
   - Fetches Nano and Gnulib from their respective Git repositories.
   - Includes the patch to modify `autogen.sh`.
   - When adding multiple Git repositories to `SRC_URI`, you must give each one a **unique name** using the `name` parameter.

2. **`SRCREV_name`**
   - specify the Git revision (spicail commit) for each repository

   **Note** If you forget to add `SRCREV_FORMAT`, Yocto will throw this error:
      ```
      Failure expanding variable SRCPV, expression was ${@bb.fetch2.get_srcrev(d)} which triggered exception
      FetchError: Fetcher failure: The SRCREV_FORMAT variable must be set when multiple SCMs are used.
      ```
3. **`SRCREV_FORMAT`**
   - To combine the `SRCREV` values into a single version string, you must define `SRCREV_FORMAT`

4. **`do_autogen`**:
   - Runs `autogen.sh` to generate the `configure` script.

5. **`addtask`**:
   - Ensures `do_autogen` runs before `do_configure`.

**why we did patch file to the autogen?** 
- The original `autogen.sh` script tries to clone Gnulib using a **private Git link**:

   ```bash
   git clone <membername>@git.savannah.gnu.org:/srv/git/gnulib.git
   ```

- This requires **SSH authentication**, which is not suitable for a Yocto build environment.

then you have to replace the private link with a **public Git link**: [GNU Gnulib Git Repository](https://savannah.gnu.org/git/?group=gnulib)

   ```bitbake
   SRC_URI = "git://git.savannah.gnu.org/git/gnulib.git;protocol=https;branch=master;name=gnulib;destsuffix=git/gnulib"
   ```

- This public link (`https`) doesn’t require authentication and works seamlessly in Yocto. 

---

### **14.  Steps to integrate `audio` in `meta-IVI` Layer**  
 
-  **Steps to Create `audio.bbclass` in `meta-IVI` Layer**  
   - Navigate to your layer directory & Create the `classes/` directory if it doesn’t exist : 
      ```bash
      cd layers/meta-IVI
      mkdir -p classes
      touch classes/audio.bbclass
      ```
   - Edit the file and add the following content:  
      ```bitbake
      IMAGE_INSTALL:append = " \   
      pavucontrol  pulseaudio-module-dbus-protocol pulseaudio-server pulseaudio-module-loopback \
      pulseaudio-module-bluetooth-discover  pulseaudio-module-bluetooth-policy \
      pulseaudio-module-bluez5-device  pulseaudio-module-bluez5-discover  \
      alsa-ucm-conf  alsa-topology-conf  alsa-state alsa-lib alsa-tools alsa-utils alsa-plugins"
      ```
- Once done, **`inherit audio`** is added to distro recipe, then all these packages will be automatically included in the **final image**. 

---

### **15. Steps to integrate `qt-features` in `meta-IVI` Layer**  

- **Steps to Create `qt-features.bbclass` in `meta-IVI` Layer**  
   - **Navigate to your layer directory & create the `classes/` directory if it doesn’t exist:**  
      ```bash
      cd layers/meta-IVI
      mkdir -p classes
      touch classes/qt-features.bbclass
      ```
   - **Edit the file and add the following content:**  
      ```bitbake
      IMAGE_INSTALL:append = " \   
      qttools qtbase-examples qtquickcontrols qtbase-plugins qtquickcontrols2 \  
      qtgraphicaleffects qtmultimedia qtserialbus qtquicktimeline qtvirtualkeyboard"
      ```
- Once done, **`inherit qt-features`** is added to distro recipe, then all these packages will be automatically included in the **final image**.

---


### **16. Steps for **RPiPlay** Integration**

- **Create the initial recipe**  
   ```bash
      mkdir -p layers/meta-IVI/recipes-rpiplay
      cd layers/meta-IVI/recipes-rpiplay
      recipetool create -o rpi-play_1.0.bb https://github.com/FD-/RPiPlay.git
   ```
   - This generates a base `.bb` file, but **it’s not reliable** because it misses dependencies.  

- **Find missing dependencies**  
   - Checked the **GitHub repository** for required libraries [RPiPlay GitHub](https://github.com/FD-/RPiPlay) .
   - Manually searched for them in **OpenEmbedded Layer Index** [OpenEmbedded Layer Index - Kirkstone Recipes](https://layers.openembedded.org/layerindex/branch/kirkstone/recipes/).  

- **Add the missing layer (`meta-networking`)**  
   - Since `avahi` is in `meta-openembedded/meta-networking` , we **must add that layer** to `bblayers.conf`:
      ```bash
      bitbake-layers layerindex-show-depends meta-networking 
      # it  will show that it needs (openembededdcore , meta-oe and meta-pyhthon)  

      bitbake-layers add-layer ../layers/meta-openembedded/meta-python
      bitbake-layers add-layer ../layers/meta-openembedded/meta-networking
      ```

- Before applying a patch, let’s first **trigger the error** by running:  
   ```bash
   bitbake rpi-play
   ```
   **Expected Error:**
   ```terminal output 
   CMake Error at renderers/CMakeLists.txt:43 (add_library):
   No SOURCES given to target: ilclient
   ```


#### **Debugging the Missing `ilclient` Library Issue**  

- **Step 1: Understanding `ilclient`**  
Before fixing anything, we need to understand what **`ilclient`** is.  
   - A quick **Google search** tells us that `ilclient` is part of the **Userland** library.  [ilclient.h GitHub](https://github.com/raspberrypi/userland/blob/master/host_applications/linux/apps/hello_pi/libs/ilclient/ilclient.h)
   - Userland is a set of **Raspberry Pi-specific** libraries that provide access to the VideoCore hardware (e.g., OpenGL, camera, and multimedia processing).  

- **Step 2: Check if `ilclient` is Present**  
Since `ilclient` should come from `userland`, we need to **verify if it exists in the sysroot**.  

   - **Find the Work Directory for `rpi-play`**  
      ```bash
         bitbake -e rpi-play | grep "^WORKDIR="
      ```
   - This will output something like:  
      ```terminal
      WORKDIR="/home/mohamed/Documents/Mastering_Embedded_Linux/5-Yocto/build-raspberrypi4/tmp-glibc/work/cortexa7t2hf-neon-vfpv4-oe-linux-gnueabi/rpi-play/1.2+gitAUTOINC+64d0341ed3-r0"
      ```

   - **Navigate to the sysroot**  
      ```bash
      # sysroot of the rpi-play
      cd /home/mohamed/Documents/Mastering_Embedded_Linux/5-Yocto/build-raspberrypi4/tmp-glibc/work/cortexa7t2hf-neon-vfpv4-oe-linux-gnueabi/rpi-play/1.2+gitAUTOINC+64d0341ed3-r0/recipe-sysroot
      ```

   - **Search for `ilclient`**  
      ```bash
         find . -name "*ilclient*"
      ```
      **Expected Output:**  
      - If `ilclient` **is present**, we should see something like:  
         ```sh
            ./usr/src/path/ilclient.h
            ./usr/src/path/libilclient.so
         ```
      - If **no results** appear, that means `ilclient` is **missing**.  



- **Step 3: Identify Why `ilclient` is Missing**  
   Since `ilclient` comes from `userland`, it should be present in our sysroot. We need to check whether `userland` is:  
      1. **Not included in DEPENDS** (so it wasn’t built).  
      2. **Installed incorrectly** (so it didn’t provide `ilclient`).  

   Let’s check the `DEPENDS` in our recipe:  
   ```rpi-play.bb
   DEPENDS = "userland openssl avahi mdns libplist gstreamer1.0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-vaapi gstreamer1.0-plugins-bad"
   ```
   - **`userland` is already listed!**  

   then let’s confirm it was actually built:  
      ```bash
      bitbake -e userland | grep "^WORKDIR="
      ```
   - If `WORKDIR` is found, then `userland` **was built**.  
   - If it’s missing, we need to `bitbake userland` separately.  

- **Step 4: Manually Verify `/opt/vc` Inside `userland`**  
  - Since the `RPiPlay` repo expects `ilclient` inside `/opt/vc`, we need to check:  
      ```bash
      # the ${D} is the image ditectory of userland
      cd /home/mohamed/Documents/Mastering_Embedded_Linux/5-Yocto/build-raspberrypi4/tmp-glibc/work/cortexa7t2hf-neon-vfpv4-oe-linux-gnueabi/userland/20220323-r0/image"
      find . -name "*ilclient*"
      ```
   - We see that `ilclient` **exists**, but in a different location:  
      ``` terminal output 
      $ find . -name "*ilclient*"
      ./usr/src/hello_pi/libs/ilclient
      ./usr/src/hello_pi/libs/ilclient/ilclient.h
      ./usr/src/hello_pi/libs/ilclient/ilclient.c
      ```
   - This is **not** where `RPiPlay` expects it to be.  
      - If `/opt/vc` **exists and contains `ilclient`**, we need to **correct the CMake paths**. 
      - If it doesn’t exist, then userland wasn’t built properly or needs extra install steps or it built correctly but it's install the output in other place `/usr/` insted of `/opt/vc` .

**How does `bitbake` handle dependencies?**  
When `bitbake` builds `rpi-play`, it pulls dependencies from the `sysroot` of its dependencies (like `userland`). But in this case, **`userland` installs `ilclient` locally inside its own `image/` directory, and not in the `sysroot`**, so `RPiPlay` can't find it.  


- **Step 5: Possible Solutions and Why They Won't Work**  
   1. **Manually copying `ilclient`**  Copying files manually into `sysroot` is not a scalable solution and goes against Yocto's clean design. 
   2. **The Proper Fix – Patching CMake + Adjusting `userland` Sysroot**  
      - **Fix 1: Ensure `ilclient` is Available in the `sysroot`**  
      Since `userland` installs `ilclient` **inside its own image directory but not in `sysroot`**, we need to tell Yocto to include `/usr/src/hello_pi/libs` in the `sysroot` of rpiplay.  

         1.  Create a `userland.bbappend` file inside our meta-layer:  
            
         ```sh
            mkdir -p meta-IVI/recipes-graphics/userland/
            touch meta-IVI/recipes-graphics/userland/userland_git.bbappend
         ```
         2. Add the following line inside `userland_git.bbappend`:  

         ```userland_git.bbappend
         SYSROOT_DIRS:append="${prefix}/src"
         ```
         🔹 **Why?** This ensures that `/usr/src/hello_pi/libs` is **copied into the sysroot**, making `ilclient` available for `rpi-play`.  

      - **Fix 2: Patch `CMakeLists.txt`**  Instead of `/opt/vc`, `CMakeLists.txt` should look in `/usr/src/hello_pi/libs`.  

         1. Navigate to the `rpi-play` source directory after unpacking:  
            ```bash
            # this is the path of source directory of the rpi-play
            cd /home/mohamed/Documents/Mastering_Embedded_Linux/5-Yocto/build-raspberrypi4/tmp-glibc/work/cortexa7t2hf-neon-vfpv4-oe-linux-gnueabi/rpi-play/1.0-r0/git/
            ```
         2. Generate a patch i recommend to make the patch file inside the `devshell`:  [concepts of diff and patch in YouTube](https://youtu.be/-s13A9MPmGU?si=levSHq4tF5SXgctj)

         3. Modify `renders/CMakeLists.txt` to replace `/opt/vc` with `/usr/`.  
            ```bash
            bitbake -c devshell rpi-play # it will open other terminal that simulate the target environments . 
            git diff > 0001_include_dir.patch
            ```
            
         4. **the patch file content**
            ```patch
            diff --git a/renderers/CMakeLists.txt b/renderers/CMakeLists.txt
            index e561250..915ba92 100755
            --- a/renderers/CMakeLists.txt
            +++ b/renderers/CMakeLists.txt
            @@ -17,20 +17,20 @@ set( RENDERER_LINK_LIBS "" )
            set( RENDERER_INCLUDE_DIRS "" )
            
            # Check for availability of OpenMAX libraries on Raspberry Pi
            -find_library( BRCM_GLES_V2 brcmGLESv2 HINTS ${CMAKE_SYSROOT}/opt/vc/lib/ )
            -find_library( BRCM_EGL brcmEGL HINTS ${CMAKE_SYSROOT}/opt/vc/lib/ )
            -find_library( OPENMAXIL openmaxil HINTS ${CMAKE_SYSROOT}/opt/vc/lib/ )
            -find_library( BCM_HOST bcm_host HINTS ${CMAKE_SYSROOT}/opt/vc/lib/ )
            -find_library( VCOS vcos HINTS ${CMAKE_SYSROOT}/opt/vc/lib/ )
            -find_library( VCHIQ_ARM vchiq_arm HINTS ${CMAKE_SYSROOT}/opt/vc/lib/ )
            +find_library( BRCM_GLES_V2 brcmGLESv2 HINTS ${CMAKE_SYSROOT}/usr/lib/ )
            +find_library( BRCM_EGL brcmEGL HINTS ${CMAKE_SYSROOT}/usr/lib/ )
            +find_library( OPENMAXIL openmaxil HINTS ${CMAKE_SYSROOT}/usr/lib/ )
            +find_library( BCM_HOST bcm_host HINTS ${CMAKE_SYSROOT}/usr/lib/ )
            +find_library( VCOS vcos HINTS ${CMAKE_SYSROOT}/usr/lib/ )
            +find_library( VCHIQ_ARM vchiq_arm HINTS ${CMAKE_SYSROOT}/usr/lib/ )
            
            if( BRCM_GLES_V2 AND BRCM_EGL AND OPENMAXIL AND BCM_HOST AND VCOS AND VCHIQ_ARM )
               # We have OpenMAX libraries available! Use them!
               message( STATUS "Found OpenMAX libraries for Raspberry Pi" )
            -  include_directories( ${CMAKE_SYSROOT}/opt/vc/include/ 
            -  	${CMAKE_SYSROOT}/opt/vc/include/interface/vcos/pthreads 
            -  	${CMAKE_SYSROOT}/opt/vc/include/interface/vmcs_host/linux 
            -  	${CMAKE_SYSROOT}/opt/vc/src/hello_pi/libs/ilclient )
            +  include_directories( ${CMAKE_SYSROOT}/usr/include/ 
            +  	${CMAKE_SYSROOT}/usr/include/interface/vcos/pthreads 
            +  	${CMAKE_SYSROOT}/usr/include/interface/vmcs_host/linux 
            +  	${CMAKE_SYSROOT}/usr/src/hello_pi/libs/ilclient )
            
               option(BUILD_SHARED_LIBS "" OFF)
               add_subdirectory(fdk-aac EXCLUDE_FROM_ALL)
            @@ -38,7 +38,7 @@ if( BRCM_GLES_V2 AND BRCM_EGL AND OPENMAXIL AND BCM_HOST AND VCOS AND VCHIQ_ARM
            
               set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DHAVE_LIBOPENMAX=2 -DOMX -DOMX_SKIP64BIT -ftree-vectorize -pipe -DUSE_EXTERNAL_OMX   -DHAVE_LIBBCM_HOST -DUSE_EXTERNAL_LIBBCM_HOST -DUSE_VCHIQ_ARM -Wno-psabi" )
               
            -  aux_source_directory( ${CMAKE_SYSROOT}/opt/vc/src/hello_pi/libs/ilclient/ ilclient_src )
            +  aux_source_directory( ${CMAKE_SYSROOT}/usr/src/hello_pi/libs/ilclient/ ilclient_src )
               set( DIR_SRCS ${ilclient_src} )
               add_library( ilclient STATIC ${DIR_SRCS} )
            ```
         5. Copy the patch to the recipe folder:  
            ```bash
            # copy the patch file to the directory of the recipe
            cp 0001_include_dir.patch /home/mohamed/Documents/Mastering_Embedded_Linux/5-Yocto/meta-IVI/recipes-rpiplay/rpiplay/rpi-play
            ```
         6. Add it to `SRC_URI` in `rpi-play_1.0.bb`:  
            ```
            SRC_URI = "git://github.com/FD-/RPiPlay.git;protocol=https;branch=master \
            file://0001_include_dir.patch  "
            ```

- **Finally `rpi-play_1.0.bb` after modifications**  

   ```bitbake
      LICENSE = "Unknown"
      LIC_FILES_CHKSUM = "file://LICENSE;md5=1ebbd3e34237af26da5dc08a4e440464 \
                        file://lib/llhttp/LICENSE-MIT;md5=f5e274d60596dd59be0a1d1b19af7978 \
                        file://lib/playfair/LICENSE.md;md5=c7cd308b6eee08392fda2faed557d79a"

      SRC_URI = "git://github.com/FD-/RPiPlay.git;protocol=https;branch=master \
               file://0001_include_dir.patch"

      PV = "1.2+git${SRCPV}"
      SRCREV = "64d0341ed3bef098c940c9ed0675948870a271f9"

      S = "${WORKDIR}/git"

      DEPENDS = "userland openssl avahi mdns libplist gstreamer1.0 \
               gstreamer1.0-plugins-base gstreamer1.0-plugins-good \
               gstreamer1.0-vaapi gstreamer1.0-plugins-bad"

      RDEPENDS_${PN} = "avahi libplist gstreamer1.0-plugins-base gstreamer1.0-plugins-good"

      inherit cmake pkgconfig

      EXTRA_OECMAKE = ""
      TARGET_LDFLAGS += "-Wl,--copy-dt-needed-entries"
      EXTRA_OEMAKE:append = 'LDFLAGS="${TARGET_LDFLAGS}"' 
   ```

   **exaplanation :**
   - These two lines pass `Wl,--copy-dt-needed-entries` to  modify the **linking behavior** in a Yocto recipe:  
      ```rpi-play.bb
      TARGET_LDFLAGS += "-Wl,--copy-dt-needed-entries"
      EXTRA_OEMAKE:append = ' LDFLAGS="${TARGET_LDFLAGS}"'
      ```
      1. **`-Wl,--copy-dt-needed-entries`**  
         - Ensures that **indirect shared library dependencies** are included in the final binary.  
         - Without it, only directly linked libraries are included, which can cause **runtime errors** if an intermediate library is missing.  

      2. **`EXTRA_OEMAKE:append = ' LDFLAGS="${TARGET_LDFLAGS}"'`**  
         - Passes `TARGET_LDFLAGS` to `make`, ensuring the linker flag is applied during the build.  

   -  How to determine the runtime dependencies of any package?  
      - You can run the following command:  

         ```bash
         $ readelf -d rpiplay | grep -i needed
         ```

      - This will list all the shared libraries (`.so` files) required by the binary. Based on this output, you can decide which packages to include in the `RDEPENDS_${PN}` variable. 

         ```terminal output
            0x00000001 (NEEDED)                     Shared library: [libplist-2.0.so.3]
            0x00000001 (NEEDED)                     Shared library: [libcrypto.so.3]
            0x00000001 (NEEDED)                     Shared library: [libdns_sd.so.1]
            0x00000001 (NEEDED)                     Shared library: [libopenmaxil.so]
            0x00000001 (NEEDED)                     Shared library: [libbcm_host.so]
            0x00000001 (NEEDED)                     Shared library: [libvcos.so]
            0x00000001 (NEEDED)                     Shared library: [libgstapp-1.0.so.0]
            0x00000001 (NEEDED)                     Shared library: [libgstreamer-1.0.so.0]
            0x00000001 (NEEDED)                     Shared library: [libgobject-2.0.so.0]
            0x00000001 (NEEDED)                     Shared library: [libglib-2.0.so.0]
            0x00000001 (NEEDED)                     Shared library: [libstdc++.so.6]
            0x00000001 (NEEDED)                     Shared library: [libm.so.6]
            0x00000001 (NEEDED)                     Shared library: [libgcc_s.so.1]
            0x00000001 (NEEDED)                     Shared library: [libc.so.6]
            0x00000001 (NEEDED)                     Shared library: [libvchostif.so]
            ```
   - **`RDEPENDS_${PN}`:**
      ```rpi-play.bb
      RDEPENDS_${PN} = "avahi libplist gstreamer1.0-plugins-base gstreamer1.0-plugins-good"
      ```
      This ensures that the necessary runtime dependencies are available when the package is installed.  




- **Step 6: Rebuilding and Testing**  

   - Rebuild `rpi-play` with the patched CMakeLists.txt:  
      ```bash
      bitbake -c cleanall rpi-play
      bitbake rpi-play
      ```
   - Verify that `ilclient` is now present in the `sysroot`:  
      ```bash
      # the recipe sysroot ditectory of rpi-play 
      find /home/mohamed/Documents/Mastering_Embedded_Linux/5-Yocto/build-raspberrypi4/tmp-glibc/work/cortexa7t2hf-neon-vfpv4-oe-linux-gnueabi/rpi-play/1.0-r0/recipe-sysroot/ -name "*ilclient*"
      ```

---

### **17. VSOMEIP Integration with Yocto (Kirkstone)**    

**VSOMEIP** is an open-source implementation of **SOME/IP (Scalable service-Oriented Middleware over IP)** used in automotive Ethernet-based communication. It enables service-oriented communication between ECUs (Electronic Control Units) following the **AUTOSAR** standard.  

- **Common Issues & Solutions**  

   Many users report errors like: [vsomeip GitHub Issue #362](https://github.com/COVESA/vsomeip/issues/362)  
   ```
   basic_socket_ext_local.hpp:133:7: error: no matching function for call to 'boost::asio::detail::io_object_impl<boost::asio::detail::reactive_socket_service_ext_local<boost::asio::local::stream_protocol_ext, boost::asio::executor>::io_object_impl(boost::asio::io_context&)'
   ```  
   This typically occurs due to **incompatibility between VSOMEIP and Boost versions**. The best working **Boost version** for **VSOMEIP** on **Yocto Kirkstone** is:  `Boost 1.71` Later versions cause the compilation to fail due to breaking changes in **Boost.Asio**.  so that you have to install [recipes-support (boost files)](https://github.com/COVESA/vsomeip/files/9394162/recipes-support.zip) in your layer and give it higher prority than the `meta`  

- **Setting Up VSOMEIP in Yocto**  
   Since **VSOMEIP** has dependencies and conflicts with some existing packages, it's essential to ensure the custom layer has a higher priority than **meta**. Modify the priority of `layer.conf`   by adjusting `BBFILE_PRIORITY_meta-IVI = "8"`  .

- **VSOMEIP Recipe for Yocto (Kirkstone)**  
   
   - create the following directory structure inside your custom layer:  
      ```bash
      mkdir -p layers/meta-IVI/recipes-connectivity/vsomeip
      ```

   - Then, create the **Bitbake recipe** file inside this directory and add the following content:  
      ```bitbake
      SUMMARY = "The implementation of SOME/IP"
      SECTION = "base"
      LICENSE = "MPLv2"
      LIC_FILES_CHKSUM = "file://LICENSE;md5=815ca599c9df247a0c7f619bab123dad"

      DEPENDS = "boost dlt-daemon"
      FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

      SRC_URI = "git://github.com/GENIVI/${BPN}.git;protocol=https"

      S = "${WORKDIR}/git"

      inherit cmake lib_package gitpkgv

      PACKAGES:remove = "${PN}-bin"
      FILES:${PN} += "${bindir}/vsomeipd ${sysconfdir}/${BPN}"
      FILES:${PN}-dev += "${libdir}/cmake"

      BBCLASSEXTEND = "nativesdk"

      do_install:append() {
         mv ${D}/usr/etc ${D}
      }
      ```  

### 18. Creating a Yocto Recipe for Scrcpy (Android Mirroring )

-  **Generate the Initial Recipe**
   We start by creating a basic recipe using `recipetool`:
   ```sh
   recipetool create -o scrcpy_1.0.bb git://github.com/Genymobile/scrcpy.git
   ```
   This generates a base recipe with the necessary metadata.

- **Edit the generated `scrcpy_1.0.bb`**
   ```bitbake
   SUMMARY = "Display and control your Android device."
   HOMEPAGE = "https://github.com/Genymobile/scrcpy"

   LICENSE = "Apache-2.0"
   LIC_FILES_CHKSUM = "file://LICENSE;md5=968e58821ffcb172a8baa9bc799f0ad1"

   SRC_URI = "git://github.com/Genymobile/scrcpy.git;protocol=https;branch=master;"
   SRCREV = "baa10ed0a36ec775712be85f22d3db3f0a6e19f2"
   S = "${WORKDIR}/git"

   DEPENDS = "ffmpeg libsdl2 meson-native ninja-native cmake-native pkgconfig-native libusb1"

   RDEPENDS:${PN} += "android-tools ffmpeg libsdl2 libusb1 "

   inherit meson pkgconfig gettext

   INHERIT += "strip"

   EXTRA_OEMESON += " \
   --buildtype=release \
   -Db_lto=true \
   -Dcompile_server=false \
   -Dprebuilt_server=${WORKDIR}/scrcpy-server-${PV} \
   "
   do_package_qa[noexec]="1"
   FILES:${PN} += "${datadir}/*"
   ```
**exaplanition**   
   - **`DEPENDS`**: Includes build-time dependencies such as `meson`, `ninja`, and `pkgconfig`.
   - **`RDEPENDS`**: Lists runtime dependencies like `android-tools` and `ffmpeg`.
   - Use `inherit` This ensures the build system correctly processes dependencies and configurations.
   - Configure `EXTRA_OEMESON`
      - **`--buildtype=release`**: Ensures an optimized release build.
      - **`-Db_lto=true`**: Enables Link-Time Optimization for better performance.
      - **`-Dcompile_server=false`**: Disables compiling the Scrcpy server.
      - **`-Dprebuilt_server=${WORKDIR}/scrcpy-server-${PV}`**: Uses a prebuilt server binary.
   - **`FILES:${PN}`**: Ensures proper files are included in the final package.
      - **Expected Error if not use FILES :**
         ```
         /usr/share/somefiles
         Please set FILES such that these items are packaged. Alternatively if they are unneeded, avoid installing them or delete them within do_install.
         scrcpy: 11 installed and not shipped files. [installed-vs-shipped]
         ```
         **Solution:** Verify the required paths and explicitly include missing files in `FILES:${PN}`.
   - **Expected Error:**
      ```
      ffmpeg was skipped: because it has a restricted license 'commercial'. Which is not listed in LICENSE_FLAGS_ACCEPTED
      ERROR: Required build target 'scrcpy' has no buildable providers.
      Missing or unbuildable dependency chain was: ['scrcpy', 'ffmpeg']
      ```
   **Solution:** Add this to your `local.conf`:
   ```bitbake
   LICENSE_FLAGS_ACCEPTED = "commercial_ffmpeg"
   ```
   For More details: [Yocto Licensing](https://docs.yoctoproject.org/dev-manual/licenses.html#enabling-commercially-licensed-recipes)

---

### **19. Building an Image**
   - To build ivi-test-image for raspberry pi , run: 
         ```
         bitbake ivi-test-image
         ```
   - This will download, compile, and package all the components needed for the image.

---

### **20.create image `wic` Writable Image Creator (Yocto Tool)**  
`wic` (Writable Image Creator) is a Yocto tool used to generate bootable disk images with custom partitioning, making it suitable for SD cards, USB drives, and hard disks. It seamlessly integrates with the Yocto build system to automate image creation and supports multiple storage devices, making it essential for embedded systems.  
for more details :  [wic Yocto Documentation](https://docs.yoctoproject.org/4.0.25/dev-manual/wic.html)   

### **Commands**  
| Command              | Usage                             | Example                                                  |
|----------------------|-----------------------------------|----------------------------------------------------------|
| `wic create <image>` | Generate a bootable `.wic` image. | `wic create sdimage-raspberrypi -e ivi-test-image `      |

### **21. flashing the image on sd card** 
```bash 
sudo dd if=./sdimage-raspberrypi-202503011435-mmcblk0.direct of=/dev/mmcblk0 status=progress
```

### **22. Enabling Video Output on Raspberry Pi 4**  

After booting into the image and testing everything, **RPiPlay wasn't displaying anything on the Raspberry Pi 4**, even though it worked on other platforms.  

#### **Investigating the Issue**  
 RPiPlay was originally designed for **Raspberry Pi 3**, and the video driver setup differs between Pi 3 and Pi 4.  
 The **default video driver settings** in `config.txt` were likely incompatible with Pi 4, preventing video output.  

#### **Solution: Update `config.txt` for Raspberry Pi 4**  
   1. **To enable proper video rendering on RPi 4**
   we need to modify `/boot/config.txt` by adding the following lines and remove the older `dtoverlay` :  
      ```config.txt
      # Enable DRM VC4 V3D driver on top of the dispmanx display stack
      dtoverlay=vc4-fkms-v3d
      max_framebuffers=2
      ```
      - `vc4-fkms-v3d` enables the **Fake KMS (FKMS) driver**, allowing OpenGL acceleration while maintaining compatibility with legacy display stacks.  
      - `max_framebuffers=2` ensures enough framebuffers are available for smooth rendering.  

   
   2.  **Reboot the system**: 
            ```
            reboot
            ```
   3. **Run RPiPlay again**, and now video output should work properly!