#include "tinyimage.hpp"

/* The error code */
TinyImgError _error;

/* Internal functions */

int _equal(const char *str1, const char *str2)
{
    return strcmp(str1, str2) == 0;
}

int _tinyimg_check_format(const char *extension)
{
    return extension != NULL && (_equal(extension, ".bmp"));
}

int _tinyimg_open_file(FILE **fp, const char *filename, const char *p_flags)
{
    *fp = fopen(filename, p_flags);
    return *fp != NULL;
}

unsigned char *_tinyimg_load_bmp(FILE *fp, int *width, int *height)
{
    unsigned char *image;          // image data
    unsigned char *palette = NULL; // palette data (if uses palette)
    int size;                      // pixel count
    short bit_count;               // bit count per pixel (24 if no palette)
    int color_count = 0;           // colors used (if uses palette)
    unsigned char temp;
    int count = 0;

    /* Checks if the pointers are not NULL */
    if (width == NULL || height == NULL)
    {
        _error = TINYIMG_INVALID_ARGUMENT;
        return NULL;
    }

    fseek(fp, 18, SEEK_SET);
    fread(width, sizeof(int), 1, fp);  // read width
    fread(height, sizeof(int), 1, fp); // read height

    unsigned long padding = (*width) % 4; // calculate padding to avoid those bytes

    fseek(fp, 28, SEEK_SET);
    fread(&bit_count, sizeof(short), 1, fp); // read bit count

    fseek(fp, 54, SEEK_SET);
    /* If uses palette (bit count is not 24) */
    if (bit_count != 24)
    {
        color_count = (int) pow(2.0, bit_count);
        palette = (unsigned char *) malloc(sizeof(unsigned char) * 4 * color_count);
        fread(palette, sizeof(unsigned char), 4 * color_count, fp);
    }

    /* Allocates memory for the image */
    size = (*width) * (*height);
    image = (unsigned char *) malloc(sizeof(unsigned char) * size * 3);

    /* Reads the image data */
    if (bit_count == 24)
    {
        unsigned char paddingBytes[4]; // extra safety at 1 byte cost
        paddingBytes[0] = 0x00;
        paddingBytes[1] = 0x00;
        paddingBytes[2] = 0x00;
        paddingBytes[3] = 0x00;

        for (int i = 0; i < *height; i++)
        {
            // std::cout << "fread -W " <<*width<<"  H "<<*height<<"   i: " << i << "  desp: " << (i*(*width)*3)
            // <<std::endl;
            fread(image + (i * (*width) * 3), (*width) * 3, 1, fp);
            fread(paddingBytes, padding, 1, fp); // read padding to ignore it
        }
    } else
    {
        while (count < size)
        {
            fread(&temp, sizeof(unsigned char), 1, fp);
            image[count * 3] = palette[temp * 4];
            image[count * 3 + 1] = palette[temp * 4 + 1];
            image[count * 3 + 2] = palette[temp * 4 + 2];
            count++;
        }
    }

    fclose(fp);
    return image;
}

unsigned char *_tinyimg_load(FILE *fp, const char *extension, int *width, int *height)
{
    unsigned char *result = nullptr; // ES: cambio para mejor estilo de programación

    if (_equal(extension, ".bmp"))
    {
        result = _tinyimg_load_bmp(fp, width, height);
    }
    return result;
}

/* External functions */

unsigned char *tinyimg_load(const char *filename, int *width, int *height, TinyImgColorType type)
{
    const char *extension;
    FILE *fp;

    /* Check if the image format is supported */
    extension = strrchr(filename, '.');
    if (!_tinyimg_check_format(extension))
    {
        _error = TINYIMG_FORMAT_UNSUPPORTED;
        return NULL;
    }

    /* Check if the file exists */
    if (!_tinyimg_open_file(&fp, filename, FILEFLAGS_READBINARY))
    {
        _error = TINYIMG_FILE_NOT_FOUND;
        return NULL;
    }

    return _tinyimg_load(fp, extension, width, height);
}

