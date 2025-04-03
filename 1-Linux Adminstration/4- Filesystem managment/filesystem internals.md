# Understanding the File System in linux 

## File system Internals
A file system organizes and manages stored data. Each file consists of:

1. **Block of Data**: The actual content stored on disk.
2. **Metadata**: Information about the file, managed through:
   - **Inode**: Stores metadata such as file size, owner, permissions, timestamps, and data block pointers.
   - **Dentry (Directory Entry)**: Maps filenames to their respective inodes.

## Hard Links vs. Soft (Symbolic) Links

- **Hard Links**:
  - Reference the same inode as the original file.
  - Do not create a new file, just another name pointing to the same data.
  - File remains accessible as long as at least one hard link exists.

- **Soft (Symbolic) Links**:
  - Reference the filename instead of the inode.
  - If the original file is deleted, the symlink becomes broken.

## Checking File Inodes and Links

- `ls -li <file>` : Display inode number and links.
- `stat <file>` : Show detailed file information including links.
- `find . -samefile <file>` : Find all hard links to a specific file.

## File Operations and Link Behavior

- **Copying a File (`cp`)**:
  - Creates a new inode and new data blocks.
  - Hard links to the original file remain unaffected.

- **Moving a File (`mv`)**:
  - If moved within the same filesystem, only the dentry changes.
  - If moved across filesystems, it behaves like a copy and delete.

- **Deleting a File (`rm`)**:
  - Reduces the link count in the inode.
  - If all hard links are removed, the file is deleted from disk.
  - Soft links to the deleted file become broken.

### Commands:

- `ls -i <file>` : Show inode number of files.
- `stat <file>` : Display file metadata.
- `df -h` : Show filesystem disk usage in human-readable format.
- `df -i` : Show inode usage.
- `ln <file> <link>` : Create a **hard link**.
- `ln -s <file> <link>` : Create a **soft link**.

---
## Directory Stack Management

Useful for quick navigation between directories.

### Commands:

- `pushd <dir>` : Push directory onto the stack.
- `popd` : Pop last pushed directory.
- `dirs` : Show directory stack.



