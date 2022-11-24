An Asset file is a file in which all files from a specific directory are packed.
The .asset file has 3 parts:
  - Header
  - Asset List
  - Asset Data

### Header
The header contains general information about the file:
  - A 4 byte long magic number (string: 'aset')
  - The total file size (in bytes) (uint64)
  - The total size of the Asset List (in bytes) (uint64)
  - The total size of the Data List (in bytes) (uint64)
  - Amount of entries in the Asset List (uint32)

### Asset List
The Asset List contains entries for each asset:
Each entry consists of:
  - Entry size (in bytes) (uint16)
  - Data size (in bytes) (uint64)
  - Data pointer (uint64)
  - Identifier (relative file path) (zero terminated string)

### Data List
The Data List is one continuous array of bytes containing the data of all asset files