int tinyimg_save(const char *filename, int width, int height, TinyImgColorType type, const unsigned char *image)
{
    int result = 0;
    FILE *fp; // file to create

    /* Check if the file exists */
    if (_tinyimg_open_file(&fp, filename, FILEFLAGS_READBINARY))
    {
        _error = TINYIMG_FILE_EXISTS;
        fclose(fp);
        result = -1; // file exist, abort
    } else
    {
        if (!_tinyimg_open_file(&fp, filename, FILEFLAGS_WRITEBINARY))
        {
            _error = TINYIMG_FILE_CAN_BE_CREATED;
            result = -2; // can't create, abort
        } else
        {
            unsigned long padding = width % 4;
            // unsigned long paddingb =  (4 - (width*3 -((width*3/4) * 4)))%4;
            // std::cout << "padding: " << padding << "          padding B: " << paddingb <<std::endl;

            unsigned char header[14];
            header[0] = 0x42;                                                //'B';
            header[1] = 0x4d;                                                //'M';
            unsigned long fileSize_02 = (width * 3 + padding) * height + 54; // calcular data + header
            // std::cout << "file size: " << fileSize_02 <<std::endl;

            header[2] = fileSize_02 & 0xFF;
            header[3] = (fileSize_02 >> 8) & 0xFF;
            header[4] = (fileSize_02 >> 16) & 0xFF;
            header[5] = (fileSize_02 >> 24) & 0xFF;
            // std::cout << "file size: " << (int)header[2] << " . " << (int)header[3] << " . "<< (int)header[4] << " .
            // " << (int)header[5] << std::endl;

            header[6] = 0;
            header[7] = 0;
            header[8] = 0;
            header[9] = 0;
            header[10] = 0x36; // offset to data, 54
            header[11] = 0;
            header[12] = 0;
            header[13] = 0;

            fwrite(header, 14, 1, fp);

            unsigned char bitmapV5Header[40];
            bitmapV5Header[0] = 0x28;
            bitmapV5Header[1] = 0;
            bitmapV5Header[2] = 0;
            bitmapV5Header[3] = 0;
            unsigned long imageWidth_7 = (unsigned long) width;
            bitmapV5Header[4] = imageWidth_7 & 0xFF;
            bitmapV5Header[5] = (imageWidth_7 >> 8) & 0xFF;
            bitmapV5Header[6] = (imageWidth_7 >> 16) & 0xFF;
            bitmapV5Header[7] = (imageWidth_7 >> 24) & 0xFF;
            unsigned long imageHeight_8 = (unsigned long) height;
            bitmapV5Header[8] = imageHeight_8 & 0xFF;
            bitmapV5Header[9] = (imageHeight_8 >> 8) & 0xFF;
            bitmapV5Header[10] = (imageHeight_8 >> 16) & 0xFF;
            bitmapV5Header[11] = (imageHeight_8 >> 24) & 0xFF;
            bitmapV5Header[12] = 0x01; // plane
            bitmapV5Header[13] = 0x00; // plane
            bitmapV5Header[14] = 0x18; // 24 bits
            bitmapV5Header[15] = 0x00; // 24 bits

            bitmapV5Header[16] = 0x00; // no compression
            bitmapV5Header[17] = 0x00; // no compression
            bitmapV5Header[18] = 0x00; // no compression
            bitmapV5Header[19] = 0x00; // no compression

            unsigned long rawDataSize = (unsigned long) (height * (width * 3 + padding));
            // std::cout << "rawDataSize: " << rawDataSize <<std::endl;
            bitmapV5Header[20] = rawDataSize & 0xFF;         // data size
            bitmapV5Header[21] = (rawDataSize >> 8) & 0xFF;  // data size
            bitmapV5Header[22] = (rawDataSize >> 16) & 0xFF; // data size
            bitmapV5Header[23] = (rawDataSize >> 24) & 0xFF; // data size

            bitmapV5Header[24] = 0x13; // hor resol
            bitmapV5Header[25] = 0x0B; // hor resol
            bitmapV5Header[26] = 0x00; // hor resol
            bitmapV5Header[27] = 0x00; // hor resol

            bitmapV5Header[28] = 0x13; // vert resol
            bitmapV5Header[29] = 0x0B; // vert resol
            bitmapV5Header[30] = 0x00; // vert resol
            bitmapV5Header[31] = 0x00; // vert resol

            bitmapV5Header[32] = 0x00; // colors in palette
            bitmapV5Header[33] = 0x00; // colors in palette
            bitmapV5Header[34] = 0x00; // colors in palette
            bitmapV5Header[35] = 0x00; // compression

            bitmapV5Header[36] = 0x00; // important colors
            bitmapV5Header[37] = 0x00; // important colors
            bitmapV5Header[38] = 0x00; // important colors
            bitmapV5Header[39] = 0x00; // important colors

            fwrite(bitmapV5Header, 40, 1, fp);

            unsigned char paddingBytes[4]; // extra safety at 1 byte cost
            paddingBytes[0] = 0x00;
            paddingBytes[1] = 0x00;
            paddingBytes[2] = 0x00;
            paddingBytes[3] = 0x00;

            for (int i = 0; i < height; i++)
            {
                // std::cout << "fwrite -W " <<width<<"  H "<<height<<"   i: " << i << "  desp: " << (i*width*3)
                // <<std::endl;
                fwrite(image + (i * width * 3), width * 3, 1,
                       fp); //            fwrite(image, 3, 4, fp);    writing 3 bytes, 4 times
                fwrite(paddingBytes, padding, 1, fp);
            }
            fclose(fp);
            result = 0;
        }
    }

    return result;
}

void tinyimg_free(unsigned char *image)
{
    free(image);
}

TinyImgError tinyimg_get_error()
{
    return _error;
}

const char *tinyimg_get_error_str()
{
    const char *result = nullptr; // ES: cambio para mejor estilo de programación
    switch (_error)
    {
        case TINYIMG_OK:
            result = NULL;
        case TINYIMG_FORMAT_UNSUPPORTED:
            result = "format unsupported";
        case TINYIMG_FILE_NOT_FOUND:
            result = "file not found";
        case TINYIMG_INVALID_ARGUMENT:
            result = "invalid argument";
        case TINYIMG_FILE_EXISTS:
            result = "can't create, file exists";
        case TINYIMG_FILE_CAN_BE_CREATED:
            result = "can't create";
    }
    return result;
}
