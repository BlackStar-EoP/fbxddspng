#include <stdint.h>
#include <string>
#include <stdio.h>
#include <regex>

uint8_t* readFile(const std::string& file, int& size)
{
    FILE* fp = fopen(file.c_str(), "rb");
    if (fp)
    {
        fseek(fp, 0L, SEEK_END);
        size = ftell(fp);
        fseek(fp, 0L, SEEK_SET);
        uint8_t* data = new uint8_t[size];
        fread(data, 1, size, fp);
        fclose(fp);
        return data;
    }

    size = 0;
    return nullptr;
}

std::string replaceDDSwithPNG(const char* data, const int size)
{
    std::string filedata(data, size);
    std::regex r("\\.dds");
    return std::regex_replace(filedata, r, ".png");
}

void writeFile(const char* filename, const std::string& filedata, const int size)
{
    FILE* fp = fopen(filename, "wb");
    if (fp)
    {
        fwrite(filedata.c_str(), 1, size, fp);
        fclose(fp);
    }
}

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        printf("Opening file %s\n", argv[1]);
        int size;
        uint8_t* data = readFile(argv[1], size);
        std::string newFiledata = replaceDDSwithPNG((char*)data, size);
        writeFile(argv[1], newFiledata, size);
        delete[] data;
    }
}
