# AES256

Advanced Encryption Standard 256 in C.

## Description

```
AES256 - Advanced Encryption Standard 256-bit
A command-line tool for encrypting and decrypting files using AES-256 encryption.

USAGE:
    aes256 [OPTIONS]
    aes256 <COMMAND> <KEY> <INPUT_FILE> <OUTPUT_FILE>

OPTIONS:
    -h, --help       Display this help message and exit
    -v, --version    Display version information and exit

COMMANDS:
    encrypt, e       Encrypt the input file with the provided key
    decrypt, d       Decrypt the input file with the provided key

ARGUMENTS:
    <KEY>            Encryption/decryption key (256-bit)
    <INPUT_FILE>     Path to the file to encrypt or decrypt
    <OUTPUT_FILE>    Path where the output will be saved
```

## License

See [LICENSE-APACHE](./LICENSE-APACHE) and [LICENSE-MIT](LICENSE-MIT) for details.
