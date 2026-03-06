
/*===============================================================================
Project Title : LSB Image Stegnography
Name          : Rishikesh Jadhavrao
Batch Id      : 25028_033
Date          : 17/12/2025
Language      : C Programming
===============================================================================

📘 Project Overview

This project implements image steganography using the Least Significant Bit (LSB) technique in the C programming language.
It allows users to hide (encode) a secret text or code file inside a (.bmp) image and 
later extract (decode) the hidden information safely without visible distortion of the image.

The system supports multiple file types (e.g .txt, .c, .h, .sh) and performs full data integrity checks during encoding and decoding.

🧩 Features

* 🔒 Secure Data Hiding using LSB bit manipulation.
* 🖼 Supports 24-bit BMP images.
* 📄 Handles multiple file types (.txt, .c, .h, .sh).
* ✅ Robust validation for file names, extensions, and image capacity.
* 🔍 Magic string verification to ensure correct decoding.
* 🧠 Modular C code with clear function separation for readability.
* 💡 Detailed console messages for easy debugging and understanding.


🧮 Encoding Steps

1. Validate Input Files
   * Source image must be .bmp
   * Secret file can be .txt, .c, .h, .sh
2. Open Required Files (src.bmp, secret.txt, stego.bmp)
3. Check Capacity — Ensure image can hold the secret data.
4. Copy BMP Header (first 54 bytes unchanged)
5. Encode the following sequentially:
   * Magic string (e.g., "#*")
   * Secret file extension size
   * Secret file extension (e.g., .txt)
   * Secret file size
   * Secret file data (actual contents)
6. Copy Remaining Image Data after encoding.
7. Output: Stego image ('destination.bmp') containing the hidden data.

🔍 Decoding Steps

1. Validate and Open Stego Image
2. Skip BMP Header (54 bytes)
3. Read and Verify Magic String
4. Decode Extension Size
5. Decode Extension Name
6. Decode Secret File Size
7. Extract Secret File Data and write to decoded file.


⚠ Error Handling

* Invalid file names or extensions are reported.
* Missing arguments or corrupted BMP files trigger descriptive error messages.
* Magic string mismatch ensures you don’t decode unencoded files.

🧩 Future Enhancements

* Support for other image formats (PNG, JPEG).
* Password-based encryption before embedding.
* GUI-based front-end for user interaction.
* Batch encoding of multiple files.

🧭 Command Format

./a.out -e <source_image.bmp> <secret_file.txt> [output_image.bmp]
./a.out -d <stego_image.bmp> [output_file_name]


*/



#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "decode.h"
#include "types.h"

int main(int argc, char *argv[])
{
    // -------- Basic argument validation -------- //
    if (argc < 2)
    {
        printf("ERROR: Missing operation type\n");
        printf("Usage:\n");
        printf("  Encoding: ./a.out -e <src.bmp> <secret.txt> [stego.bmp]\n");
        printf("  Decoding: ./a.out -d <stego.bmp> [output_file]\n");
        return 1;
    }

    // -------- Determine encode or decode -------- //
    OperationType op_type = check_operation_type(argv);

    if (op_type == e_encode)
    {
        EncodeInfo encInfo;

        if (argc >= 4 && argc <= 5)
        {
            if (read_and_validate_encode_args(argv, &encInfo) == e_success)
            {
                if (do_encoding(&encInfo) == e_success)
                {
                    printf("INFO: Encoding Done Successfully\n");
                }
                else
                {
                    printf("ERROR: Encoding Failed\n");
                }
            }
            else
            {
                printf("ERROR: Encoding Validation Failed\n");
            }
        }
        else
        {
            printf("ERROR: Invalid number of arguments for encoding!\n");
            printf("Usage: ./a.out -e <src.bmp> <secret.txt> [stego.bmp]\n");
        }
    }

    else if (op_type == e_decode)
    {
        DecodeInfo decInfo;

        if (argc >= 3 && argc <= 4)
        {
            if (read_and_validate_decode_args(argc, argv, &decInfo) == e_success)
            {
                if (do_decoding(&decInfo) == e_success)
                {
                    printf("INFO: Decoding Done Successfully\n");
                }
                else
                {
                    printf("ERROR: Decoding Failed\n");
                }
            }
            else
            {
                printf("ERROR: Decoding Validation Failed\n");
            }
        }
        else
        {
            printf("ERROR: Invalid number of arguments for decoding!\n");
            printf("Usage: ./a.out -d <stego.bmp> [output_file]\n");
        }
    }

    else
    {
        printf("ERROR: Unsupported Operation %s\n", argv[1]);
        printf("Use -e for encoding or -d for decoding.\n");
    }

    return 0;
}
