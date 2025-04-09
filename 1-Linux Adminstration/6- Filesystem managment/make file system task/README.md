# Creating a File System on an SD Card

## Checking the SD Card

Before proceeding, ensure the SD card is correctly detected by the system. Identify the device name using: `lsblk` or `sudo fdisk -l`

Assuming the SD card is `/dev/`mmcblkX, replace `X` with the actual letter assigned to your device.

## Partitioning the SD Card

If the SD card has no file system or needs repartitioning, use `fdisk`:

```bash
sudo fdisk /dev/mmcblk0
```

Steps in `fdisk`:
- Press `m` for help .
- Press `n` to create a new partition.
- Choose `p` for primary partition.
- Select partition number `1` and specify the size.
- Repeat for the second partition.
- Change the partition type using `t` (optional, see partition types below).
- Press `w` to write changes and exit.

**Partition Types**

| Type Code | Type Name       | Description                          |
| --------- | --------------- | ------------------------------------ |
| 83        | Linux           | Standard Linux partition             |
| 82        | Linux Swap      | Used for swap space                  |
| b         | W95 FAT32       | FAT32 partition, common for SD cards |
| c         | W95 FAT32 (LBA) | FAT32 with Logical Block Addressing  |
| 7         | HPFS/NTFS/exFAT | Used for Windows compatibility       |

## Formatting the Partitions

After partitioning, create a file system on each partition. Choose the file system based on the use case.

Formatting Commands:

- **FAT32 (for compatibility with Windows & embedded systems):**
  ```bash
  sudo mkfs.vfat -F 32 /dev/mmcblk0p1
  ```
- **ext4 (for Linux systems):**
  ```bash
  sudo mkfs.ext4 /dev/mmcblk0p2
  ```

**Comparing File Systems**

| File System | Max File Size | Max Partition Size | Journaling | Compatibility                                             |
| ----------- | ------------- | ------------------ | ---------- | --------------------------------------------------------- |
| FAT32       | 4GB           | 2TB                | No         | Windows, Linux, Mac                                       |
| exFAT       | 16EB          | 128PB              | No         | Windows, Linux (with drivers), Mac                        |
| ext4        | 16TB          | 1EB                | Yes        | Linux                                                     |
| NTFS        | 16EB          | 8PB                | Yes        | Windows, Linux (read/write with drivers), Mac (read-only) |


--- 
## Mounting the File Systems

To use the partitions, mount them:

```bash
sudo mount /dev/mmcblk0p1 /mnt/sdcard1
sudo mount /dev/mmcblk0p2 /mnt/sdcard2
```

To auto-mount on boot, add entries in `/etc/fstab`:

```bash
/dev/sdX1 /mnt/sdcard1 vfat defaults,nofail 0 0
/dev/sdX2 /mnt/sdcard2 ext4 defaults,nofail 0 0
```
--- 
## Verifying the File System

Check partition details using: `lsblk -f` or `sudo blkid`

