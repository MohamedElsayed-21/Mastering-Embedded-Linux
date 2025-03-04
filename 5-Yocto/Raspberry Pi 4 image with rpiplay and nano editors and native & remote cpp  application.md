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
* **RPI Play:** For screen mirroring.
* **Audio:** Support for audio playback and recording.
* **Native Hello Bullet Application:** A sample application for testing.
* **Community: Layer for Observability:** A custom layer for monitoring and observability.

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
## **Yocto Project: A Comprehensive Guide**
### **1. What is Yocto?**

The **Yocto Project** is an open-source collaboration project that provides templates, tools, and methods to help you create custom Linux-based systems for embedded products, regardless of the hardware architecture. It’s widely used in IoT, industrial automation, and other embedded systems.

---

#### **Core Concepts**
- **BitBake**
   - **BitBake** is the build engine used by Yocto.
   - It reads **recipes** (instructions for building packages) and executes tasks like fetching source code, compiling, and packaging.
   - BitBake is highly customizable and supports parallel builds.

   - **BitBake Workflow:**  

      1. **Create `bitbake.lock`** → Ensures only one instance of BitBake runs at a time to prevent conflicts.  
      2. **Read `build/conf/bblayers.conf`** → Defines which layers (e.g., meta-openembedded, meta-yocto) are included in the build.  
      3. **Read `build/conf/local.conf`** → Contains user-specific configurations like `MACHINE`, `DISTRO`, `IMAGE_FSTYPES`, etc.  
      4. **Read `meta/conf/layer.conf`** → Defines how BitBake should handle each layer, including priority and dependencies.  
      5. **Read `meta/conf/bitbake.conf`** → Core configuration file that sets global variables and paths for the build system.  
      6. **Read `classes/base.bbclass`** → Provides common build functions and settings shared across multiple recipes.  
      7. **Parse `core-image-minimal.bb`** → This is the main recipe for building a minimal image, specifying dependencies and tasks.  
      8. **Execute Tasks (`do_fetch` → `do_unpack` → `do_patch` → `do_configure` → `do_compile` → `do_install` → `do_package` → `do_rootfs` → `do_deploy`)** → Runs each task step-by-step to build the image and generate output files.  
      9. **Remove `bitbake.lock`** → Signals that the build process is complete, allowing future builds to start.
      - run this command  to see the workflow of bitbake 
         ``` bash 
         strace -e trace=openat -f bitbake core-image-minimal |& grep -E ~/Documents/Mastering_Embedded_Linux/5-Yocto/poky/qemu-build | grep -v cache
         ```

- **OpenEmbedded (OE)** is a build framework for creating customized Linux distributions for embedded systems. It provides a flexible, cross-compilation environment with package management, dependency handling, and build automation.

- **Poky** is the reference distribution of the **Yocto Project**. It serves as a build tool and minimal embedded Linux distribution, integrating **BitBake** and **OpenEmbedded** metadata.  
**Poky = OpenEmbedded Core + BitBake + Additional Metadata**  
   - **OpenEmbedded Core (OE-Core)** → Provides base recipes and classes.  
   - **BitBake** → The build engine.  
   - **Additional Metadata (meta-poky, meta-yocto, etc.)** → Adds configurations and customizations.  

- **Layers**
   - **Layers** are directories that contain related recipes, configurations, and files.
   - Layers allow you to modularize your build system. For example:
   - `meta`: Core layer provided by Yocto.
   - `meta-qt5`: Layer for Qt5 support.
   - You can add or remove layers depending on your project requirements.

- **Recipes**
   - **Recipes** (`.bb` files) contain instructions for building a specific package or component.
   - A recipe typically includes:
   - Source code location (e.g., Git repository or tarball).
   - Dependencies (other packages required for building).
   - Build instructions (e.g., `configure`, `make`, `install`).




### **2. Setting Up the Environment**

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

