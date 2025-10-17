# Advanced Encryption Standard 256-bit

A command-line tool for encrypting and decrypting files using AES-256 encryption.

## Downloads

<table>
  <tr>
    <th>Windows</th>
    <th>Linux</th>
    <th>MacOS</th>
  </tr>
  <tr>
    <td>
      <a href="https://github.com/NickSpyker/AES256/releases/download/windows-latest/aes256.exe">
        aes256.exe binary for Windows (x64)
      </a>
    </td>
    <td>
      <a href="https://github.com/NickSpyker/AES256/releases/download/linux-latest/aes256">
        aes256 binary for Linux (x64)
      </a>
    </td>
    <td>
      <a href="https://github.com/NickSpyker/AES256/releases/download/macos-latest/aes256">
        aes256 binary for macOS (Intel & Apple Silicon)
      </a>
    </td>
  </tr>
  <tr>
    <td>
      <p>Installation:</p>
      <p>Download aes256.exe and add it to your PATH</p>
    </td>
    <td colspan="2">
      <p>Installation:</p>
      <p>Download aes256</p>
      <pre><code>chmod +x aes256
sudo mv aes256 /usr/local/bin/</code></pre>
    </td>
  </tr>
</table>

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
