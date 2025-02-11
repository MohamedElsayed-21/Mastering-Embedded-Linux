# Documenting Configuration in /etc/fstab

This documentation provides a detailed explanation of how to configure partitions in the `/etc/fstab` file for automatic mounting, including the purpose of each field and additional flags you can use.

---

## **Structure of an fstab Entry**
Each entry in the `/etc/fstab` file follows this format:

``` 
<file_system>  <mount_point>  <file_system_type>  <options>  <dump>  <pass>
```

### **Field Breakdown:**
1. **`<file_system>`:**
   Specifies the filesystem or partition to be mounted. Commonly uses:
   - `UUID=<uuid>` (e.g., `UUID=259818B87A044995`) for stability.
   - `/dev/<device>` (e.g., `/dev/sda2`) for simpler setups (less stable).

2. **`<mount_point>`:**
   The directory where the filesystem will be mounted, e.g., `/media/mohamed/Hard-p1`.

3. **`<file_system_type>`:**
   The type of filesystem, e.g., `ntfs`, `ext4`, `vfat`.

4. **`<options>`:**
   Specifies options to control the mount behavior (see options below).

5. **`<dump>`:**
   Controls whether the filesystem is included in the `dump` command (used for backups):
   - `0`: Do not include in backups.
   - `1`: Include in backups.

6. **`<pass>`:**
   Specifies the order in which `fsck` (filesystem check) It’s a tool used to check and repair the filesystem. it runs during boot:
   - `0`: Do not check this partition.
   - `1`: Check first (used for root `/` filesystem).
   - `2`: Check after the root filesystem.

---

## **Common Options for the `<options>` Field**
The `<options>` field defines mount behaviors. Multiple options can be separated by commas (`,`). Below are the most common options:

### General Options:
1. **`defaults`:**
   A shorthand for the following:
   - `rw` (read and write).
   - `suid` (allow setuid bits).
   - `dev` (interpret device files like `/dev`).
   - `exec` (allow execution of binaries).
   - `auto` (automatically mount during boot).
   - `nouser` (only root can unmount).
   - `async` (asynchronous I/O).

2. **`rw` and `ro`:**
   - `rw`: Mount as read-write (default).
   - `ro`: Mount as read-only.

3. **`noexec`:**
   Prevents execution of binary files (useful for security).

4. **`nodev`:**
   Prevents interpretation of device files (e.g., `/dev/sda`).

5. **`nosuid`:**
   Ignores `setuid` and `setgid` bits for security.

6. **`uid` and `gid`:**
   Specifies the user and group ownership of files:
   - Example: `uid=1000,gid=1000` for user and group with ID `1000`.

7. **`umask`:**
   Controls file and directory permissions:
   - Example: `umask=022` sets permissions to `755` (rwxr-xr-x).

8. **`noatime` and `relatime`:**
   - `noatime`: Prevents updating the last access time (improves performance).
   - `relatime`: Updates access time only if modified (default).

9. **`user` and `nouser`:**
   - `user`: Allows non-root users to mount/unmount.
   - `nouser`: Restricts mount/unmount to root (default).
10. **`nofail`**
   - tell the system to ignore errors when a partition cannot be mounted during boot. If a partition is specified with nofail and it is missing or causes an error, the system will continue booting normally without entering emergency mode. This is especially useful when you have non-essential partitions that are not critical for the system to boot.
   
---

## **Example Configuration for NTFS Partitions**
Assume we have three partitions:

  - Ensure the UUIDs and mount points are correct.
   ```bash 
	$ blkid /dev/sda2
	/dev/sda2: BLOCK_SIZE="512" UUID="259818B87A044995" TYPE="ntfs" PARTUUID="8e94d24d-02"

	$ blkid /dev/sda4
	/dev/sda4: BLOCK_SIZE="512" UUID="15BCAA89532F79C3" TYPE="ntfs" PARTUUID="8e94d24d-04"

	$ blkid /dev/sda5
	/dev/sda5: BLOCK_SIZE="512" UUID="54757E5960A9EF64" TYPE="ntfs" PARTUUID="8e94d24d-05"
   ```
   - Verify the mount points exist. Create them if necessary:
     ```bash
   	$ sudo mkdir -p /media/mohamed/Hard-p1
	$ sudo mkdir -p /media/mohamed/Hard-p2
	$ sudo mkdir -p /media/mohamed/Hard-p3
     ```



### Add the following entries to `/etc/fstab`:

1. 
```bash 
sudo vi /etc/fstab
```
2. 
```
UUID=259818B87A044995  /media/mohamed/Hard-p1  ntfs  defaults,nofail  0  2
UUID=15BCAA89532F79C3  /media/mohamed/Hard-p2  ntfs  defaults,nofail  0  2
UUID=54757E5960A9EF64  /media/mohamed/Hard-p3  ntfs  defaults,nofail  0  2
```
---

## **Testing the Configuration**
After updating `/etc/fstab`, test the configuration without rebooting:

```bash
sudo mount -a
```
If no errors appear, the configuration is valid. To verify the mounts:

```bash
df -h
```

---