Poky is the reference build system for Yocto. To obtain the Poky repository and switch to the desired branch:
[exploring the poky direcotry](https://docs.yoctoproject.org/4.0.25/ref-manual/structure.html#source-directory-structure) 

```bash
git clone https://github.com/yoctoproject/poky.git
cd poky
git switch kirkstone
```
##### Yocto has multiple releases to ensure stability, introduce new features, and support evolving hardware. It follows a **6-month release cycle**, with some versions being **LTS (Long-Term Support)** for production use (e.g., **Dunfell, Kirkstone**).  

##### LTS releases get **2+ years of support**, while standard releases last ~1 year. Newer versions include updated **kernels, toolchains, and libraries**, while older ones receive security fixes. If you need stability, use an **LTS release**; for the latest features, go with the newest version.
---

### **3. Define the Directory Structure**

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

### 5. **Initialize the Build Environment**:
   - Run the following command to set up the build environment:
      ```bash
     source poky/oe-init-build-env build-raspberrypi4
      ```
   - This creates a `build` directory and sets up the necessary environment variables.



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

These layers provide support for Raspberry Pi, additional open-source packages, and Qt5 for graphical applications.
By following these steps, your Yocto environment is set up efficiently and ready for further customization.

- **Edit `bblayers.conf` in the `build-raspberrypi4/conf/` directory :**

   ```bblayers.conf
   BBLAYERS ?= " \
   ${TOPDIR}/../poky/meta \
   ${TOPDIR}/../poky/meta-poky \
   ${TOPDIR}/../poky/meta-yocto-bsp \
   ${TOPDIR}/../layers/meta-raspberrypi \
   ${TOPDIR}/../layers/meta-openembedded/meta-oe \
   ${TOPDIR}/../layers/meta-qt5 \

   ```
**Using `${TOPDIR}/..` in `bblayers.conf` makes pathsrelative** **to the build directory, providing key benefits:**

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

   ``` infotainment.conf
   DISTRO="infotainment"
   DISTRO_NAME="MOHAMED-infotainment"
   DISTRO_VERSION="1.0"

   MAINTAINER="mohamedelsayedhussein22@gmail.com"

   # SDK Information.
   SDK_VENDOR = "-mohamedSDK"
   SDK_VERSION = "${@d.getVar('DISTRO_VERSION').replace('snapshot-${METADATA_REVISION}', 'snapshot')}"
   SDK_VERSION[vardepvalue] = "${SDK_VERSION}"

   SDK_NAME = "${DISTRO}-${TCLIBC}-${SDKMACHINE}-${IMAGE_BASENAME}-${TUNE_PKGARCH}-${MACHINE}"

   # Installation path --> can be changed to ${HOME}-${DISTRO}-${SDK_VERSION}
   SDKPATHINSTALL = "/opt/${DISTRO}/${SDK_VERSION}" 

   INFOTAINMENT_DEFAULT_DISTRO_FEATURES = "largefile opengl ptest wayland multiarch vulkan x11 bluez5 qt5 "
   # meta/conf/distro/include/default-distrovars.inc -->  DISTRO_FEATURES_DEFAULT ?= "acl alsa argp bluetooth debuginfod ext2 ipv4 ipv6 largefile pcmcia usbgadget usbhost wifi xattr nfs zeroconf pci 3g nfc x11 vfat seccomp"
   DISTRO_FEATURES ?= "${DISTRO_FEATURES_DEFAULT} \ 
                     ${INFOTAINMENT_DEFAULT_DISTRO_FEATURES} \
                     userland  pulseaudio   "

   IMAGE_INSTALL:append=" qttools rpi-play "

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
   - If everything is correct, it should print:  
      ```
      DISTRO="infotainment"
      ```

---

#### **Enable systemd for Infotainment Distribution**  

##### By default, **Poky uses `sysvinit`** as its **init manager** unless explicitly changed. To switch to **systemd** for the Infotainment distribution, we will include a configuration file.  

For more details on init managers in Yocto, refer to the official documentation:  
🔗 [Yocto Init Manager Documentation](https://docs.yoctoproject.org/4.0.25/dev-manual/init-manager.html#using-systemd)  

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
   # It existed in meta/conf/distro/include/init-manager-systemd.inc.

   # Install systemd as the init manager
   # DISTRO_FEATURES:append=" systemd "

   # Select systemd as the init manager
   # VIRTUAL-RUNTIME_init_manager="systemd"
   # VIRTUAL-RUNTIME_initscripts="systemd-compat-units"

   # Select busybox-mdev as the device manager
   # VIRTUAL-RUNTIME_dev_manager="busybox-mdev"

   # Just use this variable to set systemd
   INIT_MANAGER = "systemd"
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
- **Open `audio.conf` and define the **audio-specific settings**:  

   ```audio.conf
   require conf/distro/poky.conf

   DISTRO="audio"
   DISTRO_NAME="audio-os "
   DISTRO_VERSION="1.0"

   MAINTAINER="mohamedelsayedhussein22@gmail.com"

   DISTRO_FEATURES:remove = " largefile opengl ptest multiarch vulkan"
   DISTRO_FEATURES:append = " userland pulseaudio bluetooth wifi alsa"
   ```
#### By default, **Poky uses `sysvinit`** as its **init manager** unless explicitly changed. so there is no addition steps here for fullfill the requirment.


- **Update `local.conf` to Use the New Audio Distribution if neededd**  
Modify `build-raspberrypi4/conf/local.conf` and set `DISTRO ?= "audio"`:  
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

   # if you use :append -you have to use it in conf only- you have to leave blank space after `"` and don't leave space before and after `=` .
   #  vice versa in `+=`- in recipes you can use both options :append and += -  you will leave blank space before and after it and not necssary to leave one after `"`

   # inherit audio
   # inherit qtfeatures
   # this feature  alreadey existed in (rpi-test-image.bb --> rpi-base.inc so you don't need to add it again)
   # MACHINE_FEATURES += "wifi bluetooth alsa"

   IMAGE_INSTALL:append=" vsomeip nano c-helloworld cpp-helloworld appssl can-utils "

   IMAGE_FEATURES += " ssh-server-dropbear debug-tweaks tools-debug "



   # Set the root filesystem size
   # IMAGE_ROOTFS_SIZE = "16384"
   # To run custom commands after the root filesystem is created.
   # ROOTFS_POSTPROCESS_COMMAND += "my_custom_script.sh"


   ```

 **Explanation of the Recipe**  

- **`require recipes-core/images/rpi-test-image.bb`**  
  - Inherits from `rpi-test-image.bb`, meaning it will have the same base configuration.  
- **`IMAGE_FEATURES += " ssh-server-dropbear debug-tweaks tools-debug "`**  
  - Adds features like SSH support (`dropbear`), debugging tweaks, and extra tools.  
  🔗 [Image Features yocto documentaion](https://docs.yoctoproject.org/4.0.25/ref-manual/features.html#image-features)  

---

#### **Structure of an Image Recipe in Yocto**  

An **image recipe** in Yocto typically consists of the following components:  
1. **Base Image** (`require` statement)  
   - It defines the core structure of the image by inheriting from an existing base image.  
   - Example: `core-image-base`, `core-image-minimal`, `rpi-test-image`, etc.  
   
2. **Image Features** (`IMAGE_FEATURES`)  
   - Defines additional capabilities like SSH, debugging tools, or package management.  
   - Example: `ssh-server-dropbear`, `debug-tweaks`, `tools-debug`.  

3. **Package Installation** (`IMAGE_INSTALL`)  
   - Specifies additional software packages to be included in the image.  
   - Example: `nano`, `c-helloworld`, `cpp-helloworld`, `appssl`, `rpi-play`.  

4. **Optional Inheritance (`inherit`)**  
   - Some images inherit special classes that modify their behavior.  
   - Example: `inherit core-image` or `inherit audio` (custom class).  

For reference, check the base images available in Yocto:  
🔗 [Yocto Base Images](https://docs.yoctoproject.org/4.0.25/ref-manual/images.html)  
🔗 [meta-raspberrypi Documentation](https://meta-raspberrypi.readthedocs.io/en/latest/)  


#### **Best Practices for Naming Yocto Recipes**  

- **Use the software name** → Match the upstream package (e.g., `nano_6.4.bb`).  
- **Follow `<package-name>_<version>.bb`** → Example: `mytool_1.0.bb`.  
- **Lowercase only** → `nginx_1.22.0.bb`, `NGINX_1.22.0.bb`.  
- **Prefix language-specific recipes** → `python3-requests_2.31.0.bb`, `perl-libxml_0.9.1.bb`.  
- **don't use space** ` ` , use `-` instead of it .
---

### **11. Creating the First Recipe: `cpp-helloworld`**  

#### We are now moving on to creating our first custom recipe for a C++ application. Following the Yocto documentation, we will generate and modify the recipe to meet our project's requirements.  

🔗 [Yocto Writing a New Recipe Documentation](https://docs.yoctoproject.org/4.0.25/dev-manual/new-recipe.html#writing-a-new-recipe)

- **Generate the Initial Recipe file**  

1. **Create a directory for C++ recipes**:  
         ```bash
         mkdir -p layers/meta-IVI/recipes-cpp/cpp-helloworld
         ```
      **why this structure necessary?**
   - **Following Yocto's Standard Structure**  
         - Each layer contains a `layer.conf` file, which defines how BitBake finds recipe files.  
         - Typically, `BBFILES` is set like this:  
            ```layer.conf
            BBFILES += "${LAYERDIR}/recipes-*/*/*.bb"
            ```
         - This means Yocto expects `.bb` files to be inside a **subdirectory** within `recipes-*`.  


   2. **Run the following command inside the `meta-IVI/recipes-cpp/cpp-helloworld` layer to create the base recipe:** 
   🔗 [Recpitool Documentation](https://docs.yoctoproject.org/4.0.25/dev-manual/new-recipe.html#creating-the-base-recipe-using-recipetool-create)

      ```bash
      cd layers/meta-IVI/recipes-cpp/cpp-helloworld
      recipetool create -o cpp-helloworld_1.0.bb https://github.com/embeddedlinuxworkshop/y_t1.git
      ```

       This will generate a folder named `cpp-helloworld_1.0.bb` with an initial recipe file.  


- **Modify the Recipe**  

   After generating the recipe, edit the `cpp-helloworld_1.0.bb` file and apply the following changes:  

      ```cpp-helloworld_1.0.bb
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

this the cpp application , we want to integrate it in out image .
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
  [Yocto: Fetching Code in Recipes](https://docs.yoctoproject.org/4.0.25/dev-manual/new-recipe.html#fetching-code)
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
#### The `files/` directory or (  `{BPN}:` → `appssl/` or `${BP} - ${BPN}-${PV}` → `appssl_1.0` ) is necessary for BitBake to recognize and access local source files. 




- **Resolving Dependencies**  
To determine the correct flags for linking against OpenSSL, you can use:  
   ```bash
  $  pkg-config --libs --cflags openssl
   -lssl -lcrypto
   ```
   This helps find the necessary compiler and linker flags.


#### **The Package  Recipe**  

   ```appssl_1.0.bb
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

#### **Understanding `install` Command**  
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
   ```sh
      recipetool create -o nano_1.0.bb https://ftp.gnu.org/gnu/nano/nano-7.2.tar.xz
   ```

- Build Nano using Bitbake:
   ```bash
      bitbake nano
   ```

---

### Method 2: Using the Official Git Repository (Nano 8.3)

For more details, visit: [Nano Git Repository](https://git.savannah.gnu.org/cgit/nano.git/tree/README.hacking).

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
 **Automate this steps**
   **1. Patch `autogen.sh`**

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

   **2. Final Recipe for Nano**
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

**Problem**
 The original `autogen.sh` script tries to clone Gnulib using a **private Git link**:
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
 
#### **Steps to Create `audio.bbclass` in `meta-IVI` Layer**  
- **Navigate to your layer directory & **Create the `classes/` directory if it doesn’t exist::**  
   ```bash
   cd layers/meta-IVI
   mkdir -p classes
   touch classes/audio.bbclass
   ```
- **Edit the file and add the following content:**  
   ```audio.bbclass
   IMAGE_INSTALL:append = " pavucontrol pulseaudio pulseaudio-module-dbus-protocol pulseaudio-server \
                           pulseaudio-module-loopback pulseaudio-module-bluetooth-discover alsa-ucm-conf \
                           pulseaudio-module-bluetooth-policy alsa-topology-conf alsa-state alsa-lib alsa-tools \
                           pulseaudio-module-bluez5-device pulseaudio-module-bluez5-discover alsa-utils alsa-plugins bluez5 "
   ```
Once **`inherit audio`** is added to a recipe, all these packages will be automatically included in the **final image**.  

####  Or simply add the `alsa` and `pulseaudio` into the `DISTRO_FEATURES`


#### **`inc` vs. `bbclass` vs `require` in Yocto**  

 **(Include File):**  
- It is **included textually** in a recipe (`.bb`) during parsing, like a **copy-paste** operation.  
- Any modification **does not directly affect** the recipes that included it unless you run **`bitbake -c clean <package>`** and rebuild.  
- `include` is used to **insert the contents of another file** into the current recipe or configuration file.
- The included file can be a `.inc` file, a `.bb` file, or any other file with valid BitBake syntax.
- Use **`include`** when you want to reuse **configurations** or **variables** from another file, but it’s optional.
- Used for **shared settings** across multiple recipes, but without the need for inheritance (`inherit`).  

 **(Class File):**  
- It is **inherited** in recipes (`inherit audio`), and its content is **executed at build time**, not just included.  
- Any modification **immediately affects all recipes** that inherit it, without needing a `clean` operation.  
- Used when there is **common build logic**, such as `kernel.bbclass` ,`autotools`, `cmake` or `image.bbclass`.
- `inherit` is used to **inherit classes** in BitBake.
- Classes are files (`.bbclass`) that contain common functionality that can be reused across multiple recipes.

 **`require` in BitBake Recipes**  
The `require` directive in BitBake is used to **include the contents of another file** into the current recipe **at parse time**. It is similar to copy-pasting the content of the required file directly into the current file.   
- **Directly Includes Another File** → The contents of the required file are inserted into the recipe as if they were written there.  
- **Used for Sharing Common Configurations** → Useful when multiple recipes need the same settings.  
- **File Must Exist** → If the required file is missing, BitBake will throw an error.  


**`inherit` is used to reuse **build logic**, **while `include` and `require` are used to reuse **configurations** or **variables**.



#### **Table with BitBake's Perspective**  

| Keyword   | Purpose                 | BitBake's Perspective               | Behavior if File/Class is Missing | Commonly Used For         |
|-----------|-----------------------------------|----------------------------------|------------------------------|----------------------------|
| `inherit` | Inherit functionality from a class (`.bbclass`).                       | Extends the recipe by executing functions from the class. | Error (class not found).          | Reusing build logic (e.g., `autotools`).  |
| `include` | Insert the contents of another file (`.inc`, `.bb`, etc.).             | Parses the included file but does not enforce its presence. | Silent (no error).                | Reusing configurations or variables.       |
| `require` | Insert the contents of another file, but raise an error if not found.  | Parses and strictly enforces the required file's presence. | Error (file not found).           | Enforcing the presence of critical files.  |

---


### **15. rpiplay**


###  Steps for **RPiPlay** Integration  

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
      bitbake-layers layerindex-show-depends meta-networking # it shows that it needs (openembededdcore , meta-oe and meta-pyhthon)  
      bitbake-layers add-layer ../layers/meta-openembedded/meta-python
      bitbake-layers add-layer ../layers/meta-openembedded/meta-networking
      ```

Before applying a patch, let’s first **trigger the error** by running:  

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
      ```bash
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

   - But let’s confirm it was actually built:  
      ```bash
      bitbake -e userland | grep "^WORKDIR="
      ```
   - If `WORKDIR` is found, then `userland` **was built**.  
   - If it’s missing, we need to `bitbake userland` separately.  

- **Step 4: Manually Verify `/opt/vc` Inside `userland`**  
Since the `RPiPlay` repo expects `ilclient` inside `/opt/vc`, we need to check:  

   ```bash
   #  # the working ditectory of userland
   cd /home/mohamed/Documents/Mastering_Embedded_Linux/5-Yocto/build-raspberrypi4/tmp-glibc/work/cortexa7t2hf-neon-vfpv4-oe-linux-gnueabi/userland/20220323-r0/image"
   find . -name "*ilclient*"
   ```
   We see that `ilclient` **exists**, but in a different location:  
      ``` terminal output 
      $ find . -name "*ilclient*"
      ./usr/src/hello_pi/libs/ilclient
      ./usr/src/hello_pi/libs/ilclient/ilclient.h
      ./usr/src/hello_pi/libs/ilclient/ilclient.c
      ```
   This is **not** where `RPiPlay` expects it to be.  
      - If `/opt/vc` **exists and contains `ilclient`**, we need to **correct the CMake paths**. 
      - If it doesn’t exist, then userland wasn’t built properly or needs extra install steps or it built correctly but it's install the output in other place `/usr/` insted of `/opt/vc` .

**How does `bitbake` handle dependencies?**  
When `bitbake` builds `rpi-play`, it pulls dependencies from the `sysroot` of its dependencies (like `userland`).
 But in this case, **`userland` installs `ilclient` locally inside its own `image/` directory, and not in the `sysroot`**, so `RPiPlay` can't find it.  


- **Step 5: Possible Solutions and Why They Won't Work**  
  - **Manually copying `ilclient`**  Copying files manually into `sysroot` is not a scalable solution and goes against Yocto's clean design. 
   
  - **The Proper Fix – Patching CMake + Adjusting `userland` Sysroot**  
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
         #  the path of working directory of the rpi-play
            cd /home/mohamed/Documents/Mastering_Embedded_Linux/5-Yocto/build-raspberrypi4/tmp-glibc/work/cortexa7t2hf-neon-vfpv4-oe-linux-gnueabi/rpi-play/1.0-r0/git/
         ```
      2. Modify `renders/CMakeLists.txt` to replace `/opt/vc` with `/usr/`.  
      3. Generate a patch i recommend to make the patch file inside the `devshell`:  [concepts of diff and patch in YouTube](https://youtu.be/-s13A9MPmGU?si=levSHq4tF5SXgctj)
         ```patch
            bitbake -c devshell rpi-play # it will open other terminal that simulate the target environments . 
            # change each  `/opt/vc` you see with  `/usr/` insted of it .
            git diff > 0001_include_dir.patch
         ```
         the patch file content if you cannot make it 
         ```
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
      4. Copy the patch to the recipe folder:  
         ```bash
         # copy the patch file to the directory of the recipe
         cp 0001_include_dir.patch /home/mohamed/Documents/Mastering_Embedded_Linux/5-Yocto/meta-IVI/recipes-rpiplay/rpiplay/rpi-play
         ```
      5. Add it to `SRC_URI` in `rpi-play_1.0.bb`:  
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
#### **`Depends` vs `RDEPENDS_${PN}`**
**Runtime Libraries** are the shared libraries a program needs **while running**, whereas **Build-time (Development) Libraries** are required **only during compilation**. Build-time libraries (e.g., `libssl-dev`, `libplist-dev`) include header files (`.h`) and static libraries needed to compile software, while runtime libraries (e.g., `libssl`, `libplist`) contain shared objects (`.so`) that the program dynamically links to during execution.  

For example, if a program uses OpenSSL, it requires `libssl-dev` at **build-time** to provide necessary headers, but at **runtime**, it only needs `libssl.so` to function properly. In Yocto, dependencies are managed accordingly: `DEPENDS` includes build-time packages, while `RDEPENDS_${PN}` ensures runtime dependencies are available in the final system.

**Note:** How to determine the runtime dependencies of a package in **Yocto (Poky/ConTe Yocto variant)**?  
You can run the following command:  
   ```bash
   $ readelf -d rpiplay | grep -i needed
   # This will list all the shared libraries (`.so` files) required by the binary. Based on this output, you can decide which packages to include in the `RDEPENDS_${PN}` variable. 

   # Example output:
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

#### *Example `RDEPENDS_${PN}`:*
   ```rpi-play.bb
   RDEPENDS_${PN} = "avahi libplist gstreamer1.0-plugins-base gstreamer1.0-plugins-good"
   ```
   This ensures that the necessary runtime dependencies are available when the package is installed.  

**Note:**  These two lines modify the **linking behavior** in a Yocto recipe:  
```rpi-play.bb
TARGET_LDFLAGS += "-Wl,--copy-dt-needed-entries"
EXTRA_OEMAKE:append = ' LDFLAGS="${TARGET_LDFLAGS}"'
```

1. **`-Wl,--copy-dt-needed-entries`**  
   - Ensures that **indirect shared library dependencies** are included in the final binary.  
   - Without it, only directly linked libraries are included, which can cause **runtime errors** if an intermediate library is missing.  

2. **`EXTRA_OEMAKE:append = ' LDFLAGS="${TARGET_LDFLAGS}"'`**  
   - Passes `TARGET_LDFLAGS` to `make`, ensuring the linker flag is applied during the build.  



- **Step 6: Rebuilding and Testing**  

   - Rebuild `rpi-play` with the patched CMakeLists.txt:  
      ```bash
      bitbake -c cleanall rpi-play
      bitbake rpi-play
      ```
   - Verify that `ilclient` is now present in the `sysroot`:  
      ```bash
         # the working ditectory of rpi-play 
         find /home/mohamed/Documents/Mastering_Embedded_Linux/5-Yocto/build-raspberrypi4/tmp-glibc/work/cortexa7t2hf-neon-vfpv4-oe-linux-gnueabi/rpi-play/1.0-r0/recipe-sysroot/ -name "*ilclient*"
      ```


---

#### **Difference Between `bitbake -c clean`, `cleanall`, and `cleansstate`**  
In **BitBake**, the `clean`, `cleansstate`, and `cleanall` commands are used to clean up build artifacts, but they differ in **scope** and **what they remove**. Understanding these differences is important for managing your build environment effectively.

- **`bitbake -c clean <recipe>`**  
  → Deletes `WORKDIR` (temporary build files `tmp/work/`) but keeps downloads and sstate cache.  
  
- **`bitbake -c cleansstate <recipe>`**  
  →  Deletes `WORKDIR` (`tmp/work/`) and shared state (`sstate-cache/`) cache but keeps downloads. Forces re-execution of tasks that use sstate (e.g., configure, compile).  
  
- **`bitbake -c cleanall <recipe>`**  
  → Deletes `WORKDIR` (`tmp/work/` ), source downloads( `downloads/` ), and sstate cache( `sstate-cache/` ). Equivalent to a fresh start for that recipe.  



#### **Comparison Table**

| Command          | Removes Working Directory | Removes Shared State Cache | Removes Downloaded Sources | Scope                     |
|------------------|---------------------------|----------------------------|----------------------------|---------------------------|
| `clean`          | Yes                       | No                         | No                         | Recipe-specific           |
| `cleansstate`    | Yes                       | Yes                        | No                         | Recipe-specific           |
| `cleanall`       | Yes                       | Yes                        | Yes                        | Recipe-specific           |



---


### **16. VSOMEIP Integration with Yocto (Kirkstone)**    

**VSOMEIP** is an open-source implementation of **SOME/IP (Scalable service-Oriented Middleware over IP)** used in automotive Ethernet-based communication. It enables service-oriented communication between ECUs (Electronic Control Units) following the **AUTOSAR** standard.  


- **Common Issues & Solutions**  

   Many users report errors like: [vsomeip GitHub Issue #362](https://github.com/COVESA/vsomeip/issues/362)  
   ```
   basic_socket_ext_local.hpp:133:7: error: no matching function for call to 'boost::asio::detail::io_object_impl<boost::asio::detail::reactive_socket_service_ext_local<boost::asio::local::stream_protocol_ext, boost::asio::executor>::io_object_impl(boost::asio::io_context&)'
   ```  
   This typically occurs due to **incompatibility between VSOMEIP and Boost versions**.  
   The best working **Boost version** for **VSOMEIP** on **Yocto Kirkstone** is:  `  Boost 1.71`
   Later versions cause the compilation to fail due to breaking changes in **Boost.Asio**.  so that you have to install [recipes-support (boost files)](https://github.com/COVESA/vsomeip/files/9394162/recipes-support.zip) in your layer and give it higher prority than the `meta`  

- **Setting Up VSOMEIP in Yocto**  
      Since **VSOMEIP** has dependencies and conflicts with some existing packages, it's essential to ensure the custom layer has a higher priority than **meta**. Modify `local.conf` or add to `layer.conf`:  
      ```sh
      BBFILE_PRIORITY_meta-IVI = "8"
      ```  

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


---

### **17. Building an Image**
   - To build ivi-test-image for raspberry pi , run: 
         ```
         bitbake ivi-test-image
         ```
   - This will download, compile, and package all the components needed for the image.

---

### **18.create image `wic` Writable Image Creator (Yocto Tool)**  
`wic` (Writable Image Creator) is a Yocto tool used to generate bootable disk images with custom partitioning, making it suitable for SD cards, USB drives, and hard disks. It seamlessly integrates with the Yocto build system to automate image creation and supports multiple storage devices, making it essential for embedded systems.  
for more details :  [wic Yocto Documentation](https://docs.yoctoproject.org/4.0.25/dev-manual/wic.html)   

### **Commands**  
| Command              | Usage                             | Example                                                  |
|----------------------|-----------------------------------|----------------------------------------------------------|
| `wic create <image>` | Generate a bootable `.wic` image. | `wic create sdimage-raspberrypi -e ivi-test-image `      |

### **19. flashing the image on sd card** 
```bash 
sudo dd if=./sdimage-raspberrypi-202503011435-mmcblk0.direct of=/dev/mmcblk0 status=progress
```

### **20. Enabling Video Output on Raspberry Pi 4**  

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
       **Why does this work?**  
         - `vc4-fkms-v3d` enables the **Fake KMS (FKMS) driver**, allowing OpenGL acceleration while maintaining compatibility with legacy display stacks.  
         - `max_framebuffers=2` ensures enough framebuffers are available for smooth rendering.  

   
   2.  **Reboot the system**: 
            ```
            sudo reboot
            ```
   3. **Run RPiPlay again**, and now video output should work properly!







