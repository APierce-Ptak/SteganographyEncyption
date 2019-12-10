# Steg - By Jordan Hettleman and Austin Pierce-Ptak
## What is steganography?
Steganography is the practice of concealing information like an image, a video, or text file inside another image, video, or text file. The advantage of steganography is that it is quite difficult to see at first that data is hidden inside of a file like an audio file or image file. You would either have to be quite suspicious or know from the sender that the image/audio/video file came with embedded data. 

## What this program does
This program focuses on hiding and reading text in an bitmap image file. This is done by changing the last significant bit for each pixel to a bit from the text file you want to hide in the image. Depending on the image, you are able to store lots of data secretly. The default image of a bee provided in this repo with a size of about 25MB can store about 3 million characters/bytes. With this program you are also able to read the image and check for hidden information. This is done by grabbing the last bit of every pixel, adding it to a character, and then writing to a file byte by byte. 

## How to compile the program
There is a provided Makefile. Just type 'make'

## How to run the program
There are three options when running the program:
- Firstly you can call the program with no arguments to hide the bee movie script inside a bitmap image of a bee.
- Secondly, you can call the program with your own arguments as follows: <br>
<i><b>./steg -c IMAGE_FILENAME TEXT_FILENAME OUTPUT_BMP_FILENAME </i></b><br>
<b>IMAGE_FILENAME</b> is the desired bmp image you would like to embed with data <br>
<b>TEXT_FILENAME</b> being the text file you will embed into the image <br>
<b>OUTPUT_BMP_FILENAME</b> being the name of the embedded image <br>
- Lastly, you can call the program to read the embedded data from an image with the following: <br>
<i><b>./steg -r IMAGE_FILENAME OUTPUT_TEXT_FILENAME </i></b><br>
<b>IMAGE_FILENAME</b> is the desired bmp image you would like to read from<br>
<b>OUTPUT_TEXT_FILENAME</b> being the name of the text file output<br>

## Included Files
### head.h
This header file contains all of the methods used in the program to make them globally accessible. The header also declares the image_data and text_data arrays which store the image and textfile data inside of them

### CLI.c
This file contains the command line interface for the program. It takes care of all user input and calls all the necessary functions 

### TextFileHandler.c
The sourced file is error checked to make sure it does exist upon opening. An array called (text_data) is created and malloc-ed according to the byte size of the file, this array will be holding the binary values. Next is reading the source file and saving it as binary in an array. The conversion of char to ascii happens via the (byte_to_binary) function which comes back as an ASCII value. This returned value (num) is then solved by checking the value if its the ASCII representation of 1 or 0 and filling that into the text_data array. 

### ImageHandler.c
#### openImageAsArray()
This function opens a bitmap image in binary mode. You then have to read the bmp file header which is 54 bytes in length. I read the first 18 bytes, then the next 8 bytes contain the width and height of the image, and then finally read in the last 28 bytes of the header. I then read the pixel data of the bmp and store it in a global array.

#### hackifyImage()
This function uses both the image data and the text file data. The image data is read and checks the value of the last bit of each pixel. Then the last bit (least significant bit) is compared with a single bit from the text file and replaced if needed. One the function completes, the entire text file (if not too large) will be embedded into the image file. 

#### rebuildImage()
This function creates the destination bmp image, and then writes the file header and modified pixel data to the new bmp file. 

#### readHiddenData()
This function reads the last bit of each pixel in the bmp file, stores them temporarily into a char until all eight bits are modified, and then writes that character to the output text file.

## Honor Code Statement
Austin and Jordan did not cheat and abided by the honor code :)