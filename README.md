# Advanced Encryption Standard 256-bit

A command-line tool for encrypting and decrypting files using AES-256 encryption.

## Usage

```
aes256 [OPTIONS]
```

or

```
aes256 [COMMAND] <KEY> <INPUT_FILE> <OUTPUT_FILE>
```

#### Options

|      Option | Short |             Description              |
|------------:|:-----:|:------------------------------------:|
|    `--help` | `-h`  |  Display this help message and exit  |
| `--version` | `-v`  | Display version information and exit |

#### Commands

|   Command | Short |                 Description                  |
|----------:|:-----:|:--------------------------------------------:|
| `encrypt` |  `e`  | Encrypt the input file with the provided key |
| `decrypt` |  `d`  | Decrypt the input file with the provided key |

#### Arguments

|        Argument |              Description               |
|----------------:|:--------------------------------------:|
|         `<KEY>` |  Encryption/decryption key (256-bit)   |
|  `<INPUT_FILE>` | Path to the file to encrypt or decrypt |
| `<OUTPUT_FILE>` |  Path where the output will be saved   |

## License

See [LICENSE-APACHE](./LICENSE-APACHE) and [LICENSE-MIT](LICENSE-MIT) for details.
