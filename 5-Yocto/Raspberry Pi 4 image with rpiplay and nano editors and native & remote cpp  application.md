### **1. Application Requirements**

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

Distributions:

* Distribution 1:
    * Includes Meta-qt5.
    * Uses systemd as the init system.

* Distribution 2:
    * Excludes Meta-qt5.
    * Uses sysvinit as the init system.
    
### **2. Setting Up the Environment**

To successfully build a Yocto-based image for the Raspberry Pi 4, follow these steps to set up your development environment.

---

#### **1. Install Required Dependencies**

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

#### **2. Download and Configure Poky**

Poky is the reference build system for Yocto. To obtain the Poky repository and switch to the desired branch:
[exploring the poky direcotry](https://docs.yoctoproject.org/4.0.25/ref-manual/structure.html#source-directory-structure) 


```bash
git clone https://github.com/yoctoproject/poky.git
cd poky
git switch kirkstone
```

---

#### **3. Define the Directory Structure**

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

#### **4. Configure Local Build Settings**

Edit `local.conf` in the `build-raspberrypi4/conf/` directory to match the target hardware and improve performance:

```local.conf
MACHINE ?= "raspberrypi4"
DL_DIR ?= "${TOPDIR}/../downloads"
BB_NUMBER_THREADS="5"
PARALLEL_MAKE="-j 5"
hostname:pn-base-files = "Mohamed"
```

##### **Explanation of Modifications:**

- `MACHINE`: Defines the target hardware as Raspberry Pi 4.
- `DL_DIR`: Points to the shared `downloads` directory, avoiding redundant downloads.
- `DISTRO`: Custom distribution name, allowing better configuration control.
- `BB_NUMBER_THREADS` & `PARALLEL_MAKE`: Optimize build performance by leveraging multiple CPU cores.
- `hostname:pn-base-files`: Sets the system hostname to "Mohamed".

By following these steps, your Yocto environment is set up efficiently and ready for further customization.



#### 5. **Initialize the Build Environment**:
   - Run the following command to set up the build environment:
     ```bash
     source poky/oe-init-build-env build-raspberrypi4
     ```
   - This creates a `build` directory and sets up the necessary environment variables.



#### **6. Fetch and Add Layers**

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
**Using `${TOPDIR}/..` in `bblayers.conf` makes paths **relative **to the build directory, providing key benefits:**

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

### - infotainment distro

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
SDK_VENDOR = "-mohamedSDK" # دي نرجسية مش اكتر :)
SDK_VERSION = "${@d.getVar('DISTRO_VERSION').replace('snapshot-${METADATA_REVISION}', 'snapshot')}"
SDK_VERSION[vardepvalue] = "${SDK_VERSION}"
SDK_NAME = "${DISTRO}-${TCLIBC}-${SDKMACHINE}-${IMAGE_BASENAME}-${TUNE_PKGARCH}-${MACHINE}"
# Installation path --> can be changed to ${HOME}-${DISTRO}-${SDK_VERSION}
SDKPATHINSTALL = "/opt/${DISTRO}/${SDK_VERSION}" 


# Disribution Feature --> NOTE: used to add customize package (for package usage).
INFOTAINMENT_DEFAULT_DISTRO_FEATURES = "largefile opengl ptest wayland multiarch vulkan x11 bluez5 bluetooth wifi qt5 "
INFOTAINMENT_DEFAULT_EXTRA_RDEPENDS = "packagegroup-core-boot"
INFOTAINMENT_DEFAULT_EXTRA_RRECOMMENDS = "kernel-module-af-packet"


DISTRO_FEATURES ?= "${DISTRO_FEATURES_DEFAULT} ${INFOTAINMENT_DEFAULT_DISTRO_FEATURES} userland"


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
##### **Explanation:**  
- `DISTRO`: Defines the distribution name used in builds.  
- `DISTRO_NAME`: A human-readable name for your distro.  
- `DISTRO_VERSION`: Specifies the version of the distribution.  
- `DISTRO_FEATURES`: Adds features like **Bluetooth** and **WiFi**.  
- `PACKAGE_CLASSES`: Uses **RPM** as the package format.  
- `INHERIT`: Ensures a package manager is included in the build.  

- **Update `local.conf` to Use the infotainment Distribution**  
Modify `build-raspberrypi4/conf/local.conf` and set `DISTRO`:  

``` local.conf
DISTRO ?= "infotainment"
```
- **Verify the Configuration**  
Run the following command to ensure the distribution is recognized:  
```bash
bitbake -e | grep "^DISTRO="
```
If everything is correct, it should print:  
```bash
DISTRO="infotainment"
```

---

### **Enable systemd for Infotainment Distribution**  

By default, **Poky uses `sysvinit`** as its **init manager** unless explicitly changed. To switch to **systemd** for the Infotainment distribution, we will include a configuration file.  

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

### - audio distro

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

DISTRO_FEATURES:append = " userland pulseaudio alsa"
```
##### **Explanation:**  
- `DISTRO`: Names the distribution as **audio**.  
- `DISTRO_NAME`: A user-friendly name for the distribution.  
- `DISTRO_VERSION`: Specifies the distribution version.  
- `DISTRO_FEATURES`: Adds **PulseAudio** and **ALSA** support.  


By default, **Poky uses `sysvinit`** as its **init manager** unless explicitly changed. so there is no addition steps here for fullfill the requirment.


- **Update `local.conf` to Use the New Audio Distribution if neededd**  
Modify `build-raspberrypi4/conf/local.conf` and set `DISTRO`:  

```local.conf
DISTRO ?= "audio"
```

- **Verify the Configuration**  
Check that the distribution is correctly set:  

```bash
bitbake -e | grep "^DISTRO="
```
Expected output:  
```bash
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

### **Structure of an Image Recipe in Yocto**  

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

```ivi-test-image.bb
require recipes-core/images/rpi-test-image.bb

inherit audio
# If you use :append in conf files, leave a blank space after `"`, and do not leave spaces before and after `=`.
# In recipes, you can use both :append and `+=`. When using `+=`, leave spaces before and after it.

IMAGE_INSTALL:append=" nano c-helloworld cpp-helloworld appssl rpi-play "
IMAGE_FEATURES += " ssh-server-dropbear debug-tweaks tools-debug "
```

### **Explanation of the Recipe**  

- **`require recipes-core/images/rpi-test-image.bb`**  
  - Inherits from `rpi-test-image.bb`, meaning it will have the same base configuration.  

- **`inherit audio`**  
  - Inherits the `audio` class, which likely sets up sound-related configurations.  

- **`IMAGE_INSTALL:append=" nano c-helloworld cpp-helloworld appssl rpi-play "`**  
  - Appends the listed packages (`nano`, custom Hello World apps, OpenSSL app, and a media player).  

- **`IMAGE_FEATURES += " ssh-server-dropbear debug-tweaks tools-debug "`**  
  - Adds features like SSH support (`dropbear`), debugging tweaks, and extra tools.  
  🔗 [Image Features yocto documentaion](https://docs.yoctoproject.org/4.0.25/ref-manual/features.html#image-features)  

---


### **Best Practices for Naming Yocto Recipes**  

- **Use the software name** → Match the upstream package (e.g., `nano_6.4.bb`).  
- **Follow `<package-name>_<version>.bb`** → Example: `mytool_1.0.bb`.  
- **Lowercase only** → `nginx_1.22.0.bb`, `NGINX_1.22.0.bb`.  
- **Prefix language-specific recipes** → `python3-requests_2.31.0.bb`, `perl-libxml_0.9.1.bb`.  
- **don't use space ` ` , use `-` instead of it .
---

### **11. Creating the First Recipe: `cpp-helloworld`**  

We are now moving on to creating our first custom recipe for a C++ application. Following the Yocto documentation, we will generate and modify the recipe to meet our project's requirements.  

🔗 [Yocto Writing a New Recipe Documentation](https://docs.yoctoproject.org/4.0.25/dev-manual/new-recipe.html#writing-a-new-recipe)

- **Generate the Initial Recipe**  

1. **Create a directory for C++ recipes**:  
   ```bash
   mkdir -p layers/meta-IVI/recipes-cpp/cpp-helloworld
   ```
 **why this structure necessary?**
  - **Following Yocto's Standard Structure**  
        - Yocto organizes recipes under folders like `recipes-core/`, `recipes-devtools/`, etc., making it easier to manage and locate them
  - *Parsing & `layer.conf` Configuration**  
        - Each layer contains a `layer.conf` file, which defines how BitBake finds recipe files.  
        - Typically, `BBFILES` is set like this:  
     ```layer.conf
     BBFILES += "${LAYERDIR}/recipes-*/*/*.bb"
     ```
        - This means Yocto expects `.bb` files to be inside a **subdirectory** within `recipes-*`.  

2. **Run the following command inside the `meta-IVI/recipes-cpp/cpp-helloworld` layer to create the base recipe:** 
🔗 [Recpitool Documentation](https://docs.yoctoproject.org/4.0.25/dev-manual/new-recipe.html#creating-the-base-recipe-using-recipetool-create)

```bash
recipetool create -o cpp-helloworld_1.0.bb https://github.com/embeddedlinuxworkshop/y_t1.git
```

This will generate a folder named `cpp-helloworld_1.0.bb` with an initial recipe file.  


- **Modify the Recipe**  

After generating the recipe, edit the `cpp-helloworld_1.0.bb` file and apply the following changes:  

```ini
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

Since `appssl` is a **local application**, we must use `SRC_URI = "file://appssl.cpp"` to fetch the source code from our local machine instead of downloading it from an external repository.  [Yocto: Fetching Code in Recipes](https://docs.yoctoproject.org/4.0.25/dev-manual/new-recipe.html#fetching-code)

- **Folder Structure**  
We follow the Yocto best practices by creating:  
```bash
mkdir -p layers/meta-IVI/recipes-cpp/appssl/files
```
The `files/` directory (or one with the same name as the recipe) is necessary for BitBake to recognize and access local source files.


``` terminal output
recipes-cpp
├── appssl
   ├── appssl_1.0.bb
   └── files
       └── appssl.cpp
```

- **Resolving Dependencies**  
To determine the correct flags for linking against OpenSSL, you can use:  
```bash
pkg-config --libs --cflags openssl
```
This helps find the necessary compiler and linker flags.


### **2. Understanding the Recipe**  

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

#### **Explanation of Variables:**
- **`${CXX}`** → Uses the C++ compiler set by Yocto.
- **`${LDFLAGS}`** → Ensures correct linking flags for the build.
- **`-lssl -lcrypto`** → Links against OpenSSL libraries.
- **`${D}${bindir}`** → Installs the compiled binary into `/usr/bin/` inside the target filesystem.

### **Understanding `install` Command**  
The `install` command in Linux is used for copying and setting file permissions.  
To check its options, run:  
```bash
man install
```
In our case:
- `install -d` → Creates the destination directory.
- `install -m 0755` → Copies the file and sets permissions (`rwxr-xr-x`).

---




### **13. Integrating Nano into Yocto**

### Method 1: Using GNU FTP (Nano 7.2)
For more details, visit: [Nano Releases](https://ftp.gnu.org/gnu/nano/).
- Navigate to your layer's `recipes-editors` directory:
   ```bash
   mkdir -p layers/meta-YourLayer/recipes-editors/nano
   cd layers/meta-YourLayer/recipes-editors/nano
   ```
- Create a recipe using `recipetool`:
   ```sh
   recipetool create -o nano_1.0.bb https://ftp.gnu.org/gnu/nano/nano-7.2.tar.xz
   ```

- Build Nano using Bitbake:
   ```sh
   bitbake nano
   ```

---

### Method 2: Using the Official Git Repository (Nano 8.3)

For more details, visit: [Nano Git Repository](https://git.savannah.gnu.org/cgit/nano.git/tree/README.hacking).

- Install dependencies required for building Nano from source:
   ```sh
   sudo apt install autoconf automake autopoint gcc gettext git groff make pkg-config texinfo
   ```
- Create a recipe using `recipetool`:
   ```sh
   recipetool create -o nano_1.0.bb git://git.savannah.gnu.org/nano.git
   ```
- Fetch and unpack the source code:
   ```sh
   bitbake -c fetch nano
   bitbake -c unpack nano
   ```
   
- Find the `WORKDIR` path:
   ```sh
   bitbake -e nano | grep -i "^workdir="
   ```
   Navigate to the printed path.

- Run `autogen.sh` to generate the `configure` script:
   ```sh
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
   ```sh
   bitbake nano
   ```
 **TODO in the future :  automate this steps**
```
 # i tried this method and there is an error figure it ! 
 
do_autogen() {
    cd ${S}
    ./autogen.sh
}

addtask do_autogen before do_configure after do_unpack
```

---

### **14.  Steps to integrate `audio` in `meta-IVI` Layer**  
 
#### **Steps to Create `audio.bbclass` in `meta-IVI` Layer**  
- **Navigate to your layer directory & **Create the `classes/` directory if it doesn’t exist::**  
```sh
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

### **`inc` vs. `bbclass` in Yocto**  

 **`.inc` (Include File):**  
- It is **included textually** in a recipe (`.bb`) during parsing, like a **copy-paste** operation.  
- Any modification **does not directly affect** the recipes that included it unless you run **`bitbake -c clean <package>`** and rebuild.  
- Used for **shared settings** across multiple recipes, but without the need for inheritance (`inherit`).  

 **`.bbclass` (Class File):**  
- It is **inherited** in recipes (`inherit audio`), and its content is **executed at build time**, not just included.  
- Any modification **immediately affects all recipes** that inherit it, without needing a `clean` operation.  
- Used when there is **common build logic**, such as `kernel.bbclass` or `image.bbclass`.  

**`inherit` is used to reuse **build logic**, **while `include` and `require` are used to reuse **configurations** or **variables**.

---  

### **15. rpiplay**










---

### **. Building an Image**
1. **Build the final Image**:
   - To build ivi-test-image for raspberry pi , run:
     ```bash
     bitbake ivi-test-image
     ```
   - This will download, compile, and package all the components needed for the image.

2. **Output Files**:
   - After a successful build, the output files (e.g., kernel, root filesystem) will be located in:
     ```
     tmp-glibc/deploy/images/raspberrypi/
     ```




